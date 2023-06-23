#ifndef TESTSUITEIMPL_HPP
#define TESTSUITEIMPL_HPP

#include <vector>
#include "string.h"

#include "TestMeta.hpp"
#include "TestCollector.hpp"
#include "Writer.hpp"

namespace gcan
{

	namespace _gcanPrivate
	{


#define TEST_NAME_FROM_STR(Name) __TEST_INTERNAL__ ## Name

#define Test_Private(Name) \
    class TEST_NAME_FROM_STR(Name) : public gcan::TestMeta \
    {                              \
        public:                       \
                 TEST_NAME_FROM_STR(Name) (): TestMeta( #Name ) { \
				 } \
                 \
            virtual void testBody() override;              \
			static bool _registered; \
		\
	};                     \
	bool TEST_NAME_FROM_STR(Name)::_registered = gcan::TestCollector::registerTest(new TEST_NAME_FROM_STR(Name));	\
    void TEST_NAME_FROM_STR(Name)  ::testBody()


	}

#define Test(Name) Test_Private(Name)

#define EXPECT_EQ(op1, op2) result &= (op1) == (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"=",!((op1) == (op2)))
#define EXPECT_NE(op1, op2) result &= (op1) != (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"!=",!((op1) != (op2)))
#define EXPECT_GT(op1, op2) result &= (op1) > (op2) ; gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,">",!((op1) > (op2)))
#define EXPECT_LT(op1, op2) result &= (op1) < (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<",!((op1) < (op2)))
#define EXPECT_GTE(op1, op2) result &= (op1) >= (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<=",!((op1) >= (op2)))
#define EXPECT_LTE(op1, op2) result &= (op1) <= (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<=",!((op1) <= (op2)))

#define EXPECT_TRUE(op) EXPECT_EQ(op, true)
#define EXPECT_FALSE(op) EXPECT_EQ(op, false)

#define EXPECT_STRING_EQ(str1, str2) result &= (strcmp(str1, str2) == 0)
#define EXPECT_STRING_NE(str1, str2) result &= (strcmp(str1, str2) != 0)

#define CONDITIONAL_ASSERT_END(result) if (!result) {return;}

#define ASSERT_EQ(op1, op2) result &&= (op1) == (op2); CONDITIONAL_ASSERT_END(result)
#define ASSERT_NE(op1, op2) result &&= (op1) != (op2) CONDITIONAL_ASSERT_END(result)
#define ASSERT_GT(op1, op2) result &&= (op1) > (op2) CONDITIONAL_ASSERT_END(result)
#define ASSERT_LT(op1, op2) result &&= (op1) < (op2) CONDITIONAL_ASSERT_END(result)
#define ASSERT_GTE(op1, op2) result &&= (op1) >= (op2) CONDITIONAL_ASSERT_END(result)
#define ASSERT_LTE(op1, op2) result &&= (op1) <= (op2) CONDITIONAL_ASSERT_END(result)

#define ASSERT_TRUE(op) ASSERT_EQ(op, true)
#define ASSERT_FALSE(op) ASSERT_EQ(op, false)

}
#endif
