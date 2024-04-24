#pragma once
#include "Based.h"

namespace offsets
{
	namespace scripts
	{
		auto __declspec(noinline) dump(IO::CacheInstance* instance, const IO::ModuleInfo* info, const std::string* data) -> bool;
	}
}
