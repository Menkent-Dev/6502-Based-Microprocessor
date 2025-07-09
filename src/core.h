#pragma once
#include <iostream>
#include <cstdint>
#include "base_converter.h"

namespace vprocessor {
	extern bool isProcessorDebug;
	struct Memory;
	struct Processor;
}

struct vprocessor::Memory {

	static constexpr uint32_t MAX_MEMORY = 65535;
	uint8_t Data[MAX_MEMORY];

	//* Initializes the Memory
	void Initialize() {
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Initializing emulated memory \"size: 65535 bytes\"\n";
		}

		for (uint32_t i = 0; i < MAX_MEMORY; i++)
		{
			Data[i] = 0;
		}

		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Done initializing emulated memory\n";
		}
	}

	//* Reads a byte
	uint8_t operator[](uint32_t Address) const {
		return Data[Address];
	}

	//* Writes a byte
	uint8_t& operator[](uint32_t Address){
		return Data[Address];
	}
};

struct vprocessor::Processor {

	// Processor registers and flags
	uint16_t PC;			//* Counter register used in a microprocessor to keep track. Short for Program Counter
	uint16_t AR;			//* Register used in storing a memory address temporally. Short for Address Register
	uint16_t SP;			//* Register used in storing the memory address of the last data element added to the stack. Short for Stack Pointer

	uint8_t A;				//* Registers used in a typical microprocessor. Short for Accumulator
	uint8_t X, Y;			//* Registers used in a typical microprocessor. It is an Index Register

	uint8_t C : 1;			//* One of the processor status flags. Short for Carry. Set interger overflows or underflows
	uint8_t Z : 1;			//* One of the processor status flags. Short for Zero. Set if result of the last operation is 0
	uint8_t V : 1;			//* One of the processor status flags. Short for Overflow. Set if result yields an invalid 2's Complement result
	uint8_t N : 1;			//* One of the processor status flags. Short for Negative. Set if result of the last operation has bit 7 set to 1

	// Opcodes:

	// System
	static constexpr uint8_t NOOP = 0x0;		//* AKA No Operation. Takes 2 cycles to finish.
	static constexpr uint8_t JUMP = 0x30;		//* AKA Jump To Address. Takes 3 cycles to finish.
	static constexpr uint8_t JTSA = 0x31;		//* AKA Jump To Stored Address.

	// Arithmetic & Logic
	static constexpr uint8_t ADDC = 0x1;		//* AKA Add With Carry. Takes 4 cycles to finish.
	static constexpr uint8_t SUBC = 0x2;		//* AKA Subtract With Carry. Takes 4 cycles to finish.
	static constexpr uint8_t INCR = 0x3;		//* AKA Increment. Takes 6 cycles to finish.
	static constexpr uint8_t DECR = 0x4;		//* AKA Decrement. Takes 6 cycles to finish.

	// Register Manipulaton
	static constexpr uint8_t LODA = 0x10;		//* AKA Load Accumulator. Takes 4 cycles to finish.
	static constexpr uint8_t LODX = 0x11;		//* AKA Load X. Takes 4 cycles to finish.
	static constexpr uint8_t LODY = 0x12;		//* AKA Load Y. Takes 4 cycles to finish.
	static constexpr uint8_t STRA = 0x13;		//* AKA Store Accumulator. Takes 4 cycles to finish.
	static constexpr uint8_t STRX = 0x14;		//* AKA Store X. Takes 4 cycles to finish.
	static constexpr uint8_t STRY = 0x15;		//* AKA Store Y. Takes 4 cycles to finish.
	static constexpr uint8_t CPAX = 0x16;		//* AKA Copy A to X. Takes 2 cycles to finish.
	static constexpr uint8_t CPAY = 0x17;		//* AKA Copy A to Y. Takes 2 cycles to finish.
	static constexpr uint8_t CPXY = 0x18;		//* AKA Copy X to Y. Takes 2 cycles to finish.
	static constexpr uint8_t CPYX = 0x19;		//* AKA Copy Y to X. Takes 2 cycles to finish.
	static constexpr uint8_t INCA = 0x1A;		//* AKA Increment A. Takes 2 cycles to finish.
	static constexpr uint8_t DECA = 0x1B;		//* AKA Decrement A. Takes 2 cycles to finish.
	static constexpr uint8_t STAD = 0x1C;		//* AKA Store Address. Takes 4 cycles to finish.
	static constexpr uint8_t LOAD = 0x1D;		//* AKA Load Address. Takes 3 cycles to finish.

	// Microprocessor Functions

	//* Resets the microprocessor
	void Reset(Memory& memory) {
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Initializing emulated processor\n";
		}
		PC = 0x8000;
		SP = 0x7F;
		C = V = N = 0;		// Resets processor status flags
		A = X = Y = 0;		// Resets registers
		memory.Initialize();

		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Done initializing emulated processor\n";
		}
	}

	//* Fetches the 8 bit data currently stored in the memory
	uint8_t FetchByte(int32_t& cycles, const Memory& memory) {
		uint8_t Data = memory[PC];
		PC++;
		cycles--;
		return Data;
	}

	//* Fetches the 16 bit data currently stored in the memory
	uint16_t FetchWord(int32_t& cycles, const Memory& memory) {
		uint16_t Data = memory[PC];
		PC++;
		Data |= (memory[PC] << 8 );
		PC++;
		cycles -= 2;
		return Data;
	}

	//* Reads the 8 bit data currently stored in the memory
	uint8_t ReadByte(int32_t& cycles, uint16_t address, const Memory& memory) {
		uint8_t data = memory[address];
		cycles--;
		return data;
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Read value from addresess \"0x" << decToHex(address) << "\"\n";
		}
	}

	//* Reads the 16 bit data currently stored in the memory
	uint16_t ReadWord(int32_t& cycles, uint16_t address, const Memory& memory) {
		uint8_t Low = ReadByte(cycles, address, memory);
		uint8_t High = ReadByte(cycles, address + 1, memory);
		return Low | (High << 8);
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Read value from addresess \"0x" << decToHex(address) << " - 0x" << decToHex(address++) << "\"\n";
		}
	}

	//* Writes an 8 bit value to memory
	void WriteByte(uint8_t operand, int32_t& cycles, uint16_t address, Memory& memory) {
		memory[address] = operand;
		cycles--;
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Value written to addresess \"0x" << decToHex(address) << "\"\n";
		}
	}

	//* Writes an 16 bit value to 2 memory addresses (One for the low byte, another for the high byte)
	void WriteWord(uint16_t operand, int32_t& cycles, uint16_t address, Memory& memory) {
		memory[address] = operand & 0xFF;
		memory[address++] = (operand >> 8);
		cycles -= 2;
		if (isProcessorDebug == true) {
			std::cout << "[DEBUG/Processor_Emulator] Value written to addresess \"0x" << decToHex(address) << " - 0x" << decToHex(address++) << "\"\n";
		}
	}

	//* Executes the data currently fetched
	void Execute(int32_t cycles, Memory& memory);

	//* Sets the appropriate flags after instruction is executed
	void SetZNFlags(uint8_t Register) {
		Z = (Register == 0x0);
		N = (Register & 0x80) > 0;
	}
};
