---
sidebar_position: 2
---

```cpp
	using namespace Virtual;
	CodeBuilder builder;
	builder << Instruction_PUTS;
	builder << 0U;
	builder += L"hellow, word";
	Code* code = *builder;
	Execute(*code);
```
