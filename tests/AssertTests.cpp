
#include "../includes/garbagecan.hpp"

#include <vector>

struct point
{
    bool operator<(const point& rhs) const { return x < rhs.x; }
    bool operator>(const point& rhs) const { return x > rhs.x; }
    bool operator==(const point& rhs) const { return x == rhs.x; }
    bool operator!=(const point& rhs) const { return x != rhs.x; }
    bool operator<=(const point& rhs) const { return x <= rhs.x; }
    bool operator>=(const point& rhs) const { return x >= rhs.x; }
    bool operator()() const { return true; }

    int x = 3;
};

Test(ASSERT_Equal)
{
    ASSERT_EQ(5, 5);
    ASSERT_EQ(5.50000, 5.5);
    ASSERT_EQ("abc", "abc");
    ASSERT_EQ(true, true);
    ASSERT_EQ('b', 'b');
    ASSERT_EQ(nullptr, nullptr);

    point a;
    point b;
    ASSERT_EQ(a, b);
}

Test(ASSERT_Not_Equal)
{
    ASSERT_NE(6, 5);
    ASSERT_NE(5.50001, 5.5);
    ASSERT_NE("abd", "abc");
    ASSERT_NE(false, true);
    ASSERT_NE('a', 'b');

    point a;
    a.x = 6;
    point b;

    ASSERT_NE(&a, nullptr);

    ASSERT_NE(a, b);
}

Test(ASSERT_Greater)
{
    ASSERT_GT(6, 5);
    ASSERT_GT(5.50001, 5.5);
    ASSERT_GT("abcd", "abc");
    ASSERT_GT('b', 'a');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    ASSERT_GT(str + 1, str);

    ASSERT_GT(a, b);
}

Test(ASSERT_Lesser)
{
    ASSERT_LT(5, 6);
    ASSERT_LT(4.99998, 4.99999);
    ASSERT_LT("abc", "abcd");
    ASSERT_LT('a', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    ASSERT_LT(str, str + 1);

    ASSERT_LT(b, a);
}

Test(ASSERT_Greater_Equal)
{
    ASSERT_GTE(6, 5);
    ASSERT_GTE(6, 6);
    ASSERT_GTE(5.50001, 5.5);
    ASSERT_GTE(5.50001, 5.50001);
    ASSERT_GTE("abcd", "abc");
    ASSERT_GTE("abcd", "abcd");
    ASSERT_GTE('b', 'a');
    ASSERT_GTE('b', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    ASSERT_GTE(str + 1, str);
    ASSERT_GTE(str + 1, str + 1);

    ASSERT_GTE(a, b);
    ASSERT_GTE(a, a);
}

Test(ASSERT_Lesser_Equal)
{
    ASSERT_LTE(5, 6);
    ASSERT_LTE(6, 6);
    ASSERT_LTE(4.99998, 4.99999);
    ASSERT_LTE(4.99998, 4.99998);
    ASSERT_LTE("abc", "abcd");
    ASSERT_LTE("abcd", "abcd");
    ASSERT_LTE('a', 'b');
    ASSERT_LTE('b', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    ASSERT_LTE(str, str + 1);
    ASSERT_LTE(str + 1, str + 1);

    ASSERT_LTE(b, a);
    ASSERT_LTE(b, b);
}

Test(ASSERT_True)
{
    ASSERT_TRUE(true);
    ASSERT_TRUE(!(!true));

    point a;
    ASSERT_TRUE(a());
    ASSERT_TRUE(5 == 5);
}

Test(ASSERT_False)
{
    ASSERT_FALSE(false);
    ASSERT_FALSE(!(!false));

    point a;
    ASSERT_FALSE(!a());
    ASSERT_FALSE(5 != 5);
}

Test(ASSERT_String_Equal)
{
    std::string a = "abc";
    std::string b = "abc";
    std::string c = "abc";

    ASSERT_STRING_EQ(a.c_str(), a.c_str());

    ASSERT_STRING_EQ("abc", b.c_str());
    ASSERT_STRING_EQ(b.c_str(), c.c_str());

    ASSERT_STRING_EQ(a.c_str(), c.c_str());
}

Test(ASSERT_String_Not_Equal)
{
    std::string a = "abc";
    std::string b = "abd";
    std::string c = "abf";

    ASSERT_STRING_NE(a.c_str(), "aaas");

    ASSERT_STRING_NE("aba", b.c_str());
    ASSERT_STRING_NE(b.c_str(), c.c_str());

    ASSERT_STRING_NE(a.c_str(), c.c_str());
}

Test(ASSERT_Float_Eps)
{
    double a = 5.5;
    double b = 5.5;

    for (unsigned i = 1; i < 100; i++)
    {
        auto eps = 1 / pow(10, i);
        ASSERT_FLOAT_EPS(a, b + eps, eps);
    }
}

Test(ASSERT_Float_Neps)
{
    double a = 5.5;
    double b = 5.55;

    for (unsigned i = 1; i < 100; i++)
    {
        auto eps = 1 / pow(10, i + 1);
        ASSERT_FLOAT_NEPS(a, b + eps, eps);
    }
}

struct MyException : public std::exception
{

};

void throw_function1()
{
    throw MyException{};
}

Test(ASSERT_Throw_Anything)
{
    ASSERT_THROWS({
                      throw(std::runtime_error(""));
                  });

    ASSERT_THROWS({
                      throw(std::overflow_error(""));
                  });

    ASSERT_THROWS({
                      throw(5);
                  });

    ASSERT_THROWS({
                      throw_function1();
                  });
}

Test(ASSERT_Throw_Exception)
{
    ASSERT_THROW_EXCEPTION(
            std::overflow_error,
            {
                throw(std::overflow_error(""));
            }
    );

    ASSERT_THROW_EXCEPTION(
            MyException,
            {
                throw_function1();
            }
    );
}

Test(ASSERT_No_Throwing)
{
    ASSERT_NO_THROW({
                        int a = 6;
                        int b = 7;
                    });
}