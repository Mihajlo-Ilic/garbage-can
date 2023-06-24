#ifndef GARBAGE_CAN_UNIT_TESTER_HPP
#define GARBAGE_CAN_UNIT_TESTER_HPP

#include <vector>
#include <string>
#include <iostream>

#include <exception>

#include <cstring>
#include <cmath>

#define GARBAGE_TESTER_MAIN \
int main() \
{ \
    gcan::TestCollector::run(); \
    return 0; \
}

namespace gcan {

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
    bool TEST_NAME_FROM_STR(Name)::_registered = gcan::TestCollector::registerTest(new TEST_NAME_FROM_STR(Name));    \
    void TEST_NAME_FROM_STR(Name)  ::testBody()

#define Test(Name) Test_Private(Name)

//-------------------------EXPECT CALLS -------------------------------

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

//-------------------------ASSERT CALLS -------------------------------

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


//-------------------------CLASSES-------------------------------


    class Outputer {
    public:

        static void logOperator(const std::string &file, int line, const std::string &op1, const std::string &op2,
                                const std::string &operation, bool failed) {
            static std::vector<std::string> _logs;

            if (failed) {
                _logs.push_back("File: " + file + ":" + std::to_string(line) + " " + op1 + " " + operation + " " + op2 +
                                " FAILED");
                std::cout << _logs.at(_logs.size() - 1) << std::endl;
            }

        }

        static void logTest(const std::string &testName, bool passed) {
            static std::vector<std::string> _logs;

            _logs.push_back("-- " + testName + (!passed ? " FAILED" : " PASSED"));
            std::cout << _logs.at(_logs.size() - 1) << std::endl;

        }

    };

    class TestMeta {
    public:
        explicit TestMeta(const std::string &name) : _name(name) {};

        TestMeta(const TestMeta &) = delete;

        TestMeta &
        operator=(const TestMeta &) = delete;

        virtual void
        prepareTest() {
        };

        virtual void
        cleanupTest() {
        };

        virtual void
        testBody() {
        };

        std::string getName() const { return _name; }

        bool getResult() const { return result; }

    protected:
        bool result = true;

    private:

        std::string _name;
    };

    class TestCollector {
    public:
        TestCollector() = delete;

        static std::vector<TestMeta *> &testRegistry() {
            static std::vector<TestMeta *> _registry;
            return _registry;
        }

        static bool registerTest(TestMeta *test) {
            TestCollector::testRegistry().push_back(test);
            return true;
        }

        static void run() {
            for (const auto &test: TestCollector::testRegistry()) {
                test->testBody();
                Outputer::logTest(test->getName(), test->getResult());
            }
        }

    };

}
#endif
