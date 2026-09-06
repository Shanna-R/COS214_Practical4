#ifndef TASKCOMPONENT_H
#define TASKCOMPONENT_H

#include <string>

class Iterator;

class TaskComponent
{
    public:
        virtual ~TaskComponent();

        virtual std::string getName() const = 0;
        virtual void display(int depth = 0) const = 0;

        virtual bool isGroup() const = 0;
};

#endif