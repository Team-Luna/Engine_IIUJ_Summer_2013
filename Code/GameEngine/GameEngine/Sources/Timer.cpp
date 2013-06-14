#include <Timer.h>
using namespace std;

Timer::Timer(double iaf, double iar, double iac, bool ila, bool ia)
{
	amount_first = iaf;
	amount_repeat = iar;
	amount_current = iac;
	loops_automatically = ila;
	active = ia;

	first_time = true;
	just_expired = false;
}

void Timer::start()
{
	active = true;
	just_expired = false;
	if (first_time)
	{
		amount_current = amount_first;
		first_time = !first_time;
	}
	else
		amount_current = amount_repeat;
}

bool Timer::check()
{
	return just_expired;
}

void Timer::tick_forward(double deltaTime)
{
	//if fixed
	if (amount_current < 0)
		just_expired = false;

	//Checking status
	if (!active)
		return;
	//Substracting
	amount_current -= deltaTime;
	if (amount_current <= 0)
	{
		active = false;
		if (loops_automatically)
			start();
		else amount_current = -1;
		just_expired = true;
		return;
	}
	just_expired = false;
}