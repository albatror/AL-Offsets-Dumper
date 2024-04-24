#pragma once
#include <cstddef>
#include <cstdint>

namespace offsets
{
	auto __declspec(noinline) dump() -> bool;

	namespace miscellaneous
	{
		inline uint64_t ClientState;
		inline uint64_t CommandBuffer;
		inline uint64_t CommandNumber;
		inline uint64_t EntityList;
		inline uint64_t FrameStage;
		inline uint64_t GameVersion;
		inline uint64_t GlobalVars;
		inline uint64_t GlowSettings;
		inline uint64_t InputSystem;
		inline uint64_t LevelName;
		inline uint64_t LevelTable;
		inline uint64_t LocalPlayer;
		inline uint64_t LocalPlayerHandle;
		inline uint64_t NameList;
		inline uint64_t NetChannel;
		inline uint64_t NetworkVarTable;
		inline uint64_t SignonState;
		inline uint64_t ViewMatrix;
		inline uint64_t ViewRender;

		namespace CBaseAnimating
		{
			inline uint64_t pStudioHdr;
		}

		namespace CWeaponX
		{
			inline uint64_t bIsSemiAuto;
			inline uint64_t fProjectileScale;
			inline uint64_t fProjectileSpeed;
			inline uint64_t fZoomTimeIn;
		}

		namespace CPlayer
		{
			inline uint64_t fLastVisibleTime;
			inline uint64_t vecCameraAngles;
			inline uint64_t vecCameraOrigin;
		}
	}

	namespace functions
	{
		inline uint64_t GetDataTableAsset;
	}

	namespace weapons
	{
		inline uint64_t offset;
	}
}
