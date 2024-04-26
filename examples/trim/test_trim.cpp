#include "strlib/string.hpp"
#include "../test.hpp"

void test_trim() {
	String str = "  Hello  ";

	TEST(String::Format("[{}]", str) == "[  Hello  ]");
	printf("[%s] - Original string\n", str.cStr());

	TEST(String::Format("[{}]", str.trimStart()) == "[Hello  ]");
	printf("[%s] - Trim start\n", str.trimStart().cStr());

	TEST(String::Format("[{}]", str.trimEnd()) == "[  Hello]");
	printf("[%s] - Trim end\n", str.trimEnd().cStr());

	TEST(String::Format("[{}]", str.trim()) == "[Hello]");
	printf("[%s] - Trim\n", str.trim().cStr());
}