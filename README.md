# Randomly Generated Mountains

A while ago I came across the [Diamond-Square Algorithm](https://en.wikipedia.org/wiki/Diamond-square_algorithm) and wanted to create my own implementation. My version is a recursive approach but after reading more about other implementations, an iterative approach makes the code easier to understand and write. This project served primarily as a way to familiarize myself with C++ and various tools used in development like CMake, Catch (TDD), and OpenGL. You can see some of the results below.


## Images
![Primary Colors Mountain](https://i.imgur.com/c55qIHj.png)
![Red/Blue Mountain](https://i.imgur.com/hqcNnr8.png)
![Wire Mesh Mountain](https://i.imgur.com/u8HTbBr.png)


## Usage

If you want to run the project on your own machine,

1. Clone the repo
2. Navigate into it's root directory and enter the following commands in your terminal:
    ```console
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    ```
    this will create an executable program in the build directory. (Make sure you have [CMake](https://cmake.org/) installed)
3. To run the executable enter:
    ```console
    $ src/mountains
    ```

## Notes

As of now the only way to change what is rendered is to mess around with the code directly in ```src/main.cc``` but I may add a an easier way to draw mountains from a .txt file or the command line in the future.
