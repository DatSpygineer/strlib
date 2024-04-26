#include "strlib/string.hpp"
#include "../test.hpp"

int main() {
	time_t _t = time(nullptr);
	struct tm* t = localtime(&_t);

	String str = String::Date("yyyy_MM_dd");
	TEST(str == String::Format("{:04d}_{:02d}_{:02d}", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday));
	printf("%s\n", str.cStr());

	return 0;
}