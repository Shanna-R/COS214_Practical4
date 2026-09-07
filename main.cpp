#include "Task.h"
#include "TaskGroup.h"
#include "TaskIterator.h"
#include "StatusDecorator.h"
#include "TaskDecorator.h"
#include "PriorityDecorator.h"
#include "AuditLogDecorator.h"

#include <iostream>
#include <memory>

void printTraversal(Iterator& iterator, const std::string& title)
{
    std::cout << "\n===== " << title << " =====\n";

    while (iterator.hasNext())
    {
        std::shared_ptr<TaskComponent> component = iterator.next();

        std::cout << component->getName();

        if (component->isGroup())
        {
            std::cout << " [GROUP]";
        }
        else
        {
            std::cout << " [TASK]";
        }

        std::cout << std::endl;
    }
}

int main()
{
    // LEVEL 0
    std::shared_ptr<TaskGroup> project(
        new TaskGroup("Software Delivery Project")
    );


    // LEVEL 1
    std::shared_ptr<TaskGroup> development(
        new TaskGroup("Development Phase")
    );

    std::shared_ptr<TaskGroup> testing(
        new TaskGroup("Testing Phase")
    );

    std::shared_ptr<TaskGroup> deployment(
        new TaskGroup("Deployment Phase")
    );

    project->add(development);
    project->add(testing);
    project->add(deployment);


    // LEVEL 2
    std::shared_ptr<TaskGroup> backend(
        new TaskGroup("Backend Module")
    );

    std::shared_ptr<TaskGroup> frontend(
        new TaskGroup("Frontend Module")
    );

    std::shared_ptr<TaskGroup> unitTesting(
        new TaskGroup("Unit Testing")
    );

    std::shared_ptr<TaskGroup> integrationTesting(
        new TaskGroup("Integration Testing")
    );

    std::shared_ptr<TaskGroup> staging(
        new TaskGroup("Staging Deployment")
    );

    std::shared_ptr<TaskGroup> production(
        new TaskGroup("Production Deployment")
    );

    development->add(backend);
    development->add(frontend);

    testing->add(unitTesting);
    testing->add(integrationTesting);

    deployment->add(staging);
    deployment->add(production);


    // LEVEL 3 - LEAF TASKS
    backend->add(
        std::shared_ptr<Task>(
            new Task("Implement Login")
        )
    );

    backend->add(
        std::shared_ptr<Task>(
            new Task("Implement Database")
        )
    );

    frontend->add(
        std::shared_ptr<Task>(
            new Task("Build Dashboard")
        )
    );

    frontend->add(
        std::shared_ptr<Task>(
            new Task("Build Profile Page")
        )
    );

    unitTesting->add(
        std::shared_ptr<Task>(
            new Task("Write Unit Tests")
        )
    );

    unitTesting->add(
        std::shared_ptr<Task>(
            new Task("Fix Test Failures")
        )
    );

    integrationTesting->add(
        std::shared_ptr<Task>(
            new Task("Run Integration Tests")
        )
    );

    staging->add(
        std::shared_ptr<Task>(
            new Task("Deploy Staging Build")
        )
    );

    production->add(
        std::shared_ptr<Task>(
            new Task("Deploy Production Release")
        )
    );


    // DISPLAY COMPLETE HIERARCHY
    std::cout << "========================================\n";
    std::cout << " SOFTWARE DELIVERY PROJECT\n";
    std::cout << "========================================\n";

    project->display();


    // DEPTH-FIRST TRAVERSAL
    std::unique_ptr<TaskIterator> depthIterator =
        project->createDepthFirstIterator();

    printTraversal(
        *depthIterator,
        "DEPTH-FIRST TRAVERSAL"
    );


    // BREADTH-FIRST TRAVERSAL
    std::unique_ptr<TaskIterator> breadthIterator =
        project->createBreadthFirstIterator();

    printTraversal(
        *breadthIterator,
        "BREADTH-FIRST TRAVERSAL"
    );


    // TWO INDEPENDENT ITERATORS
    std::unique_ptr<TaskIterator> iteratorOne =
        project->createDepthFirstIterator();

    std::unique_ptr<TaskIterator> iteratorTwo =
        project->createBreadthFirstIterator();

    std::cout << "\n===== TWO INDEPENDENT ITERATORS =====\n";

    std::cout << "Iterator 1: ";

    if (iteratorOne->hasNext())
    {
        std::cout << iteratorOne->next()->getName();
    }

    std::cout << std::endl;

    std::cout << "Iterator 2: ";

    if (iteratorTwo->hasNext())
    {
        std::cout << iteratorTwo->next()->getName();
    }

    std::cout << std::endl;


    // RUNTIME STRUCTURAL CHANGE
    std::cout << "\n===== RUNTIME CHANGE =====\n";

    backend->add(
        std::shared_ptr<Task>(
            new Task("Implement Security")
        )
    );

    std::cout << "Added: Implement Security\n";

    std::unique_ptr<TaskIterator> updatedIterator =
        project->createDepthFirstIterator();

    printTraversal(
        *updatedIterator,
        "UPDATED DEPTH-FIRST TRAVERSAL"
    );

    // =========================================================
    // PERSON 3: DECORATOR INTEGRATION & RUNTIME DEMONSTRATIONS
    // =========================================================
    std::cout << "\n========================================\n";
    std::cout << " PERSON 3: DECORATOR PATTERN DEMO\n";
    std::cout << "========================================\n";

    // 1. Create base leaf task
    std::shared_ptr<TaskComponent> secureDeployTask(
        new Task("Deploy Security Patch")
    );

    // 2. Wrap with StatusDecorator ("In Progress")
    std::shared_ptr<StatusDecorator> statusTask(
        new StatusDecorator(secureDeployTask,TaskStatus::IN_PROGRESS)
    );

    // 3. Wrap with AuditLogDecorator
    std::shared_ptr<TaskComponent> auditedTask(
        new AuditLogDecorator(statusTask, "AUDIT-2026-X9")
    );

    // 4. Wrap with PriorityDecorator (Level 1) -> Stacked Decorator
    std::shared_ptr<PriorityDecorator> fullyDecoratedTask(
        new PriorityDecorator(auditedTask, 1)
    );

    // Add stacked decorated task directly into the composite tree
    production->add(fullyDecoratedTask);

    std::cout << "\n--- Displaying Hierarchy with Stacked Decorators ---\n";
    production->display();

    // 5. Test Traversal over Decorated Items
    std::unique_ptr<TaskIterator> decoratorIterator =
        production->createDepthFirstIterator();

    printTraversal(
        *decoratorIterator,
        "TRAVERSAL OVER DECORATED PRODUCTION TASKS"
    );

    // 6. Runtime Configuration Changes (Changing Status & Escalating Priority)
    std::cout << "\n--- Executing Runtime Configuration Changes ---\n";
    std::cout << "Updating status from 'In Progress' to 'Reviewing'...\n";
    statusTask->setStatus(TaskStatus::REVIEWING);

    std::cout << "Escalating priority level from 1 to 10...\n";
    fullyDecoratedTask->setPriority(10);

    std::cout << "\n--- Updated Hierarchy Display ---\n";
    production->display();

    std::cout << "\nUpdating status from 'Reviewing' to 'Completed'...\n";
    statusTask->setStatus(TaskStatus::COMPLETED);

    std::cout << "\n--- Final Hierarchy Display ---\n";
    production->display();

    return 0;
}