#include "Task.h"
#include "TaskState.h"
#include "TodoState.h"

#include <iostream>
#include <memory>

Task::Task(const std::string& name) : name(name), state(std::unique_ptr<TaskState>(new TodoState()))
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
    for(int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }

    std::cout << "- " << name << " [" << getStatus() << "]" << std::endl;
}

bool Task::isGroup() const
{
    return false;
}

void Task::start()
{
    state->start(*this);
}

void Task::complete()
{
    state->complete(*this);
}

void Task::execute()
{
    state->execute(*this);
}

std::string Task::getStatus() const
{
    return state->getStatus();
}

void Task::setState(std::unique_ptr<TaskState> newState)
{
    if(newState)
    {
        state = std::move(newState);
    }
}