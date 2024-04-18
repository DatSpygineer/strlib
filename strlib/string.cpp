#include "string.hpp"

#include <cstdlib>
#include <cstring>
#include <locale>
#include <codecvt>

#ifndef __GNUC__
	#define strcasecmp _stricmp
	#define strncasecmp _strnicmp
#endif

static const char* STRLIB_MONTH_NAMES[] = {
	"January", "February",
	"March", "April", "May",
	"June", "July", "August",
	"September", "October", "November",
	"December"
};
static const char* STRLIB_MONTH_NAMES_ABR[] = {
	"Jan", "Feb",
	"Mar", "Apr", "May",
	"Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov",
	"Dec"
};
static const char* STRLIB_DAY_NAMES[] = {
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};
static const char* STRLIB_DAY_NAMES_ABR[] = {
	"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};

String::String(char c, size_t n): m_sString(n, '\0') {
	std::memset(m_sString.data(), c, n * sizeof(char));
}

String& String::operator=(String&& other) noexcept {
	m_sString = std::move(other.m_sString);
	other.m_sString = "";

	return *this;
}

String String::trimStart(const String& chars) const {
	size_type idx = findFirstNotOf(chars);
	if (idx == NoFind) {
		return "";
	}
	return substr(idx);
}
String String::trimEnd(const String& chars) const {
	size_type idx = findLastNotOf(chars);
	if (idx == NoFind) {
		return "";
	}
	return substr(0, idx + 1);
}
String String::trim(const String& chars) const {
	return trimStart(chars).trimEnd(chars);
}

String String::toLowercase() const {
	String str = *this;
	for (char& c : str) {
		if (c >= 'A' && c <= 'Z') {
			c += ('a' - 'A');
		}
	}
	return str;
}
String String::toUppercase() const {
	String str = *this;
	for (char& c : str) {
		if (c >= 'a' && c <= 'z') {
			c -= ('a' - 'A');
		}
	}
	return str;
}

String::iterator String::insert(size_t at, char c) {
	return insert(begin() + static_cast<std::string::difference_type>(at), c);
}
String::iterator String::insert(size_t at, const String& str) {
	m_sString.insert(at, str.m_sString);
	return begin() + static_cast<std::string::difference_type>(at);
}
String::iterator String::insert(const String::iterator& at, char c) {
	return m_sString.insert(at, c);
}
String::iterator String::insert(const String::iterator& at, const String& str) {
	return insert(std::distance(begin(), at), str);
}

String::iterator String::erase(const String::iterator& at) {
	return m_sString.erase(at);
}
String::iterator String::erase(const String::iterator& beg, const String::iterator& end) {
	return m_sString.erase(beg, end);
}
String::iterator String::erase(size_t at) {
	return m_sString.erase(begin() + static_cast<std::string::difference_type>(at));
}
String::iterator String::erase(size_t at, size_t n) {
	return m_sString.erase(begin() + static_cast<std::string::difference_type>(at), begin() + static_cast<std::string::difference_type>(at + n));
}

String& String::replace(size_t at, size_t n, const String& replacement) {
	m_sString.replace(at, n, replacement.m_sString);
	return *this;
}
String& String::replace(const String::iterator& beg, const String::iterator& end, const String& replacement) {
	m_sString.replace(beg, end, replacement.m_sString);
	return *this;
}
String& String::replace(const String& to_replace, const String& replacement) {
	size_t idx = find(to_replace);
	if (idx != NoFind) {
		replace(idx, to_replace.length(), replacement);
	}
	return *this;
}
String& String::replaceAll(const String& to_replace, const String& replacement) {
	size_t idx;
	while ((idx = find(to_replace)) != NoFind) {
		replace(idx, to_replace.length(), replacement);
	}
	return *this;
}

String String::replaceCopy(size_t at, size_t n, const String& replacement) const {
	String str = *this;
	str.replace(at, n, replacement);
	return str;
}
String String::replaceCopy(const iterator& beg, const iterator& end, const String& replacement) const {
	String str = *this;
	str.replace(beg, end, replacement);
	return str;
}
String String::replaceCopy(const String& to_replace, const String& replacement) const {
	String str = *this;
	str.replace(to_replace, replacement);
	return str;
}
String String::replaceAllCopy(const String& to_replace, const String& replacement) const {
	String str = *this;
	str.replaceAll(to_replace, replacement);
	return str;
}

String& String::removePrefix(const String& prefix) {
	if (startsWith(prefix)) {
		erase(0, prefix.length());
	}

	return *this;
}
String& String::removeSuffix(const String& suffix) {
	if (endsWith(suffix)) {
		erase(length() - suffix.length() - 1, suffix.length());
	}

	return *this;
}
String& String::removePrefix(char prefix) {
	if (startsWith(prefix)) {
		erase(0);
	}
	return *this;
}
String& String::removeSuffix(char suffix) {
	if (endsWith(suffix)) {
		erase(length() - 1);
	}
	return *this;
}

String String::withoutPrefix(const String& prefix) const {
	if (startsWith(prefix)) {
		return substr(prefix.length());
	}
	return *this;
}
String String::withoutSuffix(const String& suffix) const {
	if (endsWith(suffix)) {
		return substr(0, length() - suffix.length() - 1);
	}
	return *this;
}
String String::withoutPrefix(char prefix) const {
	if (startsWith(prefix)) {
		return substr(1);
	}
	return *this;
}
String String::withoutSuffix(char suffix) const {
	if (endsWith(suffix)) {
		return substr(0, length() - 1);
	}
	return *this;
}

int String::compare(const String& other) const {
	return std::strcmp(m_sString.data(), other.m_sString.data());
}
int String::compare(const String& other, size_t n) const {
	return std::strncmp(m_sString.data(), other.m_sString.data(), n);
}
int String::compare(const String& other, size_t offset, size_t n) const {
	return std::strncmp(m_sString.data(), other.m_sString.data() + offset, n);
}
int String::compare(const String& other, size_t this_offset, size_t offset, size_t n) const {
	return std::strncmp(m_sString.data() + this_offset, other.m_sString.data() + offset, n);
}

int String::compareNoCase(const String& other) const {
	return strcasecmp(m_sString.data(), other.m_sString.data());
}
int String::compareNoCase(const String& other, size_t n) const {
	return strncasecmp(m_sString.data(), other.m_sString.data(), n);
}
int String::compareNoCase(const String& other, size_t offset, size_t n) const {
	return strncasecmp(m_sString.data(), other.m_sString.data() + offset, n);
}
int String::compareNoCase(const String& other, size_t this_offset, size_t offset, size_t n) const {
	return strncasecmp(m_sString.data() + this_offset, other.m_sString.data() + offset, n);
}

bool String::parse(signed char& value, int base) const {
	try {
		value = static_cast<signed char>(std::stoi(m_sString, nullptr, base));
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(short& value, int base) const {
	try {
		value = static_cast<short>(std::stoi(m_sString, nullptr, base));
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(int& value, int base) const {
	try {
		value = std::stoi(m_sString, nullptr, base);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(long& value, int base) const {
	try {
		value = std::stol(m_sString, nullptr, base);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(long long& value, int base) const {
	try {
		value = std::stoll(m_sString, nullptr, base);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(unsigned char& value, int base) const {
	try {
		value = static_cast<unsigned char>(std::stoul(m_sString, nullptr, base));
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(unsigned short& value, int base) const {
	try {
		value = static_cast<unsigned short>(std::stoul(m_sString, nullptr, base));
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(unsigned int& value, int base) const {
	try {
		value = static_cast<unsigned int>(std::stoul(m_sString, nullptr, base));
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(unsigned long& value, int base) const {
	try {
		value = std::stoul(m_sString, nullptr, base);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(unsigned long long& value, int base) const {
	try {
		value = std::stoull(m_sString, nullptr, base);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(float& value) const {
	try {
		value = std::stof(m_sString);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(double& value) const {
	try {
		value = std::stod(m_sString);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}
bool String::parse(long double& value) const {
	try {
		value = std::stold(m_sString);
	} catch (const std::exception& _) {
		return false;
	}
	return true;
}

std::wstring String::stdWStr() const {
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(m_sString);
}

String String::FromChar(char value) {
	return { value, 1 };
}
String String::FromWString(const std::wstring& str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	return convert.to_bytes(str);
}
String String::FromWChar(wchar_t value) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	wchar_t temp[2] = { value, 0 };
	return convert.to_bytes(temp);
}

const size_t String::NoFind = std::string::npos;

std::vector<String> String::split(char delim) const {
	String str = *this;
	std::vector<String> tokens;

	size_t idx;
	while ((idx = str.find(delim)) != NoFind) {
		tokens.push_back(str.substr(0, idx));
		str.erase(0, idx);
	}

	if (!str.isEmpty()) {
		tokens.push_back(std::move(str));
	}
	return tokens;
}
std::vector<String> String::split(const String& delim) const {
	String str = *this;
	std::vector<String> tokens;

	size_t idx;
	while ((idx = str.find(delim)) != NoFind) {
		tokens.push_back(str.substr(0, idx));
		str.erase(0, idx + delim.length());
	}

	if (!str.isEmpty()) {
		tokens.push_back(std::move(str));
	}
	return tokens;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.m_sString;
	return os;
}
std::istream& operator>>(std::istream& is, String& string) {
	is >> string.m_sString;
	return is;
}

String String::From(uint8_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(uint16_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(uint32_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(uint64_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(int8_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(int16_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(int32_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}
String String::From(int64_t value, int base) {
	switch (base) {
		case 2: {
			return String { fmt::format("{:b}", value) };
		}
		case 8: {
			return String { fmt::format("{:o}", value) };
		}
		case 16: {
			return String { fmt::format("{:X}", value) };
		}
		default: {
			return String { fmt::format("{:d}", value) };
		}
	}
}

String String::From(float value) {
	String result('\0', snprintf(nullptr, 0, "%g", value));
	snprintf(result.data(), result.capacity(), "%g", value);
	return result;
}
String String::From(double value) {
	String result('\0', snprintf(nullptr, 0, "%lg", value));
	snprintf(result.data(), result.capacity(), "%lg", value);
	return result;
}
String String::From(long double value) {
	String result('\0', snprintf(nullptr, 0, "%Lg", value));
	snprintf(result.data(), result.capacity(), "%Lg", value);
	return result;
}
String String::From(bool value) {
	return value ? "true" : "false";
}
String String::Date(const String& format) {
	String result = format;
	auto t = time(nullptr);
	auto tm = localtime(&t);

	if (tm == nullptr) {
		throw Exception("Failed to get current date!");
	}

	result.replaceAll("yyyy", String::From(tm->tm_year + 1900));
	result.replaceAll("YYYY", String::From(tm->tm_year + 1900));
	result.replaceAll("yy", String::From(tm->tm_year + 1900).substr(0, 2));
	result.replaceAll("YY", String::From(tm->tm_year + 1900).substr(0, 2));
	result.replaceAll("MMMM", String { STRLIB_MONTH_NAMES[tm->tm_mon] });
	result.replaceAll("MMM", String { STRLIB_MONTH_NAMES_ABR[tm->tm_mon] });
	result.replaceAll("MM", String::Format("{:02d}", tm->tm_mon + 1));
	result.replaceAll("M", String::From(tm->tm_mon + 1));
	result.replaceAll("DDDD", String { STRLIB_DAY_NAMES[tm->tm_wday] });
	result.replaceAll("DDD", String { STRLIB_DAY_NAMES_ABR[tm->tm_wday] });
	result.replaceAll("DD", String::Format("{:02d}", tm->tm_mday));
	result.replaceAll("D", String::From(tm->tm_mday));
	result.replaceAll("dddd", String { STRLIB_DAY_NAMES[tm->tm_wday] });
	result.replaceAll("ddd", String { STRLIB_DAY_NAMES_ABR[tm->tm_wday] });
	result.replaceAll("dd", String::Format("{:02d}", tm->tm_mday));
	result.replaceAll("d", String::From(tm->tm_mday));

	result.replaceAll("HH", String::Format("{:02d}",tm->tm_hour));
	result.replaceAll("H", String::From(tm->tm_hour + 1));
	result.replaceAll("hh", String::Format("{:02d}",tm->tm_hour > 12 ? tm->tm_hour - 12 : tm->tm_hour));
	result.replaceAll("h", String::From(tm->tm_hour > 12 ? tm->tm_hour - 12 : tm->tm_hour));
	result.replaceAll("mm", String::Format("{:02d}", tm->tm_min));
	result.replaceAll("m", String::From((tm->tm_min + 1)));
	result.replaceAll("ss", String::Format("{:02d}",tm->tm_sec));
	result.replaceAll("s", String::From(tm->tm_sec));

	result.replaceAll("T", String { (tm->tm_hour >= 11 && tm->tm_hour < 23) ? "pm" : "am" });

	return result;
}

std::istream& String::GetLine(std::istream& is, String& line) {
	std::string stdLine;
	return std::getline(is, stdLine);
}
