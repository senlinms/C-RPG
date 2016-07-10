#include "game.h"
int fn_heal_timer(Object * o)
{
    o->timer -=1;
    if(o->timer <= 0)
        o->exist = 0;
}
int fn_heal(Object* me, Object* other)
{
    if(other->hp >= other->max_hp)
        return 0;
    int heal = me->power;
    other->hp += heal;
    return other->hp;
}
int fn_do_rand(Object * o)
{
    int r = rand() % 50;
    if(r == 0)
    {
        obj_move(o->world,o,-1,0);
    }
    if(r == 1)
    {
        obj_move(o->world,o,1,0);
    }
    if(r == 2)
    {
        obj_move(o->world,o,0,-1);
    }
    if(r == 3)
    {
        obj_move(o->world,o,0,1);
    }
    if(r == 4)
    {
        if(rand()%10 == 0)
            new_obj(o->world,"bomb",o->x,o->y,o);
    }
}
int fn_fire_timer(Object* o)
{
    o->timer -=1;
    if(o->timer <= 0)
        o->exist = 0;
}
int fn_bomb_timer(Object * o)
{
    o->timer -=1;

    snprintf(o->shape.str,3,"%d",o->timer);
    if(o->timer <=0)
    {
        int cy,cx;
        for(cy = -1; cy<=1; cy++)
        {
            for(cx = -1; cx<=1; cx++)
            {
                new_obj(o->world,"fire",o->x + cx, o->y + cy,o);
            }
        }


        o->exist = 0;
    }

}
int fn_damage(Object* me, Object *other)
{
    int damage = me->power;
    other->hp -= damage;
    return other->hp;
}
int fn_kill(Object* me, Object * other)
{
    other->exist = 0;
}

int fn_death_drop(Object* me)
{
    int i;
    for(i=0; i<10; i++)
    {
        char * item = &(me->item_slots[i][0]);
        if(!strcmp(item,""))
            continue;
        new_obj(me->world,item,me->x,me->y,me);
    }
}

int fn_root_me(Object* me, Object* other)
{
    if(me->exist == 1)
    {
        if(strcmp(other->last_action,"root"))
            return 0;
        if(num_of_empty_slot(other,other->item_slots)<1)
        {
            char buf[64];
            sprintf(buf,"you have no space for [%s]",me->type);
            set_notice(other,buf);
            return 0;
        }
        add_slot(other,"item",me->type);
        me->exist = 0;

        strcpy(other->last_action ,"none");

        char buf[64];
        sprintf(buf,"you rooted [%s]",me->type);
        set_notice(other,buf);
        return 1;
    }
    return 0;
}
int fn_thru_bullet_timer(Object* me)
{
    me->timer--;
    if(me->timer<=0)
        me->exist=0;
    if(!strcmp(me->direction,"left"))
        obj_move(me->world,me,-1,0);
    if(!strcmp(me->direction,"right"))
        obj_move(me->world,me,1,0);
    if(!strcmp(me->direction,"up"))
        obj_move(me->world,me,0,-1);
    if(!strcmp(me->direction,"down"))
        obj_move(me->world,me,0,1);
}
int fn_explode_bullet(Object *me, Object*other)
{

    int cy,cx;
    for(cy = -1; cy<=1; cy++)
    {
        for(cx = -1; cx<=1; cx++)
        {
            new_obj(me->world,"fire",me->x + cx, me->y + cy,me);
        }
    }

    me->exist = 0;
}
