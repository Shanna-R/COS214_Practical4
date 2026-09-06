#include "Task.h"

#include <iostream>

Task::Task(const std::string& name)
    : name(name)
{
}

Task::~Task()
{
}

std::string Task::getName() const
{
    return name;
}

void Task::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }

    std::cout << "- " << name << std::endl;
}

bool Task::isGroup() const
{
    return false;
}