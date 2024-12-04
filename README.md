# Code Analysis

An instructional project to implement, using a TDD approach, a set of rules for metadata needed for (source) code analysis.

## Project : Code Analysis Tool (TDD Approach)

### Overview
This project involves developing a static code analysis tool using the Test-Driven Development (TDD) approach. The tool takes input from various sources, such as source code files, archives, or standard input, and generates XML metadata about the source code. The metadata includes attributes such as filename, language, URL, hash, lines of code (LOC), and timestamp.

The goal is to implement a series of rules for generating the XML metadata according to the specified requirements, using the TDD workflow. The project must be implemented in multiple steps, with each rule being implemented and tested one at a time.

### Project Structure

- **CodeAnalysis.cpp**: The main implementation file containing the `formatAnalysisXML()` function.
- **CodeAnalysisTest.cpp**: The test file where individual test cases for each rule are written.
- **README.md**: This file, providing an overview of the project and the setup instructions.
- **CMakeLists.txt**: CMake configuration for building the project.

# Source Code Static Analysis Tool

This project implements a static code analysis tool that processes input from various sources, including individual files, directories, source-code archives, and standard input (stdin). The tool generates XML metadata for the analyzed source code, which includes essential information such as filename, programming language, URL, hash, lines of code (LOC), and timestamp.

## Input Sources

The input for the code analysis tool can come from the following sources:

1. **Individual files**: A single source code file (e.g., `main.cpp`).
2. **Directories**: A directory containing multiple source code files (e.g., `src/`).
3. **Source-code archives**: Compressed archives containing source code files (e.g., `project.tar.gz`, `file.zip`).
4. **Standard input (stdin)**: Source code provided directly via standard input (e.g., using `std::cin`).

Additionally, source code files and archives can include an associated **URL** that points to the source code location (e.g., `https://mlcollard.net/fragment.cpp`).

## Output Format

The output of the analysis is an XML element containing metadata about the source code. This metadata includes the following attributes:

- **language**: The programming language of the source code.
- **url**: The URL associated with the source code (if provided).
- **filename**: The name of the source code file.
- **timestamp**: The timestamp of when the analysis was performed.
- **loc**: The number of lines of code (LOC).
- **hash**: The SHA1 hash of the source code content.

### Example XML Output

For the following source code:

```cpp
if (a < b)
    a = b;
```
the resulting XML is:

```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" url="http://mlcollard.net/fragment.cpp" filename="fragment.cpp" timestamp="Thu Oct 31 12:15:00 2024" loc="3" hash="39dcad4f59855aa76420aa3d69af3d7ba30a91bb">
if (a &lt; b)
    a = b;
</code:unit>
```
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

The workflow for implementing one rule:
```
1. Add a single new test case for a single specific rule in the test program CodeAnalysisTest.cpp
2. Successfully compile and build
3. Run the test program and verify that the test case fails
4. Add the implementation only for the new test case in the file CodeAnalysis.cpp
5. Successfully compile and build
6. Run the test program and verify that all tests pass, including the new test case
7. Refactor the test and the added code
8. Successfully compile and build
9. Run the test program and verify that all tests still pass, including the new test case
10. Commit with the appropriate commit message
```
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

