#ifndef NAN_LD_HPP
#define NAN_LD_HPP

#include "asm.hpp"
#include "mewtypes.h"
#include "mewlib.h"
#include "mewstack.hpp"
#include "virtual.hpp"

namespace nanld {
	struct Linker {
		Virtual::CodeBuilder cb;
		nanasm::Compiler base;
		mew::stack<nanasm::Compiler> compilers;
		u64 cursor = 0;

		Linker() {}
		Linker(nanasm::Compiler base, mew::stack<nanasm::Compiler> compilers)
			: base(base), compilers(compilers) {}
		
		Linker(const char* base_path, mew::stack<const char*> pathes)
			: base(nanasm::Compiler::debugRead(base_path)),
			compilers(mew::readStack(pathes, nanasm::Compiler::debugRead))
			{  }

		inline void Merge() {
			while (MergeNext()) {}
		}

		void ShiftCodePoints(nanasm::Compiler& comp, s64 offset) {
			for (auto& p: comp.label) {
				p.second += offset;
			}
			for (auto& p: comp.calles) {
				p.first += offset;
				p.second += offset;
			}
			for (auto& p: comp.external_calles) {
				p.second += offset;
			}
			for (auto& p: comp.data_calles) {
				p.first += offset;
			}
		}
		/**
		 * @brief 
		 * Order:
			```js
			[base_entry] 
			[rhm_entry]  
			[base_code]
			[rhm_code] 
			[base_data] 
			[rhm_data]
			```
		 */
		bool MergeNext() {
			if (cursor >= compilers.count()) {return false;}
			auto rhm = compilers.at(cursor++);
			u64 next_code_size = base.cb.code_size()+rhm.cb.code_size();
			u64 next_data_size = base.cb.data_size()+rhm.cb.data_size();
			u64 offset_code_size = base.cb.code_size();
			u64 offset_data_size = base.cb.data_size();

			/* merge entry */
			u64 base_entry_end = base.label.at("end-entry");
			u64 rhm_entry_end = rhm.label.at("end-entry");
			auto rhm_entry = rhm.cb.at(0);
			// shift rhm calles from entry 
			for (auto& p: rhm.calles) {
				if (p.first > rhm_entry_end) continue;
				rhm.cb.putAtCode(p.first, p.second+base_entry_end);
			}
			base.cb.insertAtCode(base_entry_end, rhm_entry, rhm_entry_end);
			ShiftCodePoints(base, rhm_entry_end);
			
			/* find & replace extern calles */
			for (auto& p: base.external_calles) {
				auto it = rhm.label.find(p.first);
				if (it == rhm.label.end()) continue;
				base.cb.putAtCode(p.second, it->second);
				base.external_calles.erase(p.first);
			}
			for (auto& p: rhm.external_calles) {
				auto it = base.label.find(p.first);
				if (it == base.label.end()) continue;
				rhm.cb.putAtCode(p.second, it->second);
				rhm.external_calles.erase(p.first);
			}
			base.external_calles.merge(rhm.external_calles);

			/* merge data */
			u64 data_offset = base.cb.data_size();
			for (auto& p: rhm.data_calles) {
				p.second.offset += data_offset;
				rhm.cb.putAtData(p.first, p.second.offset);
			}
			base.cb.AddData(rhm.cb.GetData(), rhm.cb.data_size());
			
			/* merge code */
			auto rhm_code = rhm.cb.at(rhm_entry_end);
			u64 entry_end = base_entry_end+rhm_entry_end;
			// shift for read calles & labels offset
			ShiftCodePoints(rhm, entry_end);
			// insert code
			base.cb.insertAtCode(entry_end, rhm_code, rhm.cb.code_size()-rhm_entry_end);
			
		
			return true;
		}

	};
}

#endif