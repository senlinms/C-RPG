#include "game.h"
void set_notice(Object * obj, char *notice)
{
	strncpy(obj->last_notice, notice, 64);
}

int obj_move(World * w, Object * o, int ox, int oy)
{
	int tox = o->x + ox;
	int toy = o->y + oy;
	int ol = o->shape.layer;
	if (o->x < tox)
		o->direction = "right";
	if (o->x > tox)
		o->direction = "left";
	if (o->y > toy)
		o->direction = "up";
	if (o->y < toy)
		o->direction = "down";
	if (check_block(w, tox, toy, ol) == 0) {
		
		o->x = tox;
		o->y = toy;
		return 1;
	}
	return 0;
}

int object_to_index(Object * obj)
{
	int i;
	World * w = obj->world;
	for(i=0;i<500;i++)
	{
		if(&(w->objs[i]) == obj)
			return i;
	}
	return -1;
}
int reverse_find_valid_obj_index(World *w)
{
	int i;
	for(i = 500-1;i>=0;i--)
	{
		if(w->objs[i].exist == 0)
			continue;
		return i;
	}
	return -1;
}
void delete_object(Object * obj)
{
	//index will never be -1
	int index = object_to_index(obj);
	
	delete_object_with_index(obj->world,index);
}
//all Object deletion should use this function
void delete_object_with_index(World * w, int index)
{
	w->objs[index].exist = 0;
	
	//defragment
	int alive_obj_index = reverse_find_valid_obj_index(w);
	if(alive_obj_index == -1)
		return;
	if(index >= alive_obj_index)
		return;
	
	//update hero pointer if defragmented object is hero. without this, 
	//hero pointer will point somthing wrong and interpreted as non existed object.
	//improve later. save pointer poiniting its object. use it to replace below line
	if(&(w->objs[alive_obj_index])== w->hero)
		w->hero = &(w->objs[index]);	
	w->objs[index] = w->objs[alive_obj_index];
	w->objs[alive_obj_index].exist = 0;
	
}