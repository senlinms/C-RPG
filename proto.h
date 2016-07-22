/* act.c */
fn_obj fn_by_long_name(str_str_fn *table, char *long_name);
void table_act(str_str_fn *table, Object *obj, char *long_name);
char *long_name(str_str_fn *table, char *name);
int act_debug(Object *obj, char *name);
void debug_quit(Object *obj);
void debug_fly(Object *obj);
void debug_put_wall(Object *obj);
void debug_put_space(Object *obj);
void debug_load_world(Object *obj);
void debug_save_world(Object *obj);
void debug_fps_plus(Object *obj);
void debug_fps_minus(Object *obj);
void debug_loot(Object *obj);
void debug_interactive_new_cell(Object *obj);
int act_skill(Object *obj, char *name);
int act_item(Object *obj, char *name);
void act(Object *obj, char *mode, int num);
/* debug_fn.c */
int msgbox(Object *o);
int msgbox_yes_no(Object *o);
int fn_obj_damage(Object *o);
/* draw.c */
void set_notice(Object *obj, char *notice);
void gotoxy(int x, int y);
void set_color(char bg, char fg);
void print_notice(Object *obj, int x, int y);
void set_cell(CHAR_INFO *buffer, char c, int x, int y, unsigned char bg, unsigned char fg);
void set_str(CHAR_INFO *buffer, char *str, int x, int y, unsigned char bg, unsigned char fg);
void write_scr(CHAR_INFO *buffer, int cx, int cy);
void draw(World *w);
void draw_system(World *w);
void draw_fps(void);
void draw_map(World *w);
int draw_examine(int display_x, int display_y, World *w, int x, int y, Object *exclude);
void print_gauge(int x, int y, int max, int current, unsigned char bright_color, unsigned char dark_color);
void print_mode_name(int x, int y, Object *obj, char *mode);
void print_mode(int x, int y, Object *obj);
void print_mode_slots(int x, int y, Object *obj, int max_str_len, char (*slots)[32]);
/* global.c */
/* key_process.c */
void key_quit(Object *obj);
char *key_name(int key);
void table_key_process(str_str_fn *table, Object *obj);
void key_process(World *w);
void key_debug(Object *obj);
void key_move_up(Object *obj);
void key_move_down(Object *obj);
void key_move_left(Object *obj);
void key_move_right(Object *obj);
void key_attack(Object *obj);
void key_loot(Object *obj);
void key_skill_mode(Object *obj);
void key_item_mode(Object *obj);
void key_debug_mode(Object *obj);
void key_shortcut_0(Object *obj);
void key_shortcut_1(Object *obj);
void key_shortcut_2(Object *obj);
void key_shortcut_3(Object *obj);
void key_shortcut_4(Object *obj);
void key_shortcut_5(Object *obj);
void key_shortcut_6(Object *obj);
void key_shortcut_7(Object *obj);
void key_shortcut_8(Object *obj);
void key_shortcut_9(Object *obj);
/* main.c */
void game_over_update(World *w);
void scene_game_over(World *w);
World *game_init(void);
void tick_sleep(void);
void game_update(World *w);
void scene_map(World *w);
int main(void);
/* mk_obj.c */
fn_obj table_obj_fn_by_long_name(str_str_fn *table, char *long_name);
Object mk_dummy(World *w, int x, int y, Object *parent);
int char_pos_ith(char *buf, char c, int i);
char *get_line(char *buf, int i);
int str_len_char(char *str, char c);
int same_until_char(char *s1, char *s2, char c);
int set_obj_with_line(Object *o, char *line);
int mod_obj_with_buf(char *buf, Object *o);
Object *new_mk_obj(char *name, World *w, int x, int y, Object *parent);
/* obj_func.c */
void state_tick(Object *o);
state_slot *find_slot(state_slot *table, char *name);
int empty_state_slot_index(Object *o);
int set_state(Object *o, state_slot *table, char *name);
int obj_move(World *w, Object *o, int ox, int oy);
int object_to_index(Object *obj);
int reverse_find_valid_obj_index(World *w);
void delete_object(Object *obj);
void delete_object_with_index(World *w, int index);
/* obj_handler_overlap.c */
int fn_heal(Object *me, Object *other);
int fn_damage(Object *me, Object *other);
int fn_kill(Object *me, Object *other);
int fn_loot_me(Object *me, Object *other);
int fn_explode_bullet(Object *me, Object *other);
/* obj_handler_tick.c */
int fn_heal_timer(Object *o);
int fn_do_rand(Object *o);
int fn_fire_timer(Object *o);
int fn_bomb_timer(Object *o);
int fn_death_drop(Object *me);
int fn_thru_bullet_timer(Object *me);
/* tick.c */
void tick_overlap(World *w);
void __OLD_tick_overlap(World *w);
void tick_self(World *w);
void tick(World *w);
/* world.c */
int num_of_empty_slot(Object *obj, char (*slots)[32]);
Object *obj_at(World *w, int x, int y, Object *exclude);
Cell *get_cell_layer(World *w, int x, int y, int layer);
int add_slot(Object *obj, char *mode, char *new_slot);
int save_world(World *w, char *file_name);
int load_world(World *w, char *file_name);
int put_cell(World *w, int x, int y, Cell c);
Cell interactive_new_cell(void);
Cell new_cell(char ch, int bg, int fg, int layer, int block);
int delete_cell(World *w, int x, int y);
int get_empty_obj_index(World *w);
int check_block(World *w, int x, int y, int layer);
