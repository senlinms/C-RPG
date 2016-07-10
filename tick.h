#ifndef PROTO_TICK_H
#define PROTO_TICK_H
#include "game.h"

extern void tick(World * w);
extern void tick_self(World*w);
extern void tick_overlap(World*w);

#endif // PROTO_TICK_H
