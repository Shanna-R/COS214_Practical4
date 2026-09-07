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