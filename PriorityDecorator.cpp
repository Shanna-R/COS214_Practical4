#include "PriorityDecorator.h"

PriorityDecorator::PriorityDecorator(std::shared_ptr<TaskComponent> task, int level):TaskDecorator(task){
    this->priority = level;
}

PriorityDecorator::~PriorityDecorator(){
    //NOTHING TO DO HERE
}

std::string PriorityDecorator::getName()const{
    return TaskDecorator::getName() + "[PRIORITY LEVEL: " + std::to_string(this->getPriority()) + "]";
}

void PriorityDecorator::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }
    std::cout << "[PRIORITY " << this->priority << "] ";
    if (wrappedTask)
    {
        TaskDecorator::wrappedTask->display(0);
    }
}

int PriorityDecorator::getPriority() const
{
    return this->priority;
}

void PriorityDecorator::setPriority(int level)
{
    this->priority = level;
}