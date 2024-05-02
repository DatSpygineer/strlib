#pragma once

#include <optional>
#include "string.hpp"

template<typename ...T>
inline void Print(const String& message, T&&... args) {
	printf("%s", String::Format(message, args...).cStr());
}
template<typename ...T>
inline void PrintLn(const String& message, T&&... args) {
	printf("%s\n", String::Format(message, args...).cStr());
}

#if !defined(STRLIB_FILESYS) || STRLIB_FILESYS == 1

enum class FileMode : uint8_t {
	Read,
	ReadOrCreate,
	Write,
	Append,
	ReadWrite,
	ReadAppend
};

enum class FileSeekOrigin : uint8_t {
	Begin = SEEK_SET,
	Current = SEEK_CUR,
	End = SEEK_END
};

class File;
class Directory;

enum class SpecialDirectory {
	MyDocuments,
	MyPictures,
	MyMusic,
	MyVideos,
	Desktop,
	UserProfile,
	Home = UserProfile,
	Appdata,
	LocalAppdata,
	CommonAppdata,
	ProgramData = CommonAppdata,
	ProgramFiles,
	ProgramFilesX86,
	Temp
};

class STRLIB_API Path {
	String m_sInternalString;
public:
	Path(): m_sInternalString() { }
	Path(const String& str): m_sInternalString(str) { } // NOLINT: Implicit conversion intended
	Path(Path&& path) noexcept: m_sInternalString(std::move(path.m_sInternalString)) { path.m_sInternalString = ""; }
	Path(const Path& path) = default;

	Path& operator= (const Path& path) = default;
	inline Path& operator= (Path&& path) noexcept {
		m_sInternalString = std::move(path.m_sInternalString);
		path.m_sInternalString = "";
		return *this;
	}

	Path& append(const String& str);
	Path& append(const Path& path);
	Path& append(String&& str);
	Path& append(Path&& path);

	[[nodiscard]] bool exists() const;
	[[nodiscard]] String name(bool containExtension = false) const;
	[[nodiscard]] String extension() const;
	[[nodiscard]] Path parent() const;
	[[nodiscard]] Path toAbsolute() const;
	[[nodiscard]] inline constexpr bool isEmpty() const { return m_sInternalString.isEmpty(); }
	[[nodiscard]] bool hasExtension() const;

	[[nodiscard]] bool isAbsolute() const;
	[[nodiscard]] bool isRelative() const;

	[[nodiscard]] bool isFile() const;
	[[nodiscard]] bool isDirectory() const;
	[[nodiscard]] bool isSymLink() const;
	[[nodiscard]] bool isSocket() const;
	[[nodiscard]] bool isFIFO() const;
	[[nodiscard]] bool isBlockFile() const;
	[[nodiscard]] bool isCharacterFile() const;

	[[nodiscard]] bool matches(const String& pattern) const;

	bool remove(bool recursive) const;
	bool move(const Path& dest) const;
	inline constexpr bool rename(const Path& dest) const { return move(dest); }
	bool copy(const Path& dest) const;

	[[nodiscard]] inline String& asString() { return m_sInternalString; }
	[[nodiscard]] inline constexpr const String& asString() const { return m_sInternalString; }
	[[nodiscard]] inline constexpr const std::string& stdStr() const { return m_sInternalString.stdStr(); }
	[[nodiscard]] inline const char* cStr() const { return m_sInternalString.cStr(); }

	static Path Join(const std::initializer_list<Path>& paths);

	Path operator/ (Path&& other) const;
	Path operator/ (const Path& other) const;
	Path operator/ (String&& other) const;
	Path operator/ (const String& other) const;
	Path& operator/= (Path&& other);
	Path& operator/= (const Path& other);
	Path& operator/= (String&& other);
	Path& operator/= (const String& other);
	Path operator+ (Path&& other) const;
	Path operator+ (const Path& other) const;
	Path operator+ (String&& other) const;
	Path operator+ (const String& other) const;
	Path& operator+= (Path&& other);
	Path& operator+= (const Path& other);
	Path& operator+= (String&& other);
	Path& operator+= (const String& other);

	inline constexpr bool operator== (const Path& path) const { return m_sInternalString == path.m_sInternalString; }
	inline constexpr bool operator!= (const Path& path) const { return m_sInternalString == path.m_sInternalString; }

	[[nodiscard]] inline explicit operator const String&() const { return m_sInternalString; }

	static Path CurrentPath();
	static Path TempPath();
	static Path GetSpecialPath(SpecialDirectory directory);
};

class STRLIB_API File {
	FILE* m_pFile;
public:
	File(): m_pFile(nullptr) { }
	File(const Path& path, FileMode mode, bool binary = false);
	~File();

	[[nodiscard]] char read() const;
	[[nodiscard]] String readToEnd() const;
	size_t readBytes(std::vector<uint8_t>& data, size_t n) const;
	[[nodiscard]] String readLine() const;

	template<typename T>
	bool read(T& result) const;
	template<typename T>
	bool read(std::vector<T>& result, size_t count) const;

	bool write(char c) const;
	bool write(const String& str) const;
	bool writeLine(const String& str) const;
	bool writeBytes(const std::vector<uint8_t>& data) const;

	template<typename T>
	bool writeObject(const T& result);
	template<typename T>
	bool writeObjects(const std::vector<T>& result);

	[[nodiscard]] size_t size() const;

	[[nodiscard]] inline constexpr bool seek(FileSeekOrigin origin, int offset) const {
		return fseek(m_pFile, static_cast<long>(origin), offset) >= 0;
	}
	[[nodiscard]] inline constexpr size_t tell() const { return ftell(m_pFile); }
	[[nodiscard]] inline constexpr size_t position() const { return ftell(m_pFile); }

	inline constexpr void flush() const { fflush(m_pFile); }
	[[nodiscard]] inline constexpr bool eof() const { return feof(m_pFile) != 0; }

	[[nodiscard]] inline constexpr bool hasError() const { return ferror(m_pFile); }

	[[nodiscard]] inline constexpr bool isOpen() const { return m_pFile != nullptr; }
	void close();
};

class STRLIB_API Directory {
	Path m_path;
public:
	explicit Directory(Path&& path) noexcept: m_path(std::move(path)) { }
	explicit Directory(const Path& path): m_path(path) { }
	Directory(Directory&& directory) noexcept = default;
	Directory(const Directory& directory) = default;

	[[nodiscard]] bool exists() const;
	bool create(bool recursive) const;
	bool remove(bool recursive) const;

	[[nodiscard]] std::vector<Path> files(const String& pattern = "*.*") const;
};


inline Path operator""_P(const char* cstr, size_t len) { return Path { String {cstr, len}}; }
template<>
struct STRLIB_API fmt::formatter<Path> : fmt::formatter<std::string_view> {
	auto format(const Path& path, fmt::format_context& ctx) const {
		return fmt::formatter<std::string_view>::format(path.asString().stdStr(), ctx);
	}
};

#ifdef STRLIB_HEADER_ONLY
	#ifndef STRLIB_IO_IMPL
		#define STRLIB_IO_IMPL
		#include "io.cpp"
	#endif
#endif

#endif