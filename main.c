
#include "game.h"

typedef void (*fn_scene)(World*);

fn_scene scene;

void scene_map(World*);

void game_over_update(World* w)
{
    static int i = 0;
    static char * msg = "Game Over ";
    i = i % strlen(msg);
    printf("%c",msg[i]);
    i++;
    Sleep(100);
    if (kbhit())
    {
        w->hero->hp = 100;
        w->hero->exist = 1;
        scene = scene_map;
    }
}
void scene_game_over(World * w)
{
    while (scene == scene_game_over)
    {
        game_over_update(w);
    }
}
World * game_init()
{
    int cx,cy;
    int i;
    srand(time(0));
    World *w = (World*)malloc(sizeof(World));
    memset(w,0,sizeof(World));

    int fill = 80*20;

    new_obj(w,"hero",0,0,0);

    for (cy = 0; cy<100; cy++)
    {
        for (cx = 0; cx<100; cx++)
        {
            w->map[cy][cx].bg_color = 0;
            w->map[cy][cx].fg_color = 6;
            w->map[cy][cx].layer = 0;
            w->map[cy][cx].block = 0;
            strcpy(w->map[cy][cx].str,".");
        }
    }

    for (i = 0; i< 400; i++)
    {
        Cell c;
        c.fg_color = 2;
        c.bg_color = 0;
        c.layer  =1;
        c.block = 1;
        strcpy(c.str,"#");
        w->map[rand()%100][rand()%100] = c;
    }
    int k = 50;
    while (k--)
        new_obj(w,"enemy",rand()%100,rand()%100,0);

    int kkk = new_obj_from(w,"./data/obj_kkk.txt",0,0,0);
    //w->hero = &(w->objs[kkk]);
    return w;
}

void fps()
{
    static clock_t fps_t = 0;
    static clock_t loop_t2;
    static clock_t loop_t1;
    static int loop_frame = 0;
    static int max_fps=0;

    loop_t1 = clock();

    if (fps_t + 1000  <= clock())
    {
        gotoxy(0,24);
        set_color(0,15);

        printf("fps:[%3d] goal_fps:[%3d]",loop_frame,goal_fps);
        if (max_fps == 0)
        {
            set_color(0,4+8);
            printf("          ");
        }
        if (max_fps == 1)
        {
            set_color(0,4+8);
            printf(" [max_fps]");
        }

        fps_t = clock();
        loop_frame = 0;
    }

    loop_t2 = clock();
    loop_frame++;
    clock_t diff = loop_t2 - loop_t1;
    clock_t tick_ms = 1000/goal_fps;
    if (diff <= tick_ms)
    {
        Sleep(tick_ms - diff);
        max_fps = 0;
    }
    else
    {
        max_fps = 1;
    }

}
void game_update(World* w)
{


    tick(w);
    if (w->hero->exist == 0 || w->hero->hp<=0)
    {
        scene = scene_game_over;
        return;
    }
    draw(w);
    key_process(w);
    fps();

}



void scene_map(World* w)
{
    //pre scene routine
    while (scene == scene_map)
    {
        game_update(w);
    }
    //post scene routine
}
int main()
{
#ifdef DEBUG
    MessageBoxA(0,"this is debug session","title",MB_OK);
#endif
    scene = scene_map;
    World *w = game_init();
    while (scene != 0)
    {
        scene(w);
    }
    free(w);
}

