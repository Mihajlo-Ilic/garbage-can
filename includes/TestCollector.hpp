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

		static bool registerTest(TestMeta *test)
		{
			TestCollector::_testRegistry["a"] = test;
			return true;
		}

		static void run()
		{
			for (const auto& it: TestCollector::_testRegistry)
			{
				it.second->testBody();
			}
		}

	private:
		static std::map<std::string, TestMeta*> _testRegistry;
	};

}

#endif
