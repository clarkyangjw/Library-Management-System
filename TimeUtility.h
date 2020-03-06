#ifndef SICT_TIMEUTILITY_H
#define SICT_TIMEUTILITY_H
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <stdio.h>
#include <cstdlib> 
#include <string>

using namespace std;

namespace sict {
	class TimeUtility {
	public:
		TimeUtility();
		~TimeUtility();
		void timeToString(time_t time1, char* szTime);
		time_t stringToTime(char* szTime);
		string addMonth(time_t& tTime);
	};
}
#endif