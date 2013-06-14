#ifndef __Action_h__
#define __Action_h__

class Level;
class Field;

class Action
{
	public:
		Level* location;

		virtual int get_type() = 0;	//1 - Unit
									//2 - Evaluate
									//3 - Wait/Animation
									//4 - If/Then/Else
									//5 - Loop
		virtual Action* get_next_action() = 0;
		virtual Action* get_extra_action() = 0;
		virtual bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0) = 0;
};


#endif