#pragma once
#include <iostream>

class Exception : public std::exception {
protected:
	char* str;
public:
	Exception(const char* s) {
		str = new char[strlen(s)];
		strcpy_s(str, strlen(s) + 1, s);
	}
	void print() const {
		std::cout << "\nException" << str;
	}
};

class InvalidLengthException : public Exception {
public:
	InvalidLengthException(const char* s) : Exception(s) {}
	void print() const {
		std::cout << "\nInvalidLengthException" << str;
	}
};

class NotEnoughSpaceException : public Exception {
public:
	NotEnoughSpaceException(const char* s) : Exception(s) {}
	void print() const {
		std::cout << "\nNotEnoughSpaceException" << str;
	}
};

class NullptrException : public Exception {
public:
	NullptrException(const char* s) : Exception(s) {}
	void print() const {
		std::cout << "\nNullptrException" << str;
	}
};