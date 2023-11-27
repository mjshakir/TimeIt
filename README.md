# TimeIt - Low Overhead Timing Library

![Ubuntu X86_64](https://github.com/mjshakir/TimeIt/actions/workflows/ubuntu_X86_64.yml/badge.svg)
![Ubuntu ARM](https://github.com/mjshakir/TimeIt/actions/workflows/ubuntu_arm.yml/badge.svg)
![Ubuntu RISCV](https://github.com/mjshakir/TimeIt/actions/workflows/ubuntu_riscv.yml/badge.svg)
![macOS X86_64](https://github.com/mjshakir/TimeIt/actions/workflows/macos_x86_64.yml/badge.svg)
![macOS ARM](https://github.com/mjshakir/TimeIt/actions/workflows/macos_arm.yml/badge.svg)
![Windows X86_64](https://github.com/mjshakir/TimeIt/actions/workflows/windows_x86_64.yml/badge.svg)
![Windows ARM](https://github.com/mjshakir/TimeIt/actions/workflows/windows_arm.yml/badge.svg)

TimeIt is a lightweight `C++` library designed to provide low-overhead timing functionality for your projects. Whether you need to measure the execution time of a specific function or profile an entire project, TimeIt makes it easy and efficient. This README provides an overview of TimeIt, its features, and instructions for integrating it into your C++ projects.

## Features

- Simple and easy-to-use API for measuring execution time.
- Minimal overhead to ensure accurate timing results.
- Ability to time both functions and entire projects.
- Support for various time units (seconds, milliseconds, microseconds, etc.).
- Compatibility with `C++20` and above.
- Cross-platform support for `Windows`, `Linux`, and `macOS`.

## Getting Started

### Prerequisites

- CMake (Version 3.5 or higher)
- C++ Compiler (`C++20` or higher)

### Installation

To integrate `TimeIt` into your `C++` project, follow these steps:

1. Clone the `TimeIt` repository to your local machine:

```bash
git clone https://github.com/mjshakir/TimeIt.git
```
2. Create a build directory and navigate to it:
```bash
cd TimeIt
```
```bash
mkdir build
```
```bash
cd build
```
3. Configure the build with CMake, specifying any desired options (e.g., colored output and build type):
```bash
cmake -DFORCE_COLORED_OUTPUT=ON -DCMAKE_BUILD_TYPE=Release ..
```
4. Build TimeIt using your chosen build system (e.g., `Ninja`):
```bash
cmake --build .
```

5. (Optional) Install TimeIt globally on your system:
```bash
sudo cmake --install .
```

#### Alterntive Installation
1. Install `Ninja` (if not already installed) as a build system:
- Linux (Debian based):
```bash
sudo apt-get install ninja-build -y
```
- macOS:
```bash
brew install ninja
```
- Windows:
```powershell
choco install ninja
```
2. Clone the `TimeIt` repository to your local machine:
```bash
git clone https://github.com/your_username/TimeIt.git
```
```bash
cd TimeIt
```
3. Configure the build with CMake, specifying any desired options (e.g., colored output and build type):
```bash
cmake -DFORCE_COLORED_OUTPUT=ON -DCMAKE_BUILD_TYPE=Release -B build -G Ninja
```
4. Build TimeIt using your chosen build `Ninja` system:
```bash
cd build
```
```bash
ninja
```
5. (Optional) preform test:
```bash
ninja test
```
### Including TimeIt as a Git Submodule

If you want to include the [TimeIt](https://github.com/mjshakir/TimeIt) library as a Git submodule in your project, follow these steps:

-Step 1: Add TimeIt as a Git Submodule 

In your project's repository, navigate to the directory where you want to add TimeIt as a submodule and run the following command:

```bash
git submodule add https://github.com/mjshakir/TimeIt.git extern/TimeIt
```

- Step 2: Update Your Project's CMakeLists.txt

In your project's CMakeLists.txt, configure the TimeIt submodule and link it to your project. Here's an example:
```cmake
# Include the TimeIt submodule
add_subdirectory(thirdparty/TimeIt)

# Add your project's source files

# Create an executable or library for your project
add_executable(your_project ${YOUR_SOURCE_FILES})

# Link your project with TimeIt
target_link_libraries(your_project PRIVATE TimeIt::TimeIt)

```
- Step 3: Build Your Project

Now, when you build your project, CMake will automatically build TimeIt as part of your project's build process because it's included as a submodule.

## Usage
TimeIt provides two main classes: `TimeIt` and `TimeFunction`, allowing you to time functions and projects easily.

### Timing a Project Example
```cpp
#include "TimeIt.hpp"

int main() {
    // Start timing the entire project
    TimeIt::TimeIt timer("MyProject");

    // Your project code here

    // Get the execution time in seconds
    double executionTime = timer.get_time();
    std::cout << "Project Execution Time: " << executionTime << " seconds" << std::endl;
    return 0;
}
```
### Timing a Function Example
```cpp
#include "TimeFunction.hpp"

int MyFunction(int a, int b) {
    return a*b;
}

int main() {
    // Timing a function and obtaining the execution time in seconds
    double executionTime = TimeIt::TimeFunction::timed_Function(MyFunction, 10, 20);
    std::cout << "Execution Time: " << executionTime << " seconds" << std::endl;
    return 0;
}

```

## Contributing to TimeIt
We welcome contributions to ThreadPool! Whether you're a seasoned developer or just starting out, there are many ways to contribute to this project.

### Ways to Contribute
1. Reporting bugs or problems: If you encounter any bugs or issues, please open an issue in the GitHub repository. We appreciate detailed reports that help us understand the cause of the problem.

2. Suggesting enhancements: Do you have ideas for making ThreadPool even better? We'd love to hear your suggestions. Please create an issue to discuss your ideas.

3. Code contributions: Want to get hands-on with the code? Great! Please feel free to fork the repository and submit your pull requests. Whether it's bug fixes, new features, or improvements to documentation, all contributions are greatly appreciated.

### Contribution Process
1. Fork the repository and create your branch from main.
2. If you've added or changed code, please ensure the testing suite passes. Add new tests for new features or bug fixes.
3. Ensure your code follows the existing style to keep the codebase consistent and readable.
4. Include detailed comments in your code so others can understand your changes.
5. Write a descriptive commit message.
6. Push your branch to GitHub and submit a pull request.