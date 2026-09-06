#ifndef STATUSDECORATOR_H
#define STATUSDECORATOR_H

#include "TaskDecorator.h"
#include <string>

class StatusDecorator : public TaskDecorator
{
    private:
    //TODO: MAKE THIS AN ENUM SUCH THAT IT IS EASIER TO ALTER AND CHANGE 
        std::string status; // Options: "In Progress", "Reviewing", "Completed"

    public:
        StatusDecorator(std::shared_ptr<TaskComponent> task, const std::string& status = "In Progress");
        virtual ~StatusDecorator();

        virtual std::string getName() const override;
        virtual void display(int depth = 0) const override;

        std::string getStatus() const;
        void setStatus(const std::string& newStatus);
};

#endif