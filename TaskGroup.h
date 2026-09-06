#ifndef TASKGROUP_H
#define TASKGROUP_H

#include "TaskComponent.h"

#include <memory>
#include <string>
#include <vector>

class TaskIterator;

class TaskGroup : public TaskComponent
{
    private:
        std::string name;
        std::vector<std::shared_ptr<TaskComponent> > children;

        friend class TaskIterator;

    public:
        TaskGroup(const std::string& name);
        virtual ~TaskGroup();

        void add(const std::shared_ptr<TaskComponent>& component);
        bool remove(const std::string& componentName);

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;
        virtual bool isGroup() const override;

        std::unique_ptr<TaskIterator> createDepthFirstIterator() const;
        std::unique_ptr<TaskIterator> createBreadthFirstIterator() const;
};

#endif