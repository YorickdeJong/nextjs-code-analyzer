# NextJS Code Analyzer

NextJS Code Analyzer is a tool designed to analyze Next.js codebases by parsing the JavaScript or TypeScript code into an AST (Abstract Syntax Tree) and performing various analysis tasks.

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