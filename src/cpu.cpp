#include <iostream>
#include <cstdint>
#include "cpu.h"
#include "base_converter.h"

uint32_t vprocessor::CPU::Execute(uint32_t cycles, vprocessor::Memory& memory) {

	auto ADD = [&cycles, &memory, this] (uint8_t operand) {
		uint16_t sum = A;
		bool signbitcheck = !((A ^ operand) & 0x80);

		sum += operand;
		sum += C;
		A = (sum & 0xFF);
		SetZNFlags(A);
		C = sum > 0xFF;
		V = signbitcheck && ((A ^ operand) & 0x80);
	};
	
	uint32_t cyclesRequested = cycles;

	while (cycles > 0) {
		uint8_t Ins = FetchByte(cycles, memory);
		switch (Ins) {
			
			case NOOP: {
				cycles--;
				std::cout << "[INFO/CPU_Emulator] NOOP instruction successfully executed\n";
			} break;

			case JUMP: {
				uint16_t address = FetchWord(cycles, memory);
				PC = address;
				std::cout << "[INFO/CPU_Emulator] JUMP instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Program counter now on address \"" << decToHex(PC) << "\"\n";
				}
			} break;

			case JTSA: {
				PC = AR;
				AR = 0x0000;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] JTSA instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Program counter now on address \"" << decToHex(PC) << "\"\n";
					std::cout << "[DEBUG/CPU_Emulator] Address register reset\n";
				}
			}

			// Arithmetic & Logic

			case ADDC: {
				uint16_t address = FetchWord(cycles, memory);
				uint8_t operand = ReadByte(cycles, address, memory);
				ADD(operand);
				std::cout << "[INFO/CPU_Emulator] ADDC instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] " << operand << " added to accumulator (now \"" << A << "\")\n";
				}
			} break;

			case SUBC: {
				uint16_t address = FetchWord(cycles, memory);
				uint8_t operand = ReadByte(cycles, address, memory);
				ADD(~operand);
				std::cout << "[INFO/CPU_Emulator] SUBC instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] " << operand << " subtracted to accumulator (now \"" << A << "\")\n";
				}
			} break;

			case INCR: {
				uint16_t address = FetchWord(cycles, memory);
				uint8_t operand = ReadByte(cycles, address, memory);
				operand++;
				cycles--;
				WriteByte(operand, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] INCR instruction successfully executed\n";
			} break;

			case DECR: {
				uint16_t address = FetchWord(cycles, memory);
				uint8_t operand = ReadByte(cycles, address, memory);
				operand--;
				cycles--;
				WriteByte(operand, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] DECR instruction successfully executed\n";
			} break;

			// Register Manipulaton

			case LODA: {
				uint16_t address = FetchWord(cycles, memory);
				A = ReadByte(cycles, address, memory);
				SetZNFlags(A);
				std::cout << "[INFO/CPU_Emulator] LODA instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Loaded value from memory address \"Ox" << decToHex(address) << "\" to accumulator (now \"" << A << "\")\n";
				}
			} break;

			case LODX: {
				uint16_t address = FetchWord(cycles, memory);
				X = ReadByte(cycles, address, memory);
				SetZNFlags(X);
				std::cout << "[INFO/CPU_Emulator] LODX instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Loaded value from memory address \"Ox" << decToHex(address) << "\" to index register X (now \"" << X << "\")\n";
				}
			} break;

			case LODY: {
				uint16_t address = FetchWord(cycles, memory);
				Y = ReadByte(cycles, address, memory);
				SetZNFlags(Y);
				std::cout << "[INFO/CPU_Emulator] LODY instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Loaded value from memory address \"Ox" << decToHex(address) << "\" to index register Y (now \"" << Y << "\")\n";
				}
			} break;

			case STRA: {
				uint16_t address = FetchWord(cycles, memory);
				WriteByte(A, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] STRA instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Stored value from accumulator \"" << A << "\" to memory address \"Ox" << decToHex(address) << "\"\n";
				}
			}

			case STRX: {
				uint16_t address = FetchWord(cycles, memory);
				WriteByte(X, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] STRX instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Stored value from index register X \"" << X << "\" to memory address \"Ox" << decToHex(address) << "\"\n";
				}
			}

			case STRY: {
				uint16_t address = FetchWord(cycles, memory);
				WriteByte(Y, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] STRY instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Stored value from index register Y \"" << Y << "\" to memory address \"Ox" << decToHex(address) << "\"\n";
				}
			}

			case CPAX: {
				X = A;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] CPAX instruction successfully executed\n";
			} break;

			case CPAY: {
				Y = A;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] CPAY instruction successfully executed\n";
			} break;

			case CPXY: {
				Y = X;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] CPXY instruction successfully executed\n";
			} break;

			case CPYX: {
				X = Y;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] CPYX instruction successfully executed\n";
			} break;

			case INCA: {
				A++;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] INCA instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Accumulator incremented (now \"" << A << "\")\n";
				}
			} break;

			case DECA: {
				A--;
				cycles--;
				std::cout << "[INFO/CPU_Emulator] DECA instruction successfully executed\n";
				if (isProcessorDebug == true) {
					std::cout << "[DEBUG/CPU_Emulator] Accumulator decremented (now \"" << A << "\")\n";
				}
			} break;

			case STAD: {
				uint16_t address = FetchWord(cycles, memory);
				WriteWord(AR, cycles, address, memory);
				std::cout << "[INFO/CPU_Emulator] STAD instruction successfully executed\n";
			}

			case LOAD: {
				uint16_t address = FetchWord(cycles, memory);
				AR = address;
				std::cout << "[INFO/CPU_Emulator] LOAD instruction successfully executed\n";
			}

			// Only if the instruction doesn't exist will this trigger.
			default: {
				std::cerr << "[ERROR/CPU_Emulator] Invalid instruction or instruction not handled" << std::endl;
			} break;
		}
	}
	uint32_t cyclesUsed = cyclesRequested - cycles;
	return cyclesUsed;
}