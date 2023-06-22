#ifndef TESTABLE_HPP
#define TESTABLE_HPP

#include <functional>
#include <memory>

#define Test(TEST_NAME) Test("", TEST_NAME)
#define Test(TEST_SUITE, TEST_NAME)

class Testable
{
public:
	explicit Testable() = default;

	Testable(const Testable&) = delete;
	Testable& operator=(const Testable&) = delete;

	void operator()() const;

private:
	std::shared_ptr<std::function<void()>> _test;
};


#endif
