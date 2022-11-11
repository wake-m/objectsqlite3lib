#include "Value.h"

Value::Value()
{
}

Value::~Value()
{
}

Value::Value(int value)
{
    *this = value;
}

Value::Value(bool value)
{
    *this = value;
}

Value::Value(double value)
{
    *this = value;
}

Value::Value(const char* value)
{
    *this = value;
}

Value::Value(const std::string& value)
{
    *this = value;
}

Value& Value::operator=(int value)
{
    this->m_Value = std::to_string(value);
    return *this;
}

Value& Value::operator=(bool value)
{
    this->m_Value = value ? "true" : "false";
    return *this;
}

Value& Value::operator=(double value)
{
    this->m_Value = std::to_string(value);
    return *this;
}

Value& Value::operator=(const char* value)
{
    this->m_Value = value;
    return *this;
}

Value& Value::operator=(const std::string& value)
{
    this->m_Value = value;
    return *this;
}

Value::operator bool() {

    return this->m_Value == "true";
}

Value::operator int() {
    return std::atoi(this->m_Value.c_str());
}

Value::operator char() {
    return *this->m_Value.c_str();
}

Value::operator double() {
    return std::atof(this->m_Value.c_str());
}

Value::operator std::string() {
    return this->m_Value;
}