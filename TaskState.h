#ifndef TASKSTATE_H
#define TASKSTATE_H

#include <string>

class Task;

class TaskState
{
    public:
        virtual ~TaskState() {}

        virtual void start(Task& task) = 0;
        virtual void complete(Task& task) = 0;
        virtual void execute(Task& task) = 0;

        virtual std::string getStatus() const = 0;
};

#endif