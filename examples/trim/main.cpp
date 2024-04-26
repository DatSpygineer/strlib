#include <cassert>
#include "strlib/string.hpp"

int main() {
	String str = "  Hello  ";

	assert(String::Format("[{}]", str) == "[  Hello  ]");
	printf("[%s] - Original string\n", str.cStr());

	assert(String::Format("[{}]", str.trimStart()) == "[Hello  ]");
	printf("[%s] - Trim start\n", str.trimStart().cStr());

	assert(String::Format("[{}]", str.trimEnd()) == "[  Hello]");
	printf("[%s] - Trim end\n", str.trimEnd().cStr());

	assert(String::Format("[{}]", str.trim()) == "[Hello]");
	printf("[%s] - Trim\n", str.trim().cStr());

	return 0;
}