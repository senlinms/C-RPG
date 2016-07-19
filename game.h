#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FPS_LIMIT 500
#define BUFFER_CX 80
#define BUFFER_CY 24

extern CHAR_INFO screen_buffer[BUFFER_CY][BUFFER_CX];
extern int goal_fps;
extern int frame_count;
struct Object;
struct Cell;
struct World;

typedef void (*fn_scene)(struct World*);

typedef int (*fnptr)(struct Object * obj);
typedef int (*fnptr2)(struct Object * obj_me, struct Object * obj_other);

typedef struct 
{
	char* name;
	char* long_name;
	fnptr fn;
} fn_name_pair;

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
    fnptr death_fn;
    fnptr tick_fn;
    fnptr2 overlap_fn;

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

} Object;
typedef struct World
{
    struct Cell map[100][100];
    struct Object objs[500];
    struct Object * hero;
} World;


extern void scene_map(struct World*);
extern int  check_block(struct World * w, int x, int y,int layer);
extern int  get_empty_obj_index(struct World *w);
extern int  delete_cell(struct World * w, int x, int y);
extern Cell new_cell(char ch, int bg, int fg, int layer,int block);
extern Cell interactive_new_cell();
extern int  put_cell(struct World * w, int x, int y, Cell c);
extern int  load_world(struct World * w, char *file_name);
extern int  save_world(struct World * w, char * file_name);
extern int  add_slot(struct Object *obj, char* mode, char* new_slot);
extern Cell* get_cell_layer(struct World*w, int x, int y, int layer);
extern struct Object* obj_at(struct World* w, int x, int y, struct Object *exclude);
extern int  num_of_empty_slot(struct Object* obj, char (*slots)[SHORT_STRLEN];);
extern int  find_empty_slot(struct Object *obj,char *mode);
extern void game_over();
extern World * game_init();
extern int game_loop(struct World* w);
extern int game();
extern int fn_fire_timer(struct Object* o);
extern int fn_explode_bullet(struct Object *me, struct Object*other);
extern int fn_root_me(struct Object* me, struct Object* other);
extern int fn_death_drop(struct Object* me);
extern int fn_kill(struct Object* me, struct Object * other);
extern int fn_damage(struct Object* me, struct Object *other);
extern int fn_bomb_timer(struct Object * o);
extern int fn_do_rand(struct Object * o);
extern int fn_heal(struct Object* me, struct Object* other);
extern int fn_heal_timer(struct Object * o);
extern int fn_thru_bullet_timer(struct Object* me);

extern void key_process(struct World * w);

extern void tick(struct World * w);
extern void tick_self(struct World*w);
extern void tick_overlap(struct World*w);

extern void obj_move(struct World * w, struct Object * o, int ox, int oy);
extern void set_notice(struct Object* obj, char* notice);

extern struct Object mk_dummy(struct World *w, int x, int y,struct Object* parent);
extern struct Object mk_bomb(struct World *w, int x, int y,struct Object* parent);
extern struct Object mk_fire(struct World *w, int x, int y,struct Object* parent);
extern struct Object mk_thru_bullet(struct World *w, int x, int y, struct Object* parent);
extern struct Object mk_explode_bullet(struct World *w, int x, int y, struct Object* parent);
extern struct Object mk_enemy(struct World * w, int x,int y,struct Object* parent);
extern struct Object mk_hero(struct World *w, int x, int y,struct Object* parent);
extern struct Object mk_heal(struct World*w, int x, int y,struct Object* parent);
extern struct Object mk_coin(struct World*w, int x, int y,struct Object* parent);
extern struct Object mk_book(struct World*w, int x, int y,struct Object* parent);
extern void act(struct Object * obj, char* mode, int num);
extern int  act_debug(struct Object * obj, char* name);
extern int  act_skill(struct Object * obj, char* name);
extern int  act_item(struct Object * obj, char* name);
extern void print_mode_slots(int x, int y, struct Object* obj, int max_str_len, char (*slots)[SHORT_STRLEN];);
extern void print_mode(int x, int y, struct Object *obj);
extern void print_mode_name(int x,int y,struct Object * obj, char* mode);
extern int draw_examine(int display_x, int display_y, World* w, int x, int y,struct Object* exclude);
extern void print_gauge(int x,int y, int max,int current, unsigned char bright_color,unsigned char dark_color);
extern void draw(struct World * w);
extern void write_scr(CHAR_INFO * buffer, int cx, int cy);
extern void set_str(CHAR_INFO *buffer,char * str, int x , int y, unsigned char bg, unsigned char fg);
extern void set_cell(CHAR_INFO * buffer,char c, int x, int y, unsigned char bg, unsigned char fg);
extern void print_notice(struct Object* obj,int x, int y);

extern void gotoxy(int x, int y);

extern void set_color(char bg, char fg);


extern fn_name_pair table_debug[100];
extern fn_name_pair key_fn_table[100];
extern fn_name_pair table_tick_obj_fn[100];
extern fn_name_pair table_overlap_obj_fn[100];
extern fn_scene scene;


extern void debug_fly(struct Object * obj);
extern void debug_put_wall(struct Object * obj);
extern void debug_put_space(struct Object * obj);
extern void debug_load_world(struct Object * obj);
extern void debug_save_world(struct Object * obj);
extern void debug_fps_plus(struct Object * obj);
extern void debug_fps_minus(struct Object * obj);
extern void debug_root(struct Object * obj);
extern void debug_interactive_new_cell(struct Object * obj);
extern void debug_quit(struct Object * obj);

extern void key_move_up(struct Object *);
extern void key_move_down(struct Object *);
extern void key_move_left(struct Object *);
extern void key_move_right(struct Object *);
extern void key_attack(struct Object *);
extern void key_root(struct Object *);
extern void key_skill_mode(struct Object *);
extern void key_item_mode(struct Object *);
extern void key_debug_mode(struct Object *);
extern void key_shortcut_0(struct Object *);
extern void key_shortcut_1(struct Object *);
extern void key_shortcut_2(struct Object *);
extern void key_shortcut_3(struct Object *);
extern void key_shortcut_4(struct Object *);
extern void key_shortcut_5(struct Object *);
extern void key_shortcut_6(struct Object *);
extern void key_shortcut_7(struct Object *);
extern void key_shortcut_8(struct Object *);
extern void key_shortcut_9(struct Object *);
extern void key_quit(struct Object *);


extern struct Object* new_mk_obj(char* , World * , int , int , struct Object* );

#endif // GAME_H_INCLUDED

