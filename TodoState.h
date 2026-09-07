#ifndef TODOSTATE_H
#define TODOSTATE_H

#include "TaskState.h"

class TodoState : public TaskState
{
    public:
        virtual ~TodoState() {}

        virtual void start(Task& task) override;
        virtual void complete(Task& task) override;
        virtual void execute(Task& task) override;

        virtual std::string getStatus() const override;
};

#endif