#pragma once
#include <memory>
#include <unordered_map>

namespace IO
{
	auto __declspec(noinline) INIT(const wchar_t* name, const wchar_t* full = nullptr) -> bool;
	auto __declspec(noinline) FREE() -> void;

	auto __declspec(noinline) GetProcessID(const wchar_t* name, const wchar_t* full = nullptr) -> uint32_t;

	struct ModuleInfo
	{
		uint64_t addr;
		size_t   size;
	};
	auto __declspec(noinline) GetModuleInfo(const wchar_t* name) -> std::shared_ptr<ModuleInfo>;
	auto __declspec(noinline) GetModuleBase(const wchar_t* name) -> uint64_t;
	auto __declspec(noinline) GetModuleSize(const wchar_t* name) -> size_t;

	auto __declspec(noinline) RPM(uint64_t addr, void* data, size_t size) -> bool;
	auto __declspec(noinline) WPM(uint64_t addr, void* data, size_t size) -> bool;

	template<typename T>
	auto __forceinline RPM(uint64_t addr) -> T { auto data = T(); return RPM(addr, &data, sizeof(data)) ? data : T(); }
	template<typename T>
	auto __forceinline WPM(uint64_t addr, T data) -> bool { return WPM(addr, &data, sizeof(data)); }
}
