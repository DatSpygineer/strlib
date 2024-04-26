#pragma once

#if __cplusplus < 201711UL
	#error Unsupported C++ standard! Expected C++ 17 or newer!
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fmt/format.h>

class String {
	std::string m_sString;
public:
	String(): m_sString() { }
	String(const char* cstr): m_sString(cstr) { }			// NOLINT: Implicit conversion for backwards compatibility
	String(const char* cstr, size_t len): m_sString(cstr, len) { }
	String(std::string&& str): m_sString(std::move(str)) { }	// NOLINT: Implicit conversion for backwards compatibility
	String(const std::string& str): m_sString(str) { }			// NOLINT: Implicit conversion for backwards compatibility
	String(String&& str) noexcept : m_sString(std::move(str.m_sString)) { str.m_sString = ""; }
	String(const String& str) = default;
	String(char c, size_t n);

	using traits_type    = std::string::traits_type;
	using allocator_type = std::string::allocator_type;
	using value_type      = std::string::value_type;
	using size_type       = std::string::size_type;
	using difference_type = std::string::difference_type;
	using pointer         = std::string::pointer;
	using const_pointer   = std::string::const_pointer;
	using reference       = std::string::reference&;
	using const_reference = std::string::const_reference&;
	using iterator       = std::string::iterator;
	using const_iterator = std::string::const_iterator;
	using reverse_iterator       = std::string::reverse_iterator;
	using const_reverse_iterator = std::string::const_reverse_iterator;

	String& operator= (String&& other) noexcept;
	String& operator= (const String& other) = default;

	[[nodiscard]] inline constexpr size_t length() const noexcept { return m_sString.length(); }
	[[nodiscard]] inline constexpr size_t size() const noexcept { return m_sString.size(); }
	[[nodiscard]] inline constexpr size_t capacity() const noexcept { return m_sString.capacity(); }
	[[nodiscard]] inline constexpr bool isEmpty() const noexcept { return m_sString.empty(); }

	inline constexpr char* data() { return m_sString.data(); }
	[[nodiscard]] inline constexpr const char* data() const { return m_sString.data(); }
	[[nodiscard]] inline constexpr const char* cStr() const { return m_sString.c_str(); }

	inline std::string& stdStr() { return m_sString; }
	[[nodiscard]] inline constexpr const std::string& stdStr() const { return m_sString; }

	[[nodiscard]] std::wstring stdWStr() const;

	[[nodiscard]] std::u8string asUtf8() const;
	[[nodiscard]] std::u16string asUtf16() const;
	[[nodiscard]] std::u32string asUtf32() const;

	inline void reserve(size_t n) { m_sString.reserve(n); }
#if __cplusplus < 202002L
	[[nodiscard]] inline bool startsWith(char c) const { return m_sString.front() == c; }
	[[nodiscard]] inline bool startsWith(const String& str) const { return m_sString.substr(0, str.length()) == str.m_sString; }
	[[nodiscard]] inline bool endsWith(char c) const { return m_sString.back() == c; }
	[[nodiscard]] inline bool endsWith(const String& str) const {
		return m_sString.length() >= str.length() && m_sString.substr(m_sString.length() - str.length()) == str.m_sString;
	}
#else
	[[nodiscard]] inline bool startsWith(char c) const { return m_sString.starts_with(c); }
	[[nodiscard]] inline bool startsWith(const String& str) const { return m_sString.starts_with(str.m_sString); }
	[[nodiscard]] inline bool endsWith(char c) const { return m_sString.ends_with(c); }
	[[nodiscard]] inline bool endsWith(const String& str) const { return m_sString.ends_with(str.m_sString); }
#endif

