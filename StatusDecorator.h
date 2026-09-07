#ifndef STATUSDECORATOR_H
#define STATUSDECORATOR_H

#include "TaskDecorator.h"
#include <string>
#include "TaskStatus.h"

class StatusDecorator : public TaskDecorator
{
    private:
        TaskStatus status;

    public:
        StatusDecorator(std::shared_ptr<TaskComponent> task, TaskStatus status = TaskStatus::IN_PROGRESS);
        virtual ~StatusDecorator();

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;

        TaskStatus getStatus() const;
        void setStatus(TaskStatus newStatus);
};

#endif