#pragma once

#include <stdint.h>

namespace r2bix
{
	enum eColorMaskFlag
	{
		CMF_Foreground = 1,
		CMF_Background = 1 << 1,
	};
	class ColorMaskOption
	{
	public:
		ColorMaskOption();
		ColorMaskOption( const int flags );

		void On( const eColorMaskFlag flag );
		void Off( const eColorMaskFlag flag );

		uint8_t GetMask() const { return mMask; }

	private:
		uint32_t mMaskFlags;
		uint8_t mMask;
	};
}