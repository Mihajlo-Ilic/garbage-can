#ifndef TESTSUITEIMPL_HPP
#define TESTSUITEIMPL_HPP

#include <vector>
#include <cstring>
#include <cmath>
#include <exception>

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
#define EXPECT_GT(op1, op2) result &= (op1) > (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,">",!((op1) > (op2)))
#define EXPECT_LT(op1, op2) result &= (op1) < (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<",!((op1) < (op2)))
#define EXPECT_GTE(op1, op2) result &= (op1) >= (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<=",!((op1) >= (op2)))
#define EXPECT_LTE(op1, op2) result &= (op1) <= (op2); gcan::Outputer::logOperator(__FILE__,__LINE__,#op1,#op2,"<=",!((op1) <= (op2)))

#define EXPECT_TRUE(op) EXPECT_EQ(op, true)
#define EXPECT_FALSE(op) EXPECT_EQ(op, false)

#define EXPECT_STRING_EQ(str1, str2) result &= (strcmp(str1, str2) == 0)
#define EXPECT_STRING_NE(str1, str2) result &= (strcmp(str1, str2) != 0)

#define EXPECT_FLOAT_EPS(float1, float2, eps) result &= (fabs((a)-(b)) <= eps)
#define EXPECT_FLOAT_NEPS(float1, float2, eps) result &= (fabs((a)-(b)) >= eps); gcan::Outputer::logOperator(__FILE__,__LINE__, std::to_string(fabs((a)-(b))),std::to_string(eps),">=",(fabs((a)-(b)) >= eps))

#define EXPECT_THROW_EXCEPTION(except, statement) result =false; try statement catch(const std::exception& e) {result = (typeid(e) == typeid(except));}
#define EXPECT_THROWS(statement) result =false; try statement catch(...) {result = true;}
#define EXPECT_NO_THROW(statement) try statement catch(...) {result = false;}

#define CONDITIONAL_ASSERT_END if (!result) {return;}

#define ASSERT_EQ(op1, op2) result &= (op1) == (op2); CONDITIONAL_ASSERT_END
#define ASSERT_NE(op1, op2) result &= (op1) != (op2);CONDITIONAL_ASSERT_END
#define ASSERT_GT(op1, op2) result &= (op1) > (op2);CONDITIONAL_ASSERT_END
#define ASSERT_LT(op1, op2) result &= (op1) < (op2);CONDITIONAL_ASSERT_END
#define ASSERT_GTE(op1, op2) result &= (op1) >= (op2);CONDITIONAL_ASSERT_END
#define ASSERT_LTE(op1, op2) result &= (op1) <= (op2);CONDITIONAL_ASSERT_END

#define ASSERT_TRUE(op) ASSERT_EQ(op, true) CONDITIONAL_ASSERT_END
#define ASSERT_FALSE(op) ASSERT_EQ(op, false) CONDITIONAL_ASSERT_END

#define ASSERT_STRING_EQ(str1, str2) result &= (strcmp(str1, str2) == 0); CONDITIONAL_ASSERT_END
#define ASSERT_STRING_NE(str1, str2) result &= (strcmp(str1, str2) != 0); CONDITIONAL_ASSERT_END

#define ASSERT_FLOAT_EPS(float1, float2, eps) result &= (fabs((a)-(b)) <= eps); CONDITIONAL_ASSERT_END
#define ASSERT_FLOAT_NEPS(float1, float2, eps) result &= (fabs((a)-(b)) >= eps); CONDITIONAL_ASSERT_END

#define ASSERT_THROW_EXCEPTION(except, statement) result =false; try statement catch(const std::exception& e) {result = (typeid(e) == typeid(except));} CONDITIONAL_ASSERT_END
#define ASSERT_THROWS(statement) result =false; try statement catch(...) {result = true;} CONDITIONAL_ASSERT_END
#define ASSERT_NO_THROW(statement) try statement catch(...) {result = false;} CONDITIONAL_ASSERT_END

}
#endif
