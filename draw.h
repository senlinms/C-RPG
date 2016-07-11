#ifndef PROTO_DRAW_H
#define PROTO_DRAW_H
extern void print_mode_slots(int x, int y, Object* obj, int max_str_len, char (*slots)[SHORT_STRLEN];);
extern void print_mode(int x, int y, Object *obj);
extern void print_mode_name(int x,int y,Object * obj, char* mode);
extern int draw_info(int display_x, int display_y, World* w, int x, int y,Object* exclude);
extern void print_gauge(int x,int y, int max,int current, unsigned char bright_color,unsigned char dark_color);
extern void draw(World * w);
extern void write_scr(CHAR_INFO * buffer, int cx, int cy);
extern void set_str(CHAR_INFO *buffer,char * str, int x , int y, unsigned char bg, unsigned char fg);
extern void set_cell(CHAR_INFO * buffer,char c, int x, int y, unsigned char bg, unsigned char fg);
extern void print_notice(Object* obj,int x, int y);

extern void gotoxy(int x, int y);

extern void set_color(char bg, char fg);


#endif // PROTO_DRAW_H
