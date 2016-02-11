#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

class Light
{
public:
    Light();
    void Draw();

    float X, Y, Radius, RColor, GColor, BColor;
};

class Actor
{
public:
    Actor();
    void Draw();

    int Solid, HP;
    float X, Y, Alpha, Speed, Width, Height;
    Light* DLight = new Light;
    char Sprite[255];
};

void CreatePlayer(float spawnx, float spawny);
extern Actor *player;

#endif // ACTORS_H_INCLUDED
