#include "TaskIterator.h"
#include "TaskComponent.h"
#include "TaskGroup.h"

#include <deque>
#include <stdexcept>

TaskIterator::TaskIterator(
    const TaskGroup* root,
    TraversalOrder order
)
    : currentIndex(0)
{
    if (root == 0)
    {
        return;
    }

    if (order == DEPTH_FIRST)
    {
        for (std::vector<std::shared_ptr<TaskComponent> >::const_iterator it =
                 root->children.begin();
             it != root->children.end();
             ++it)
        {
            addDepthFirst(*it);
        }
    }
    else
    {
        std::deque<std::shared_ptr<TaskComponent> > queue;

        for (std::vector<std::shared_ptr<TaskComponent> >::const_iterator it =
                 root->children.begin();
             it != root->children.end();
             ++it)
        {
            queue.push_back(*it);
        }

        while (!queue.empty())
        {
            std::shared_ptr<TaskComponent> current = queue.front();
            queue.pop_front();

            snapshot.push_back(current);

            TaskGroup* group =
                dynamic_cast<TaskGroup*>(current.get());

            if (group)
            {
                for (std::vector<std::shared_ptr<TaskComponent> >::const_iterator it =
                         group->children.begin();
                     it != group->children.end();
                     ++it)
                {
                    queue.push_back(*it);
                }
            }
        }
    }
}

TaskIterator::~TaskIterator()
{
}

void TaskIterator::addDepthFirst(
    const std::shared_ptr<TaskComponent>& component
)
{
    snapshot.push_back(component);

    TaskGroup* group =
        dynamic_cast<TaskGroup*>(component.get());

    if (group)
    {
        for (std::vector<std::shared_ptr<TaskComponent> >::const_iterator it =
                 group->children.begin();
             it != group->children.end();
             ++it)
        {
            addDepthFirst(*it);
        }
    }
}

bool TaskIterator::hasNext() const
{
    return currentIndex < snapshot.size();
}

std::shared_ptr<TaskComponent> TaskIterator::next()
{
    if (!hasNext())
    {
        throw std::out_of_range("Iterator has no more elements.");
    }

    return snapshot[currentIndex++];
}