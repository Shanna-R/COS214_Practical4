#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

class TaskComponent;

class Iterator
{
    public:
        virtual ~Iterator() {}

        virtual bool hasNext() const = 0;
        virtual std::shared_ptr<TaskComponent> next() = 0;
};

#endif