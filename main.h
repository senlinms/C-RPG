#ifndef PROTO_MAIN_H
#define PROTO_MAIN_H
#include "game.h"
extern void game_over();
extern World * game_init();
extern int game_loop(World* w);
extern int game();

#endif // PROTO_MAIN_H
