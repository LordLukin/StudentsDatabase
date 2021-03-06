#pragma once
#include "Person.hpp"
#include <string>

class Student : public Person
{
public:
    Student(const std::string & name,
            const std::string & lastName,
            const std::string & pesel,
            Gender gender,
            const std::string & address,
            int index);
    Student(const std::string & packedData);
    std::string toString(char delimeter = ' ') const override;
    int getIndex() const;

private:
    int index_;
};
