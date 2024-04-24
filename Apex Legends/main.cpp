#include "Based.h"

auto main(int argc, const char* argv[]) -> int
{
	(void)argc;
	(void)argv;
	std::atexit(IO::FREE);
	if (!IO::INIT(L"EasyAntiCheat_launcher.exe")) return 1;
	auto info = IO::GetModuleInfo(L"EasyAntiCheat_launcher.exe");
	if (!info || !info->addr || !info->size) return 2;
	std::printf("[+] Found EasyAntiCheat_launcher.exe at 0x%02llX [%02llX]\n", info->addr, info->size);

	auto date = std::chrono::system_clock::now();
	std::printf("[!] %s\n", std::format("{:%Y%m%d-%H%M%S}", date).c_str());
	offsets::dump() ? std::printf("[+] Dumped\n") : std::printf("[-] Failed\n");
	auto ends = std::chrono::system_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(ends - date);
	auto sstr = std::stringstream();
	sstr << diff;
	std::printf("[!] %s (%s)\n", std::format("{:%Y%m%d-%H%M%S}", ends).c_str(), sstr.str().c_str());
#ifdef NDEBUG
	std::cin.get();
#endif
	return 0;
}
