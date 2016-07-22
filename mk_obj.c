#include "game.h"
fn_obj table_obj_fn_by_long_name(str_str_fn * table, char *long_name)
{
	if (long_name == 0)
		return 0;
	if (table == 0)
		return 0;
	for (int i = 0; i < 100; i++) {
		if (strlen(table[i].long_name) == 0)
			continue;
		if (!strcmp(table[i].long_name, long_name))
			return table[i].fn;
	}
	return 0;
}

Object mk_dummy(World * w, int x, int y, Object * parent)
{
	Object o;
	memset(&o, 0, sizeof(Object));
	strcpy(o.shape.str, "d");
	if (parent != 0)
		o.direction = parent->direction;
	else
		o.direction = "down";
	o.parent = parent;
	strcpy(o.type, "dummy");
	o.shape.bg_color = 0;
	o.shape.fg_color = 15;
	o.shape.layer = 1;
	o.exist = 1;
	o.x = x;
	o.y = y;
	o.tick_fn = 0;
	o.overlap_fn = 0;
	o.death_fn = fn_death_drop;
	o.hp = 100;
	o.mp = 100;
	o.power = 1;
	o.shape.block = 1;
	strcpy(o.operation_mode, "debug");
	o.world = w;

	return o;
}

int char_pos_ith(char *buf, char c, int i)
{
	int x;
	int found = 0;
	for (x = 0; x < 4096; x++) {
		if (buf[x] == 0)
			return -1;
		if (buf[x] == c) {
			if (found == i)
				return x;
			found++;
		}

	}
}

char *get_line(char *buf, int i)
{
	if (i == 0)
		return buf;
//0th char is first char hence i-1
	return buf + char_pos_ith(buf, '\n', i - 1) + 1;
}

int str_len_char(char *str, char c)
{
	int i;
	for (i = 0; i < 4096; i++) {

		if (str[i] == 0)
			return -1;

		if (str[i] == c)
			return i;
	}
	return -1;
}

int same_until_char(char *s1, char *s2, char c)
{
	int i;
	for (i = 0; i < 4096; i++) {
		if (s1[i] == c && s2[i] == c)
			return 1;
		if (s1[i] == 0 && s2[i] == 0)
			return 1;
		if (s1[i] != s2[i])
			return 0;
		if (s1[i] == s2[i])
			continue;

	}
}

//obj_x.txt need newline at the end!
int set_obj_with_line(Object * o, char *line)
{

	char *first = line;
	char *second = line + char_pos_ith(line, ' ', 0) + 1;
	int len = str_len_char(second, '\r');
	char buf[32];
	memset(buf, 0, sizeof(char) * 32);
	if (same_until_char(first, "type ", ' ')) {

		strncpy(o->type, second, len);
		o->type[len] = 0;
		return 1;
	}
	if (same_until_char(first, "shape.str ", ' ')) {

		strncpy(o->shape.str, second, len);
		o->shape.str[len] = 0;
		return 1;
	}
	if (same_until_char(first, "timer ", ' ')) {

		strncpy(buf, second, len);
		o->timer = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "shape.layer ", ' ')) {

		strncpy(buf, second, len);
		o->shape.layer = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "shape.fg_color ", ' ')) {

		strncpy(buf, second, len);
		o->shape.fg_color = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "shape.bg_color ", ' ')) {

		strncpy(buf, second, len);
		o->shape.bg_color = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "shape.block ", ' ')) {

		strncpy(buf, second, len);
		o->shape.block = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "hp ", ' ')) {

		strncpy(buf, second, len);
		o->hp = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "max_hp ", ' ')) {

		strncpy(buf, second, len);
		o->max_hp = atoi(buf);
		return 1;
	}

	if (same_until_char(first, "mp ", ' ')) {

		strncpy(buf, second, len);
		o->mp = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "max_mp ", ' ')) {

		strncpy(buf, second, len);
		o->max_mp = atoi(buf);
		return 1;
	}
	if (same_until_char(first, "power ", ' ')) {

		strncpy(buf, second, len);
		o->power = atoi(buf);
		return 1;
	}

	if (same_until_char(first, "item ", ' ')) {

		strncpy(buf, second, len);
		add_slot(o, "item", buf);
		return 1;
	}
	if (same_until_char(first, "skill ", ' ')) {

		strncpy(buf, second, len);
		add_slot(o, "skill", buf);
		return 1;
	}
	if (same_until_char(first, "debug ", ' ')) {
		strncpy(buf, second, len);
		add_slot(o, "debug", buf);
		return 1;
	}
	if (same_until_char(first, "offset_x ", ' ')) {

		strncpy(buf, second, len);
		obj_move(o->world, o, atoi(buf), 0);
		return 1;
	}
	if (same_until_char(first, "offset_y ", ' ')) {

		strncpy(buf, second, len);
		obj_move(o->world, o, 0, atoi(buf));
		return 1;
	}
	if (same_until_char(first, "fn_tick ", ' ')) {

		strncpy(buf, second, len);
		fn_obj fn = table_obj_fn_by_long_name(table_tick_obj_fn, buf);
		o->tick_fn = fn;
		if (fn == 0)
			return 0;

		return 1;
	}

	if (same_until_char(first, "fn_overlap ", ' ')) {
		strncpy(buf, second, len);
		fn_obj fn = table_obj_fn_by_long_name(table_overlap_obj_fn, buf);
		o->overlap_fn = fn;
		if (fn == 0)
			return 0;
		return 1;
	}
	//ignore unknown things
	//if you want to inspect unknown string use return 0;
	return 1;
}

int mod_obj_with_buf(char *buf, Object * o)
{
	int i;
	for (i = 0; i < 4096; i++) {
		char *line = get_line(buf, i);
		if (strlen(line) <= 1)
			break;
		if (line == 0)
			break;
		int success = set_obj_with_line(o, line);
		if (success == 0) {
			char error_str[256];
			MessageBox(0, buf, "error", MB_OK);

			sprintf(error_str,
				"line index:%d\nstring:%s\nstrlen:%d", i, line,
				strlen(line));
			MessageBox(0, error_str, "error", MB_OK);

			break;
		}
	}
	return 1;
}

Object *new_mk_obj(char *name, World * w, int x, int y, Object * parent)
{

	char file_name[256];
	sprintf(file_name, "./data/obj_%s.txt", name);
	FILE *fp = fopen(file_name, "rb");
	if (fp == 0) {
		char buf[512];
		sprintf(buf, "unable to open file:%s", file_name);
		MessageBox(0, buf, "error", MB_OK);
		exit(1);
		return 0;
	}

	char buf[4096];
	memset(buf, 0, sizeof(char) * 4096);
	int rpos = fread(buf, 1, 4096, fp);
	fseek(fp, 0, SEEK_END);
	int epos = ftell(fp);
	if (rpos != epos)
		return 0;
	fclose(fp);
	Object o = mk_dummy(w, x, y, parent);
	mod_obj_with_buf(buf, &o);
	int k = get_empty_obj_index(w);

	if (k == -1)
		return -1;
	w->objs[k] = o;

	//never return o. o is in stack. therefore it will be deleted when function finished.
	return &(w->objs[k]);
}
