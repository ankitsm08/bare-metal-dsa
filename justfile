set shell := ["bash", "-eu", "-o", "pipefail", "-c"]

# list available recipes
default:
    @just --list

# build both C and C++ test binaries
build-all: build-c build-cpp

# build C test binaries
build-c:
    @echo "==> Building C binaries..."
    @make -C c

# build C++ test binaries
build-cpp:
    @echo "==> Building C++ binaries..."
    @make -C cpp

# generate compile_commands.json using bear
compile-commands: clean
    @echo "==> Generating compilation database (compile_commands.json)..."
    rm -f compile_commands.json
    bear -- just build-all

# clean all build artifacts
clean:
    @echo "==> Cleaning C binaries..."
    @make -C c clean
    @echo "==> Cleaning C++ binaries..."
    @make -C cpp clean

# run a specific C test
run-c name: build-c
    ./c/bin/test_{{ name }}

# run a specific C++ test
run-cpp name: build-cpp
    ./cpp/bin/test_{{ name }}

# scaffold a new C module using template files
new-c type name:
    @if [ "{{ type }}" != "ds" ] && [ "{{ type }}" != "algo" ]; then \
        echo "Error: type must be 'ds' or 'algo'"; exit 1; \
    fi
    mkdir -p c/include/{{ type }} c/src/{{ type }} c/tests
    # Copy and substitute placeholders
    sed "s/__NAME__/{{ name }}/g; s/__TYPE__/{{ type }}/g" templates/c/header.h > c/include/{{ type }}/{{ name }}.h
    sed "s/__NAME__/{{ name }}/g; s/__TYPE__/{{ type }}/g" templates/c/source.c > c/src/{{ type }}/{{ name }}.c
    sed "s/__NAME__/{{ name }}/g; s/__TYPE__/{{ type }}/g" templates/c/test.c > c/tests/test_{{ name }}.c
    @echo "Scaffolded C files for {{ name }} ({{ type }})"

# scaffold a new C++ module (header-only) using template files
new-cpp type name:
    @if [ "{{ type }}" != "ds" ] && [ "{{ type }}" != "algo" ]; then \
        echo "Error: type must be 'ds' or 'algo'"; exit 1; \
    fi
    mkdir -p cpp/include/{{ type }} cpp/tests
    # capitalize the first letter for C++ Class Name
    NAME_CAP=$(echo "{{ name }}" | sed -E 's/^(.)/\U\1/') ; \
    sed "s/__NAME__/{{ name }}/g; s/__TYPE__/{{ type }}/g; s/__CLASS_NAME__/${NAME_CAP}/g" templates/cpp/header.hpp > cpp/include/{{ type }}/{{ name }}.hpp
    sed "s/__NAME__/{{ name }}/g; s/__TYPE__/{{ type }}/g" templates/cpp/test.cpp > cpp/tests/test_{{ name }}.cpp
    @echo "Scaffolded C++ (header-only) files for {{ name }} ({{ type }})"

# format all C/C++ code using clang-format
format:
    @echo "==> Formatting C/C++ files..."
    fd -tf -e c -e cpp -e h -e hpp \
      -X clang-format -i
    @echo "==> Formatting Markdown files..."
    fd -tf -e md -X prettier --write --color
