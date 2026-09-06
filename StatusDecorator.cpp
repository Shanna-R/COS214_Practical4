#include "StatusDecorator.h"
#include <iostream>

StatusDecorator::StatusDecorator(std::shared_ptr<TaskComponent> task, TaskStatus status):TaskDecorator(task){
    this->status = status;
}

StatusDecorator::~StatusDecorator()
{
}

std::string StatusDecorator::getName() const
{
    return TaskDecorator::getName() + " (" + statusToString(this->status) + ")";
}

void StatusDecorator::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }
    std::cout << "STATUS [" << statusToString(this->status) << "] ";
    if (wrappedTask)
    {
        wrappedTask->display(0);
    }
}

TaskStatus StatusDecorator::getStatus() const
{
    return this->status;
}

void StatusDecorator::setStatus(TaskStatus newStatus)
{
    this->status = newStatus;
}