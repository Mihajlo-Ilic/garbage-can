
#ifndef TEST_RESULT_HPP
#define TEST_RESULT_HPP

#include <type_traits>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cxxabi.h>

using str = const std::string&;

template<class Class>
struct has_ostream_operator_impl {
    template<class V>
    static auto test(V*) -> decltype(std::declval<std::ostream>() << std::declval<V>());
    template<typename>
    static auto test(...) -> std::false_type;

    using type = typename std::is_same<std::ostream&, decltype(test<Class>(0))>::type;
};

template<class Class>
struct has_ostream_operator : has_ostream_operator_impl<Class>::type {};

template<class T>
typename std::enable_if<has_ostream_operator<T>::value, std::string>::type
toStr(T arg)
{
    std::stringstream result;
    result << arg;
    return result.str();
}

template<class T>
typename std::enable_if<!has_ostream_operator<T>::value, std::string>::type
toStr(T arg)
{
    std::stringstream result;

    if (std::is_null_pointer<T>())
    {
        result << "Null Pointer";
    }
    else
    {
        int status;
        char *name;
        const std::type_info &info = typeid(arg);

        name = abi::__cxa_demangle(info.name(), NULL, NULL, &status);
        result << "not printable Type:" << name;
        free(name);
    }
    return result.str();
}

template<typename T, typename V, typename Z>
std::stringstream log3(str file,int line, str operation, str op1, str op2, str op3, T value1, V value2, Z value3)
{
    std::stringstream result;

    result << "-- " << file << ":" << line << " " << operation << "(" << op1 << ", " << op2 << ", " << op3 << ") FAILED" << std::endl;
    result << "\tvalue of arg1: " << toStr(value1) << std::endl;
    result << "\tvalue of arg2: " << toStr(value2) << std::endl;
    result << "\tvalue of arg3: " << toStr(value3) << std::endl;

    return result;
}

template<typename T, typename V>
std::stringstream log2(str file,int line, str operation, str op1, str op2, T value1, V value2)
{
    std::stringstream result;

    result << "-- " << file << ":" << line << " " << operation << "(" << op1 << ", " << op2 << ") FAILED" << std::endl;
    result << "\tvalue of arg1: " << toStr(value1) << std::endl;
    result << "\tvalue of arg2: " << toStr(value2) << std::endl;

    return result;
}

template<typename T>
std::stringstream log1(str file,int line, str operation, str op1, T value)
{
    std::stringstream result;

    result << "-- " << file << ":" << line << " " << operation << "(" << op1 << ") FAILED" << std::endl;
    result << "\tvalue of arg: " << toStr(value) << std::endl;

    return result;
}

template<typename T>
std::stringstream logTryCatch(str file,int line,str operation, str statement, T message)
{
    std::stringstream result;

    result << "-- " << file << ":" << line << " " << operation << "(" << statement << ") FAILED" << std::endl;
    result << "\tResult of try catch: " << std::endl;
    result << "\t\tException message: " << message << std::endl;

    return result;
}

#endif
