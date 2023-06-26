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

Test(Expect_Equal)
{
    EXPECT_EQ(5, 5);
    EXPECT_EQ(5.50000, 5.5);
    EXPECT_EQ("abc", "abc");
    EXPECT_EQ(true, true);
    EXPECT_EQ('b', 'b');
    EXPECT_EQ(nullptr, nullptr);

    point a;
    point b;
    EXPECT_EQ(a, b);
}

Test(Expect_Not_Equal)
{
    EXPECT_NE(6, 5);
    EXPECT_NE(5.50001, 5.5);
    EXPECT_NE("abd", "abc");
    EXPECT_NE(false, true);
    EXPECT_NE('a', 'b');

    point a;
    a.x = 6;
    point b;

    EXPECT_NE(&a, nullptr);

    EXPECT_NE(a, b);
}

Test(Expect_Greater)
{
    EXPECT_GT(6, 5);
    EXPECT_GT(5.50001, 5.5);
    EXPECT_GT("abcd", "abc");
    EXPECT_GT('b', 'a');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    EXPECT_GT(str + 1, str);

    EXPECT_GT(a, b);
}

Test(Expect_Lesser)
{
    EXPECT_LT(5, 6);
    EXPECT_LT(4.99998, 4.99999);
    EXPECT_LT("abc", "abcd");
    EXPECT_LT('a', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    EXPECT_LT(str, str + 1);

    EXPECT_LT(b, a);
}

Test(Expect_Greater_Equal)
{
    EXPECT_GTE(6, 5);
    EXPECT_GTE(6, 6);
    EXPECT_GTE(5.50001, 5.5);
    EXPECT_GTE(5.50001, 5.50001);
    EXPECT_GTE("abcd", "abc");
    EXPECT_GTE("abcd", "abcd");
    EXPECT_GTE('b', 'a');
    EXPECT_GTE('b', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    EXPECT_GTE(str + 1, str);
    EXPECT_GTE(str + 1, str + 1);

    EXPECT_GTE(a, b);
    EXPECT_GTE(a, a);
}

Test(Expect_Lesser_Equal)
{
    EXPECT_LTE(5, 6);
    EXPECT_LTE(6, 6);
    EXPECT_LTE(4.99998, 4.99999);
    EXPECT_LTE(4.99998, 4.99998);
    EXPECT_LTE("abc", "abcd");
    EXPECT_LTE("abcd", "abcd");
    EXPECT_LTE('a', 'b');
    EXPECT_LTE('b', 'b');

    point a;
    a.x = 6;
    point b;

    const char *str= "abc";

    EXPECT_LTE(str, str + 1);
    EXPECT_LTE(str + 1, str + 1);

    EXPECT_LTE(b, a);
    EXPECT_LTE(b, b);
}

Test(Expect_True)
{
    EXPECT_TRUE(true);
    EXPECT_TRUE(!(!true));

    point a;
    EXPECT_TRUE(a());
    EXPECT_TRUE(5 == 5);
}

Test(Expect_False)
{
    EXPECT_FALSE(false);
    EXPECT_FALSE(!(!false));

    point a;
    EXPECT_FALSE(!a());
    EXPECT_FALSE(5 != 5);
}

Test(Expect_String_Equal)
{
    std::string a = "abc";
    std::string b = "abc";
    std::string c = "abc";

    EXPECT_STRING_EQ(a.c_str(), a.c_str());

    EXPECT_STRING_EQ("abc", b.c_str());
    EXPECT_STRING_EQ(b.c_str(), c.c_str());

    EXPECT_STRING_EQ(a.c_str(), c.c_str());
}

Test(Expect_String_Not_Equal)
{
    std::string a = "abc";
    std::string b = "abd";
    std::string c = "abf";

    EXPECT_STRING_NE(a.c_str(), "aaas");

    EXPECT_STRING_NE("aba", b.c_str());
    EXPECT_STRING_NE(b.c_str(), c.c_str());

    EXPECT_STRING_NE(a.c_str(), c.c_str());
}

Test(Expect_Float_Eps)
{
    double a = 5.5;
    double b = 5.5;

    for (unsigned i = 1; i < 100; i++)
    {
        auto eps = 1 / pow(10, i);
        EXPECT_FLOAT_EPS(a, b + eps, eps);
    }
}

Test(Expect_Float_Neps)
{
    double a = 5.5;
    double b = 5.55;

    for (unsigned i = 1; i < 100; i++)
    {
        auto eps = 1 / pow(10, i + 1);
        EXPECT_FLOAT_NEPS(a, b + eps, eps);
    }
}

struct MyException : public std::exception
{

};

void throw_function()
{
    throw MyException{};
}

Test(Expect_Throw_Anything)
{
    EXPECT_THROWS({
        throw(std::runtime_error(""));
    })

    EXPECT_THROWS({
       throw(std::overflow_error(""));
    })

    EXPECT_THROWS({
       throw(5);
    })

    EXPECT_THROWS({
      throw_function();
    })
}

Test(Expect_Throw_Exception)
{
    EXPECT_THROW_EXCEPTION(
        std::overflow_error,
        {
            throw(std::overflow_error(""));
        }
    );

    EXPECT_THROW_EXCEPTION(
        MyException,
        {
            throw_function();
        }
    );
}

Test(Expect_No_Throwing)
{
    EXPECT_NO_THROW(
        int a = 6;
        int b = 7;
   );
}