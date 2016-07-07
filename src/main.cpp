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
#include "states.h"

#define YE_Caption "Yay Evil 2.0 - COLLISION!"

int multisample = 0;
bool fullscreen = 0;

bool YE_LogMap = 0;
bool YE_LogTex = 1;

bool YE_Shadows = 1;
int YE_ShadowQuality = 10;
float YE_ShadowIntensity = 0.6;
float YE_ShadowScaleA = 1.0;

const char *lmap = "map01.ye";

GLuint Lightbuffer = 0;

SDL_GLContext glContext;
SDL_Event event;
SDL_Window *screen;

YE_Map stmap;
std::map<std::string, GLuint> Textures;

int time1, time2;
float deltatime = 0;

Font *font;
Font *menufont;

float tile_size = 64.0;

Actor *player = new Actor;
Mouse *pmouse = new Mouse;
Camera *cam = new Camera;

void YE_Init (void)
{
    Log(0, "[General] Yay Evil is starting...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log(1, "[SDL] SDL initialization failed: %s", SDL_GetError());
        exit(1);
    }

    Log(0, "[SDL] SDL_VIDEO initialized.", cam->res.x, cam->res.y);

    atexit(SDL_Quit);

    YE_InitFontLoader();

    if (multisample)
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample);
    }

    screen = SDL_CreateWindow(YE_Caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        cam->res.x, cam->res.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN * (fullscreen));

    if (screen == NULL)
    {
        Log(1, "[SDL] Opening %dx%d window failed: %s", cam->res.x, cam->res.y, SDL_GetError());
        exit(1);
    }

    Log(0, "[SDL] Opening %dx%d window successful.", cam->res.x, cam->res.y);

    glContext = SDL_GL_CreateContext(screen);

    if(glContext == NULL)
    {
            Log(1, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            exit(1);
    }

    Log(0, "[SDL] OpenGL context created.");

    glewInit();
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glOrtho(0, cam->res.x / tile_size, 0, cam->res.y / tile_size, -1, 1);

    //create empty buffer
    glGenFramebuffers(1, &Lightbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, Lightbuffer);

    //create texture that we are going to render to
    GLuint RenderTexture;
    glGenTextures(1, &RenderTexture);
    glBindTexture(GL_TEXTURE_2D, RenderTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cam->res.x, cam->res.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
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

    time1 = SDL_GetTicks();
    YE_LoadTextures();

    SDL_ShowCursor(SDL_DISABLE);
    pmouse->NormalCursor->Create("cursor.png", 30, 30);

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

    Vector2i input(0, 0);

    input = Vector2i(right - left, up - down);

    if (input.x != 0 || input.y != 0)
        player->Move(input.normalize() * player->Speed * deltatime);

    return 0;
}

void YE_Update (void)
{
    for(Actor actor : stmap.Actors)
        actor.CurrentState->Update(&actor);

    YE_Renderer();

    //calculate deltatime
    time2 = SDL_GetTicks();
    deltatime = (time2-time1) * 0.001;
    time1 = time2;

    SDL_GL_SwapWindow(screen);
}

bool YE_CheckArg(const char *arg, char *argv[], int& num)
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

//still useless
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
        cam->res.x = std::max(SCREEN_WIDTH_MIN, atoi(argv[p+1]));

    if(YE_CheckArg("-h", argv, p))
        cam->res.y = std::max(SCREEN_HEIGHT_MIN, atoi(argv[p+1]));

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

    if(YE_CheckArg("-logmap", argv, p))
        YE_LogMap = clip(atoi(argv[p+1]), 0, 1);

    if(YE_CheckArg("-logtex", argv, p))
        YE_LogTex = clip(atoi(argv[p+1]), 0, 1);

    if(cam->res == 0)
        cam->res = Vector2i(SCREEN_WIDTH_DEF, SCREEN_HEIGHT_DEF);

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
