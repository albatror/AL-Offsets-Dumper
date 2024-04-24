#include "netvars.h"

auto offsets::netvars::dump(IO::CacheInstance* instance, const IO::ModuleInfo* info, const std::string* data) -> bool
{
    auto stream = std::ofstream("netvars.ini");
    if (!stream.good()) return false;

    auto offsets = std::map<std::string, std::map<std::string, uint64_t>>();

	{
        struct DataMap
        {
            uint64_t m_dataDesc;
            int32_t  m_dataNumFields;
            uint32_t _pad0;
            uint64_t m_dataClassName;
            uint64_t _pad1;
            uint64_t _pad2;
            uint64_t m_baseMap;
        };
        struct DataTypeDesc
        {
            int32_t  m_fieldType;
            uint32_t _pad0;
            uint64_t m_fieldName;
            uint32_t m_fieldOffset[2];
            uint64_t m_externalName;
            uint64_t _pad1[5];
            uint64_t m_td;
            int32_t  m_fieldSizeInBytes;
            uint64_t _pad2[5];
        };
        auto matches = PS::SearchInSectionMultiple(data->c_str(), ".text", "\x48\x8D\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC", "xxx????xxxxxxxxx");
        if (!matches.size()) return false;

        for (auto i = size_t(); i < matches.size(); i++)
        {
            auto addr = matches[i];
            addr += 3;
            addr += *reinterpret_cast<const int32_t*>(data->c_str() + addr);
            addr += 4;

            auto maps = reinterpret_cast<const DataMap*>(data->c_str() + addr);
            if (!maps->m_dataNumFields || maps->m_dataNumFields < 0 || maps->m_dataNumFields > 0x1000) continue;

            char cstr[0x100];
            cstr[sizeof(cstr) - 1] = '\0';
            if (!instance->RPM(maps->m_dataClassName, cstr, sizeof(cstr) - 1) || !std::strlen(cstr)) continue;

            auto desc = std::make_unique<DataTypeDesc[]>(maps->m_dataNumFields);
            if (!instance->RPM(maps->m_dataDesc, desc.get(), sizeof(DataTypeDesc) * maps->m_dataNumFields)) continue;

            for (auto x = 0; x < maps->m_dataNumFields; x++)
            {
                char name[0x100];
                name[sizeof(name) - 1] = '\0';
                if (!instance->RPM(desc[x].m_fieldName, name, sizeof(name) - 1) || !std::strlen(name)) continue;

                offsets[cstr][name] = desc[x].m_fieldOffset[0];
            }
        }
	}

    {
        struct RecvTable
        {
            uint64_t _pad0;
            uint64_t m_pProps;
            int32_t  m_iProps;
            uint32_t _pad1[256];
            uint32_t _pad2[43];
            uint64_t m_decoder;
            uint64_t m_name;
            bool     m_initialized;
            bool     m_inMainList;
            uint8_t  _pad3[6];
        };
        struct RecvProp
        {
            int32_t  m_type;
            int32_t  m_offset;
            uint32_t _pad0[6];
            uint64_t m_dataTable;
            uint64_t m_name;
            bool     m_isInsideArray;
            uint8_t  _pad1[7];
            uint64_t m_arrayProp;
            uint64_t m_proxyFn;
            uint32_t _pad2[4];
            int32_t  m_flags;
            uint32_t _pad3;
            int32_t  m_iNumElements;
            uint32_t _pad4;
        };

        {
            auto matches = PS::SearchInSectionMultiple(data->c_str(), ".text", "\x4C\x8D\x0D\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8", "xxx????xx????xxx????xxx????x");
            if (!matches.size()) return false;

            for (auto i = size_t(); i < matches.size(); i++)
            {
                auto tableBase = matches[i] + 7 + 6 + 7;
                tableBase += 3;
                tableBase += *reinterpret_cast<const int32_t*>(data->c_str() + tableBase);
                tableBase += 4;

                auto tableData = RecvTable();
                if (!instance->RPM(info->addr + tableBase, &tableData, sizeof(tableData))) continue;

                char tableName[128];
                tableName[sizeof(tableName) - 1] = '\0';
                if (!instance->RPM(tableData.m_name, tableName, sizeof(tableName) - 1) || !std::strlen(tableName)) continue;

                for (auto x = 0; x < tableData.m_iProps; x++)
                {
                    auto propData = RecvProp();
                    if (!instance->RPM(instance->RPM<uint64_t>(tableData.m_pProps + sizeof(uint64_t) * x), &propData, sizeof(propData))) continue;
                    if (!propData.m_offset) continue;

                    char propName[128];
                    propName[sizeof(propName) - 1] = '\0';
                    if (!instance->RPM(propData.m_name, propName, sizeof(propName) - 1) || !std::strlen(propName)) continue;

                    offsets[tableName][propName] = propData.m_offset;
                }
            }
        }

        {
            auto matches = PS::SearchInSectionMultiple(data->c_str(), ".text", "\x48\x8D\x15\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8", "xxx????xx????xxx????x");

            for (auto i = size_t(0); i < matches.size(); i++)
            {
                auto tableBase = matches[i] + 7 + 6;
                tableBase += 3;
                tableBase += *reinterpret_cast<const int32_t*>(data->c_str() + tableBase);
                tableBase += 4;

                auto tableData = RecvTable();
                if (!instance->RPM(info->addr + tableBase, &tableData, sizeof(tableData))) continue;

                char tableName[128];
                tableName[sizeof(tableName) - 1] = '\0';
                if (!instance->RPM(tableData.m_name, tableName, sizeof(tableName) - 1) || !std::strlen(tableName)) continue;

                for (auto x = 0; x < tableData.m_iProps; x++)
                {
                    auto propData = RecvProp();
                    if (!instance->RPM(instance->RPM<uint64_t>(tableData.m_pProps + sizeof(uint64_t) * x), &propData, sizeof(propData))) continue;
                    if (!propData.m_offset) continue;

                    char propName[128];
                    propName[sizeof(propName) - 1] = '\0';
                    if (!instance->RPM(propData.m_name, propName, sizeof(propName) - 1) || !std::strlen(propName)) continue;

                    offsets[tableName][propName] = propData.m_offset;
                }
            }
        }

        {
            auto matches = PS::SearchInSectionMultiple(data->c_str(), ".text", "\x48\x8D\x0D\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x48\x89", "xxx????xx????????xx");

            for (auto i = size_t(0); i < matches.size(); i++)
            {
                auto tableBase = matches[i] + 7;
                tableBase += 2;
                tableBase += *reinterpret_cast<const int32_t*>(data->c_str() + tableBase);
                tableBase += 8;

                auto tableData = RecvTable();
                if (!instance->RPM(info->addr + tableBase - 16, &tableData, sizeof(tableData))) continue;

                char tableName[128];
                tableName[sizeof(tableName) - 1] = '\0';
                if (!instance->RPM(tableData.m_name, tableName, sizeof(tableName) - 1) || !std::strlen(tableName)) continue;

                for (auto x = 0; x < tableData.m_iProps; x++)
                {
                    auto propData = RecvProp();
                    if (!instance->RPM(instance->RPM<uint64_t>(tableData.m_pProps + sizeof(uint64_t) * x), &propData, sizeof(propData))) continue;
                    if (!propData.m_offset) continue;

                    char propName[128];
                    propName[sizeof(propName) - 1] = '\0';
                    if (!instance->RPM(propData.m_name, propName, sizeof(propName) - 1) || !std::strlen(propName)) continue;

                    offsets[tableName][propName] = propData.m_offset;
                }
            }
        }
    }

    for (auto& [name, list] : offsets)
    {
        stream << "[" << name << "]\n";

        auto sorted = std::map<uint64_t, std::string>();
        for (auto& [k, v] : list) sorted[v] = k;
        for (auto& [k, v] : sorted) stream << v << "=0x" << std::hex << k << "\n";

        stream << "\n";
    }

    stream.flush();
    stream.close();
    return offsets.size() > 0;
}
