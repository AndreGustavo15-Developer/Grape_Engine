<!--
<p align="center"> <img src="./assets/banner2.png" alt="Dynora Engine Banner" width="100%" /> </p>
-->
<h1 align="center">DYNORA ENGINE</h1>

<p align="center"> <strong>High-performance modular game engine written in Zig + C</strong> </p> 

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

## Table of Contents

[Overview](#overview)  
[Core Philosophy](#core-philosophy)  
[Goals](#goals)  
[Current State](#current-state)  
[First Implemented System](#first-implemented-system)  
[Repository Structure](#repository-structure-evolving)  
[Build](#build-in-progress)  
[Documentation](#documentation)  
[Contributing](#contributing)  
[Project Direction](#project-direction)   
[License](#license)  
[Author](#author)  

---

## Overview

**Dynora Engine** is a modular game engine in development, **designed to grow, adapt, and scale as unified systems** — where independent modules work together while preserving performance and flexibility.

Every subsystem is built as an independent module, allowing the engine to scale without sacrificing maintainability.

Dynora’s mission is to provide a **high-performance, deeply modular architecture** where ideas can be assembled into scalable systems — empowering developers to build complex interactive worlds with precision and control.

> **Current Status:** Pre-architecture phase  
> The Technical Design Document (TDD) is evolving, and the engine architecture is being designed with long-term scalability in mind.

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

The project is currently focused on:

- Technical Design Documentation (TDD)  
- Core architecture definition  
- Modular system validation  
- Building foundational systems  

Planned systems include:

- ECS (Entity Component System)  
- Rendering Pipeline  
- Editor  
- Physics  
- Audio  
- Asset Pipeline  

These systems will be implemented as the architecture matures.

---

## First Implemented System

### Logger

The logging system is the first subsystem implemented to validate the modular architecture.

Current design goals:

- Hot-path optimized performance  
- Modular backend support  
- Decoupled interfaces  
- Future asynchronous logging support (in development) 

Example:

```c
DYNORA_LOG_INFO(DYNORA_LOG_GENERAL, "System initialized");
```

The logger serves as the first architectural foundation for validating Dynora's modular design principles.

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

## Build (in progress)

The build pipeline is currently under development and is based on:

* Zig Build System
* C integration for low-level systems

Build instructions will be expanded as the architecture stabilizes.

---

## Documentation

Documentation is split into two layers:

### Wiki

Architecture, systems, and technical design:

[Dynora Engine Wiki](https://github.com/AndreGustavo15-Developer/DynoraEngine/wiki)

### Local Docs

Internal documentation and technical design documents:

```bash
/docs
/docs/tdd
```

The TDD defines the conceptual and technical direction of Dynora.

---

## Contributing

At this stage, contributions are focused on **architecture and system design**.

Ways to contribute:

* Discuss ideas through issues
* Review architectural decisions
* Suggest improvements to foundational systems
* Propose modular subsystem designs

See **[CONTRIBUTING.md](CONTRIBUTING.md)** for contribution guidelines.

---

## Project Direction

### Current Focus

* Define the core architecture
* Validate modular systems
* Ensure performance-first design

### Avoid

* Premature feature expansion
* External dependencies without architectural alignment

Dynora prioritizes **architectural strength before feature breadth**.

---

## License

MIT License — free for personal, educational, and commercial use.

---

## Author

Created and maintained by **[André Gustavo](https://github.com/AndreGustavo15-Developer)**.

---

<p align="center"> <strong>Assemble ideas. Build systems.</strong> </p>