#include <iostream>
#include <TimeStamp.h>

int main()
{
	SLog::TimeStamp ts;
	std::cout << ts.getFormatTimeStamp() << std::endl;
}
