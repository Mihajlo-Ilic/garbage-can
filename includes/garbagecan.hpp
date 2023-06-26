#ifndef GARBAGE_CAN_UNIT_TESTER_HPP
#define GARBAGE_CAN_UNIT_TESTER_HPP

#include <vector>

#include <exception>

#include "comparer.hpp"
#include "writer.hpp"

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

#define FILE __FILE__,__LINE__

#define EXPECT_EQ(op1, op2)  {if (!compare2(op1, op2, equality))     addLog(this, log2(FILE, "EXPECT_EQ",  #op1, #op2, op1, op2));}
#define EXPECT_NE(op1, op2)  {if (!compare2(op1, op2, notEqual))     addLog(this, log2(FILE, "EXPECT_NE",  #op1, #op2, op1, op2));}
#define EXPECT_GT(op1, op2)  {if (!compare2(op1, op2, greater))      addLog(this, log2(FILE, "EXPECT_GT",  #op1, #op2, op1, op2));}
#define EXPECT_LT(op1, op2)  {if (!compare2(op1, op2, lesser))       addLog(this, log2(FILE, "EXPECT_LT",  #op1, #op2, op1, op2));}
#define EXPECT_GTE(op1, op2) {if (!compare2(op1, op2, greaterEqual)) addLog(this, log2(FILE, "EXPECT_GTE", #op1, #op2, op1, op2));}
#define EXPECT_LTE(op1, op2) {if (!compare2(op1, op2, lesserEqual))  addLog(this, log2(FILE, "EXPECT_LTE", #op1, #op2, op1, op2));}

#define EXPECT_TRUE(op)  {if (!compare1(op, isTrue))  addLog(this, log1(FILE, "EXPECT_TRUE",   #op, op));}
#define EXPECT_FALSE(op) {if (!compare1(op, isFalse)) addLog(this, log1(FILE, "EXPECT_FALSE",  #op, op));}

#define EXPECT_STRING_EQ(str1, str2) {if (!compare2(str1, str2, cStringEqual))    addLog(this, log2(FILE, "EXPECT_STRING_EQ",      #str1, #str2, str1, str2));}
#define EXPECT_STRING_NE(str1, str2) {if (!compare2(str1, str2, cStringNotEqual)) addLog(this, log2(FILE, "EXPECT_STRING_NOT_EQ",  #str1, #str2, str1, str2));}

#define EXPECT_FLOAT_EPS(op1, op2,  eps) {if (!compare3(op1, op2, eps, floatEqualInEps))    addLog(this, log3(FILE, "EXPECT_FLOAT_EPS",   #op1, #op2, #eps, op1, op2, eps));}
#define EXPECT_FLOAT_NEPS(op1, op2, eps) {if (!compare3(op1, op2, eps, floatNotEqualInEps)) addLog(this, log3(FILE, "EXPECT_FLOAT_NEPS",  #op1, #op2, #eps, op1, op2, eps));}

#define EXPECT_THROW_EXCEPTION(except, statement)
#define EXPECT_THROWS(statement)
#define EXPECT_NO_THROW(statement)

//-------------------------ASSERT CALLS -------------------------------

#define CONDITIONAL_ASSERT_END if (!result) {return;}

#define ASSERT_EQ(op1, op2)  {if (!compare2(op1, op2, equality))     addLog(this, log2(FILE, "ASSERT_EQ",  #op1, #op2, op1, op2));}
#define ASSERT_NE(op1, op2)  {if (!compare2(op1, op2, notEqual))     addLog(this, log2(FILE, "ASSERT_NE",  #op1, #op2, op1, op2));}
#define ASSERT_GT(op1, op2)  {if (!compare2(op1, op2, greater))      addLog(this, log2(FILE, "ASSERT_GT",  #op1, #op2, op1, op2));}
#define ASSERT_LT(op1, op2)  {if (!compare2(op1, op2, lesser))       addLog(this, log2(FILE, "ASSERT_LT",  #op1, #op2, op1, op2));}
#define ASSERT_GTE(op1, op2) {if (!compare2(op1, op2, greaterEqual)) addLog(this, log2(FILE, "ASSERT_GTE", #op1, #op2, op1, op2));}
#define ASSERT_LTE(op1, op2) {if (!compare2(op1, op2, lesserEqual))  addLog(this, log2(FILE, "ASSERT_LTE", #op1, #op2, op1, op2));}

#define ASSERT_TRUE(op)  {if (!compare1(op, isTrue))  addLog(this, log1(FILE, "ASSERT_TRUE",   #op, op));}
#define ASSERT_FALSE(op) {if (!compare1(op, isFalse)) addLog(this, log1(FILE, "ASSERT_FALSE",  #op, op));}

#define ASSERT_STRING_EQ(str1, str2) {if (!compare2(str1, str2, cStringEqual))    addLog(this, log2(FILE, "ASSERT_STRING_EQ",      #str1, #str2, str1, str2));}
#define ASSERT_STRING_NE(str1, str2) {if (!compare2(str1, str2, cStringNotEqual)) addLog(this, log2(FILE, "ASSERT_STRING_NOT_EQ",  #str1, #str2, str1, str2));}

#define ASSERT_FLOAT_EPS(op1, op2,  eps) {if (!compare3(op1, op2, eps, floatEqualInEps))    addLog(this, log3(FILE, "ASSERT_FLOAT_EPS",   #op1, #op2, #eps, op1, op2, eps));}
#define ASSERT_FLOAT_NEPS(op1, op2, eps) {if (!compare3(op1, op2, eps, floatNotEqualInEps)) addLog(this, log3(FILE, "ASSERT_FLOAT_NEPS",  #op1, #op2, #eps, op1, op2, eps));}

#define ASSERT_THROW_EXCEPTION(except, statement)
#define ASSERT_THROWS(statement)
#define ASSERT_NO_THROW(statement)


//-------------------------CLASSES-------------------------------

    class TestCollector;

    class TestMeta {
    public:
        explicit TestMeta(std::string name) : _name(std::move(name)) {};

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
        friend void addLog(TestMeta *me, std::stringstream&& ss)
        {
            me->logs.push_back(ss.str());
        }

        std::string _name;
        std::vector<std::string> logs;

        friend class TestCollector;
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

                std::cout << "-- " << test->_name << (test ->logs.empty() ? " PASSED" : " FAILED") << std::endl;
                for (const auto& it : test->logs)
                {
                    std::cout << it << std::endl;
                }

            }
        }

    };

}
#endif
