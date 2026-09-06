#ifndef AUDITLOGDECORATOR_H
#define AUDITLOGDECORATOR_H

#include "TaskDecorator.h"
#include <string>

class AuditLogDecorator : public TaskDecorator
{
    private:
        std::string auditID;

    public:
        AuditLogDecorator(std::shared_ptr<TaskComponent> task, const std::string& auditID);
        virtual ~AuditLogDecorator();

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;
};

#endif