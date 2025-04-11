#include <iostream>
#include <cstdint>
#include "cpu.h"
#include "base_converter.h"

int main() {
	std::cout << "[INFO/Init] Starting!\n";
	int cycles = 12;
	vprocessor::Memory CPU_MEM;
	vprocessor::CPU Processor;

	Processor.Reset(CPU_MEM);
	std::cout << "[INFO/Init] All modules are initialized\n";

	// Example instruction code
	CPU_MEM[0x0001] = 0x28;

	CPU_MEM[0x8000] = Processor.NOOP;
	CPU_MEM[0x8001] = Processor.LODA;
	CPU_MEM[0x8002] = 0x01;
	CPU_MEM[0x8003] = 0x00;
	CPU_MEM[0x8004] = Processor.INCR;
	// End of instruction code

	std::cout << "[INFO/Main] Executing program\n";
	const int mainThread = Processor.Execute(cycles, CPU_MEM);

	uint16_t programCounter = Processor.PC;
	uint16_t stackPointer = Processor.SP;
	uint16_t Carry = Processor.C;
	uint16_t Overflow = Processor.V;
	uint16_t Negative = Processor.N;
	uint16_t Zero = Processor.Z;

	uint16_t Index_X = Processor.X;
	uint16_t Index_Y = Processor.Y;
	uint16_t Accumulator = Processor.A;

	std::cout << "[INFO/Main] Program exited. Took " << cycles << " cycles to finish with " << mainThread << " cycles used\n |\n";

	std::cout << " | PC: 0x" << decToHex(programCounter) << " SP: 0x" << decToHex(stackPointer) << "\n |\n";
	std::cout << " | Flags:\n";
	std::cout << " | C: " << Carry << " V: " << Overflow << " N: " << Negative << " Z: " << Zero << "\n |\n";
	std::cout << " | Registers:\n";
	std::cout << " | A: " << Accumulator << " X: " << Index_X << " Y: " << Index_Y << "\n";
	return 0;
}
