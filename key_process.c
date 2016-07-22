#include "game.h"

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
			table[i].fn(obj, 0);
			return;
		}
	}
}

void key_process(World * w)
{
	Object *obj = w->hero;
	table_key_process(key_fn_table, obj);
}

//object function

int key_debug(Object * obj, Object * obj2)
{
	set_state(obj, table_state, "poison");
	return 1;
}

int key_move_up(Object * obj, Object * obj2)
{
	obj_move(obj->world, obj, 0, -1);
	strcpy(obj->last_action, "move_up");
	return 1;
}

int key_move_down(Object * obj, Object * obj2)
{

	obj_move(obj->world, obj, 0, 1);
	strcpy(obj->last_action, "move_down");
	return 1;
}

int key_move_left(Object * obj, Object * obj2)
{

	obj_move(obj->world, obj, -1, 0);
	strcpy(obj->last_action, "move_left");
	return 1;
}

int key_move_right(Object * obj, Object * obj2)
{
	obj_move(obj->world, obj, 1, 0);
	strcpy(obj->last_action, "move_right");
	return 1;
}

int key_attack(Object * obj, Object * obj2)
{
	new_mk_obj("bomb", obj->world, obj->x, obj->y, obj);
	strcpy(obj->last_action, "bomb");
	return 1;
}

int key_loot(Object * obj, Object * obj2)
{

	act_debug(obj, "loot");
	return 1;
}

int key_skill_mode(Object * obj, Object * obj2)
{
	strcpy(obj->operation_mode, "skill");
	return 1;
}

int key_item_mode(Object * obj, Object * obj2)
{
	strcpy(obj->operation_mode, "item");
	return 1;
}

int key_debug_mode(Object * obj, Object * obj2)
{
	strcpy(obj->operation_mode, "debug");
	return 1;
}

int key_shortcut_0(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 0);
	return 1;
}

int key_shortcut_1(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 1);
	return 1;
}

int key_shortcut_2(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 2);
	return 1;
}

int key_shortcut_3(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 3);
	return 1;
}

int key_shortcut_4(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 4);
	return 1;
}

int key_shortcut_5(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 5);
	return 1;
}

int key_shortcut_6(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 6);
	return 1;
}

int key_shortcut_7(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 7);
	return 1;
}

int key_shortcut_8(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 8);
	return 1;
}

int key_shortcut_9(Object * obj, Object * obj2)
{
	act(obj, obj->operation_mode, 9);
	return 1;
}

int key_quit(Object * obj, Object * obj2)
{
	exit(0);
	return 1;
}
