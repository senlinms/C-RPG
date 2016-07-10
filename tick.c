#include "game.h"
void tick_overlap(World*w)
{
    int i,j;
    for(i=0; i<500; i++)
    {
        for(j = 0; j<500; j++)
        {
            Object *obj = &(w->objs[i]);
            Object * obj2 = &(w->objs[j]);

            if(obj->exist == 0)
                continue;
            if(obj2->exist == 0)
                continue;
            if(obj != obj2&&
                    obj->x == obj2->x &&
                    obj->y == obj2->y &&
                    obj->overlap_fn!=0)
            {
                obj->overlap_fn(obj,obj2);
            }
        }
    }
}
void tick_self(World*w)
{
    int i;
    for(i=0; i<500; i++)
    {
        Object *obj = &(w->objs[i]);

        if(obj->exist == 0)
            continue;
        if(obj->tick_fn !=0 )
            obj->tick_fn(obj);
        if(obj->hp <= 0)
        {
            if(obj->exist == 1)
            {
                if(obj->death_fn != 0)
                    obj->death_fn(obj);

                obj->exist = 0;

            }
        }


    }
}
void tick(World * w)
{
    tick_self(w);
    tick_overlap(w);
}
