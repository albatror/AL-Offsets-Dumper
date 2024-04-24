#include "functions.h"

auto offsets::functions::dump(IO::CacheInstance*, const IO::ModuleInfo*, const std::string* data) -> bool
{
	auto stream = std::ofstream("functions.ini");
	if (!stream.good()) return false;
	stream << "[functions]\n";

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\xE8\x00\x00\x00\x00\x4C\x8B\xF0\x48\x8D\x8D", "x????xxxxxx");
		if (!offset) return false;
		offset += 1;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		GetDataTableAsset = offset;
		stream << "GetDataTableAsset=0x" << std::hex << GetDataTableAsset << "\n";
	}

	stream.flush();
	stream.close();
	return true;
}
