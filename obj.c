#include "game.h"
void set_notice(Object* obj, char* notice)
{
    strncpy(obj->last_notice,notice,64);
}

void obj_move(World * w, Object * o, int ox, int oy)
{
    int tox = o->x + ox;
    int toy = o->y + oy;
    int ol = o->shape.layer;
    if (check_block(w,tox,toy,ol) == 0)
    {
        if (o->x < tox)
            o->direction = "right";
        if (o->x > tox)
            o->direction = "left";
        if (o->y > toy)
            o->direction = "up";
        if (o->y < toy)
            o->direction = "down";
        o->x = tox;
        o->y = toy;
    }
}

