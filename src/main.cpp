#include <iostream>
#include <cstdint>
#include "cpu.h"
#include "base_converter.h"

int main() {
	std::cout << "[INFO/Init] Starting!\n";
	int cycles = 12;
	vprocessor::Memory memory;
	vprocessor::CPU processor;

	processor.Reset(memory);
	std::cout << "[INFO/Init] All modules are initialized\n";

	memory[0x0001] = 0x28;

	memory[0x8000] = processor.NOOP;
	memory[0x8001] = processor.LODA;
	memory[0x8002] = 0x01;
	memory[0x8003] = 0x00;
	memory[0x8004] = processor.INCR;

	std::cout << "[INFO/Main] Executing program\n";
	const int mainThread = processor.Execute(cycles, memory);

	uint16_t programCounter = processor.PC;
	uint16_t stackPointer = processor.SP;
	uint16_t Carry = processor.C;
	uint16_t Overflow = processor.V;
	uint16_t Negative = processor.N;
	uint16_t Zero = processor.Z;

	uint16_t Index_X = processor.X;
	uint16_t Index_Y = processor.Y;
	uint16_t Accumulator = processor.A;

	std::cout << "[INFO/Main] Program exited. Took " << cycles << " cycles to finish with " << mainThread << " cycles used\n";

	std::cout << "[INF0/CPU_Emulator] PROCESSOR TRACE:\n |\n";
	std::cout << " | PC: 0x" << decToHex(programCounter) << " SP: 0x" << decToHex(stackPointer) << "\n |\n";
	std::cout << " | Flags:\n";
	std::cout << " | C: " << Carry << " V: " << Overflow << " N: " << Negative << " Z: " << Zero << "\n |\n";
	std::cout << " | Registers:\n";
	std::cout << " | A: " << Accumulator << " X: " << Index_X << " Y: " << Index_Y << "\n";
	return 0;
}
