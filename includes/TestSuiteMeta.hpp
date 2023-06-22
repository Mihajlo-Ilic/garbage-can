#ifndef TESTSUITEIMPL_HPP
#define TESTSUITEIMPL_HPP

#include <vector>

#include "TestMeta.hpp"
#include "TestCollector.hpp"

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

}
#endif
