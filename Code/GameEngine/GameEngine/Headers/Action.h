#ifndef __Action_h__
#define __Action_h__

class Action
{
	public:
	Action();
	void set_values(char* nm, int id, double s1, double s2, bool l, bool e, bool ex);

	char* name;
	int ID;
	double scale1;
	double scale2;
	bool loop;
	bool evaluate;
	bool extra;
	Action* father;
	Action* next_normal;
	Action* next_extra;
};

#endif
