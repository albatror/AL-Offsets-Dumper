#include "miscellaneous.h"

auto offsets::miscellaneous::dump(IO::CacheInstance*, const IO::ModuleInfo*, const std::string* data) -> bool
{
	auto stream = std::ofstream("miscellaneous.ini");
	if (!stream.good()) return false;
	stream << "[miscellaneous]\n";

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8D\x15\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x8D\x0D", "xxx????xxx????xxx");
		if (!offset) return false;
		offset += 7;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		ClientState = offset;
		stream << "ClientState=0x" << std::hex << ClientState << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x0F\x85\x00\x00\x00\x00\x4C\x8B\x05\x00\x00\x00\x00\x48\x8D\x0D", "xx????xxx????xxx");
		if (!offset) return false;
		offset += 6;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		CommandBuffer = offset;
		stream << "CommandBuffer=0x" << std::hex << CommandBuffer << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x45\x33\xF6\x8B\x2D\x00\x00\x00\x00", "xxxxx????");
		if (!offset) return false;
		offset += 3;
		offset += 2;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		CommandNumber = offset;
		stream << "CommandNumber=0x" << std::hex << CommandNumber << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x4C\x8D\x3D\x00\x00\x00\x00\x48\x85\xED", "xxx????xxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		EntityList = offset;
		stream << "EntityList=0x" << std::hex << EntityList << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x89\x15\x00\x00\x00\x00\x83\xFA\x07", "xx????xxx");
		if (!offset) return false;
		offset += 2;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		FrameStage = offset;
		stream << "FrameStage=0x" << std::hex << FrameStage << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8D\x15\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x75\x1A", "xxx????xxx????x????xxxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		GameVersion = offset;
		stream << "GameVersion=0x" << std::hex << GameVersion << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8D\x15\x00\x00\x00\x00\xFF\x50\x18\x85\xC0", "xxx????xxxxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		GlobalVars = offset;
		stream << "GlobalVars=0x" << std::hex << GlobalVars << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8B\x05\x00\x00\x00\x00\x8B\x54\x01\x30", "xxx????xxxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		GlowSettings = offset;
		stream << "GlowSettings=0x" << std::hex << GlowSettings << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x00\x00\x00\x00\x89\x4C\x24\x20\x48\x8D\x0D\x00\x00\x00\x00", "xxxxxxxxxxx????");
		if (!offset) return false;
		offset += 4 + 4;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		InputSystem = offset;
		stream << "InputSystem=0x" << std::hex << InputSystem << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x7C\x07\x48\x8D\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x83\x3D\x00\x00\x00\x00\x00", "xxxxx????xxxxxxxxxx?????");
		if (!offset) return false;
		offset += 2;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		LevelName = offset;
		stream << "LevelName=0x" << std::hex << LevelName << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x4C\x8D\x05\x00\x00\x00\x00\x41\x3B\x14\x80", "xxx????xxxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		LevelTable = offset;
		stream << "LevelTable=0x" << std::hex << LevelTable << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x89\x41\x30\x48\x8D\x0D\x00\x00\x00\x00", "xxxxxx????");
		if (!offset) return false;
		offset += 3;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;
		offset += 8;

		LocalPlayer = offset;
		stream << "LocalPlayer=0x" << std::hex << LocalPlayer << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x8B\x05\x00\x00\x00\x00\x44\x0F\xB7\x05\x00\x00\x00\x00\x83\xF8\xFF\x74", "xx????xxxx????xxxx");
		if (!offset) return false;
		offset += 2;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		LocalPlayerHandle = offset;
		stream << "LocalPlayerHandle=0x" << std::hex << LocalPlayerHandle << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x4C\x8D\x05\x00\x00\x00\x00\x0F\x1F\x40\x00\x8D\x42\xFE", "xxx????xxxxxxx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		NameList = offset;
		stream << "NameList=0x" << std::hex << NameList << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x83\x3D\x00\x00\x00\x00\x00\x74\x70", "xxx?????xx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 5;

		NetChannel = offset;
		stream << "NetChannel=0x" << std::hex << NetChannel << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8D\x15\x00\x00\x00\x00\x83\x7C\x11\x00\x00\x74\x0F", "xxx????xxx??xx");
		if (!offset) return false;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		NetworkVarTable = offset;
		stream << "NetworkVarTable=0x" << std::hex << NetworkVarTable << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x83\x3D\x00\x00\x00\x00\x02\x48\x8D\x05\x00\x00\x00\x00\x7C\x07", "xx????xxxx????xx");
		if (!offset) return false;
		offset += 2;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 5;

		SignonState = offset;
		stream << "SignonState=0x" << std::hex << SignonState << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x49\x8B\x7B\x28\x4C\x89\xB3\x00\x00\x00\x00", "xxxxxxx????");
		if (!offset) return 0;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 7);

		ViewMatrix = offset;
		stream << "ViewMatrix=0x" << std::hex << ViewMatrix << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x0F\x84\x00\x00\x00\x00\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x28", "xx????xxx????xxxxxx");
		if (!offset) return false;
		offset += 6;
		offset += 3;
		offset += *reinterpret_cast<const int32_t*>(data->c_str() + offset);
		offset += 4;

		ViewRender = offset;
		stream << "ViewRender=0x" << std::hex << ViewRender << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8B\x9F\x00\x00\x00\x00\x48\x85\xDB\x75\x0C", "xxx????xxxxx");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 3);

		CBaseAnimating::pStudioHdr = offset;
		stream << "CBaseAnimating::pStudioHdr=0x" << std::hex << CBaseAnimating::pStudioHdr << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x40\x53\x48\x83\xEC\x20\x80\xB9\x00\x00\x00\x00\x00\x8B\xDA\x75\x00", "xxxxxxxx????xxxx?");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 8);

		CWeaponX::bIsSemiAuto = offset;
		stream << "CWeaponX::bIsSemiAuto=0x" << std::hex << CWeaponX::bIsSemiAuto << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x10\x93\x00\x00\x00\x00\xF3\x0F\x5E\xC1", "xxx????xxxx????xxxx");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 11);

		CWeaponX::fProjectileScale = offset;
		stream << "CWeaponX::fProjectileScale=0x" << std::hex << CWeaponX::fProjectileScale << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\xF3\x0F\x10\x8B\x00\x00\x00\x00\xF3\x0F\x10\x83\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x10\x93", "xxxx????xxxx????xxx????xxxx");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 4);

		CWeaponX::fProjectileSpeed = offset;
		stream << "CWeaponX::fProjectileSpeed=0x" << std::hex << CWeaponX::fProjectileSpeed << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\xEB\x00\xF3\x0F\x10\x88\x00\x00\x00\x00\x0F\x57\xC0\x0F\x2E\xC8\x7A\x00\x74\x00", "x?xxxx????xxxxxxx?x?");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 6);

		CWeaponX::fZoomTimeIn = offset;
		stream << "CWeaponX::fZoomTimeIn=0x" << std::hex << CWeaponX::fZoomTimeIn << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x4C\x8B\xCE\x49\x8B\x3E", "xxxxxx");
		if (!offset) return false;
		offset += 3 + 3 + 5;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset);

		CPlayer::fLastVisibleTime = offset;
		stream << "CPlayer::fLastVisibleTime=0x" << std::hex << CPlayer::fLastVisibleTime << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8B\xF9\x0F\x2E\x89", "xxxxxx");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 6) + 12;

		CPlayer::vecCameraAngles = offset;
		stream << "CPlayer::vecCameraAngles=0x" << std::hex << CPlayer::vecCameraAngles << "\n";
	}

	{
		auto offset = PS::SearchInSection(data->c_str(), ".text", "\x48\x8B\xF9\x0F\x2E\x89", "xxxxxx");
		if (!offset) return false;
		offset = *reinterpret_cast<const int32_t*>(data->c_str() + offset + 6);

		CPlayer::vecCameraOrigin = offset;
		stream << "CPlayer::vecCameraOrigin=0x" << std::hex << CPlayer::vecCameraOrigin << "\n";
	}

	stream.flush();
	stream.close();
	return true;
}
