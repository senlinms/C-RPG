#include "game.h"

Object *obj_at(World * w, int x, int y, Object * exclude)
{
	int i;
	for (i = 0; i < 500; i++) {
		if (w->objs[i].exist == 0)
			continue;
		if (w->objs[i].x != x)
			continue;
		if (w->objs[i].y != y)
			continue;
		if (&(w->objs[i]) == exclude)
			continue;
		return &(w->objs[i]);
	}
	return 0;
}

//can be improved by making scratch buffer.
//loop for all object and put obj to scratch.
//access scratch by index
//in this way, only one full loop is required.

Cell *get_cell_layer(World * w, int x, int y, int layer)
{

	int i;

	if (x < 0 || y < 0 || x >= 100 || y >= 100)
		return 0;

	for (i = 0; i < 500; i++) {
		Object *o = &(w->objs[i]);
		if (o->exist == 0)
			continue;
		if (o->x == x && o->y == y && o->shape.layer == layer)
			return &(o->shape);
	}
	Cell *mc = &(w->map[y][x]);
	if (layer == mc->layer)
		return &(w->map[y][x]);
	return 0;;
}

int add_slot(Object * obj, char *mode, char *new_slot)
{
	char (*slots)[SHORT_STRLEN];
	if (!strcmp(mode, "debug"))
		slots = obj->debug_slots;
	else if (!strcmp(mode, "skill"))
		slots = obj->skill_slots;
	else if (!strcmp(mode, "item"))
		slots = obj->item_slots;
	else
		return 0;
	int empty_i = find_empty_slot(obj, mode);
	if (empty_i == -1)
		return 0;
	strcpy(slots[empty_i], new_slot);
	return 1;
}

int save_world(World * w, char *file_name)
{
	FILE *fp = fopen(file_name, "wb");
	fwrite(w, sizeof(World), 1, fp);
	fclose(fp);
	return 1;
}

int load_world(World * w, char *file_name)
{
	FILE *fp = fopen(file_name, "rb");
	fread(w, sizeof(World), 1, fp);
	fclose(fp);
	int i;
	for (i = 0; i < 500; i++) {
		if (w->objs[i].exist == 1)
			w->objs[i].world = w;
		//need debugging
		if (w->objs[i].shape.str[0] == '@')
			w->hero = &(w->objs[i]);
	}
	return 1;
}

int put_cell(World * w, int x, int y, Cell c)
{
	if (y < 0 || x < 0 || y >= 100 || x >= 100)
		return 0;
	w->map[y][x] = c;
	return 1;
}

Cell interactive_new_cell()
{
	//not implemented yet
	Cell c;
	memset(&c, 0, sizeof(c));
	return c;
}

Cell new_cell(char ch, int bg, int fg, int layer, int block)
{
	Cell c;
	c.bg_color = bg;
	c.fg_color = fg;
	c.layer = layer;
	c.str[0] = ch;
	c.str[1] = 0;
	c.block = block;
	return c;
}

int delete_cell(World * w, int x, int y)
{
	w->map[y][x].str[0] = '.';
	w->map[y][x].str[1] = 0;
	w->map[y][x].layer = 0;
	w->map[y][x].block = 0;
	w->map[y][x].bg_color = 0;
	w->map[y][x].fg_color = 6;
	return 1;
}

int get_empty_obj_index(World * w)
{
	int i;
	for (i = 0; i < 500; i++) {
		if (w->objs[i].exist == 0)
			return i;
	}
	return -1;
}

//layer -1 can go through anywhere
int check_block(World * w, int x, int y, int layer)
{
	int i;
	if (x >= 100 || y >= 100 || x < 0 || y < 0)
		return 1;
	if (w->map[y][x].layer == layer && w->map[y][x].block != 0)
		return 1;

	if (layer == -1)
		return 0;

	for (i = 0; i < 500; i++) {
		Object *o = &(w->objs[i]);
		if (o->exist == 0)
			continue;
		if (o->x == x &&
		    o->y == y && o->shape.layer == layer && o->shape.block != 0)
		{
			return 1;
		}
	}
	return 0;
}
