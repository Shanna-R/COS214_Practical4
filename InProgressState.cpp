#include "InProgressState.h"
#include "CompletedState.h"
#include "Task.h"

#include <iostream>
#include <memory>

void InProgressState::start(Task& task)
{
    std::cout << "[STATE] '" << task.getName() << "' is already IN_PROGRESS." << std::endl;
}

void InProgressState::complete(Task& task)
{
    std::cout << "[STATE] " << task.getName() << ": IN_PROGRESS -> COMPLETED" << std::endl;

    task.setState(std::unique_ptr<TaskState>(new CompletedState()));
}

void InProgressState::execute(Task& task)
{
    std::cout << "[STATE] Executing software task: " << task.getName() << std::endl;
}

std::string InProgressState::getStatus() const
{
    return "IN_PROGRESS";
}