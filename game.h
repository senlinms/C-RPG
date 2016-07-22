#ifndef GAME_H
#define GAME_H


#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FPS_LIMIT 500
#define BUFFER_CX 80
#define BUFFER_CY 24

struct Object;
struct Cell;
struct World;

typedef void (*fn_scene)(struct World*);

typedef int (*fn_obj)(struct Object * obj);
typedef int (*fn_obj_obj)(struct Object * obj_me, struct Object * obj_other);

typedef struct state_slot
{
	char *name;
	fn_obj fn_initial;
	fn_obj fn_tick_condition;
	fn_obj fn_tick;
	fn_obj fn_terminate;
	
} state_slot;
typedef struct str_str_fn
{
	char* name;
	char* long_name;
	fn_obj fn;
} str_str_fn;

typedef struct Cell
{
    char fg_color;
    char bg_color;
    char str[3];
    int layer;
    int block;
} Cell;

#define SHORT_STRLEN 32

typedef struct Object
{
    char type[SHORT_STRLEN];

    char last_action[SHORT_STRLEN];
    char last_notice[128];
    int hp, mp;
    int max_hp,max_mp;
    int power;
    struct Cell shape;
    fn_obj death_fn;
    fn_obj tick_fn;
    fn_obj_obj overlap_fn;

    int x,y;
    int timer;
    int exist;
    //layer 0 == floor
    //layer 1 == obj
    struct World * world;
    char operation_mode[SHORT_STRLEN];
    char skill_slots[10][SHORT_STRLEN];
    char item_slots[10][SHORT_STRLEN];
    char debug_slots[10][SHORT_STRLEN];
    char* direction;
    struct Object *parent;
	struct state_slot * state[100];
} Object;
typedef struct World
{
    struct Cell map[100][100];
    struct Object objs[500];
    struct Object * hero;
	int last_obj_index;
} World;

#endif

//build.bat 
//cproto -DPROTO_H -e -p -v -o proto.h *.c 
//gcc *.c -static -m32 -std=c11 -w -o game[release].exe
#ifndef PROTO_H
#define PROTO_H
#include "proto.h"
#endif