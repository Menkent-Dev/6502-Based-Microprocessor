# Building the Program

## Prequisites
Before compiling (as with any other cpp programs):
* Install [g++](https://gcc.gnu.org/)

## 1. Visual Studio Code Tasks
1. Open Visual Studio Code.
2. Go to the command palette (or press Ctrl+Shift+P)
3. Click `Run Tasks` and select the following:
   * Run `Build and compile main and object files` if you want to compile the entire program.
   * Run `Link core object file` and/or `Link base converter object file` if you want to link the individual object files.

## 2. Manual (For those who use other IDEs or primarily use terminals)
1. Open any terminal or IDE of your choice.
2. Compile:
   * For the individual cpp files:
   ```bash
   g++ -c src/core.cpp -o build/object/core.o
   g++ -c src/base_converter.cpp -o build/object/base_converter.o
   ```
   * For the main program itself:
   ```bash
   g++ src/main.cpp build/object/core.o build/object/base_converter.o -o build/virtual_microprocessor.exe
   ```


> [!NOTE]
> The compiler may take some time to compile the entire program, so please wait.


If everything went well, the compiled program should be in the `build` directory.
