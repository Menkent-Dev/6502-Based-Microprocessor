#include <iostream>
#include <fstream>
#include <cstdint>
#include "core.h"
#include "base_converter.h"

vprocessor::Memory LoadDefaultProgram(int loadCode, vprocessor::Memory memory, vprocessor::Processor processor) {
	if (loadCode == 1) {
		std::cout << "[WARNING/Main] File cannot be opened. Using built-in program\n";
	} else if (loadCode == 2) {
		std::cout << "[INFO/Main] No file provided. Using built-in program\n";
	}
	memory[0x0001] = 0x28;

	memory[0x8000] = processor.NOOP;
	memory[0x8001] = processor.LODA;
	memory[0x8002] = 0x01;
	memory[0x8003] = 0x00;
	memory[0x8004] = processor.INCR;

	std::cout << "[INFO/Main] Program loaded in memory\n";
	if (vprocessor::isProcessorDebug == true) {
		std::cout << "[DEBUG/Main] Loaded \"default_program\" to memory location 0x8000-0x8100\n";
	}

	return memory;
}

int main(int argc, char* argv[]) {
	std::cout << "[INFO/Init] Starting!\n";
	int cycles = 12;
	vprocessor::Memory memory;
	vprocessor::Processor processor;

	if (argc > 1 && argv[2] != NULL) {
		std::string programMode = argv[2];
		if (programMode == "1") {
			vprocessor::isProcessorDebug = true;
			std::cout << "[DEBUG/Init] Debug mode enabled\n";
		}
	}

	processor.Reset(memory);
	std::cout << "[INFO/Init] All modules are initialized\n";

	if (argv[1] != NULL) {
		std::string filePath = argv[1];
		std::ifstream inputFile(filePath);
		char inputBuffer[256];
		inputFile.open(filePath, inputFile.binary | inputFile.in);
		if (inputFile.is_open() && argc > 1) {
			for (int i = 0; i < 256; i++)
			{
				inputFile.read(&inputBuffer[i], i);
				memory[0x8000 + i] = inputBuffer[i];
			}
			std::cout << "[INFO/Main] Loaded file contents to memory\n";
			if (vprocessor::isProcessorDebug == true) {
				std::cout << "[DEBUG/Main] Loaded \"" << filePath << "\" to memory location 0x8000-0x8100\n";
			}
		} else if (inputFile.is_open() == false) {
			memory = LoadDefaultProgram(1, memory, processor);
		}
	} else {
		memory = LoadDefaultProgram(2, memory, processor);
	}

	std::cout << "[INFO/Processor_Emulator] Executing program\n";
	processor.Execute(cycles, memory);

	uint16_t programCounter = processor.PC;
	uint16_t stackPointer = processor.SP;
	uint16_t addressRegister = processor.AR;
	uint16_t Carry = processor.C;
	uint16_t Overflow = processor.V;
	uint16_t Negative = processor.N;
	uint16_t Zero = processor.Z;

	uint16_t Index_X = processor.X;
	uint16_t Index_Y = processor.Y;
	uint16_t Accumulator = processor.A;

	std::cout << "[INFO/Processor_Emulator] Program exited (Reason: Program run out of cycles)\n";
	if (vprocessor::isProcessorDebug ==  true) {
		std::cout << "[DEBUG/Processor_Emulator] PROCESSOR TRACE:\n |\n";
		std::cout << " | PC: 0x" << decToHex(programCounter) << " SP: 0x" << decToHex(stackPointer) << " AR: 0x" << decToHex(addressRegister) << "\n |\n";
		std::cout << " | Flags:\n";
		std::cout << " | C: " << Carry << " V: " << Overflow << " N: " << Negative << " Z: " << Zero << "\n |\n";
		std::cout << " | Registers:\n";
		std::cout << " | A: " << Accumulator << " X: " << Index_X << " Y: " << Index_Y << "\n";
	}

	std::cout << "[INFO/Main] Exiting Emulator\n";
	return 0;
}
