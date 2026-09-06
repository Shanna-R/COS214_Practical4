#ifndef TASKITERATOR_H
#define TASKITERATOR_H

#include "Iterator.h"

#include <memory>
#include <vector>

class TaskComponent;
class TaskGroup;

class TaskIterator : public Iterator
{
    public:
        enum TraversalOrder
        {
            DEPTH_FIRST,
            BREADTH_FIRST
        };

    private:
        std::vector<std::shared_ptr<TaskComponent> > snapshot;
        std::size_t currentIndex;

        void addDepthFirst(
            const std::shared_ptr<TaskComponent>& component
        );

    public:
        TaskIterator(
            const TaskGroup* root,
            TraversalOrder order
        );

        virtual ~TaskIterator();

        virtual bool hasNext() const override;

        virtual std::shared_ptr<TaskComponent> next() override;
};

#endif