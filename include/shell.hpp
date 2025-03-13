#ifndef NAN_SHELL_IMPL
#define NAN_SHELL_IMPL	

#include "mewall.h"
#include "virtual.hpp"

#pragma pack(push, 1)

namespace Virtual::Shell {
	using namespace mew::utils;
	namespace fs = std::filesystem;
	#define MAX_NAN_SHELL_COMMAND 256

	enum struct ShellSignals {
		None, Pending, Exit, Freeze
	};
	
	struct Shell {
		Virtual::VM_Async async;
		ShellSignals signals = ShellSignals::Pending;
		Shell() { }

		void SpawnExecuting(const char* path) {
			auto code = Virtual::Code_LoadFromFile(path);
			signals = ShellSignals::Freeze;
			async.Append(*code);
		}

		void Update() {
			async.ExecuteStep();
		}

		void ParserCommand(const char* cmd) {
			if (*cmd == 0) return;
			TokenRow words(cmd);
			if (words.same("run")) {
				SpawnExecuting(*++words);
			} else 
			if (words.same("exit")) {
				async.hardStop();
				signals = ShellSignals::Exit;
				return;
			}
		}

		bool listen() {
			if (signals != ShellSignals::Freeze) {
				printf(">> ");
				char buffer[MAX_NAN_SHELL_COMMAND] = {0};
				gets(buffer);
				ParserCommand(buffer);
			}
			Update();
			return signals != ShellSignals::Exit;
		}

	};
}
#pragma pack(pop)


#endif