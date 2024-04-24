#include "convars.h"

auto offsets::convars::dump(IO::CacheInstance* instance, const IO::ModuleInfo* info, const std::string* data) -> bool
{
    struct RawConVar
    {
        uint64_t m_vTable;          // 0x0000
        uint64_t m_pNext;           // 0x0008
        uint64_t m_bRegistered;     // 0x0010
        uint64_t m_pszName;         // 0x0018
        uint64_t m_pszDescription;  // 0x0020
        uint64_t m_pszDataType;     // 0x0028
        uint32_t m_iFlags;          // 0x0030
        char     pad_0034[4];       // 0x0034
        uint64_t m_pParent;         // 0x0038
        uint64_t m_pTable;          // 0x0040
        uint64_t m_pszDefaultValue; // 0x0048
        uint64_t m_pszString;       // 0x0050
        uint64_t m_iStringLength;   // 0x0058
        float    m_fValue;          // 0x0060
        int32_t  m_nValue;          // 0x0064
        bool     m_bHasMin;         // 0x0068
        bool     m_bHasMax;         // 0x0069
        char     pad_006A[2];       // 0x006A
        float    m_fMinValue;       // 0x006C
        float    m_fMaxValue;       // 0x0070
    };
    auto stream = std::ofstream("convars.ini");
    if (!stream.good()) return false;
    stream << "[convars]\n";

    auto matches = PS::SearchInSectionMultiple(data->c_str(), ".text", "\x48\x8B\x05\x00\x00\x00\x00\x48\x00\x00\x48\x8B\x00\x00\x00\x00\x00\xFF\x00\x00\x00\x00\x00", "xxx????x??xx?????x?????");
    if (!matches.size()) return false;

    auto offsets = std::map<std::string, uint64_t>();
    for (auto i = size_t(); i < matches.size(); i++)
    {
        auto offset = matches[i];
        offset += 3;
        offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
        offset += 4;

        auto convar = RawConVar();
        if (!instance->RPM(info->addr + offset, &convar, sizeof(convar))) continue;
        if (!instance->RPM<uint64_t>(convar.m_vTable)) continue;

        char name[128];
        name[sizeof(name) - 1] = '\0';
        if (!instance->RPM(convar.m_pszDescription, name, sizeof(name) - 1)) continue;
        if (!instance->RPM(convar.m_pszName, name, sizeof(name) - 1) || !std::strlen(name)) continue;

        offsets[name] = offset;
    }

    for (auto& [k, v] : offsets) stream << k << "=0x" << std::hex << v << "\n";

    stream.flush();
    stream.close();
	return offsets.size() > 0;
}
