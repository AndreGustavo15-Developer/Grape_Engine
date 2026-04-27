<!--
<p align="center"> <img src="./assets/banner2.png" alt="Dynora Engine Banner" width="100%" /> </p>
-->
<h1 align="center">DYNORA ENGINE</h1>

<p align="center"> <strong>Modular game engine focused on performance and scalability (Zig + C)</strong> </p> 

<p align="center"> <em>Grow modular worlds.</em> </p>

<p align="center"> 
  <a href="LICENSE"> 
    <img src="https://img.shields.io/badge/license-MIT-green.svg" /> 
  </a> 
  <a href="https://github.com/AndreGustavo15-Developer/DynoraEngine/issues"> 
    <img src="https://img.shields.io/github/issues/AndreGustavo15-Developer/DynoraEngine.svg" /> 
  </a> 
  <a href="https://github.com/AndreGustavo15-Developer/DynoraEngine/stargazers"> 
    <img src="https://img.shields.io/github/stars/AndreGustavo15-Developer/DynoraEngine.svg" /> 
  </a> 
</p>

---

## Overview

**Dynora Engine** is a modular game engine in development, **designed to grow, adapt, and scale as unified systems** — where independent modules work together while preserving performance and flexibility.

Every subsystem is built as an independent module, allowing the engine to scale without sacrificing maintainability.

Dynora’s mission is to provide a **high-performance, deeply modular architecture** where ideas can be assembled into scalable systems — empowering developers to build complex interactive worlds with precision and control.

---

## Core Philosophy

Dynora is built on the belief that a game engine should behave as an **adaptive architecture**:

- Systems are **modular and replaceable**
- The core coordinates independent subsystems
- Features evolve without compromising the whole

This philosophy drives every architectural decision.

### Principles

- **Modular Architecture** — loosely coupled and extensible systems  
- **Adaptive Pipelines** — execution paths adapt to context and hardware  
- **Hybrid ECS Design** — balancing flexibility and high performance  
- **Scalable Foundations** — systems designed to evolve with the project  

Dynora is not just built for features — it is built for **system growth**.

---

## Goals

Dynora aims to:

- Define a deeply modular and extensible architecture  
- Achieve high performance in critical systems  
- Support pluggable modules and backends (DLLs/modules) 
- Grow into a production-ready open-source engine  
- Give developers full architectural control  

---

## Current State

> **Architecture Design Phase**

Dynora is currently defining its **core architecture and system boundaries**.

- The Technical Design Document (TDD) is actively evolving
- Core modules are being designed, not fully implemented
- The logger system is the first subsystem used to validate architectural decisions

This means the project is early, but also the best moment to influence its foundations.

---

## Why Dynora Exists

Many engines become difficult to evolve over time due to tightly coupled systems and unclear boundaries.

Dynora is an attempt to explore a different approach:

- Systems should be **independent but cooperative**
- Architecture should **adapt**, not resist change
- Performance should be considered **from the start**
- Growth should not require rewriting the engine

This project is as much about **architecture exploration** as it is about building an engine.

---

## What Exists Today

### Logger (first subsystem)

The logging system is the first implemented module, designed to validate:

- Module boundaries
- Backend abstraction
- Performance considerations in hot paths
- Decoupled interfaces

Example:

```c
DYNORA_LOG_INFO(DYNORA_LOG_GENERAL, "System initialized");
```
Planned evolution:

- Asynchronous logging
- Multiple backends
- Filtering and formatting layers

---

## Architecture Direction

Dynora is being designed around a few core principles:

### Modular Systems

Each subsystem should be independently replaceable and testable.

### Clear Boundaries

Modules communicate through well-defined interfaces.

### Performance Awareness

Critical paths are considered early in design, not as an afterthought.

### Incremental Validation

Systems are implemented early in minimal form to validate architectural decisions.

---

### Planned Systems

These systems are planned but **not yet fully implemented**:

- ECS (Entity Component System)
- Rendering pipeline
- Editor
- Physics
- Audio
- Asset pipeline

All systems will follow the same modular design philosophy.

---

## Repository Structure

```bash
DynoraEngine/
│
├── engine/
│   ├── logger/
│   ├── ecs/
│   ├── renderer/
│
├── backends/
│   └── logger_console/
│
├── docs/
│   └── tdd/
│
├── examples/
│
├── tests/
│
└── (README.md, LICENSE, ...)
```

The structure will continue evolving alongside the architecture.

---

## Build

> ⚠️ Temporary build system

Dynora currently uses **CMake** as a temporary build system while the architecture is being defined.

The long-term plan is to migrate to the **Zig build system**, but this will only happen after the core architecture stabilizes.

### Requirements

- C compiler (GCC, Clang, or MSVC)
- CMake 3.x

### Build Steps

```bash
git clone https://github.com/AndreGustavo15-Developer/DynoraEngine
cd DynoraEngine

mkdir build
cd build

cmake ..
cmake --build .
```
### Output

The current build produces early engine modules and test binaries used for architectural validation.

---

## Documentation

### Local Docs

Internal documentation and technical design documents:

```bash
/docs
/docs/tdd
```
The **TDD (Technical Design Document)** is the main reference for architectural decisions.

---

## Contributing

Dynora is in an early stage, so contributions are **especially valuable right now** — particularly in architecture and system design.

## Ways to Contribute
- Review and discuss architecture decisions
- Suggest improvements to the logger system
- Propose module interfaces and boundaries
- Identify risks in modular design
- Improve documentation and clarity
- Add tests or small validation implementations

## Before You Start

For anything beyond small changes:

> Open an issue first to discuss your idea.

This helps keep the architecture consistent and avoids duplicated work.

## Good First Contributions
- Improve README or docs
- Suggest API improvements for the logger
- Add small test cases
- Review TDD sections and raise questions

### Current Needs

Dynora is currently looking for contributors interested in:

- Low-level systems design
- Engine architecture
- Performance-oriented C/Zig development
- API design and modular interfaces

See **[CONTRIBUTING.md](CONTRIBUTING.md)** for contribution guidelines.

---

## Project Direction
### Current Focus
- Defining core architecture
- Validating modular design through small systems
- Building strong foundations

### Intentionally Avoiding (for now)
- Large feature expansion
- Premature optimization without validation
- External dependencies that constrain architecture

---

## Roadmap (Conceptual)
- Define core architecture
- Stabilize logger module
- Implement initial ECS prototype
- Define rendering abstraction
- Expand documentation and examples

---

## License

MIT License — free for personal, educational, and commercial use.

---

## Author

Created and maintained by **[André Gustavo](https://github.com/AndreGustavo15-Developer)**.

---

<p align="center"> <strong>Assemble ideas. Build systems.</strong> </p>
