#include <exception>
using namespace std;

#ifndef __Timer_h__
#define __Timer_h__

class Timer
{
	public:
		Timer(double iaf, double iar, double iac, bool ila, bool ia);

		double amount_first;
		double amount_repeat;
		double amount_current;
		bool loops_automatically;
		bool active;

		bool first_time;
		bool just_expired;

		void start();
		bool check();
		void tick_forward(double deltaTime);
};

#endif
