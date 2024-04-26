#include "strlib/io.hpp"
#include "strlib/string.hpp"
#include "../test.hpp"

void test_string_builder() {
	StringBuilder sb;
	sb.append('s');
	TEST(sb.str() == "s");

	sb.append("tring");
	TEST(sb.str() == "string");

	sb.appendLine("string");
	TEST(sb.str() == "stringstring\n");
}