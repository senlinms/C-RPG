#include "game.h"

void set_notice(Object * obj, char *notice)
{
	strncpy(obj->last_notice, notice, 64);
}

void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p = { x, y };
	SetConsoleCursorPosition(h, p);
}

void set_color(char bg, char fg)
{
	WORD c = (bg << 4) | fg;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, c);
}

void print_notice(Object * obj, int x, int y)
{
	set_str(screen_buffer, obj->last_notice, x, y, 0, 3 + 8);
}

void
set_cell(CHAR_INFO * buffer, char c, int x, int y, unsigned char bg,
	 unsigned char fg)
{
	if (y < 0 || x < 0 || y >= BUFFER_CY || x >= BUFFER_CX)
		return;
	CHAR_INFO ci;
	ci.Char.AsciiChar = c;
	ci.Attributes = (WORD) ((bg << 4) | fg);
	buffer[y * BUFFER_CX + x] = ci;
}

void
set_str(CHAR_INFO * buffer, char *str, int x, int y, unsigned char bg,
	unsigned char fg)
{
	int cx;
	for (cx = 0; cx < BUFFER_CX; cx++) {
		char c = str[cx];
		if (c == 0)
			break;
		set_cell(buffer, c, x + cx, y, bg, fg);
	}
}

void write_scr(CHAR_INFO * buffer, int cx, int cy)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sz = { cx, cy };
	COORD xy = { 0, 0 };
	SMALL_RECT sr = { 0, 0, cx, cy };
	WriteConsoleOutput(h, buffer, sz, xy, &sr);
}

void draw(World * w)
{
	memset(screen_buffer, 0, sizeof(CHAR_INFO) * BUFFER_CX * BUFFER_CY);
	draw_map(w);
	draw_system(w);
	draw_fps();
	write_scr(screen_buffer, BUFFER_CX, BUFFER_CY);
}

void draw_system(World * w)
{
	char hp_str[32];
	sprintf(hp_str, "HP:%7d", w->hero->hp);
	set_str(screen_buffer, hp_str, 62, 0, 0, 4 + 8);
	print_gauge(62, 1, w->hero->max_hp, w->hero->hp, 4 + 8, 4);
	char mp_str[32];
	sprintf(mp_str, "MP:%7d", w->hero->mp);
	set_str(screen_buffer, mp_str, 62, 2, 0, 1 + 8);
	print_gauge(62, 3, w->hero->max_mp, w->hero->mp, 1 + 8, 1);
	print_mode(62, 4, w->hero);
	print_notice(w->hero, 0, 21);
	draw_examine(60, 20, w, w->hero->x, w->hero->y, w->hero);
}

void draw_fps()
{
	static clock_t fps_t = 0;
	static int last_frame_count = 0;
	if (fps_t + 1000 <= clock()) {
		fps_t = clock();
		last_frame_count = frame_count;
		frame_count = 0;
	}

	char buf[70];
	char flag_str[70];

	if (last_frame_count < goal_fps) {
		sprintf(flag_str, "");
	}
	if (last_frame_count >= goal_fps) {
		sprintf(flag_str, "[max fps]");
	}

	sprintf(buf, "fps:[%3d] goal_fps:[%3d]", last_frame_count, goal_fps);
	set_str(screen_buffer, buf, 0, 23, 0, 15);
	int cur_x = strlen(buf);
	set_str(screen_buffer, flag_str, 0 + cur_x, 23, 0, 4 + 8);
}

