#include "weapons.h"

auto offsets::weapons::dump(IO::CacheInstance* instance, const IO::ModuleInfo*, const std::string* data) -> bool
{
    struct RawWeaponDataField
    {
        uint64_t m_pszName;
        uint64_t m_pszDefault;
        uint64_t m_pszDescription;
        uint8_t  m_iType;
        uint8_t  m_iFlags;
        uint16_t m_iIndex;
        uint16_t m_iOffset;
        uint16_t _pad0;
    };
    auto stream = std::ofstream("weapons.ini");
    if (!stream.good()) return false;
    stream << "[weapons]\n";

    {
        auto addr = PS::SearchInSection(data->c_str(), ".text", "\x4C\x8B\x83\x00\x00\x00\x00\x4C\x8D\x8B\x00\x00\x00\x00\x48\x8B\xD3\x33\xC9\xE8\x00\x00\x00\x00", "xxx????xxx????xxxxxx????");
        if (!addr) return false;
        addr += 7;
        addr += 3;
        addr = *reinterpret_cast<const int32_t*>(data->c_str() + addr);

        offsets::weapons::offset = addr;
        stream << "offset=0x" << std::hex << offsets::weapons::offset << "\n";
    }

    auto addr = PS::SearchInSection(data->c_str(), ".text", "\x40\x57\x48\x83\xEC\x20\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x8D\x0D", "xxxxxxxxx????xxx????xxx");
    if (!addr) return false;
    addr += 2 + 4 + 7;
    addr += 3;
    addr += *reinterpret_cast<const int32_t*>(data->c_str() + addr);
    addr += 4;

    auto offsets = std::map<std::string, uint64_t>();
    for (auto i = 0; i < 0x500; i++)
    {
        auto buffer = reinterpret_cast<const RawWeaponDataField*>(data->c_str() + addr + sizeof(RawWeaponDataField) * i);
        if (!buffer->m_iOffset) continue;

        char name[128];
        name[sizeof(name) - 1] = '\0';
        if (!instance->RPM(buffer->m_pszName, name, sizeof(name) - 1)) continue;
        if (!std::strlen(name) || std::strlen(name) < 3) continue;

        offsets[name] = buffer->m_iOffset;
    }

    {
        auto list = std::map<uint64_t, std::string>();
        for (auto& [k, v] : offsets) list[v] = k;
        for (auto& [k, v] : list) stream << v << "=0x" << std::hex << k << "\n";
    }

    stream.flush();
    stream.close();
    return offsets.size() > 0;
}
