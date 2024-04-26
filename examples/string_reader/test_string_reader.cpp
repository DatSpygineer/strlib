#include "strlib/io.hpp"
#include "strlib/string.hpp"
#include "../test.hpp"

void test_string_reader() {
	StringReader sr("Test string\nAnother line\nLine 2");
	TEST(sr.read() == "Test");
	TEST(sr.read() == "string");
	TEST(sr.next());

	String line;
	TEST(sr.readLine(line));
	TEST(line == "Another line");

	sr.seek(0);
	TEST(sr.read() == "Test");
	TEST(sr.tell() == 4);
	TEST(sr.peek() == ' ');
	TEST(sr.readChar() == ' ');
	sr.seek(3, std::ios::cur);
	TEST(sr.readToEnd() == "ing\nAnother line\nLine 2");
	TEST(sr.eof());
}