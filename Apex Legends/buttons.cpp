#include "buttons.h"

auto offsets::buttons::dump(IO::CacheInstance* instance, const IO::ModuleInfo* info, const std::string* data) -> bool
{
    struct RawConCommand
    {
        uint64_t m_vTable;               // 0x0000
        uint64_t m_pNext;                // 0x0008
        bool     m_bRegistered;          // 0x0010
        char     pad_0011[7];            // 0x0011
        uint64_t m_pszName;              // 0x0018
        uint64_t m_pszDescription;       // 0x0020
        uint64_t m_pszDataType;          // 0x0028
        uint32_t m_iFlags;               // 0x0030
        char     pad_0034[20];           // 0x0034
        uint64_t m_fnCommandCallback;    // 0x0048
        uint64_t m_fnCompletionCallback; // 0x0050
        uint32_t m_fnCommandType;        // 0x0058
    };
    auto stream = std::ofstream("buttons.ini");
    if (!stream.good()) return false;
    stream << "[buttons]\n";

    auto matches = PS::SearchInSectionMultiple(data->c_str(), ".data", "\x7F\x00\x00\x00\x00\x00\x00\x00\x7F\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", "xxx?????xxxxxxxxxxx??????xx??????xx??????xx????xxxx");
    if (!matches.size()) return false;

    auto offsets = std::map<std::string, uint64_t>();
    for (auto i = size_t(); i < matches.size(); i++)
    {
        auto conc = reinterpret_cast<const RawConCommand*>(data->c_str() + matches[i] - 5);
        if (!conc->m_bRegistered || !conc->m_pszName || !conc->m_fnCommandCallback || conc->m_fnCommandType != 2) continue;

        char name[33];
        name[sizeof(name) - 1] = '\0';
        if (!instance->RPM(conc->m_pszName, name, sizeof(name) - 1)) continue;
        if (!std::strlen(name) || name[0] != '+') continue;

        auto cstr = std::string();
        cstr.resize(0x100);
        if (!instance->RPM(conc->m_fnCommandCallback, cstr.data(), cstr.size())) continue;

        auto offset = PS::Search(cstr.c_str(), cstr.size(), "\x84\xC0\x75\x44\x8B\x05\x00\x00\x00\x00\x3B\xD8\x74\x3A\x8B\x0D\x00\x00\x00\x00\x3B\xD9\x74\x30\x85\xC0\x75\x08", "xxxxxx????xxxxxx????xxxxxxxx");
        if (!offset) continue;
        offset += 2 + 2 + 2;
        offset += *reinterpret_cast<const int32_t*>(cstr.data() + offset);
        offset += 4;
        offset += conc->m_fnCommandCallback - info->addr;
        
        offsets[name] = offset;
    }

    for (auto& [k, v] : offsets) stream << k << "=0x" << std::hex << v << "\n";

    stream.flush();
    stream.close();
	return offsets.size() > 0;
}
