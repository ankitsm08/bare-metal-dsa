# Bare-Metal DSA

My personal playground for building core data structures and algorithms completely from scratch. No STL, no standard library magic for the internals. Just raw memory, pointers, and math.

I usually start by writing everything in strict C. It forces me to actually understand what's happening under the hood with memory allocation (`malloc`/`free`) and double pointers. Once I have the raw mechanics working and understand the system-level execution, I re-implement the same structures and algorithms in C++. This helps me understand how templates, classes, and OOP abstractions are used to build the standard libraries I rely on every day.

## Repository Structure

```text
.
├── c/                      # Raw C implementations
│   ├── bin/                # Compiled test executables (ignored in git)
│   ├── include/            # Header files (.h)
│   │   ├── algo/
│   │   └── ds/
│   ├── src/                # Source files (.c)
│   │   ├── algo/
│   │   └── ds/
│   ├── tests/              # Standalone test files with main()
│   └── Makefile            # Auto-links src/ and tests/
│
├── cpp/                    # C++ Object-Oriented implementations
│   ├── bin/
│   ├── include/            # Header files (.hpp)
│   │   ├── algo/
│   │   └── ds/
│   ├── tests/
│   └── Makefile
│
└── justfile                # Repo automation and scaffolding
```

## Tooling and Automation

This repository uses `just` as a command runner for building, testing, and scaffolding.  
Optional: `bear` to generate `compile_commands.json` for LSP.

### Commands

**Build and Run**

```bash
just build-all         # Compiles everything in c/ and cpp/
just build-c           # Compiles only C binaries
just run-c vector      # Builds and runs c/bin/test_vector
just compile-commands  # Generates compile_commands.json
```

**Scaffold New Code**

Automatically generates the `.h`, `.c`, and `test_*.c` for C, `.hpp`, and `test_*.cpp` for C++ boilerplate for a new data structure or algorithm.

```bash
# just <new-c|new-cpp> <ds|algo> <name>
just new-c ds linked_list
just new-cpp algo dijkstra
```

**Format Code**

Requires `fd`, `clang-format`, and `prettier`.

```bash
just format
```

## License

**MIT License**
