#ifndef PROTO_WORLD_H
#define PROTO_WORLD_H
#include "game.h"
extern int  check_block(World * w, int x, int y,int layer);
extern int  get_empty_obj_index(World *w);
extern int  delete_cell(World * w, int x, int y);
extern Cell new_cell(char ch, int bg, int fg, int layer,int block);
extern Cell interactive_new_cell();
extern int  put_cell(World * w, int x, int y, Cell c);
extern int  load_world(World * w, char *file_name);
extern int  save_world(World * w, char * file_name);
extern int  add_slot(Object *obj, char* mode, char* new_slot);
extern Cell* get_cell_layer(World*w, int x, int y, int layer);
extern Object* obj_at(World* w, int x, int y, Object *exclude);
extern int  num_of_empty_slot(Object* obj, char (*slots)[SHORT_STRLEN];);
extern int  find_empty_slot(Object *obj,char *mode);


#endif // WORLD_H_INCLUDED
