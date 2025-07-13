# Building the Program

1. Install [g++](https://gcc.gnu.org/)
2. Open any terminal or IDE of your choice.
3. Compile:
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
> The compiler may take a while to compile the whole program, so please wait.

If everything went well, the compiled program should be in the `build` directory.
