#include "TaskGroup.h"
#include "TaskIterator.h"

#include <iostream>

TaskGroup::TaskGroup(const std::string& name)
    : name(name)
{
}

TaskGroup::~TaskGroup()
{
}

void TaskGroup::add(
    const std::shared_ptr<TaskComponent>& component
)
{
    if (component)
    {
        children.push_back(component);
    }
}

bool TaskGroup::remove(const std::string& componentName)
{
    for (std::vector<std::shared_ptr<TaskComponent> >::iterator it =
             children.begin();
         it != children.end();
         ++it)
    {
        if ((*it)->getName() == componentName)
        {
            children.erase(it);
            return true;
        }
    }

    return false;
}

std::string TaskGroup::getName() const
{
    return name;
}

void TaskGroup::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }

    std::cout << "+ " << name << std::endl;

    for (std::vector<std::shared_ptr<TaskComponent> >::const_iterator it =
             children.begin();
         it != children.end();
         ++it)
    {
        (*it)->display(depth + 1);
    }
}

bool TaskGroup::isGroup() const
{
    return true;
}

std::unique_ptr<TaskIterator>
TaskGroup::createDepthFirstIterator() const
{
    return std::unique_ptr<TaskIterator>(
        new TaskIterator(this, TaskIterator::DEPTH_FIRST)
    );
}

std::unique_ptr<TaskIterator>
TaskGroup::createBreadthFirstIterator() const
{
    return std::unique_ptr<TaskIterator>(
        new TaskIterator(this, TaskIterator::BREADTH_FIRST)
    );
}