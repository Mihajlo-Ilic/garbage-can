#ifndef TESTABLE_HPP
#define TESTABLE_HPP

#include <functional>
#include <memory>
#include <string>

namespace gcan
{
	class TestMeta
	{
	public:
		explicit TestMeta(const std::string& name) : _name(name) {};

		TestMeta(const TestMeta&) = delete;
		TestMeta&
		operator=(const TestMeta&) = delete;

		virtual void
		prepareTest()
		{
		};
		virtual void
		cleanupTest()
		{
		};

		virtual void
		testBody()
		{
		};

	private:

		std::string _name;

		std::shared_ptr<std::function<void()>> _test;
	};
}

#endif
