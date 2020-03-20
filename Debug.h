#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

namespace GAME {
	/// This enum is a simple 8-bit unsigned char
	enum class EMessageType : unsigned char {
		INFO = 0,
		WARNING,
		ERROR,
		FATAL_ERROR
	};

	class Debug {
	public:
		/// New in C11: this deletes the automatic constructor from being formed if no other constructor is decleared 
		Debug() = delete;

		/// Since I'm going C11 nutts - let's kill any default constructor or operator that the compiler might create
		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator=(const Debug&) = delete;
		Debug& operator=(Debug&&) = delete;


		static void Init();
		static void Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line);
	};
}

#endif