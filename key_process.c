#include "game.h"
void key_move_up(Object *);
void key_move_down(Object *);
void key_move_left(Object *);
void key_move_right(Object *);
void key_attack(Object *);
void key_root(Object *);
void key_skill_mode(Object *);
void key_item_mode(Object *);
void key_debug_mode(Object *);
void key_shortcut_0(Object *);
void key_shortcut_1(Object *);
void key_shortcut_2(Object *);
void key_shortcut_3(Object *);
void key_shortcut_4(Object *);
void key_shortcut_5(Object *);
void key_shortcut_6(Object *);
void key_shortcut_7(Object *);
void key_shortcut_8(Object *);
void key_shortcut_9(Object *);

fn_name_pair key_fn_table[100] ={
    {"up","move_up",		key_move_up},
    {"down","move_down",	key_move_down},
    {"left","move_left",	key_move_left},
    {"right","move_right",  key_move_right},
    {" ","attack",	  key_attack},
    {",","root",	  key_root},
    {"s","skill_mode",key_skill_mode},
    {"i","item_mode", key_item_mode},
    {"d","debug_mode",key_debug_mode},
    {"0","shortcut_0",key_shortcut_0},
    {"1","shortcut_1",key_shortcut_1},
    {"2","shortcut_2",key_shortcut_2},
    {"3","shortcut_3",key_shortcut_3},
    {"4","shortcut_4",key_shortcut_4},
    {"5","shortcut_5",key_shortcut_5},
    {"6","shortcut_6",key_shortcut_6},
    {"7","shortcut_7",key_shortcut_7},
    {"8","shortcut_8",key_shortcut_8},
    {"9","shortcut_9",key_shortcut_9},
    {"","",0},
};

char* key_name(int key)
{
    if (key == 0 || key == 0xe0)
        key = getch();
    if (key == 72)
        return "up";
    if (key == 80)
        return "down";
    if (key == 75)
        return "left";
    if (key == 77)
        return "right";

    //assume static variable placed in heap area
    static char letter[2];
    letter[0] = (char)key;
    letter[1] = 0;
    return letter;
}
void table_key_process(fn_name_pair * table, Object * obj)
{
    if (!kbhit())
        return;
    char* name = key_name(getch());
    for (int i = 0;i<100;i++)
    {
        if (!strcmp(table[i].name,name))
        {
            if (table[i].fn == 0)
                return;
            table[i].fn(obj);
            return;
        }
    }
}

void key_process(World* w)
{
    Object * obj = w->hero;
    table_key_process(key_fn_table,obj);
}




void key_move_up(Object * obj)
{
    obj_move(obj->world, obj, 0,-1);
    strcpy(obj->last_action ,"move_up");
}
void key_move_down(Object * obj)
{

    obj_move(obj->world, obj, 0,1);
    strcpy(obj->last_action  ,"move_down");
}
void key_move_left(Object * obj)
{

    obj_move(obj->world,obj,-1,0);
    strcpy(obj->last_action  ,"move_left");
}
void key_move_right(Object * obj)
{
    obj_move(obj->world,obj, 1,0);
    strcpy(obj->last_action  ,"move_right");
}
void key_attack(Object * obj)
{
    new_obj(obj->world, "bomb",obj->x,obj->y,obj);
    strcpy(obj->last_action,"bomb");
}
void key_root(Object *obj)
{

    act_debug(obj,"root");
}
void key_skill_mode(Object *obj)
{
    strcpy(obj->operation_mode, "skill");
}
void key_item_mode(Object* obj)
{
    strcpy(obj->operation_mode , "item");
}
void key_debug_mode(Object* obj)
{
    strcpy(obj->operation_mode , "debug");
}
void key_shortcut_0(Object* obj)
{
    act(obj,obj->operation_mode, 0);
}
void key_shortcut_1(Object* obj)
{
    act(obj,obj->operation_mode, 1);
}
void key_shortcut_2(Object* obj)
{
    act(obj,obj->operation_mode, 2);
}
void key_shortcut_3(Object* obj)
{
    act(obj,obj->operation_mode, 3);
}
void key_shortcut_4(Object* obj)
{
    act(obj,obj->operation_mode, 4);
}
void key_shortcut_5(Object* obj)
{
    act(obj,obj->operation_mode,5);
}
void key_shortcut_6(Object* obj)
{
    act(obj,obj->operation_mode,6);
}
void key_shortcut_7(Object* obj)
{
    act(obj,obj->operation_mode,7);
}
void key_shortcut_8(Object* obj)
{
    act(obj,obj->operation_mode,8);
}
void key_shortcut_9(Object* obj)
{
    act(obj,obj->operation_mode,9);
}


