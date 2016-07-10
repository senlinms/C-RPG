#ifndef PROTO_ACT_H
#define PROTO_ACT_H
#include "game.h"
extern void act(Object * obj, char* mode, int num);
extern int  act_debug(Object * obj, char* name);
extern int  act_skill(Object * obj, char* name);
extern int  act_item(Object * obj, char* name);

#endif // PROTO_ACT_H
