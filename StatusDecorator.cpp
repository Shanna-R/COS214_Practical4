#include "StatusDecorator.h"
#include <iostream>

StatusDecorator::StatusDecorator(std::shared_ptr<TaskComponent> task, const std::string& status):TaskDecorator(task){
    this->status = status;
}

StatusDecorator::~StatusDecorator()
{
}

std::string StatusDecorator::getName() const
{
    return TaskDecorator::getName() + " (" + this->status + ")";
}

void StatusDecorator::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }
    std::cout << "STATUS [" << this->status << "] ";
    if (wrappedTask)
    {
        wrappedTask->display(0);
    }
}

std::string StatusDecorator::getStatus() const
{
    return this->status;
}

void StatusDecorator::setStatus(const std::string& newStatus)
{
    this->status = newStatus;
}