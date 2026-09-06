#ifndef TASK_H
#define TASK_H

#include "TaskComponent.h"

class Task : public TaskComponent
{
    private:
        std::string name;

    public:
        Task(const std::string& name);
        virtual ~Task();

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;
        virtual bool isGroup() const override;
};

#endif