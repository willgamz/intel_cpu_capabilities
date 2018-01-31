#pragma once

#include <stdio.h>
#include <intrin.h> 
#include <iostream>
#include <bitset> 

namespace intel {
	namespace pt {
		
		//Enumeration of Intel Processor Trace Capabilities
		//Intel PT CPUID.(EAX=07H,ECX=0H):EBX[bit 25] = 1.
		class cpu_capabilties 
		{
		public:
			const char* leaf_ebx_14h[32] = {
				"0 CR3 Filtering Support",
				"1 Configurable PSB_and CycleAccurate Mode Supported",
				"2 IP Filtering and TraceStop supported, and Preserve Intel PT MSRs across warm reset",
				"3 MTC Supported",
				"4 PTWRITE Supported",
				"5 Power Event Trace Supported",
				"rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv", //reserved
				"rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv"
			};

			const char* leaf_ecx_14h[32] = {
				"0 ToPA Output Supported",
				"1 ToPA Tables Allow Multiple Output Entries",
				"2 Single-Range Output Supported",
				"3 Output to Trace Transport Subsystem Supported",
				"rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv", //reserved
				"rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv","rv"
				"31 IP Payloads are LIP"
			};

		public:
			cpu_capabilties() { init_cpuid_ctx(); }

		public:
			void dump() 
			{
				std::cout << std::endl;
				std::cout << "Intel PT CPU capabilities Analysis:" << std::endl;
				if (std::bitset<32>(cpuid_eax07_ecx0[1]).test(25))
				{
					std::cout << " Intel PT Supported." << std::endl;
					std::cout << "   capabilities EBX:" << std::endl;
					for (int i = 0; i <= 31; i++)
					{
						if (std::bitset<32>(leaf_14h_regs[1]).test(i))
							std::cout << "    " << leaf_ebx_14h[i] << std::endl;
					}

					std::cout << "   capabilities ECX:" << std::endl;
					for (int i = 0; i <= 31; i++)
					{
						if (std::bitset<32>(leaf_14h_regs[2]).test(i))
							std::cout << "    " << leaf_ebx_14h[i] << std::endl;
					}
				}
				else 
				{
					std::cout << " No Intel PT Supported" << std::endl;
				}

				std::cout << std::endl;
				std::cout << "Intel PT CPU capabilities raw data:" << std::endl;
				std::cout << " Features: (CPUID.(EAX=07H,ECX=0H)):" << std::endl;
				std::cout << "  EAX:" << std::bitset<32>(cpuid_eax07_ecx0[0]) << std::endl;
				std::cout << "  EBX:" << std::bitset<32>(cpuid_eax07_ecx0[1]) << "  : Note: 25 bit must be ON. Example: " << std::bitset<32>((1 << 25)) << std::endl;
				std::cout << "  ECX:" << std::bitset<32>(cpuid_eax07_ecx0[2]) << std::endl;
				std::cout << "  EDX:" << std::bitset<32>(cpuid_eax07_ecx0[3]) << std::endl;

				std::cout << "  Capabilities (CPUID.(EAX=14H,ECX=0)):" << std::endl;
				std::cout << "    EAX:" << std::bitset<32>(leaf_14h_regs[0]) << std::endl;
				std::cout << "    EBX:" << std::bitset<32>(leaf_14h_regs[1]) << std::endl;
				std::cout << "    ECX:" << std::bitset<32>(leaf_14h_regs[2]) << std::endl;
				std::cout << "    EDX:" << std::bitset<32>(leaf_14h_regs[3]) << std::endl;

				std::cout << "  Capabilities (CPUID.(EAX=14H,ECX=1)):" << std::endl;
				std::cout << "    EAX:" << std::bitset<32>(leaf_14h_subleaf_01_regs[0]) << std::endl;
				std::cout << "    EBX:" << std::bitset<32>(leaf_14h_subleaf_01_regs[1]) << std::endl;
				std::cout << "    ECX:" << std::bitset<32>(leaf_14h_subleaf_01_regs[2]) << std::endl;
				std::cout << "    EDX:" << std::bitset<32>(leaf_14h_subleaf_01_regs[3]) << std::endl;
			}

		private:
			void init_cpuid_ctx()
			{
				__cpuidex(cpuid_eax07_ecx0, 0x07, 0);
				__cpuidex(leaf_14h_regs, 0x14, 0);
				__cpuidex(leaf_14h_subleaf_01_regs, 0x14, 1);
			}

		private:
			//[0]EAX, [1]EBX,[2]ECX, [3]EDX
			int cpuid_eax07_ecx0[4] = { 0 };        			
			int leaf_14h_regs[4] = { 0 };
			int leaf_14h_subleaf_01_regs[4] = { 0 };
		};
	}	
}
