#include "strlib/io.hpp"
#include "strlib/string.hpp"

void test_printf() {
	Print("{}", 32);
	Print("{}", 44);

	PrintLn("");

	PrintLn("{}", 32);
	PrintLn("{}", 44);
}