#include "CompletedState.h"
#include "Task.h"

#include <iostream>

void CompletedState::start(Task& task)
{
    std::cout << "[STATE] Cannot start '" << task.getName() << "' because it is already COMPLETED." << std::endl;
}

void CompletedState::complete(Task& task)
{
    std::cout << "[STATE] '" << task.getName() << "' is already COMPLETED." << std::endl;
}

void CompletedState::execute(Task& task)
{
    std::cout << "[STATE] '" << task.getName() << "' is already completed. No further execution required." << std::endl;
}

std::string CompletedState::getStatus() const
{
    return "COMPLETED";
}