#include "AuditLogDecorator.h"
#include <iostream>

AuditLogDecorator::AuditLogDecorator(std::shared_ptr<TaskComponent> task, const std::string& auditID):TaskDecorator(task){
    this->auditID = auditID;
}

AuditLogDecorator::~AuditLogDecorator()
{
}

std::string AuditLogDecorator::getName() const
{
    return TaskDecorator::getName() + " {AUDIT: " + this->auditID + "}";
}

void AuditLogDecorator::display(int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }
    std::cout << "<AUDIT LOG " << auditID << "> ";
    if (wrappedTask)
    {
        wrappedTask->display(0);
    }
}