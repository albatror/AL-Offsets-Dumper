#include "scripts.h"

auto offsets::scripts::dump(IO::CacheInstance* instance, const IO::ModuleInfo* info, const std::string* data) -> bool
{
	struct ScriptInfo
	{
		uint64_t name;
		uint64_t data;
		uint64_t _pad0;
		uint32_t size;
		uint32_t _pad1;
		uint64_t _pad2;
	};

	// r2\scripts\vscripts\feature_flags.gnut.client
	for (auto i = 0xF598C78ull; i < info->size; i += sizeof(ScriptInfo))
	{
		auto scri = reinterpret_cast<const ScriptInfo*>(data->c_str() + i);
		if (!scri || !scri->name || !scri->data || !scri->size) break;

		char name[0x100];
		name[sizeof(name) - 1] = '\0';
		if (!instance->RPM(scri->name, name, sizeof(name) - 1)) break;
		
		auto cstr = std::string();
		cstr.resize(scri->size);
		if (!instance->RPM(scri->data, cstr.data(), cstr.size())) break;

		std::filesystem::create_directories(std::filesystem::path(name).parent_path().string());
		auto stream = std::ofstream(name, std::ios::binary);
		if (!stream.good()) continue;

		stream.write(cstr.c_str(), cstr.size() - 1);
		stream.flush();
		stream.close();
	}

	return true;
}
