#include "offsets.h"

#include "miscellaneous.h"
#include "functions.h"
#include "buttons.h"
#include "convars.h"
#include "netvars.h"
#include "scripts.h"
#include "weapons.h"

auto offsets::dump() -> bool
{
	auto info = IO::GetModuleInfo(L"EasyAntiCheat_launcher.exe");
	if (!info || !info->addr || !info->size) return false;

	auto data = std::string();
	data.resize(info->size);

	auto instance = IO::CacheInstance();
	instance.RPM(info->addr, data.data(), data.size());
	if (!miscellaneous::dump(&instance, info.get(), &data)) return false;
	if (!functions::dump(&instance, info.get(), &data)) return false;
	if (!buttons::dump(&instance, info.get(), &data)) return false;
	if (!convars::dump(&instance, info.get(), &data)) return false;
	if (!netvars::dump(&instance, info.get(), &data)) return false;
	if (!scripts::dump(&instance, info.get(), &data)) return false;
	if (!weapons::dump(&instance, info.get(), &data)) return false;

	return true;
}