void draw_map(World * w)
{
	int cx, cy;
	static Cell *cell_buffer[20][30];
	memset(cell_buffer, 0, sizeof(Cell *) * 20 * 30);
	//map screen size == 30x20
	for (cy = 0; cy < 20; cy++) {
		for (cx = 0; cx < 30; cx++) {
			int hx = w->hero->x;
			int hy = w->hero->y;
			//check error
			//get_cell returns tile or obj shape
			Cell *c;
			c = get_cell_layer(w, hx - 15 + cx, hy - 10 + cy, 2);
			if (c == 0) {
				c = get_cell_layer(w, hx - 15 + cx,
						   hy - 10 + cy, 1);
				if (c == 0) {
					c = get_cell_layer(w, hx - 15 + cx,
							   hy - 10 + cy, 0);
				}
			}
			cell_buffer[cy][cx] = c;
		}
	}
	for (cy = 0; cy < 20; cy++) {
		for (cx = 0; cx < 30; cx++) {
			Cell *c = cell_buffer[cy][cx];
			if (c == 0) {
				set_cell(screen_buffer, ' ', cx * 2, cy, 0, 0);
				set_cell(screen_buffer, ' ', cx * 2 + 1, cy, 0,
					 0);
			} else {
				//trim to fit 2 char
				c->str[2] = 0;
				int len = strlen(c->str);
				if (len == 0) {
					set_cell(screen_buffer, ' ', cx * 2, cy,
						 0, 0);
					set_cell(screen_buffer, ' ', cx * 2 + 1,
						 cy, 0, 0);
				}
				if (len == 1) {

					set_cell(screen_buffer, c->str[0],
						 cx * 2, cy, c->bg_color,
						 c->fg_color);
					set_cell(screen_buffer, ' ', cx * 2 + 1,
						 cy, 0, 0);
				}
				if (len == 2) {
					set_cell(screen_buffer, c->str[0],
						 cx * 2, cy, c->bg_color,
						 c->fg_color);
					set_cell(screen_buffer, c->str[1],
						 cx * 2 + 1, cy, c->bg_color,
						 c->fg_color);
				}
			}
		}
	}

}

int
draw_examine(int display_x, int display_y, World * w, int x, int y,
	     Object * exclude)
{
	Object *obj = obj_at(w, x, y, exclude);
	if (obj == 0)
		return 0;
	set_str(screen_buffer, obj->type, display_x, display_y, 0,
		obj->shape.fg_color);
	return 1;
}

void
print_gauge(int x, int y, int max, int current, unsigned char bright_color,
	    unsigned char dark_color)
{
	int dark, bright;
	if (max == 0) {
		//10 character
		set_str(screen_buffer, "None      ", x, y, 0, dark_color);
		return;
	}
	double g = (double)current / (double)max;
	int percent = g * 100;
	if (percent > 100) {
		percent = 100;
	} else if (percent <= 0) {
		percent = 0;
	}

	bright = percent / 10;
	dark = 10 - bright;

	int bi, di;
	for (bi = 0; bi < bright; bi++)
		set_str(screen_buffer, " ", x + bi, y, bright_color, 0);
	for (di = 0; di < dark; di++)
		set_str(screen_buffer, " ", x + bi + di, y, dark_color, 0);

}

void print_mode_name(int x, int y, Object * obj, char *mode)
{
	char buf[64];
	sprintf(buf, "[%s]", mode);
	int len = strlen(buf);
	int pad = 16 - len;
	if (pad < 0)
		buf[15] = 0;
	set_str(screen_buffer, buf, x, y, 0, 15);
}

void print_mode(int x, int y, Object * obj)
{
	char *mode = obj->operation_mode;
	print_mode_name(x, y, obj, mode);

	if (!strcmp(mode, "skill"))
		print_mode_slots(x, y + 1, obj, 14, obj->skill_slots);
	if (!strcmp(mode, "item"))
		print_mode_slots(x, y + 1, obj, 14, obj->item_slots);
	if (!strcmp(mode, "debug"))
		print_mode_slots(x, y + 1, obj, 14, obj->debug_slots);
}

void
print_mode_slots(int x, int y, Object * obj, int max_str_len,
		 char (*slots)[SHORT_STRLEN])
{
	int i;
	int ii = 0;
	for (i = 0; i < 10; i++) {
		if (!strcmp(slots[i], ""))
			continue;
		char buf[64];

		sprintf(buf, "[%d] %s", i, slots[i]);
		if (strlen(buf) > max_str_len)
			buf[max_str_len] = 0;
		int pad = max_str_len - strlen(buf);
		int k;
		set_str(screen_buffer, buf, x, y + ii, 0, 15 - 8);
		ii++;
	}
}
