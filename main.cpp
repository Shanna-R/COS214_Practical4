#include "Task.h"
#include "TaskGroup.h"
#include "TaskIterator.h"
#include "TaskDecorator.h"
#include "PriorityDecorator.h"
#include "AuditLogDecorator.h"

#include <iostream>
#include <memory>

// =========================================================
// ANSI COLOR ESCAPE CODES FOR TERMINAL FORMATTING
// =========================================================
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BOLD_RED    "\033[1;\033[31m"
#define BOLD_GREEN  "\033[1;\033[32m"
#define BOLD_YELLOW "\033[1;\033[33m"
#define BOLD_BLUE   "\033[1;\033[34m"
#define BOLD_MAGENTA "\033[1;\033[35m"
#define BOLD_CYAN   "\033[1;\033[36m"

void printTraversal(Iterator& iterator, const std::string& title)
{
    std::cout << BOLD_CYAN << "\n===== " << title << " =====\n" << RESET;

    while (iterator.hasNext())
    {
        std::shared_ptr<TaskComponent> component = iterator.next();

        std::cout << component->getName();

        if (component->isGroup())
        {
            std::cout << YELLOW << " [GROUP]" << RESET;
        }
        else
        {
            std::cout << GREEN << " [TASK]" << RESET;
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
    std::cout << BOLD_BLUE << "========================================\n";
    std::cout << " SOFTWARE DELIVERY PROJECT HIERARCHY\n";
    std::cout << "========================================\n" << RESET;

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

    std::cout << BOLD_MAGENTA << "\n===== TWO INDEPENDENT ITERATORS =====\n" << RESET;

    std::cout << BOLD << "Iterator 1 (Depth-First): " << RESET;
    if (iteratorOne->hasNext())
    {
        std::cout << CYAN << iteratorOne->next()->getName() << RESET;
    }
    std::cout << std::endl;

    std::cout << BOLD << "Iterator 2 (Breadth-First): " << RESET;
    if (iteratorTwo->hasNext())
    {
        std::cout << CYAN << iteratorTwo->next()->getName() << RESET;
    }
    std::cout << std::endl;


    // RUNTIME STRUCTURAL CHANGE
    std::cout << BOLD_YELLOW << "\n===== RUNTIME STRUCTURAL CHANGE =====\n" << RESET;

    backend->add(
        std::shared_ptr<Task>(
            new Task("Implement Security")
        )
    );

    std::cout << GREEN << "[+] Added: 'Implement Security' to Backend Module\n" << RESET;

    std::unique_ptr<TaskIterator> updatedIterator =
        project->createDepthFirstIterator();

    printTraversal(
        *updatedIterator,
        "UPDATED DEPTH-FIRST TRAVERSAL"
    );


    // =========================================================
    // PERSON 3: DECORATOR INTEGRATION & RUNTIME DEMONSTRATIONS
    // =========================================================
    std::cout << BOLD_MAGENTA << "\n========================================\n";
    std::cout << " PERSON 3: DECORATOR PATTERN DEMO\n";
    std::cout << "========================================\n" << RESET;

    // Direct pointer to Task so state transitions can be called directly
    std::shared_ptr<Task> secureDeployTask(
        new Task("Deploy Security Patch")
    );

    // Wrapped directly in AuditLogDecorator (StatusDecorator removed)
    std::shared_ptr<TaskComponent> auditedTask(
        new AuditLogDecorator(secureDeployTask, "AUDIT-2026-X9")
    );

    // Wrapped in PriorityDecorator
    std::shared_ptr<PriorityDecorator> fullyDecoratedTask(
        new PriorityDecorator(auditedTask, 1)
    );

    production->add(fullyDecoratedTask);

    std::cout << BOLD_YELLOW << "\n--- Displaying Hierarchy with Stacked Decorators ---\n" << RESET;
    production->display();

    std::unique_ptr<TaskIterator> decoratorIterator =
        production->createDepthFirstIterator();

    printTraversal(
        *decoratorIterator,
        "TRAVERSAL OVER DECORATED PRODUCTION TASKS"
    );

    // Runtime Configuration Changes (State Pattern & Priority Escalation)
    std::cout << BOLD_YELLOW << "\n--- Executing Runtime Configuration Changes ---\n" << RESET;
    
    std::cout << CYAN << "Transitioning task state to 'In Progress' via Task State Pattern...\n" << RESET;
    secureDeployTask->start();

    std::cout << CYAN << "Escalating priority level from 1 to 10 via PriorityDecorator...\n" << RESET;
    fullyDecoratedTask->setPriority(10);

    std::cout << BOLD_YELLOW << "\n--- Updated Hierarchy Display ---\n" << RESET;
    production->display();

    std::cout << CYAN << "\nTransitioning task state to 'Completed' via Task State Pattern...\n" << RESET;
    secureDeployTask->complete();

    std::cout << BOLD_YELLOW << "\n--- Final Hierarchy Display ---\n" << RESET;
    production->display();


    // =========================================================
    // TASK STATE PATTERN TEST
    // =========================================================
    Task login("Implement Login");

    std::cout << BOLD_GREEN << "\n========================================\n";
    std::cout << " TASK STATE PATTERN TEST\n";
    std::cout << "========================================\n" << RESET;

    std::cout << BOLD << "Initial state: " << RESET 
              << YELLOW << login.getStatus() << RESET << std::endl;

    login.execute();

    std::cout << CYAN << "\nStarting task...\n" << RESET;
    login.start();

    std::cout << BOLD << "Current state: " << RESET 
              << YELLOW << login.getStatus() << RESET << std::endl;

    login.execute();

    std::cout << CYAN << "\nCompleting task...\n" << RESET;
    login.complete();

    std::cout << BOLD << "Current state: " << RESET 
              << GREEN << login.getStatus() << RESET << std::endl;

    std::cout << RED << "\nTrying invalid transition (start on completed task)...\n" << RESET;
    login.start();

    std::cout << RED << "\nTrying to complete again...\n" << RESET;
    login.complete();

    return 0;
}