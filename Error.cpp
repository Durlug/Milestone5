//OOP244 Assignment
//Milestone 2
//Error.cpp
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca


#include "Error.h"
#include <cstring>
namespace ict 
{

	Error::Error() 
	{
		message_ = nullptr;
	}

	Error::Error(const char* Error)
	{
		message_ = nullptr;
		message(Error);
	}

	Error::~Error()
	{
		delete[] message_;
	}

	
	Error& Error::operator=(const char* errorMessage) 
	{
		clear();           //De-allocating the memory pointed by message_
		message(errorMessage); //Allocating memory

		return *this;
	}

	void Error::clear()
	{
		delete[] message_;
		message_ = nullptr;
	}

	bool Error::isClear() const
	{
		if (message_ == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Error::message(const char* value)
	{
		clear();                                    //De-allocating the memory pointed by message_
		message_ = new char[strlen(value) + 1];     //Setting message to new char with length of string value + 1
		strcpy(message_, value);                    //Copying value argument into message_ variable
	}

	const char* Error::message() const              //Getter function to return string stored in message
	{
		return message_;
	}

	std::ostream& operator<<(std::ostream& os, const Error& other)
	{
		if (!other.isClear())                  
		{
			os << other.message();
		}
		return os;
	}


}