#include "game.h"
int fn_heal(Object* me, Object* other)
{
    if(other->hp >= other->max_hp)
        return 0;
    int heal = me->power;
    other->hp += heal;
    return other->hp;
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
