#include "../includes/TestCollector.hpp"

#include <iostream>

Test(My_Test){
	std::cout << "Hello from me " << std::endl;
}

int main()
{
	gcan::TestCollector::run();
	return 0;
}
