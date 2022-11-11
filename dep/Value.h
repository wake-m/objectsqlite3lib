#ifndef VALUE_H
#define VALUE_H
#include<iostream>
#include<string>
class Value
{
public:
	Value();
	~Value();
	Value(int value);
	Value(bool value);
	Value(double value);
	Value(const char* value);
	Value(const std::string& value);


	Value& operator = (int value);
	Value& operator = (bool value);
	Value& operator = (double value);
	Value& operator = (const char* value);
	Value& operator = (const std::string& value);


	operator int();
	operator bool();
	operator double();
	operator char();
	operator std::string();
private:
	std::string m_Value;
};

#endif // !VALUE_H