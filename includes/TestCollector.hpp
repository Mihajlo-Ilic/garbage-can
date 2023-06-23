#ifndef TEST_COLLECTOR_HPP
#define TEST_COLLECTOR_HPP

#include <map>

#include "TestSuiteMeta.hpp"

namespace gcan
{

	class TestCollector
	{
	public:
		TestCollector() = delete;

		using MetaNew = std::unique_ptr<TestMeta>;

        static std::vector<TestMeta*>& testRegistry()
        {
            static std::vector<TestMeta*> _registry;
            return _registry;
        }

		static bool registerTest(TestMeta *test)
		{
            TestCollector::testRegistry().push_back(test);
			return true;
		}

		static void run()
		{
            for (const auto& test: TestCollector::testRegistry())
            {
                test->testBody();
            }
		}

	};

}

#endif
