#ifndef PRIORITYDECORATOR_H 
#define PRIORITYDECORATOR_H 

#include "TaskDecorator.h"
#include <iostream>

class PriorityDecorator: public TaskDecorator{
    private:
    //PRIORITIES ARE ASSIGNED IN ASCENDING ORDER 
    //PRIORITIES ARE = TO GROUPS AND ARE GROUPED IN ORDER OF PRIORITY
    //HIGHEST PRIORITY = 0
    //LOWER PRIORITY = N
        int priority;

    public:
        PriorityDecorator(std::shared_ptr<TaskComponent> task, int level);
        virtual ~PriorityDecorator();

        virtual std::string getName()const override;
        virtual void display(int depth = 0)const override;

        int getPriority()const;
        void setPriority(int level);

};

#endif 