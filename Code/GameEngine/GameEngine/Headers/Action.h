#ifndef __Action_h__
#define __Action_h__

class Action
{
	public:
	Action();
	void set(char* nm, bool in, double d);

	char* name;
	bool interruptable;
	double delay;
};

#endif
