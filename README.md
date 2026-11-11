
---
language:
  - en
license: mit
tags:
  - x86-64
  - linux
  - cpp
  - c-plus-plus
  - systems-programming
  - debugging
  - symbolic-debugging
  - reverse-engineering
  - cybersecurity
  - security-research
  - ai-agent
  - agent-architecture
---

## x86 Agent Kernel

A symbolic debugging agent for Linux x86-64.

### Overview

x86 Agent Kernel is an experimental C++20 project
focused on developing an agent architecture for
low-level system observation, symbolic reasoning
and debugging on Linux x86-64 environments.

### Architecture

The project is organised into three primary components:

- **Kernel:** Core agent functionality and coordination.
- **Perception:** System observation and information gathering.
- **Reasoning:** Symbolic reasoning and decision-making.

### Technology Stack

- C++20
- CMake 3.20+
- Linux x86-64

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Project Status

Experimental development.

### Licence

See [LICENSE](LICENSE).
