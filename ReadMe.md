

# NextJS Code Analyzer
NextJS Code Analyzer is a comprehensive tool designed for developers working with Next.js. It specializes in parsing JavaScript or TypeScript code into an Abstract Syntax Tree (AST) and performing various analysis tasks to improve code quality, maintainability, and performance. This tool is ideal for Next.js developers looking to optimize their codebase.

## Features
- AST Parsing: Convert your Next.js codebase into an AST for detailed analysis.
- Code Analysis: Perform a variety of analysis tasks to identify potential issues and optimization  opportunities.
- Support for JavaScript and TypeScript: Compatible with both JavaScript and TypeScript Next.js projects.

## Prerequisites
Before you can use or contribute to NextJS Code Analyzer, you need to have the following installed on your system:

- Node.js (preferably the latest LTS version)
- npm or Yarn (for managing JavaScript dependencies)
- CMake (for building C++ code)
- A C++ compiler like GCC, Clang, or MSVC (depending on your platform)

# NextJS Code Analyzer

NextJS Code Analyzer is a tool designed to analyze Next.js codebases by parsing the JavaScript or TypeScript code into an AST (Abstract Syntax Tree) and performing various analysis tasks. It currently gives you feedback on whether your component is correctly defined as a 
client side operation, or should be refactored. 

## Prerequisites

Before you can use or contribute to NextJS Code Analyzer, you need to have the following installed on your system:

- Node.js (preferably the latest LTS version)
- npm or Yarn (for managing JavaScript dependencies)
- CMake (for building C++ code)
- A C++ compiler like GCC, Clang, or MSVC (depending on your platform)
- Python (required by node-gyp for building native addons)

## Setup

To set up the project, follow these steps:

1. **Clone the Repository:**

```bash
git clone --recurse-submodules https://github.com/YorickdeJong/nextjs-code-analyzer.git 
```

Install JavaScript Dependencies and build cmake:

```bash
npm install
```

or if you're using Yarn:

```bash
yarn install
```

## Building repo

To build to C++ and typescript files, run:

```bash
npm run build
```

To build in debug mode, run:

```bash
npm run debug-build
```

## Parsing

Run the following command to parse data:

```bash
node parse <path_to_file_name>
```


## Usage Examples Localy
# Parsing a File

To parse a specific file, use the following command:

```bash
cd implementations/typescript/src/out && node index.js
```


### LAUNCH NEXTJS CODE ANALYZER EXTENSION IN DEBUG MODE FOR TESTING
1. Open a new VS Code instance with the workspace directory set to nextjs-code-analyzer
2. Press F5 with the src/extension.ts opened
3. In the new window press CTRL+SHIFT+P and enter NEXTJS, select the extension that pops up
4. Select a file to debug



## Contributing Guidelines
We welcome contributions to the NextJS Code Analyzer! If you're interested in contributing, please follow these guidelines:

- Code Standards: Ensure your code adheres to the project's coding standards.
- Pull Requests: Submit pull requests with clear, descriptive titles and detailed descriptions of the changes.
Issue Reporting: For bug reports or feature requests, use the issue tracker with clear, concise, and complete information.
License
- NextJS Code Analyzer is released under MIT, which allows free usage of this library.


Created by Blue Waterfall:
- www.bluewaterfall.nl/en
- www.bluewaterfall.nl/nl
- www.bluewaterfall.nl/fr
- www.bluewaterfall.nl/du

