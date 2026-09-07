#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "TaskState.h"

class CompletedState : public TaskState
{
    public:
        virtual ~CompletedState() {}

        virtual void start(Task& task) override;
        virtual void complete(Task& task) override;
        virtual void execute(Task& task) override;

        virtual std::string getStatus() const override;
};

#endif