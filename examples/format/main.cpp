#include "strlib/string.hpp"
#include "../test.hpp"

struct Foo {
	int Bar;
	int Baz;

	Foo(int bar, int baz): Bar(bar), Baz(baz) { }
};

template<>
struct fmt::formatter<Foo> : fmt::nested_formatter<int> {
	auto format(const Foo& foo, fmt::format_context& ctx) const {
		return write_padded(ctx, [=, this](auto out) {
			return fmt::format_to(out, "Foo(Bar = {}, Baz = {})", nested(foo.Bar), nested(foo.Baz));
		});
	}
};

int main() {
	String str = String::Format("{} {} {}", 32, true, -4.24);
	TEST(str == "32 true -4.24");
	str = String::Format("{}", Foo(4, 20));
	TEST(str == "Foo(Bar = 4, Baz = 20)");
	str = String::Format("{0} {0:x} {0:o} {0:b}", 15);
	TEST(str == "15 f 17 1111");
	str = String::Format("{0} {0:#02X} {0:#o} {0:#08b}", 15);
	TEST(str == "15 0XF 017 0b001111");

	return 0;
}