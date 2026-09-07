# TaskForge — Hierarchical Work Processing

## COS 214 Practical 4

TaskForge is a C++11 software delivery management system developed to demonstrate the practical application of four Gang of Four design patterns:

- **Composite** — represents hierarchical project tasks and groups.
- **Iterator** — provides traversal of the task hierarchy without exposing its internal structure.
- **State** — manages task lifecycle and state-dependent behaviour.
- **Decorator** — dynamically adds functionality such as status reporting, priority information, and audit logging.

The system models a software delivery project containing development, testing, and deployment phases. Tasks can be organised into nested groups, traversed using different strategies, and moved through a controlled lifecycle.

---

## 1. Features

TaskForge demonstrates the following functionality:

### Hierarchical Task Management

The project is represented as a recursive hierarchy of tasks and task groups.

Example structure:

```text
Software Delivery Project
├── Development Phase
│   ├── Backend Module
│   │   ├── Implement Login
│   │   ├── Implement Database
│   │   └── Implement Security
│   └── Frontend Module
│       ├── Build Dashboard
│       └── Build Profile Page
│
├── Testing Phase
│   ├── Unit Testing
│   │   ├── Write Unit Tests
│   │   └── Fix Test Failures
│   └── Integration Testing
│       └── Run Integration Tests
│
└── Deployment Phase
    ├── Staging Deployment
    │   └── Deploy Staging Build
    └── Production Deployment
        ├── Deploy Production Release
        └── Deploy Security Patch
```

### Composite Pattern

`TaskComponent` provides the common abstraction for individual tasks and task groups.

- `Task` represents a leaf task.
- `TaskGroup` represents a composite containing other `TaskComponent` objects.
- Groups can contain both tasks and other groups.
- The hierarchy can therefore be nested to multiple levels.

### Iterator Pattern

The hierarchy can be traversed without exposing the internal container used by `TaskGroup`.

Two traversal strategies are demonstrated:

- Depth-First Search (DFS)
- Breadth-First Search (BFS)

Independent iterator objects can traverse the same hierarchy separately.

### State Pattern

Tasks have a lifecycle represented by three states:

```text
TODO → IN_PROGRESS → COMPLETED
```

The task behaviour changes according to its current state.

Valid transitions include:

- `TODO → IN_PROGRESS`
- `IN_PROGRESS → COMPLETED`

Invalid transitions are also handled explicitly, for example attempting to start a task that has already been completed.

### Decorator Pattern

Task functionality can be extended dynamically without modifying the original `Task` class.

The implementation includes:

- `PriorityDecorator`
- `AuditLogDecorator`

Decorators can be stacked at runtime.

Example:

```text
PriorityDecorator
        ↓
AuditLogDecorator
        ↓
Task
```

This allows a task to display priority, audit information, and status together.

---

## 2. Project Structure

```text
TaskForge/
│
├── AuditLogDecorator.cpp
├── AuditLogDecorator.h
├── CompletedState.cpp
├── CompletedState.h
├── InProgressState.cpp
├── InProgressState.h
├── Iterator.h
├── PriorityDecorator.cpp
├── PriorityDecorator.h
├── Task.cpp
├── Task.h
├── TaskComponent.cpp
├── TaskComponent.h
├── TaskDecorator.cpp
├── TaskDecorator.h
├── TaskGroup.cpp
├── TaskGroup.h
├── TaskIterator.cpp
├── TaskIterator.h
├── TaskStatus.h
├── TodoState.cpp
├── TodoState.h
│
├── main.cpp
├── Makefile
├── Dockerfile
├── README.md
│
└── docs/
    └── [project documentation and diagrams]
```

---

## 3. Design Pattern Structure

### Composite

```text
             TaskComponent
              /         \
             /           \
          Task          TaskGroup
                         /    \
                       Task   TaskGroup
```

`TaskComponent` is the common polymorphic interface. `Task` is a leaf while `TaskGroup` is a composite.

This allows clients to work with individual tasks and groups through the same abstraction.

### Iterator

```text
TaskIterator
     |
     +---- DFS traversal
     |
     +---- BFS traversal
```

The iterator is responsible for traversal behaviour rather than requiring client code to directly access the `TaskGroup` container.

### State

```text
             TaskState
            /    |     \
           /     |      \
       Todo   InProgress  Completed
```

The `Task` delegates lifecycle operations to its current state object.

### Decorator

```text
TaskComponent
      |
      +-- TaskDecorator
             |
             +-- PriorityDecorator
             +-- AuditLogDecorator
```

Decorators maintain the `TaskComponent` interface and wrap another component, allowing functionality to be combined dynamically.

---

## 4. Requirements

The project uses:

- C++11
- GNU g++
- GNU Make
- Docker
- GDB
- Valgrind

The project is designed to build inside the supplied Docker environment so that the required development and debugging tools are available consistently.

---

## 5. Running the Project with Docker

### Build the Docker Image

From the project root:

```bash
docker build -t taskforge .
```

The Dockerfile installs:

- g++
- make
- gdb
- valgrind
- git

and then builds the project using the Makefile.

### Start the Container

```bash
docker run --rm -it taskforge
```

The project is located in:

```text
/app
```

Inside the container, verify the files:

```bash
ls -l
```

---

## 6. Building with Make

Inside the Docker container:

```bash
make clean
make
```

The Makefile compiles the project using C++11 and produces the executable:

```text
taskforge
```

The expected compiler standard is:

```text
-std=c++11
```

To confirm that the executable was created:

```bash
ls -l taskforge
```

---

## 7. Running TaskForge

Run the completed application with:

```bash
./taskforge
```

The demonstration includes:

