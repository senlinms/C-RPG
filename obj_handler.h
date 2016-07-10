#ifndef PROTO_OBJ_HANDLER_H
#define PROTO_OBJ_HANDLER_H
#include "game.h"
extern int fn_fire_timer(Object* o);
extern int fn_explode_bullet(Object *me, Object*other);
extern int fn_root_me(Object* me, Object* other);
extern int fn_death_drop(Object* me);
extern int fn_kill(Object* me, Object * other);
extern int fn_damage(Object* me, Object *other);
extern int fn_bomb_timer(Object * o);
extern int fn_do_rand(Object * o);
extern int fn_heal(Object* me, Object* other);
extern int fn_heal_timer(Object * o);
extern int fn_thru_bullet_timer(Object* me);
#endif // PROTO_OBJ_HANDLER_H
