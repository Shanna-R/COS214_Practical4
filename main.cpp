#include "Task.h"
#include "TaskGroup.h"
#include "TaskIterator.h"
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

    // 1. Concrete Task (Context for State Pattern)
    std::shared_ptr<Task> secureDeployTask(
        new Task("Deploy Security Patch")
    );

    // 2. Wrap directly with AuditLogDecorator (StatusDecorator removed)
    std::shared_ptr<TaskComponent> auditedTask(
        new AuditLogDecorator(secureDeployTask, "AUDIT-2026-X9")
    );

    // 3. Wrap with PriorityDecorator
    std::shared_ptr<PriorityDecorator> fullyDecoratedTask(
        new PriorityDecorator(auditedTask, 1)
    );

    production->add(fullyDecoratedTask);

    std::cout << "\n--- Displaying Hierarchy with Stacked Decorators ---\n";
    production->display();

    std::unique_ptr<TaskIterator> decoratorIterator =
        production->createDepthFirstIterator();

    printTraversal(
        *decoratorIterator,
        "TRAVERSAL OVER DECORATED PRODUCTION TASKS"
    );

    // 4. Runtime Configuration Changes (State Transitions & Priority Escalation)
    std::cout << "\n--- Executing Runtime Configuration Changes ---\n";
    std::cout << "Starting task via State Pattern...\n";
    secureDeployTask->start();

    std::cout << "Escalating priority level from 1 to 10...\n";
    fullyDecoratedTask->setPriority(10);

    std::cout << "\n--- Updated Hierarchy Display ---\n";
    production->display();

    std::cout << "\nCompleting task via State Pattern...\n";
    secureDeployTask->complete();

    std::cout << "\n--- Final Hierarchy Display ---\n";
    production->display();

     Task login("Implement Login");

    std::cout << "\n===== STATE TEST =====\n";

    std::cout << "Initial state: "
              << login.getStatus()
              << std::endl;

    login.execute();

    std::cout << "\nStarting task...\n";
    login.start();

    std::cout << "Current state: "
              << login.getStatus()
              << std::endl;

    login.execute();

    std::cout << "\nCompleting task...\n";
    login.complete();

    std::cout << "Current state: "
              << login.getStatus()
              << std::endl;

    std::cout << "\nTrying invalid transition...\n";
    login.start();

    std::cout << "\nTrying to complete again...\n";
    login.complete();

    return 0;
}