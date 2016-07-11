#include "game.h"

void debug_fly(Object * obj);
void debug_put_wall(Object * obj);
void debug_put_space(Object * obj);
void debug_load_world(Object * obj);
void debug_save_world(Object * obj);
void debug_fps_plus(Object * obj);
void debug_fps_minus(Object * obj);
void debug_root(Object * obj);
void debug_interactive_new_cell(Object * obj);

fn_name_pair table_debug[100] =
{
    {"fly","debug_fly",debug_fly},
    {"put_wall","debug_put_wall", debug_put_wall},
    {"put_space","debug_put_space",debug_put_space},
    {"load_world","debug_load_world",debug_load_world},
    {"save_world","debug_save_world",debug_save_world},
    {"fps+","debug_fps+",debug_fps_plus},
    {"fps-","debug_fps-",debug_fps_minus},
    {"root","debug_root",debug_root},
    {"interactive_new_cell","debug_interactive_new_cell",debug_interactive_new_cell}
};

//long_name임 그냥 name아님
fnptr fn_by_name(fn_name_pair *table, char* long_name)
{
    if (long_name == 0)
        return 0;
    if (table == 0)
        return 0;
    for (int i =0; i<100; i++)
    {
        if (table[i].long_name == 0)
            continue;
        if (!strcmp(table[i].long_name,long_name))
            return table[i].fn;
    }
    return 0;
}
int table_act(fn_name_pair *table, Object * obj, char* long_name)
{
    fnptr fn = fn_by_name(table,long_name);
    if (fn != 0)
        fn(obj);

    char buf[64];
    sprintf(buf,"command %s is issued",long_name);
    set_notice(obj,buf);
}

char* long_name(fn_name_pair* table, char* name)
{
    for (int i =0; i<100; i++)
    {
        if (!strcmp(table[i].name,name))
            return table[i].long_name;
    }
    return 0;
}

int act_debug(Object * obj, char* name)
{
    table_act(table_debug,obj,long_name(table_debug,name));
}

////////////////////////////////////////////
// debug functions
////////////////////////////////////////////
void debug_fly(Object * obj)
{
    if (obj->shape.layer == 2)
        obj->shape.layer = 1;
    else
        obj->shape.layer = 2;
}
void debug_put_wall(Object * obj)
{
    Cell c = new_cell('#',0,2,1,1);
    put_cell(obj->world,obj->x,obj->y,c);
}
void debug_put_space(Object * obj)
{
    Cell c = new_cell('.',0,6,0,0);
    put_cell(obj->world,obj->x,obj->y,c);
}
void debug_load_world(Object * obj)
{
    load_world(obj->world,"world.bin");
    gotoxy(0,0);
    set_color(0,14);
    printf("world loaded");
    Sleep(1000);
}
void debug_save_world(Object * obj)
{
    save_world(obj->world,"world.bin");
    gotoxy(0,0);
    set_color(0,15);
    printf("world saved");
    Sleep(1000);
}
void debug_fps_plus(Object * obj)
{
    goal_fps += 5;
    if (goal_fps >= FPS_LIMIT)
        goal_fps = FPS_LIMIT;
}
void debug_fps_minus(Object * obj)
{
    goal_fps -= 5;
    if (goal_fps <= 10)
        goal_fps = 10;
}
void debug_root(Object * obj)
{
    strcpy(obj->last_action, "root");
}
void debug_interactive_new_cell(Object * obj)
{
    Cell c = interactive_new_cell();
    put_cell(obj->world,obj->x,obj->y,c);
}
int act_skill(Object * obj, char* name)
{
    int hx = obj->x;
    int hy = obj->y;
    World *w = obj->world;
    if (name==0)
        return 0;
    new_obj(w, name,hx,hy,obj);
    char buf[64];
    sprintf(buf,"skill %s is issued",name);
    set_notice(obj,buf);
}

int act_item(Object * obj, char* name)
{
    char buf[64];
    sprintf(buf,"item %s is used",name);
    set_notice(obj,buf);
}
void act(Object * obj, char* mode, int num)
{
    char (*slots)[SHORT_STRLEN];
    if (!strcmp(mode,"skill"))
    {
        slots = obj->skill_slots;
        act_skill(obj,&(slots[num]));
    }
    if (!strcmp(mode,"item"))
    {
        slots = obj->item_slots;
        act_item(obj,&(slots[num]));
    }
    if (!strcmp(mode,"debug"))
    {
        slots = obj->debug_slots;
        act_debug(obj,&(slots[num]));
    }
    strcpy(obj->last_action,slots[num]);
}

