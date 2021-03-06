#include "game.h"

fnptr fn_by_long_name(str_str_fn * table, char *long_name)
{
	//possibly 0
	if (long_name == 0)
		return 0;
	if (table == 0)
		return 0;
	if (strlen(long_name) == 0)
		return 0;
	for (int i = 0; i < 100; i++) {
		if (strlen(table[i].long_name) == 0)
			continue;
		if (!strcmp(table[i].long_name, long_name))
			return table[i].fn;
	}
	return 0;
}

void table_act(str_str_fn * table, Object * obj, char *long_name)
{
	fnptr fn = fn_by_long_name(table, long_name);
	if (fn == 0 || long_name == 0) {

		char buf[64];
		sprintf(buf, "command %s can not be issued", long_name);
		set_notice(obj, buf);

	} else {
		fn(obj, 0);

		char buf[64];
		sprintf(buf, "command %s is issued", long_name);
		set_notice(obj, buf);
	}
}

char *long_name(str_str_fn * table, char *name)
{
	for (int i = 0; i < 100; i++) {
		if (strlen(table[i].name) == 0)
			continue;

		if (!strcmp(table[i].name, name))
			return table[i].long_name;
	}
	return 0;
}

int act_debug(Object * obj, char *name)
{
	table_act(table_debug, obj, long_name(table_debug, name));
	return 1;
}

////////////////////////////////////////////
// debug functions
////////////////////////////////////////////
int debug_quit(Object * obj, Object * obj2)
{
	exit(0);
	return 1;
}

int debug_fly(Object * obj, Object * obj2)
{
	if (obj->shape.layer == 2)
		obj->shape.layer = 1;
	else
		obj->shape.layer = 2;
	return 1;
}

int debug_put_wall(Object * obj, Object * obj2)
{
	Cell c = new_cell('#', 0, 2, 1, 1);
	put_cell(obj->world, obj->x, obj->y, c);
	return 1;
}

int debug_put_space(Object * obj, Object * obj2)
{
	Cell c = new_cell('.', 0, 6, 0, 0);
	put_cell(obj->world, obj->x, obj->y, c);
	return 1;
}

int debug_load_world(Object * obj, Object * obj2)
{
	load_world(obj->world, "world.bin");
	gotoxy(0, 0);
	set_color(0, 14);
	printf("world loaded");
	Sleep(1000);
	return 1;
}

int debug_save_world(Object * obj, Object * obj2)
{
	save_world(obj->world, "world.bin");
	gotoxy(0, 0);
	set_color(0, 15);
	printf("world saved");
	Sleep(1000);
	return 1;
}

int debug_fps_plus(Object * obj, Object * obj2)
{
	goal_fps += 5;
	if (goal_fps >= FPS_LIMIT)
		goal_fps = FPS_LIMIT;
	return 1;
}

int debug_fps_minus(Object * obj, Object * obj2)
{
	goal_fps -= 5;
	if (goal_fps <= 10)
		goal_fps = 10;
	return 1;
}

int debug_loot(Object * obj, Object * obj2)
{
	strcpy(obj->last_action, "loot");
	return 1;
}

int debug_interactive_new_cell(Object * obj, Object * obj2)
{
	Cell c = interactive_new_cell();
	put_cell(obj->world, obj->x, obj->y, c);
	return 1;
}

int act_skill(Object * obj, char name[SHORT_STRLEN])
{
	int hx = obj->x;
	int hy = obj->y;
	World *w = obj->world;
	if (strlen(name) == 0)
		return 0;
	new_mk_obj(name, w, hx, hy, obj);
	char buf[64];
	sprintf(buf, "skill %s is issued", name);
	set_notice(obj, buf);
	return 1;
}

int act_item(Object * obj, char name[SHORT_STRLEN])
{
	char buf[64];
	sprintf(buf, "item %s is used", name);
	set_notice(obj, buf);
	return 1;
}

void act(Object * obj, char *mode, int num)
{
	char (*slots)[SHORT_STRLEN];
	if (!strcmp(mode, "skill")) {
		slots = obj->skill_slots;
		act_skill(obj, slots[num]);
	}
	if (!strcmp(mode, "item")) {
		slots = obj->item_slots;
		act_item(obj, slots[num]);
	}
	if (!strcmp(mode, "debug")) {
		slots = obj->debug_slots;
		act_debug(obj, slots[num]);
	}
	strcpy(obj->last_action, slots[num]);
}
