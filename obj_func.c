#include "game.h"

void state_tick(Object * o)
{
	int i;
	//reduce 100 to 10 later
	for(i=0;i<100;i++)
	{
		//assume fragmented
		if(o->state[i]==0)
			continue;
		if(o->state[i]->fn_tick_condition(o))
			o->state[i]->fn_tick(o);
		else
		{
			o->state[i]->fn_terminate(o);
			o->state[i] = 0;
		}		
	}
}
state_slot * find_slot(state_slot* table, char* name)
{
	if (name == 0)
		return 0;
	if (table == 0)
		return 0;
	for (int i = 0; i < 100; i++) {
		if (strlen(table[i].name) == 0)
			continue;
		if (!strcmp(table[i].name, name))
			return &(table[i]);
	}
	return 0;
}
int empty_state_slot_index(Object *o)
{
	int i;
	for(i=0;i<100;i++)
	{
		if(o->state[i]==0)
			return i;
	}
	return -1;
}
int set_state(Object * o, state_slot * table, char* name)
{
	state_slot * slot  = find_slot(table, name);
	int index = empty_state_slot_index(o);
	if(index == -1)
		return 0;
	o->state[index] = slot;
	slot->fn_initial(o);	
	return 1;
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