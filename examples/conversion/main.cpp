#include "strlib/string.hpp"
#include "../test.hpp"

int main() {
	String str = String::From(true);
	TEST(str == "true");
	printf("%s\n", str.cStr());

	str = String::From(false);
	TEST(str == "false");
	printf("%s\n", str.cStr());

	str = String::From(12);
	TEST(str == "12");
	printf("%s\n", str.cStr());

	str = String::From(12, 2);
	TEST(str == "1100");
	printf("%s\n", str.cStr());

	str = String::From(12, 8);
	TEST(str == "14");
	printf("%s\n", str.cStr());

	str = String::From(12, 16);
	TEST(str == "C");
	printf("%s\n", str.cStr());

	str = String::From(1.24);
	TEST(str == "1.24");
	printf("%s\n", str.cStr());

	str = String::FromChar('C');
	TEST(str == "C");
	printf("%s\n", str.cStr());

	str = String::FromWChar(L'Ü');
	TEST(str == "Ü");
	printf("%s\n", str.cStr());

	str = String::FromWString(L"Helló wörld!");
	TEST(str == "Helló wörld!");
	printf("%s\n", str.cStr());

	std::wstring wstr = str.stdWStr();
	TEST(wstr == L"Helló wörld!");
	wprintf(L"%ls\n", wstr.c_str());

	str = String::FromUtf8(u8"Helló wörld!");
	std::u8string u8str = str.asUtf8();
	TEST(u8str == u8"Helló wörld!");

	str = String::FromUtf16(u"Helló wörld!");
	std::u16string u16str = str.asUtf16();
	TEST(u16str == u"Helló wörld!");

	str = String::FromUtf32(U"Helló wörld!");
	std::u32string u32str = str.asUtf32();
	TEST(u32str == U"Helló wörld!");

	str = "32";
	int i;
	TEST(str.parse(i));
	TEST(i == 32);

	int x;
	str = "0x40";
	TEST(str.parse(x, 16));
	TEST(x == 0x40);

	int o;
	str = "010";
	TEST(str.parse(o, 8));
	TEST(o == 010);

	int b;
	str = "0b1011";
	TEST(str.parse(b, 2));
	TEST(b == 0b1011);

	float f;
	str = "3.14";
	TEST(str.parse(f));
	TEST(f == 3.14f);

	return 0;
}