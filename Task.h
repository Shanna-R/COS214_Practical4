#ifndef TASK_H
#define TASK_H

#include "TaskComponent.h"

#include <memory>
#include <string>

class TaskState;

class Task : public TaskComponent
{
    private:
        std::string name;
        std::unique_ptr<TaskState> state;

    public:
        Task(const std::string& name);
        virtual ~Task();

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;
        virtual bool isGroup() const override;

        // State-related behaviour
        void start();
        void complete();
        void execute();

        std::string getStatus() const;

        // Used by concrete states to change the Context's state
        void setState(std::unique_ptr<TaskState> newState);
};

#endif