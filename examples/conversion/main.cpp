#include <cassert>
#include "strlib/string.hpp"

int main() {
	String str = String::From(true);
	assert(str == "true");
	printf("%s\n", str.cStr());

	str = String::From(false);
	assert(str == "false");
	printf("%s\n", str.cStr());

	str = String::From(12);
	assert(str == "12");
	printf("%s\n", str.cStr());

	str = String::From(12, 2);
	assert(str == "1100");
	printf("%s\n", str.cStr());

	str = String::From(12, 8);
	assert(str == "14");
	printf("%s\n", str.cStr());

	str = String::From(12, 16);
	assert(str == "C");
	printf("%s\n", str.cStr());

	str = String::From(1.24);
	assert(str == "1.24");
	printf("%s\n", str.cStr());

	str = String::FromChar('C');
	assert(str == "C");
	printf("%s\n", str.cStr());

	str = String::FromWChar(L'Ü');
	assert(str == "Ü");
	printf("%s\n", str.cStr());

	str = String::FromWString(L"Helló wörld!");
	assert(str == "Helló wörld!");
	printf("%s\n", str.cStr());

	std::wstring wstr = str.stdWStr();
	assert(wstr == L"Helló wörld!");
	wprintf(L"%ls\n", wstr.c_str());

	str = "32";
	int i;
	assert(str.parse(i));
	assert(i == 32);

	int x;
	str = "0x40";
	assert(str.parse(x, 16));
	assert(x == 0x40);

	int o;
	str = "010";
	assert(str.parse(o, 8));
	assert(o == 010);

	int b;
	str = "0b1011";
	assert(str.parse(b, 2));
	assert(b == 0b1011);

	float f;
	str = "3.14";
	assert(str.parse(f));
	assert(f == 3.14f);

	return 0;
}