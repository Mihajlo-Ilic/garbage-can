#include "../includes/TestCollector.hpp"

#include <iostream>

Test(My_Test){
    EXPECT_EQ(2,3);

    EXPECT_LTE(5,3);
    EXPECT_GT(5,3);
}

int main()
{
	gcan::TestCollector::run();
	return 0;
}
