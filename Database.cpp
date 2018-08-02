#include "Database.hpp"
#include <algorithm>
#include <iostream>
#include <functional>

NotFound::NotFound(const std::string &message)
    : std::out_of_range(message)
{}

bool Database::addPerson(Person* person)
{
    people_.push_back(person);
}

Person* Database::findByName(const std::string & lastName) const
{
    return find([lastName](auto item){ return item->getLastName() == lastName; });
}

Person* Database::findByPesel(const std::string & pesel) const
{
    return find([pesel](auto item){ return item->getPesel() == pesel; });
}

Person* Database::find(std::function<bool(People::value_type)> what) const
{
    auto it = std::find_if(people_.begin(), people_.end(), what);
    if (it != people_.end())
    {
        return *it;
    }
    throw NotFound("Does not exist");
}

void Database::show() const
{
    std::cout << "=== DATABASE: ===" << std::endl;
    for(const auto & person : people_)
    {
        person->show();
    }
}

void Database::sort(SortCriteria criterion)
{
    switch (criterion)
    {
    case SortCriteria::LastName: { sortByName(); break; }
    case SortCriteria::Pesel:    { sortByPesel(); break; }
    case SortCriteria::Salary:   { sortBySalary(); break; }
    }
}

void Database::sortByName()
{
    std::sort(people_.begin(), people_.end(), [](Person* lhs, Person* rhs)
    {
        return lhs->getLastName() < rhs->getLastName();
    });
}
void Database::sortByPesel()
{
    std::sort(people_.begin(), people_.end(), [](Person* lhs, Person* rhs)
    {
        return lhs->getPesel() < rhs->getPesel();
    });
}

void Database::sortBySalary()
{
    std::sort(people_.begin(), people_.end(), [](Person* lhs, Person* rhs)
    {
        return lhs->getSalary() >= rhs->getSalary();
    });
}
