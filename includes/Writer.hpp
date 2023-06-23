#ifndef GARBAGE_CAN_WRITER_HPP
#define GARBAGE_CAN_WRITER_HPP

#include <iostream>
#include <istream>
#include <vector>

namespace gcan
{

    struct LogOperator
    {
        int line;
        std::string file;
        std::string op1;

        std::string op2;
    };

    class Outputer
    {
    public:

        static void logOperator(const std::string& file,int line, const std::string& op1, const std::string& op2,const std::string& operation, bool failed)
        {
            static std::vector<std::string> _logs;

            if (failed)
            {
                _logs.push_back("File: " + file + ":" + std::to_string(line) + " " + op1 + " " + operation + " " + op2 + " FAILED");
                std::cout << _logs.at(_logs.size() - 1) << std::endl;
            }

        }

    };

}

#endif