	[[nodiscard]] inline size_type find(char c) const { return m_sString.find(c); }
	[[nodiscard]] inline size_type find(char c, size_t offset) const { return m_sString.find(c, offset); }
	[[nodiscard]] inline size_type find(const String& str) const { return m_sString.find(str.m_sString); }
	[[nodiscard]] inline size_type find(const String& str, size_t offset) const { return m_sString.find(str.m_sString, offset); }
	[[nodiscard]] inline size_type findLast(char c) const { return m_sString.rfind(c); }
	[[nodiscard]] inline size_type findLast(char c, size_t offset) const { return m_sString.rfind(c, offset); }
	[[nodiscard]] inline size_type findLast(const String& str) const { return m_sString.rfind(str.m_sString); }
	[[nodiscard]] inline size_type findLast(const String& str, size_t offset) const { return m_sString.rfind(str.m_sString, offset); }
	[[nodiscard]] inline size_type findFirstOf(const String& str) const { return m_sString.find_first_of(str.m_sString); }
	[[nodiscard]] inline size_type findFirstOf(const String& str, size_t offset) const { return m_sString.find_first_of(str.m_sString, offset); }
	[[nodiscard]] inline size_type findFirstNotOf(const String& str) const { return m_sString.find_first_not_of(str.m_sString); }
	[[nodiscard]] inline size_type findFirstNotOf(const String& str, size_t offset) const { return m_sString.find_first_not_of(str.m_sString, offset); }
	[[nodiscard]] inline size_type findLastOf(const String& str) const { return m_sString.find_last_of(str.m_sString); }
	[[nodiscard]] inline size_type findLastOf(const String& str, size_t offset) const { return m_sString.find_last_of(str.m_sString, offset); }
	[[nodiscard]] inline size_type findLastNotOf(const String& str) const { return m_sString.find_last_not_of(str.m_sString); }
	[[nodiscard]] inline size_type findLastNotOf(const String& str, size_t offset) const { return m_sString.find_last_not_of(str.m_sString, offset); }
	[[nodiscard]] inline bool contains(char c) { return find(c) != std::string::npos; }
	[[nodiscard]] inline bool contains(const String& str) { return find(str) != std::string::npos; }

	[[nodiscard]] inline String substr(size_t start) const { return m_sString.substr(start); }
	[[nodiscard]] inline String substr(size_t start, size_t n) const { return m_sString.substr(start, n); }

	[[nodiscard]] String trimStart(const String& chars = " \t\n\r") const;
	[[nodiscard]] String trimEnd(const String& chars = " \t\n\r") const;
	[[nodiscard]] String trim(const String& chars = " \t\n\r") const;

	inline char& first() { return m_sString.front(); }
	[[nodiscard]] inline char first() const { return m_sString.front(); }
	inline char& last() { return m_sString.back(); }
	[[nodiscard]] inline char last() const { return m_sString.back(); }

	[[nodiscard]] String toLowercase() const;
	[[nodiscard]] String toUppercase() const;

	inline String& append(char c) { m_sString.push_back(c); return *this; }
	inline String& append(String&& str) { m_sString += str.m_sString; str.m_sString.clear(); return *this; }
	inline String& append(const String& str) { m_sString += str.m_sString; return *this; }

	iterator insert(size_t at, char c);
	iterator insert(size_t at, const String& str);
	iterator insert(const iterator& at, char c);
	iterator insert(const iterator& at, const String& str);

	iterator erase(const iterator& at);
	iterator erase(const iterator& beg, const iterator& end);
	iterator erase(size_t at);
	iterator erase(size_t at, size_t n);

	String& replace(size_t at, size_t n, const String& replacement);
	String& replace(const iterator& beg, const iterator& end, const String& replacement);
	String& replace(const String& to_replace, const String& replacement);
	String& replaceAll(const String& to_replace, const String& replacement);

	[[nodiscard]] String replaceCopy(size_t at, size_t n, const String& replacement) const;
	[[nodiscard]] String replaceCopy(const iterator& beg, const iterator& end, const String& replacement) const;
	[[nodiscard]] String replaceCopy(const String& to_replace, const String& replacement) const;
	[[nodiscard]] String replaceAllCopy(const String& to_replace, const String& replacement) const;

	String& removePrefix(const String& prefix);
	String& removeSuffix(const String& suffix);
	String& removePrefix(char prefix);
	String& removeSuffix(char suffix);

