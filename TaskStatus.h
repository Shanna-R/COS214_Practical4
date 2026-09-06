#ifndef TASKSTATUS_H
#define TASKSTATUS_H 

#include <string>

enum class TaskStatus{
    IN_PROGRESS,
    PENDING,
    COMPLETED
};


inline std::string statusToString(TaskStatus status){
    switch(status){
        case TaskStatus::IN_PROGRESS:
            return "In_Progress";
        case TaskStatus::PENDING:
            return "Pending";
        case TaskStatus::COMPLETED:
            return "Completed";
        default:
            "Unknown";
    }
}

#endif 