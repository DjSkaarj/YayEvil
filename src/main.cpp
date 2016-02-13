/*              */
/* Yay Evil 2.0 */
/*              */

#include "common.h"

#define screen_width_min 640
#define screen_height_min 480
#define YE_Caption "Yay Evil 2.0 - NOW WITH FAKE AO!!!"

int screen_width = 1024;
int screen_height = 768;
int multisample = 0;
GLuint Lightbuffer = 0;
SDL_Surface *screen;

YE_Map stmap;
std::map<std::string, GLuint> Textures;

int time1, time2;
float deltatime = 0;

char* lmap = "map01.ye";

float cam_x, cam_y;
Actor *player = new Actor;

void YE_Init (void)
{
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    Log(0, "[General] Yay Evil is starting...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log(1, "[SDL] SDL initialization failed: %s", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    if (multisample != 0)
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample);
    }

    screen = SDL_SetVideoMode(screen_width, screen_height, 24, SDL_OPENGL);
    if (!screen)
    {
        Log(1, "[SDL] Opening %dx%d window failed: %s", screen_width, screen_height, SDL_GetError());
        exit(1);
    }

    Log(0, "[SDL] Opening %dx%d window successful.", screen_width, screen_height);

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

    time1=SDL_GetTicks();
    SDL_WM_SetCaption(YE_Caption, NULL);
    YE_LoadTextures();
}

int YE_Events (void)
{
    SDL_Event event;
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
    }
    Uint8 *keys = SDL_GetKeyState(NULL);
    if(keys['w'] || keys[SDLK_UP])
    {
        player->Y += player->Speed * deltatime;
    }
    if(keys['s'] || keys[SDLK_DOWN])
    {
        player->Y -= player->Speed * deltatime;
    }
    if(keys['a'] || keys[SDLK_LEFT])
    {
        player->X -= player->Speed * deltatime;
    }
    if(keys['d'] || keys[SDLK_RIGHT])
    {
        player->X += player->Speed * deltatime;
    }
    return 0;
}

void YE_Update (void)
{
    YE_Renderer();

    //calculate deltatime
    time2 = SDL_GetTicks();
    deltatime = (time2-time1)*0.001;
    time1 = time2;

    SDL_GL_SwapBuffers();
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

int main (int argc, char *argv[])
{
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
        screen_width = atoi(argv[p+1]);

    if(YE_CheckArg("-h", argv, p))
        screen_height = atoi(argv[p+1]);

    if(YE_CheckArg("-multisample", argv, p))
        multisample = atoi(argv[p+1]);

    screen_width = std::max(screen_width_min, screen_width);
    screen_height = std::max(screen_height_min, screen_height);

    YE_Init();

    char mapname[255] = "maps/";
    YE_LoadMap(strcat(mapname, lmap));
    CreatePlayer(0, 0);

    while (true)
    {
        if(YE_Events())
            exit(1);
        YE_Update();
    }
    return 0;
}