	[[nodiscard]] String withoutPrefix(const String& prefix) const;
	[[nodiscard]] String withoutSuffix(const String& suffix) const;
	[[nodiscard]] String withoutPrefix(char prefix) const;
	[[nodiscard]] String withoutSuffix(char suffix) const;

	[[nodiscard]] inline String offset(size_t n) const { return m_sString.substr(n); }

	[[nodiscard]] std::vector<String> split(char delim) const;
	[[nodiscard]] std::vector<String> split(const String& delim) const;

	[[nodiscard]] int compare(const String& other) const;
	[[nodiscard]] int compare(const String& other, size_t n) const;
	[[nodiscard]] int compare(const String& other, size_t offset, size_t n) const;
	[[nodiscard]] int compare(const String& other, size_t this_offset, size_t offset, size_t n) const;
	[[nodiscard]] int compareNoCase(const String& other) const;
	[[nodiscard]] int compareNoCase(const String& other, size_t n) const;
	[[nodiscard]] int compareNoCase(const String& other, size_t offset, size_t n) const;
	[[nodiscard]] int compareNoCase(const String& other, size_t this_offset, size_t offset, size_t n) const;

	bool parse(bool& value) const;
	bool parse(signed char& value, int base = 10) const;
	bool parse(short& value, int base = 10) const;
	bool parse(int& value, int base = 10) const;
	bool parse(long& value, int base = 10) const;
	bool parse(long long& value, int base = 10) const;
	bool parse(unsigned char& value, int base = 10) const;
	bool parse(unsigned short& value, int base = 10) const;
	bool parse(unsigned int& value, int base = 10) const;
	bool parse(unsigned long& value, int base = 10) const;
	bool parse(unsigned long long& value, int base = 10) const;
	bool parse(float& value) const;
	bool parse(double& value) const;
	bool parse(long double& value) const;

	template<typename ...T>
	inline static String Format(const String& format, T&&... args) {
		return { fmt::vformat(format.m_sString, fmt::make_format_args(args...)) };
	}

	static String FromChar(char value);
	static String FromWChar(wchar_t value);
	static String FromWString(const std::wstring& str);
	static String FromUtf8(const std::u8string& str);
	static String FromUtf16(const std::u16string& str);
	static String FromUtf32(const std::u32string& str);

	static String From(uint8_t value, int base = 10);
	static String From(uint16_t value, int base = 10);
	static String From(uint32_t value, int base = 10);
	static String From(uint64_t value, int base = 10);
	static String From(int8_t value, int base = 10);
	static String From(int16_t value, int base = 10);
	static String From(int32_t value, int base = 10);
	static String From(int64_t value, int base = 10);
	static String From(float value);
	static String From(double value);
	static String From(long double value);
	static String From(bool value);

	static String Date(const String& format);

	[[nodiscard]] inline String operator+ (char c) const { return { m_sString + c }; }
	[[nodiscard]] inline String operator+ (String&& other) const {
		String result = { m_sString + other.m_sString };
		other.m_sString.clear();
		return result;
	}
	[[nodiscard]] inline String operator+ (const String& other) const { return { m_sString + other.m_sString }; }
	inline String operator+= (char c) { m_sString += c; return *this; }
	inline String operator+= (String&& other) { m_sString += other.m_sString; other.m_sString.clear(); return *this; }
	inline String operator+= (const String& other) { m_sString += other.m_sString; return *this; }

	[[nodiscard]] inline constexpr bool operator== (const String& other) const { return m_sString == other.m_sString; }
	[[nodiscard]] inline constexpr bool operator!= (const String& other) const { return m_sString != other.m_sString; }

	[[nodiscard]] inline constexpr char operator[] (size_t idx) const { return m_sString[idx]; }
	inline constexpr char& operator[] (size_t idx) { return m_sString[idx]; }

	std::string& operator* () { return m_sString; }
	const std::string& operator* () const { return m_sString; }
	std::string& operator-> () { return m_sString; }
	const std::string& operator-> () const { return m_sString; }

