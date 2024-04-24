#include "IO.h"

#include <cwctype>

#include <string>
#include <algorithm>

#include <Windows.h>
#include <TlHelp32.h>

namespace IO
{
	uint32_t GameID = 0;
	HANDLE   GameHandle = INVALID_HANDLE_VALUE;
}

auto IO::INIT(const wchar_t* name, const wchar_t* full) -> bool
{
	GameID = GetProcessID(name, full);
	if (!GameID) return false;

	GameHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GameID);
	if (!GameHandle || GameHandle == INVALID_HANDLE_VALUE) return false;

	std::printf("[+] Found %ws (%lu) [%02llX]\n", name, GameID, reinterpret_cast<uint64_t>(GameHandle));
	return true;
}

auto IO::FREE() -> void
{
	GameID = 0;

	if (GameHandle && GameHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(GameHandle);

		GameHandle = INVALID_HANDLE_VALUE;
	}
}

auto IO::GetProcessID(const wchar_t* name, const wchar_t* full) -> uint32_t
{
	if (!name || !std::wcslen(name)) return 0;
	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if ( hSnapshot == INVALID_HANDLE_VALUE ) return 0;

	auto data = PROCESSENTRY32W();
	data.dwSize = sizeof(data);
	for (auto bCond = Process32FirstW(hSnapshot, &data); bCond; bCond = Process32NextW(hSnapshot, &data))
	{
		if (std::ranges::equal(std::wstring_view(data.szExeFile), std::wstring_view(name), [](wchar_t a, wchar_t b) -> bool {
			return std::towlower(a) == std::towlower(b);
		}))
		{
			if (full && std::wcslen(full))
			{
				auto handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, data.th32ProcessID);
				if (!handle) continue;

				auto buffer = std::wstring();
				buffer.resize(MAX_PATH);
				auto length = static_cast<DWORD>(buffer.size());
				auto status = QueryFullProcessImageNameW(handle, 0, buffer.data(), &length);
				CloseHandle(handle);
				if (!status || !length) continue;

				if ( std::wstring_view(buffer.c_str()).find(full) == std::wstring_view::npos ) continue;
			}

			CloseHandle(hSnapshot);
			return data.th32ProcessID;
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

auto IO::GetModuleInfo(const wchar_t* name) -> std::shared_ptr<ModuleInfo>
{
	if (!name || !std::wcslen(name) || !GameID) return nullptr;
	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GameID);
	if ( hSnapshot == INVALID_HANDLE_VALUE ) return nullptr;

	auto data = MODULEENTRY32W();
	data.dwSize = sizeof(data);
	for (auto bCond = Module32FirstW(hSnapshot, &data); bCond; bCond = Module32NextW(hSnapshot, &data))
	{
		if (std::ranges::equal(std::wstring_view(data.szModule), std::wstring_view(name), [](wchar_t a, wchar_t b) -> bool {
			return std::towlower(a) == std::towlower(b);
		}))
		{
			auto info = std::make_shared<ModuleInfo>();
			info->addr = reinterpret_cast<uint64_t>(data.modBaseAddr);
			info->size = data.modBaseSize;

			CloseHandle(hSnapshot);
			return info;
		}
	}

	CloseHandle(hSnapshot);
	return nullptr;
}

auto IO::GetModuleBase(const wchar_t* name) -> uint64_t
{
	auto info = GetModuleInfo(name);
	if (!info) return 0;

	return info->addr;
}

auto IO::GetModuleSize(const wchar_t* name) -> size_t
{
	auto info = GetModuleInfo(name);
	if (!info) return 0;

	return info->size;
}

auto IO::RPM(uint64_t addr, void* data, size_t size) -> bool
{
	if (!GameID || !GameHandle || GameHandle == INVALID_HANDLE_VALUE || addr <= 0x10000 || addr >= 0x7FFFFFFEFFFF || addr + size >= 0x7FFFFFFF0000) return false;

	return ReadProcessMemory(GameHandle, reinterpret_cast<LPCVOID>(addr), data, size, NULL);
}

auto IO::WPM(uint64_t addr, void* data, size_t size) -> bool
{
	if (!GameID || !GameHandle || GameHandle == INVALID_HANDLE_VALUE || addr <= 0x10000 || addr >= 0x7FFFFFFEFFFF || addr + size >= 0x7FFFFFFF0000) return false;

	return WriteProcessMemory(GameHandle, reinterpret_cast<LPVOID>(addr), data, size, NULL);
}
