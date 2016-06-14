/*              */
/* Yay Evil 2.0 */
/*              */

#include "map.h"
#include "math.h"
#include "log.h"
#include "renderer.h"
#include "font.h"
#include "fontloader.h"
#include "mouse.h"

#define screen_width_min 320
#define screen_height_min 240
#define YE_Caption "Yay Evil 2.0 - POWERED BY SDL2!"

int screen_width = 1024;
int screen_height = 768;
int multisample = 0;
GLuint Lightbuffer = 0;
bool fullscreen = 0;

SDL_GLContext glContext;
SDL_Event event;
SDL_Window *screen;

bool YE_Cmd = 0;

bool YE_Shadows = 1;
int YE_ShadowQuality = 10;
float YE_ShadowIntensity = 0.6;
float YE_ShadowScaleA = 1.0;

YE_Map stmap;
std::map<std::string, GLuint> Textures;

int time1, time2;
float deltatime = 0;

const char* lmap = "map01.ye";
Font *font;
Font *menufont;

float cam_x, cam_y;
Actor *player = new Actor;
Mouse *pmouse = new Mouse;

void YE_Init (void)
{
    Log(0, "[General] Yay Evil is starting...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log(1, "[SDL] SDL initialization failed: %s", SDL_GetError());
        exit(1);
    }

    Log(0, "[SDL] SDL_VIDEO initialized.", screen_width, screen_height);

    atexit(SDL_Quit);

    YE_InitFontLoader();

    if (multisample != 0)
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample);
    }

    if(fullscreen)
        screen = SDL_CreateWindow(YE_Caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    else
        screen = SDL_CreateWindow(YE_Caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                screen_width, screen_height, SDL_WINDOW_OPENGL);

    if (screen == NULL)
    {
        Log(1, "[SDL] Opening %dx%d window failed: %s", screen_width, screen_height, SDL_GetError());
        exit(1);
    }

    Log(0, "[SDL] Opening %dx%d window successful.", screen_width, screen_height);

    glContext = SDL_GL_CreateContext(screen);

    if( glContext == NULL )
    {
            Log(1, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            exit(1);
    }

    Log(0, "[SDL] OpenGL context created.");

    glewInit();
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glOrtho(0, screen_width / 64.0, 0, screen_height / 64.0, -1, 1);

    //create empty buffer
    glGenFramebuffers(1, &Lightbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, Lightbuffer);

    //create texture that we are going to render to
    GLuint RenderTexture;
    glGenTextures(1, &RenderTexture);
    glBindTexture(GL_TEXTURE_2D, RenderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, RenderTexture, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Log(1, "[OpenGL] Couldn't create framebuffer!");
        exit(1);
    }

    Log(0, "[OpenGL] Framebuffer created.");

    time1=SDL_GetTicks();
    YE_LoadTextures();

    font = YE_LoadFont("fonts/YayEvil.ttf", 30).release();
    menufont = YE_LoadFont("fonts/Consola.ttf", 20).release();
}

int YE_Events (void)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return 1;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return 1;
        }
        pmouse->HandleEvents();
    }

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    bool up = (keys[SDL_GetScancodeFromKey(SDLK_w)] || keys[SDL_SCANCODE_UP]);
    bool down = (keys[SDL_GetScancodeFromKey(SDLK_s)] || keys[SDL_SCANCODE_DOWN]);
    bool left = (keys[SDL_GetScancodeFromKey(SDLK_a)] || keys[SDL_SCANCODE_LEFT]);
    bool right = (keys[SDL_GetScancodeFromKey(SDLK_d)] || keys[SDL_SCANCODE_RIGHT]);

    if(up && down)
    {
        up = false;
        down = false;
    }
    if(left && right)
    {
        left = false;
        right = false;
    }

    Vector2f movement(0, 0);

    if(up)
        movement.y += player->Speed * deltatime;
    if(down)
        movement.y -= player->Speed * deltatime;
    if(left)
        movement.x -= player->Speed * deltatime;
    if(right)
        movement.x += player->Speed * deltatime;

    player->Move(movement);

    return 0;
}

void YE_Update (void)
{
    YE_Renderer();

    //calculate deltatime
    time2 = SDL_GetTicks();
    deltatime = (time2-time1)*0.001;
    time1 = time2;

    SDL_GL_SwapWindow(screen);
}

bool YE_CheckArg(const char* arg, char *argv[], int& num)
{
    for (int i = 0; argv[i] != NULL; i++)
    {
        if (!strcmp(argv[i], arg))
        {
            num = i;
            return true;
        }
    }
    return false;
}

void YE_CleanUp (void)
{}

int main (int argc, char *argv[])
{
    UNUSED(argc);

    Log_Init();

    for (int i = 0; argv[i] != NULL; i++)
        Log(0, "[ARGS] argv[%d] contains %s", i, argv[i]);

    //Check args
    int p;
    if(YE_CheckArg("-map", argv, p))
    {
        Log(0, "[ARGS] Map '%s' will be loaded (%s %s)", argv[p+1], argv[p], argv[p+1]);
        lmap = argv[p+1];
    }

    if(YE_CheckArg("-w", argv, p))
        screen_width = std::max(screen_height_min, atoi(argv[p+1]));

    if(YE_CheckArg("-h", argv, p))
        screen_height = std::max(screen_height_min, atoi(argv[p+1]));

    if(YE_CheckArg("-multisample", argv, p))
        multisample = clip(atoi(argv[p+1]), 0, 1);

    if(YE_CheckArg("-fullscreen", argv, p))
        fullscreen = clip(atoi(argv[p+1]), 0, 1);

    if(YE_CheckArg("-shadows", argv, p))
        YE_Shadows = clip(atoi(argv[p+1]), 0, 1);

    if(YE_CheckArg("-shadowquality", argv, p))
        YE_ShadowQuality = clip(atoi(argv[p+1]), 1, 15);

    if(YE_CheckArg("-shadowintensity", argv, p))
        YE_ShadowIntensity = clip(atof(argv[p+1]), 0.1, 1.0);

    if(YE_CheckArg("-shadowscale", argv, p))
        YE_ShadowScaleA = clip(atof(argv[p+1]), 1.0, 3.0);

    if(YE_CheckArg("-cmd", argv, p))
        YE_Cmd = clip(atoi(argv[p+1]), 0, 1);

    YE_Init();

    char mapname[255] = "maps/";
    YE_LoadMap(strcat(mapname, lmap));
    CreatePlayer(stmap.PlayerX, stmap.PlayerY);

    while (true)
    {
        if(YE_Events())
            exit(1);
        YE_Update();
    }

    YE_CleanUp();
    return 0;
}
