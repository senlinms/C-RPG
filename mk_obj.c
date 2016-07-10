#include "game.h"
//change fn_do_rand to move_random
//나머지는 모두 0으로 초기화됨
fn_name_pair table_tick_obj_fn[100] = {
		{"move_random","obj_fn_move_random",fn_do_rand},
		{"fire_timer","obj_fn_fire_timer", fn_fire_timer},
		{"bomb_timer","obj_fn_bomb_timer",fn_bomb_timer},
		{"thru_bullet_timer","obj_fn_thru_bullet_timer",fn_thru_bullet_timer},
		{"heal_timer","obj_fn_heal_timer",fn_heal_timer}};
		

Object* new_mk_obj(char* , World * , int , int , Object* );		
fnptr table_obj_fn_by_long_name(fn_name_pair * table, char* long_name)
{
	if(long_name == 0)
		return 0;
	if(table == 0)
		return 0;
	for(int i =0;i<100;i++)
	{
		//다른 곳에도 이 오류 처리 추가하기
		if(table[i].long_name == 0)
			continue;
		if(!strcmp(table[i].long_name,long_name))
			return table[i].fn;
	}
	return 0;
}

Object mk_dummy(World *w, int x, int y,Object* parent)
{
    Object o;
    memset(&o,0,sizeof(Object));
    strcpy(o.shape.str,"d");
    if(parent != 0)
        o.direction = parent->direction;
    else
        o.direction = "down";
    o.parent = parent;
    strcpy(o.type,"dummy");
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
    strcpy(o.operation_mode,"debug");

    o.world = w;
    return o;
}
Object mk_bomb(World *w, int x, int y,Object* parent)
{
	
	Object* o = new_mk_obj("bomb",w,x,y,parent);
    return *o;
}
Object mk_fire(World *w, int x, int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"*");

    strcpy(o.type , "fire");
    o.shape.fg_color = 13;
    o.tick_fn = fn_fire_timer;
    o.overlap_fn = fn_damage;
    o.timer = 10;
    o.shape.layer = 0;
    o.power = 9;
    o.hp = 10;
    o.shape.block = 0;
    return o;
}
Object mk_thru_bullet(World *w, int x, int y, Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"x");

    strcpy(o.type, "thru gun");
    o.shape.fg_color = 14;
    o.tick_fn = fn_thru_bullet_timer;
    o.overlap_fn = fn_damage;
    o.timer = 15;
    o.shape.layer = 2;
    o.power = 30;
    o.hp = 1;
    o.shape.block = 0;
    return o;
}
Object mk_explode_bullet(World *w, int x, int y, Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"x");

    strcpy(o.type, "explode-bullet");
    o.shape.fg_color = 15;
    o.tick_fn = fn_thru_bullet_timer;
    o.overlap_fn = fn_explode_bullet;
    o.timer = 15;
    o.shape.layer = 2;
    o.power = 1;
    o.hp = 1;
    o.shape.block = 0;
    return o;
}
Object mk_enemy(World * w, int x,int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"e");

    strcpy(o.type , "enemy");
    o.shape.fg_color = 15;
    o.tick_fn = fn_do_rand;
    add_slot(&o,"item","coin");
    o.shape.layer = 1;
    o.shape.block = 1;
    return o;
}
Object mk_hero(World *w, int x, int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"@");

    strcpy(o.type , "hero");
    o.shape.fg_color = 15;
    o.max_hp = 100;
    o.max_mp = 100;
    o.hp = o.max_hp;
    o.mp = o.max_mp;
    o.shape.block = 1;
    o.shape.layer = 1;
    add_slot(&o,"debug","root");
    add_slot(&o,"debug","fly");
    add_slot(&o,"debug","put_wall");
    add_slot(&o,"debug","put_space");
    add_slot(&o,"debug","load_world");
    add_slot(&o,"debug","save_world");
    add_slot(&o,"debug","fps+");
    add_slot(&o,"debug","fps-");

    add_slot(&o,"skill","heal");
    add_slot(&o,"skill","bomb");
    add_slot(&o,"skill","thru gun");
    add_slot(&o,"skill","bomb gun");
    return o;
}
Object mk_heal(World*w, int x, int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"~");

    strcpy(o.type , "heal");
    o.shape.fg_color = 2+8;
    o.tick_fn = fn_heal_timer;
    o.overlap_fn = fn_heal;
    o.timer = 90;
    o.shape.layer = 0;
    o.power = 1;
    o.hp = 10;
    o.shape.block = 0;
    return o;
}
Object mk_coin(World*w, int x, int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"$");
    o.shape.fg_color = 6+8;//bright yellow
    o.tick_fn = 0;
    strcpy(o.type , "coin");
    o.overlap_fn = fn_root_me;
    o.timer = 0;
    o.shape.layer = 0;
    o.power = 0;
    o.hp = 99999999;
    o.shape.block = 0;
    return o;
}
Object mk_book(World*w, int x, int y,Object* parent)
{
    Object o = mk_dummy(w,x,y,parent);
    strcpy(o.shape.str,"$");
    o.shape.fg_color = 6;//yellow
    o.tick_fn = 0;
    strcpy(o.type , "book");
    o.overlap_fn = fn_root_me;
    o.timer = 0;
    o.shape.layer = 0;
    o.power = 0;
    o.hp = 99999999;
    o.shape.block = 0;
    return o;
}
int char_pos_ith(char* buf,char c, int i)
{
    int x;
    int found = 0;
    for(x=0; x<4096; x++)
    {
        if(buf[x]== 0)
            return -1;
        if(buf[x]==c)
        {
            if(found == i)
                return x;
            found++;
        }

    }
}
char* get_line(char* buf, int i)
{
    if(i==0)
        return buf;
//0th char is first char hence i-1
    return buf+char_pos_ith(buf,'\n',i-1)+1;
}
int str_len_char(char* str,char c)
{
    int i;
    for(i=0; i<4096; i++)
    {

        if(str[i] == 0)
            return -1;

        if(str[i] == c)
            return i;
    }
    return -1;
}
int same_until_char(char* s1, char*s2,char c)
{
    int i;
    for(i=0;i<4096;i++)
    {
        if(s1[i] == c && s2[i] ==c)
            return 1;
        if(s1[i] == 0 && s2[i] ==0)
            return 1;
        if(s1[i] != s2[i])
            return 0;
        if(s1[i] == s2[i])
            continue;


    }
}

