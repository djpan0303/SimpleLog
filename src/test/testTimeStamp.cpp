#include <iostream>
#include <TimeStamp.h>

int main()
{
	SimpleLog::TimeStamp ts;
	std::cout << ts.getFormatTimeStamp() << std::endl;
}
