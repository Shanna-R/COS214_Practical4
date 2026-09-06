#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H

#include "TaskComponent.h"
#include <memory>

class TaskDecorator:public TaskComponent{
    protected:
        std::shared_ptr<TaskComponent> wrappedTask;

    public:
        TaskDecorator(std::shared_ptr<TaskComponent> task);
        virtual ~TaskDecorator();

        virtual std::string getName()const override;
        virtual void display(int depth = 0)const override;
        virtual bool isGroup()const override;

};

#endif 