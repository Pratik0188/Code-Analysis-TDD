# Code Analysis

An instructional project to implement, using a TDD approach, a set of rules for metadata needed for (source) code analysis.

## Project 3: Code Analysis Tool (TDD Approach)

### Overview
This project involves developing a static code analysis tool using the Test-Driven Development (TDD) approach. The tool takes input from various sources, such as source code files, archives, or standard input, and generates XML metadata about the source code. The metadata includes attributes such as filename, language, URL, hash, lines of code (LOC), and timestamp.

The goal is to implement a series of rules for generating the XML metadata according to the specified requirements, using the TDD workflow. The project must be implemented in multiple steps, with each rule being implemented and tested one at a time.

### Project Structure

- **CodeAnalysis.cpp**: The main implementation file containing the `formatAnalysisXML()` function.
- **CodeAnalysisTest.cpp**: The test file where individual test cases for each rule are written.
- **README.md**: This file, providing an overview of the project and the setup instructions.
- **CMakeLists.txt**: CMake configuration for building the project.

### Rules Implementation

The project is structured around implementing specific rules, which are detailed below. Each rule must be implemented following the TDD process:
1. Write a test.
2. Implement the minimal code to pass the test.
3. Refactor the code for clarity and simplicity.

The rules cover various attributes such as `language`, `filename`, `LOC`, `hash`, `timestamp`, and handling of special cases such as standard input or archives.

#### Rules Implemented

1. **Language Determination**:
   - For non-archive source-code files, the file extension determines the language.
   - For archives, the entry filename determines the language.
   - For standard input (`stdin`), a declared language must be provided.

2. **Filename**:
   - For non-archive files, the disk filename is used for the `filename` attribute.
   - For standard input, the filename is represented by `-` and the entry filename is `"data"`.
   - For archives, the entry filename is used for the `filename` attribute.

3. **Lines of Code (LOC)**:
   - If provided, include the `LOC` attribute with the value.
   - The minimum LOC value is `0`.

4. **Hash**:
   - The hash is a SHA1 160-bit value represented in 40 hex characters.
   - If provided, the `hash` attribute is included.

5. **Timestamp**:
   - If a timestamp is provided, include the `timestamp` attribute.

6. **URL**:
   - If a URL is provided, include the `url` attribute.
   - The URL attribute takes priority over other sources.

7. **Error Handling**:
   - Print error messages for unsupported file extensions or missing language declarations for `stdin`.

#### Error Messages
- `"Extension not supported"` for unsupported file extensions.
- `"Using stdin requires a declared language"` when `stdin` input is used without a declared language.

### TDD Workflow

For each rule:
1. **Write a test**: Add a test case to `CodeAnalysisTest.cpp`.
2. **Implement the rule**: Write the minimal code to pass the test in `CodeAnalysis.cpp`.
3. **Refactor**: Clean up the code for clarity and simplicity while ensuring all tests pass.
4. **Commit**: Commit each change with a meaningful message.

### Commit Message Guidelines

To maintain a consistent style and clarity in the project history, follow the guidelines below when committing changes.

#### General Guidelines
- **Start with a verb**: Use action verbs to describe what the commit does (e.g., `Add`, `Fix`, `Change`, `Refactor`).
- **Capitalized subject line**: Always capitalize the first letter of the subject line.
- **Keep the subject concise**: Limit the subject line to 50 characters or less.
- **No period at the end of the subject line**: Do not add a period at the end of the subject line.
- **Use imperative mood**: Write the message as if giving a command (e.g., `Fix bug` instead of `Fixed bug`).
- **Use the body for additional context**: If necessary, use the body of the commit to explain **why** the change was made, not **what** was changed.

#### Example Commit Message Format
```bash
git commit -am "Add new feature for code analysis"
```
# Build Instructions for Code Analysis Project

This document provides the instructions for building the Code Analysis Project on macOS using both GCC and Clang compilers.

## Prerequisites

Before building the project, ensure you have the following installed:

- **GCC** or **Clang** for compiling the code.
- **CMake** for configuring and building the project.

### Installing GCC on macOS

If you don't have GCC installed on your macOS system, you can install it using Homebrew:

```bash
brew install gcc
mkdir build-gcc
cd build-gcc
cmake .. --preset macos-gcc
make
./CodeAnalysisTest
```
### Using build-clang on macOS
```bash
mkdir build-clang
cd build-clang
cmake .. --fresh
make
./CodeAnalysisTest

