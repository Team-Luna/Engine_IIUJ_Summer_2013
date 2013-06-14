#include <Trigger.h>
#include <Windows.h>
using namespace std;

Trigger::Trigger(Condition* input_con, Event* input_eve, bool input_tk) {
	con = input_con;
	eve = input_eve;
	takes_units = input_tk;
}

void Trigger::check(Field* source, Field* target) {
	if (con == 0)
		return;
	if (eve == 0)
		return;
	if (con->check_condition(source, target))
		eve->invokeEvent(source, target);
}

