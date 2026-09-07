#include "TodoState.h"
#include "InProgressState.h"
#include "Task.h"

#include <iostream>
#include <memory>

void TodoState::start(Task& task)
{
    std::cout << "[STATE] " << task.getName() << ": TODO -> IN_PROGRESS" << std::endl;

    task.setState(std::unique_ptr<TaskState>(new InProgressState()));
}

void TodoState::complete(Task& task)
{
    std::cout << "[STATE] Cannot complete '" << task.getName() << "' because it has not been started." << std::endl;
}

void TodoState::execute(Task& task)
{
    std::cout << "[STATE] Cannot execute '" << task.getName() << "' while it is TODO. Start the task first." << std::endl;
}

std::string TodoState::getStatus() const
{
    return "TODO";
}