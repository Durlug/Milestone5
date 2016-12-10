//OOP244 Assignment
//Milestone 2
//Error.h
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca


#ifndef SICT_ERROR_H__
#define SICT_ERROR_H__
#include <iostream>
namespace ict 
{
	class Error 
	{
	protected:
		char* message_;

	public:
		Error();
		Error(const char* Error);
		Error(const Error& em) = delete;
		virtual ~Error();
		Error& operator=(const Error& em) = delete;
		Error& operator=(const char* errorMessage);
		void clear();
		bool isClear() const;
		void message(const char* value);
		const char* message() const;

		

	};
	// operator<< overload prototype
	std::ostream& operator<<(std::ostream& os, const Error& other);
}
#endif
