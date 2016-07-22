
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

CHAR_INFO screen_buffer[BUFFER_CY][BUFFER_CX];
int goal_fps = 25;
int frame_count = 0;

state_slot table_state[100] = {
	{"poison",msgbox,msgbox_yes_no,fn_obj_damage,msgbox2},
	{"",0,0,0,0}
};

str_str_fn table_debug[100] = {
	{"fly", "debug_fly", debug_fly},
	{"put_wall", "debug_put_wall", debug_put_wall},
	{"put_space", "debug_put_space", debug_put_space},
	{"load_world", "debug_load_world", debug_load_world},
	{"save_world", "debug_save_world", debug_save_world},
	{"fps+", "debug_fps+", debug_fps_plus},
	{"fps-", "debug_fps-", debug_fps_minus},
	{"loot", "debug_loot", debug_loot},
	{"interactive_new_cell", "debug_interactive_new_cell",
	 debug_interactive_new_cell},
	{"quit", "debug_quit", debug_quit}
};

str_str_fn key_fn_table[100] = {
	{"up", "move_up", key_move_up},
	{"down", "move_down", key_move_down},
	{"left", "move_left", key_move_left},
	{"right", "move_right", key_move_right},
	{" ", "attack", key_attack},
	{",", "loot", key_loot},
	{"s", "skill_mode", key_skill_mode},
	{"i", "item_mode", key_item_mode},
	{"d", "debug_mode", key_debug_mode},
	{"0", "shortcut_0", key_shortcut_0},
	{"1", "shortcut_1", key_shortcut_1},
	{"2", "shortcut_2", key_shortcut_2},
	{"3", "shortcut_3", key_shortcut_3},
	{"4", "shortcut_4", key_shortcut_4},
	{"5", "shortcut_5", key_shortcut_5},
	{"6", "shortcut_6", key_shortcut_6},
	{"7", "shortcut_7", key_shortcut_7},
	{"8", "shortcut_8", key_shortcut_8},
	{"9", "shortcut_9", key_shortcut_9},
	{"q", "quit", key_quit},
	{"`", "debug", key_debug},
	{"", "", 0},
};

str_str_fn table_tick_obj_fn[100] = {
	{"move_random", "fn_move_random", fn_do_rand},
	{"fire_timer", "fn_fire_timer", fn_fire_timer},
	{"bomb_timer", "fn_bomb_timer", fn_bomb_timer},
	{"thru_bullet_timer", "fn_thru_bullet_timer",
	 fn_thru_bullet_timer},
	{"heal_timer", "fn_heal_timer", fn_heal_timer}
};

str_str_fn table_overlap_obj_fn[100] = {
	{"heal", "fn_heal", fn_heal},
	{"damage", "fn_damage", fn_damage},
	{"kill", "fn_kill", fn_kill},
	{"loot_me", "fn_loot_me", fn_loot_me},
	{"explode_bullet", "fn_explode_bullet", fn_explode_bullet}
};

fn_scene scene;
