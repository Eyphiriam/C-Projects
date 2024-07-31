# README for Dining Philosophers Simulation

This README document provides a comprehensive overview of the Dining Philosophers Simulation project implemented in C++ using POSIX threads. This project simulates the classic synchronization problem involving philosophers alternately thinking and eating while avoiding deadlocks.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Implementation Details](#implementation-details)


## Project Overview

The Dining Philosophers problem is a multi-threaded simulation in which multiple philosophers, sitting around a circular table, contemplate and eat. They use a shared resource (forks) located between them. Each philosopher needs two forks to eat, which introduces complexity in resource allocation and requires careful synchronization to prevent deadlocks and ensure fairness.


## Implementation Details

- **Philosophers**: Implemented as threads using POSIX threads (pthreads).
- **Mutex and Condition Variables**: Used to synchronize access to shared resources (forks) and manage philosopher states.
- **States**:
  - `THINKING`: The philosopher is thinking.
  - `HUNGRY`: The philosopher wants to eat and is trying to acquire forks.
  - `EATING`: The philosopher is eating.
- **Functions**:
  - `test(int phnum)`: Checks if a philosopher can start eating.
  - `take_fork(int phnum)`: Manages the action of a philosopher trying to pick up forks.
  - `put_fork(int phnum)`: Manages the action of a philosopher releasing forks and returning to thinking.
  - `philosopher(void* num)`: The main function executed by each philosopher thread.