	inline auto begin() { return m_sString.begin(); }
	[[nodiscard]] inline auto begin() const { return m_sString.begin(); }
	inline auto rbegin() { return m_sString.rbegin(); }
	[[nodiscard]] inline auto rbegin() const { return m_sString.rbegin(); }
	inline auto end() { return m_sString.end(); }
	[[nodiscard]] inline auto end() const { return m_sString.end(); }
	inline auto rend() { return m_sString.rend(); }
	[[nodiscard]] inline auto rend() const { return m_sString.rend(); }

	static const size_t NoFind;
	static const String Empty;

	friend std::ostream& operator<< (std::ostream& os, const String& string);
	friend std::istream& operator>> (std::istream& is, String& string);
};

inline String operator""_S(const char* cstr, size_t len) { return { cstr, len }; }
template<>
struct fmt::formatter<String> : fmt::formatter<std::string_view> {
	auto format(const String& str, fmt::format_context& ctx) const {
		return fmt::formatter<std::string_view>::format(str.stdStr(), ctx);
	}
};

class StringBuilder {
	std::ostringstream m_ss;
public:
	StringBuilder() = default;
	explicit StringBuilder(const String& str): m_ss(str.stdStr()) { }

	inline StringBuilder& append(char c) { m_ss << c; return *this; }
	inline StringBuilder& append(const String& str) { m_ss << str; return *this; }
	inline StringBuilder& appendLine(const String& str) { m_ss << str << std::endl; return *this; }

	inline std::ostringstream& stdStream() { return m_ss; }
	[[nodiscard]] inline const std::ostringstream& stdStream() const { return m_ss; }
	[[nodiscard]] inline String str() const { return m_ss.str(); }
};
template<>
struct fmt::formatter<StringBuilder> : fmt::formatter<std::string_view> {
	auto format(const StringBuilder& sb, fmt::format_context& ctx) const {
		return fmt::formatter<std::string_view>::format(sb.str().stdStr(), ctx);
	}
};

class StringReader {
	std::istringstream m_ss;
public:
	StringReader() = default;
	explicit StringReader(const String& str): m_ss(str.stdStr()) { }

	inline void str(const String& str) { m_ss.str(str.stdStr()); }
	[[nodiscard]] inline String str() const { return m_ss.str(); }

	inline char readChar() {
		return m_ss.get();
	}
	inline String read() {
		String str;
		m_ss >> str;
		return str;
	}
	inline String read(size_t n) {
		String str;
		str.reserve(n);
		for (size_t i = 0; i < n && !m_ss.eof(); i++) {
			char c = static_cast<char>(m_ss.get());
			str += c;
		}
		return str;
	}
	inline String readToEnd() {
		auto start = m_ss.tellg();
		m_ss.seekg(0, std::ios::end);
		auto end = m_ss.tellg();
		m_ss.seekg(start, std::ios::beg);

		return read(end - start);
	}
	inline bool readLine(String& line) {
		return static_cast<bool>(std::getline(m_ss, line.stdStr()));
	}

	inline void seek(std::streamoff i) {
		m_ss.seekg(i);
	}
	inline void seek(std::streamoff i, std::ios_base::seekdir seekDir) {
		m_ss.seekg(i, seekDir);
	}
	inline std::streamoff tell() {
		return m_ss.tellg();
	}
	inline int peek() {
		return m_ss.peek();
	}
	inline bool next() {
		if (m_ss.eof()) return false;
		m_ss.seekg(1, std::ios_base::cur);
		return true;
	}
	inline bool eof() {
		return m_ss.eof() || m_ss.peek() < 0;
	}

	inline std::istringstream& stdStream() { return m_ss; }
	[[nodiscard]] inline const std::istringstream& stdStream() const { return m_ss; }
};

class Exception : public std::exception {
	String m_sMessage;
public:
	explicit Exception(String&& message) noexcept: m_sMessage(std::move(message)) { }
	explicit Exception(const String& message) noexcept: m_sMessage(message) { }
	template<typename ...T>
	explicit Exception(const String& format, T... args) noexcept: String({ fmt::vformat(format.stdStr(), fmt::make_format_args(args...)) }) { }

	[[nodiscard]] virtual String message() const noexcept { return m_sMessage; }
	[[nodiscard]] const char* what() const noexcept override { return message().cStr(); }
};