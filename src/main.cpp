#include <iostream>
#include <cstdint>
#include "cpu.h"
#include "base_converter.h"

int main() {
	std::cout << "[INFO/Init] Starting!\n";
	int cycles = 12;
	vprocessor::Memory CPU_MEM;
	vprocessor::CPU MicroCPU;

	MicroCPU.Reset(CPU_MEM);
	std::cout << "[INFO/Init] All modules are initialized\n";

	CPU_MEM[0x0001] = 0x28;

	CPU_MEM[0x8000] = MicroCPU.NOOP;
	CPU_MEM[0x8001] = MicroCPU.LODA;
	CPU_MEM[0x8002] = 0x01;
	CPU_MEM[0x8003] = 0x00;
	CPU_MEM[0x8004] = MicroCPU.INCR;

	std::cout << "[INFO/Main] Executing program\n";
	const int mainThread = MicroCPU.Execute(cycles, CPU_MEM);

	uint16_t programCounter = MicroCPU.PC;
	uint16_t stackPointer = MicroCPU.SP;
	uint16_t Carry = MicroCPU.C;
	uint16_t Overflow = MicroCPU.V;
	uint16_t Negative = MicroCPU.N;
	uint16_t Zero = MicroCPU.Z;

	uint16_t Index_X = MicroCPU.X;
	uint16_t Index_Y = MicroCPU.Y;
	uint16_t Accumulator = MicroCPU.A;

	std::cout << "[INFO/Main] Program exited. Took " << cycles << " cycles to finish with " << mainThread << " cycles used\n";

	std::cout << "[INF0/CPU_Emulator] PROCESSOR TRACE:\n |\n";
	std::cout << " | PC: 0x" << decToHex(programCounter) << " SP: 0x" << decToHex(stackPointer) << "\n |\n";
	std::cout << " | Flags:\n";
	std::cout << " | C: " << Carry << " V: " << Overflow << " N: " << Negative << " Z: " << Zero << "\n |\n";
	std::cout << " | Registers:\n";
	std::cout << " | A: " << Accumulator << " X: " << Index_X << " Y: " << Index_Y << "\n";
	return 0;
}