- Construction of the hierarchical software delivery project.
- DFS traversal.
- BFS traversal.
- Independent traversal instances.
- A runtime structural change to the hierarchy.
- Task lifecycle/state transitions.
- Invalid state transitions.
- Decorated task behaviour.
- Stacked decorators.
- Final task status changes.

The program demonstrates the patterns as part of one integrated software delivery workflow rather than as isolated examples.

---

## 8. State Demonstration

A task initially starts in the `TODO` state.

A typical lifecycle is:

```text
TODO
 |
 | start()
 v
IN_PROGRESS
 |
 | complete()
 v
COMPLETED
```

The implementation also demonstrates invalid operations.

For example, attempting to execute a task while it is still `TODO` is rejected.

Attempting to start a task after it has reached `COMPLETED` is also rejected.

These behaviours are handled by the appropriate state object rather than by a large conditional statement inside `Task`.

---

## 9. Iterator Demonstration

TaskForge provides two traversal behaviours over the same hierarchy.

### Depth-First Search

DFS explores a branch before moving to the next branch.

```text
Project
→ Development
→ Backend
→ Login
→ Database
→ Security
→ Frontend
...
```

### Breadth-First Search

BFS visits nodes level by level.

```text
Project
→ Development
→ Testing
→ Deployment
→ Backend
→ Frontend
→ Unit Testing
...
```

The iterator abstraction prevents client code from needing direct access to the internal task containers.

Two iterator objects can also operate independently on the same hierarchy.

---

## 10. Runtime Structural Modification

The application demonstrates a structural change while the system is running.

For example, the following task is added to the backend module:

```text
Implement Security
```

A new traversal performed after the modification can discover the newly added task.

The implementation deliberately avoids modifying the hierarchy while an active traversal is using the same structure. Structural changes are performed between traversal runs so that iterator behaviour remains predictable and safe.

---

## 11. Decorator Demonstration

A deployment task can be dynamically decorated with multiple behaviours.

Example:

```text
Deploy Security Patch
```

can be wrapped as:

```text
PriorityDecorator
        |
AuditLogDecorator
        |
Deploy Security Patch
```

This results in combined behaviour such as:

```text
[PRIORITY 1] <AUDIT LOG AUDIT-2026-X9> STATUS [In_Progress] - Deploy Security Patch [TODO]
```

The decorators can be stacked without changing the original Task implementation.

---

## 12. Memory Management

TaskForge uses polymorphic ownership for dynamically created components.

Owning relationships use smart pointers so that objects are automatically destroyed when their owning object is destroyed.

Polymorphic base classes provide virtual destructors to ensure correct destruction through base-class pointers.

This prevents ownership from being left ambiguous and reduces the possibility of memory leaks.

---

## 13. GDB Debugging

The project is compiled with debugging information using:

```text
-g
```

To start GDB:

```bash
gdb ./taskforge
```

A useful breakpoint is:

```text
break Task::start
```

Then run the program:

```text
run
```

Useful inspection commands include:

```text
print name
print *state
print *this
next
continue
```

These commands allow the current task, state object, and transition behaviour to be inspected while the program is executing.

Exit GDB with:

```text
quit
```

---

## 14. Valgrind Memory Testing

The final executable can be checked with Valgrind using:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

The completed implementation was tested with Valgrind.

The final run reported:

```text
in use at exit: 0 bytes in 0 blocks
```

and:

```text
All heap blocks were freed -- no leaks are possible
```

The final error summary reported:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

---

## 15. Docker Environment Verification

The required tools can be checked inside the container:

```bash
g++ --version
make --version
gdb --version
valgrind --version
```

This ensures that the project can be built and tested using the same environment expected for assessment.

---

## 16. Clean Build

To remove generated object files and the executable:

```bash
make clean
```

To perform a fresh build:

```bash
make clean
make
```

Then run:

```bash
./taskforge
```

---

## 17. Makefile

The project uses a Makefile so that the complete application can be built with:

```bash
make
```

and cleaned with:

```bash
make clean
```

The final executable is:

```text
taskforge
```

---

## 18. Dockerfile

The supplied Dockerfile creates a reproducible Ubuntu 22.04 development environment containing the required C++ compiler, build system, debugger, and memory-analysis tools.

The image can be built with:

```bash
docker build -t taskforge .
```

and run with:

```bash
docker run --rm -it taskforge
```

---

## 19. Documentation

Additional project documentation and UML/activity diagrams are stored in the:

```text
docs/
```

directory.

The accompanying practical report contains:

- System description
- UML class diagram
- GoF participant mapping
- Design and ownership rationale
- Object diagram
- State diagram
- Activity diagrams
- Traversal modification policy
- GDB investigation
- Valgrind evidence
- Docker evidence
- GitHub development evidence
- Team contribution statement

---

## 20. GitHub Repository

The complete source code and development history are maintained in the project Git repository.

GitHub: [https://github.com/Shanna-R/COS214_Practical4.git](https://github.com/Shanna-R/COS214_Practical4.git)

The repository contains the source code, build configuration, Docker configuration, README, and documentation required to reproduce the project.

---

## 21. Quick Start

For a complete build and run:

```bash
docker build -t taskforge .
docker run --rm -it taskforge
```

Then inside the container:

```bash
make clean
make
./taskforge
```

For debugging:

```bash
gdb ./taskforge
```

For memory testing:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

---

## 22. Summary

TaskForge integrates the Composite, Iterator, State, and Decorator design patterns into a single software delivery management system.

The Composite pattern provides the recursive project hierarchy, the Iterator pattern provides controlled traversal, the State pattern manages task lifecycle behaviour, and the Decorator pattern dynamically extends task functionality.

The project is built using C++11 and Make, runs inside a Docker environment, and has been tested using GDB and Valgrind to verify runtime behaviour and memory management.

## 23. Updates 

**StatusDecorator has been removed from the concrete decorators and the main.cpp has since been updated**
