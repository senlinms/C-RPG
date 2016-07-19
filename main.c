
#include "game.h"


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
    
    new_mk_obj("enemy",w,10,10,0);

    Object * hero_ptr;
	hero_ptr = new_mk_obj("hero",w,0,0,0);
	w->hero = hero_ptr;
	return w;
}

void fps()
{
    static clock_t fps_t = 0;
    static clock_t loop_t2;
    static clock_t loop_t1 =0; 
    static int loop_frame = 0;
    static int max_fps=0;


	loop_frame++;
    if (fps_t + 1000  <= clock())
    {
        gotoxy(0,24);
        set_color(0,15);

        printf("fps:[%3d] goal_fps:[%3d]",loop_frame,goal_fps);
        if (loop_frame < goal_fps)
        {
            set_color(0,4+8);
            printf("          ");
        }
        if (loop_frame >= goal_fps)
        {
            set_color(0,4+8);
            printf(" [max_fps]");
        }

        fps_t = clock();
        loop_frame = 0;
    }
	
    while(1)
	{
		if (clock() - loop_t1 < (1000/goal_fps) )
		{
			Sleep(5);
		}
		else
		{		
			loop_t1 = clock();
			break;
		}
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

