#include "TaskDecorator.h"

TaskDecorator::TaskDecorator(std::shared_ptr<TaskComponent> task){
    this->wrappedTask = task;
}

TaskDecorator::~TaskDecorator(){
//SHARED POINTER SO DO NOT DELETE HERE     
}

std::string TaskDecorator::getName()const{
    if(this->wrappedTask){
        return this->wrappedTask->getName();
    }
    return "";
}

void TaskDecorator::display(int depth)const{
    if(this->wrappedTask){
        this->wrappedTask->display(depth);
    }
}

bool TaskDecorator::isGroup()const{
    if(this->wrappedTask){
        return this->wrappedTask->isGroup();
    }
    return false;
}

