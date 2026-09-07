#ifndef INPROGRESSSTATE_H
#define INPROGRESSSTATE_H

#include "TaskState.h"

class InProgressState : public TaskState
{
    public:
        virtual ~InProgressState() {}

        virtual void start(Task& task) override;
        virtual void complete(Task& task) override;
        virtual void execute(Task& task) override;

        virtual std::string getStatus() const override;
};

#endif