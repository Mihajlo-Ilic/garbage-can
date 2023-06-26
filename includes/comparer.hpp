#ifndef COMPARER_HPP
#define COMPARER_HPP

#include <functional>
#include <cmath>
#include <cstring>

template <class T>
bool compare1( T op1,  bool (*predicate1)(T))
{
    return predicate1(op1);
}

template <class T>
bool isTrue(T op)
{
    return op == true;
}

template <class T>
bool isFalse(T op)
{
    return op == false;
}

template <class T, class V>
bool compare2( T op1, V op2,  bool (*predicate2)(T, V))
{
    return predicate2(op1, op2);
}

template <class T, class V, class Z>
bool compare3( T op1, V op2, Z op3,  bool (*predicate3)(T, V, Z))
{
    return predicate3(op1, op2, op3);
}

template <class T, class V>
bool equality(T op1, V op2)
{
    return op1 == op2;
}

template <class T, class V>
bool notEqual(T op1, V op2)
{
    return op1 != op2;
}

template <class T, class V>
bool greater(T op1, V op2)
{
    return op1 > op2;
}

template <class T, class V>
bool lesser(T op1, V op2)
{
    return op1 < op2;
}

template <class T, class V>
bool greaterEqual(T op1, V op2)
{
    return op1 >= op2;
}

template <class T, class V>
bool lesserEqual(T op1, V op2)
{
    return op1 <= op2;
}

template <class T, class V>
bool cStringEqual(T op1,V op2)
{
    return strcmp(op1, op2) == 0;
}

template <class T, class V>
bool cStringNotEqual(T op1, V op2)
{
    return strcmp(op1, op2) != 0;
}

template <class T, class V, class Z>
bool floatEqualInEps(T op1, V op2, Z eps)
{
    return (fabs(op1 - op2) / op2 <= eps);
}

template <class T, class V, class Z>
bool floatNotEqualInEps(T op1, V op2, Z eps)
{
    return (fabs(op1 - op2) / op2 > eps);
}

#endif