//obj_x.txt안에는 언제나 끝에 한줄을 비워둘것!
int set_obj_with_line(Object* o, char* line)
{
    char* first = line;
    char*second = line + char_pos_ith(line,' ',0) + 1;
    if(same_until_char(first,"type ",' '))
    {
        int len = str_len_char(second,'\r');
        strncpy(o->type,second,len);
        o->type[len] = 0;
        return 1;
    }
    if(same_until_char(first,"shape.str ",' '))
    {
        int len = str_len_char(second,'\r');
        strncpy(o->shape.str,second,len);
        o->shape.str[len] = 0;
        return 1;
    }
	if(same_until_char(first,"timer  ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->timer = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"shape.fg_color ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->shape.fg_color = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"shape.bg_color ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->shape.bg_color = atoi(buf);
        return 1;
    }
	if(same_until_char(first,"shape.block ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->shape.block = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"hp ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->hp = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"max_hp ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->max_hp = atoi(buf);
        return 1;
    }

    if(same_until_char(first,"mp ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->mp = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"max_mp ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->max_mp = atoi(buf);
        return 1;
    }
    if(same_until_char(first,"power ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        o->power = atoi(buf);
        return 1;
    }

    if(same_until_char(first,"item ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        add_slot(o,"item",buf);
        return 1;
    }
    if(same_until_char(first,"skill ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        add_slot(o,"skill",buf);
        return 1;
    }
    if(same_until_char(first,"debug ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
        add_slot(o,"debug",buf);
        return 1;
    }
	if(same_until_char(first,"offset_x ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
		obj_move(o->world,o,atoi(buf),0);
        return 1;
    }
	if(same_until_char(first,"offset_y ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
		obj_move(o->world,o,0,atoi(buf));
        return 1;
    }
	if(same_until_char(first,"fn_tick ",' '))
    {
        int len = str_len_char(second,'\r');
        char buf[32]= {0,};
        strncpy(buf,second,len);
		fnptr fn = table_obj_fn_by_long_name(table_tick_obj_fn,buf);
		o->tick_fn = fn;
		if(fn == 0)
			return 0;
		
        return 1;
    }
    return 0;
}

int mod_obj_with_buf(char * buf,Object* o)
{
    int i;
    for(i=0; i<4096; i++)
    {
        char* line = get_line(buf,i);
		if(strlen(line) <=1)
			break;
        if(line == 0)
            break;
        int success = set_obj_with_line(o,line);
        if(success == 0)
        {
            char error_str[256];
            MessageBox(0,buf,"error",MB_OK);
			
			sprintf(error_str,"line index:%d\nstring:%s",i,line);
            MessageBox(0,error_str,"error",MB_OK);
			
            break;
        }
    }
    return 1;
}

int new_obj_from(World* w, char* file_name,int x, int y,Object * parent)
{
    FILE * fp = fopen(file_name,"rb");

    if(fp==0)
        return 0;
    char buf[4096];
    int rpos = fread(buf,1,4096,fp);
    fseek(fp,0,SEEK_END);
    int epos = ftell(fp);
    if(rpos != epos)
        return 0;
    Object o = mk_dummy(w,x,y,parent);
    mod_obj_with_buf(buf,&o);
    int k = get_empty_obj_index(w);
    if(k==-1)
        return -1;
    w->objs[k] = o;

    if(!strcmp(o.type,"hero"))
    {
        w->hero = &(w->objs[k]);
    }
    return k;
}

int new_obj(World * w, char * type, int x, int y, Object* parent)
{
    Object o;
    if(!strcmp(type,"bomb"))
    {
        o = mk_bomb(w,x,y,parent);
    }
    else if(!strcmp(type,"fire"))
    {
        o = mk_fire(w,x,y,parent);
    }
    else if(!strcmp(type,"heal"))
    {
        o = mk_heal(w,x,y,parent);
    }
    else if(!strcmp(type,"enemy"))
    {
        o = mk_enemy(w,x,y,parent);
    }
    else if(!strcmp(type,"hero"))
    {
        o = mk_hero(w,x,y,parent);
    }
    else if(!strcmp(type,"coin"))
    {
        o = mk_coin(w,x,y,parent);
    }
    else if(!strcmp(type,"book"))
    {
        o = mk_book(w,x,y,parent);
    }
    else if(!strcmp(type,"thru gun"))
    {
        if(!strcmp(parent->direction , "left"))
            o = mk_thru_bullet(w,x-1,y,parent);

        if(!strcmp(parent->direction , "right"))
            o = mk_thru_bullet(w,x+1,y,parent);

        if(!strcmp(parent->direction , "up"))
            o = mk_thru_bullet(w,x,y-1,parent);

        if(!strcmp(parent->direction,"down"))
            o = mk_thru_bullet(w,x,y+1,parent);
    }
    else if(!strcmp(type,"bomb gun"))
    {
        if(!strcmp(parent->direction , "left"))
            o = mk_explode_bullet(w,x-1,y,parent);

        if(!strcmp(parent->direction , "right"))
            o = mk_explode_bullet(w,x+1,y,parent);

        if(!strcmp(parent->direction , "up"))
            o = mk_explode_bullet(w,x,y-1,parent);

        if(!strcmp(parent->direction,"down"))
            o = mk_explode_bullet(w,x,y+1,parent);
    }
    else
        return -1;// false

    int k = get_empty_obj_index(w);
    w->objs[k] = o;

    if(!strcmp(type,"hero"))
    {
        w->hero = &(w->objs[k]);
    }
    return k;
}





Object* new_mk_obj(char* name, World * w, int x, int y, Object* parent)
{
	char file_name[256];
	sprintf(file_name,"./data/obj_%s.txt",name);
	FILE * fp = fopen(file_name,"rb");
    if(fp==0)
	{
		printf("unable to open file:%s",file_name);
		exit(1);
		return 0;
	}
        
    char buf[4096];
    int rpos = fread(buf,1,4096,fp);
    fseek(fp,0,SEEK_END);
    int epos = ftell(fp);
    if(rpos != epos)
        return 0;
    Object o = mk_dummy(w,x,y,parent);
    mod_obj_with_buf(buf,&o);
    int k = get_empty_obj_index(w);
    if(k==-1)
        return -1;
    w->objs[k] = o;
    if(!strcmp(o.type,"hero"))
    {
        w->hero = &(w->objs[k]);
    }
	//o를 리턴하면 안됨. o는 스택에 들어어서 함수가 끝나면 삭제됨
    return &(w->objs[k]);
}
