#include "game.h"
void key_quit(Object * obj)
{
	exit(0);
}

char *key_name(int key)
{
	if (key == 0 || key == 0xe0)
		key = getch();
	if (key == 72)
		return "up";
	if (key == 80)
		return "down";
	if (key == 75)
		return "left";
	if (key == 77)
		return "right";

	//assume static variable placed in heap area
	static char letter[2];
	letter[0] = (char)key;
	letter[1] = 0;
	return letter;
}

void table_key_process(str_str_fn * table, Object * obj)
{

	if (!kbhit())
		return;

	char *name = key_name(getch());
	for (int i = 0; i < 100; i++) {
		if (strlen(table[i].name) == 0)
			continue;
		if (!strcmp(table[i].name, name)) {
			if (table[i].fn == 0)
				return;
			table[i].fn(obj);
			return;
		}
	}
}

void key_process(World * w)
{
	Object *obj = w->hero;
	table_key_process(key_fn_table, obj);
}

void key_debug(Object * obj)
{
	set_state(obj, table_state, "poison");
}

void key_move_up(Object * obj)
{
	obj_move(obj->world, obj, 0, -1);
	strcpy(obj->last_action, "move_up");
}

void key_move_down(Object * obj)
{

	obj_move(obj->world, obj, 0, 1);
	strcpy(obj->last_action, "move_down");
}

void key_move_left(Object * obj)
{

	obj_move(obj->world, obj, -1, 0);
	strcpy(obj->last_action, "move_left");
}

void key_move_right(Object * obj)
{
	obj_move(obj->world, obj, 1, 0);
	strcpy(obj->last_action, "move_right");
}

void key_attack(Object * obj)
{
	new_mk_obj("bomb", obj->world, obj->x, obj->y, obj);
	strcpy(obj->last_action, "bomb");
}

void key_loot(Object * obj)
{

	act_debug(obj, "loot");
}

void key_skill_mode(Object * obj)
{
	strcpy(obj->operation_mode, "skill");
}

void key_item_mode(Object * obj)
{
	strcpy(obj->operation_mode, "item");
}

void key_debug_mode(Object * obj)
{
	strcpy(obj->operation_mode, "debug");
}

void key_shortcut_0(Object * obj)
{
	act(obj, obj->operation_mode, 0);
}

void key_shortcut_1(Object * obj)
{
	act(obj, obj->operation_mode, 1);
}

void key_shortcut_2(Object * obj)
{
	act(obj, obj->operation_mode, 2);
}

void key_shortcut_3(Object * obj)
{
	act(obj, obj->operation_mode, 3);
}

void key_shortcut_4(Object * obj)
{
	act(obj, obj->operation_mode, 4);
}

void key_shortcut_5(Object * obj)
{
	act(obj, obj->operation_mode, 5);
}

void key_shortcut_6(Object * obj)
{
	act(obj, obj->operation_mode, 6);
}

void key_shortcut_7(Object * obj)
{
	act(obj, obj->operation_mode, 7);
}

void key_shortcut_8(Object * obj)
{
	act(obj, obj->operation_mode, 8);
}

void key_shortcut_9(Object * obj)
{
	act(obj, obj->operation_mode, 9);
}
