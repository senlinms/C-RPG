#ifndef PROTO_MK_OBJ_H
#define PROTO_MK_OBJ_H
extern Object mk_dummy(World *w, int x, int y,Object* parent);
extern Object mk_bomb(World *w, int x, int y,Object* parent);
extern Object mk_fire(World *w, int x, int y,Object* parent);
extern Object mk_thru_bullet(World *w, int x, int y, Object* parent);
extern Object mk_explode_bullet(World *w, int x, int y, Object* parent);
extern Object mk_enemy(World * w, int x,int y,Object* parent);
extern Object mk_hero(World *w, int x, int y,Object* parent);
extern Object mk_heal(World*w, int x, int y,Object* parent);
extern Object mk_coin(World*w, int x, int y,Object* parent);
extern Object mk_book(World*w, int x, int y,Object* parent);

#endif // PROTO_MK_OBJ_H
