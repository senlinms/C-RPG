#include "game.h"
int msgbox(Object * o, Object * o2)
{
	MessageBox(0, "poison started", "object type", MB_OK);
	return 1;
}

int msgbox2(Object * o, Object * o2)
{
	MessageBox(0, "poison ended", "object type", MB_OK);
	return 1;
}

int msgbox_yes_no(Object * o, Object * o2)
{
	int ret =
	    MessageBox(0, "yes to return 1 no to return 0", "YES_NO", MB_YESNO);
	if (ret == IDYES)
		return 1;
	else
		return 0;
}

int fn_obj_damage(Object * o, Object * o2)
{
	o->hp -= 1;
	return 1;
}
