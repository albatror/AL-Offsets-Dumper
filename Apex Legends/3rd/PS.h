#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <vector>

namespace PS
{
	auto Search(const char* data, size_t size, const char* sigs, const char* mask) -> uint64_t;
	auto SearchMultiple(const char* data, size_t size, const char* sigs, const char* mask) -> std::vector<uint64_t>;

	auto SearchInSection(const char* data, const char* name, const char* sigs, const char* mask) -> uint64_t;
	auto SearchInSectionMultiple(const char* data, const char* name, const char* sigs, const char* mask) -> std::vector<uint64_t>;
}
