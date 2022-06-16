#pragma once

#include <stdint.h>

namespace r2base
{
	enum eForegroundColor : unsigned char
	{
		FG_Black = 0,
		FG_Blue,
		FG_Green,
		FG_Aqua,
		FG_Red,
		FG_Purple,
		FG_Yellow,
		FG_White,
		FG_Gray,
		FG_LightBlue,
		FG_LightGreen,
		FG_LightAqua,
		FG_LightLed,
		FG_LightPurple,
		FG_LightYellow,
		FG_BrightWhite,
	};

	enum eBackgroundColor : unsigned char
	{
		BG_Black		= 0,
		BG_Blue			= 1 << 4,
		BG_Green		= 2 << 4,
		BG_Aqua			= 3 << 4,
		BG_Red			= 4 << 4,
		BG_Purple		= 5 << 4,
		BG_Yellow		= 6 << 4,
		BG_White		= 7 << 4,
		BG_Gray			= 8 << 4,
		BG_LightBlue	= 9 << 4,
		BG_LightGreen	= 10 << 4,
		BG_LightAqua	= 11 << 4,
		BG_LightLed		= 12 << 4,
		BG_LightPurple	= 13 << 4,
		BG_LightYellow	= 14 << 4,
		BG_BrightWhite	= 15 << 4,
	};

	using ColorValue = unsigned short;
	unsigned char GetForegroundColor( const ColorValue color_value );
	unsigned char GetBackgroundColor( const ColorValue color_value );

	const ColorValue DefaultColorValue = r2base::eForegroundColor::FG_White | r2base::eBackgroundColor::BG_Black;



	enum eColorFlag
	{
		CF_Foreground = 1,
		CF_Background = 1 << 1,
	};
	class ColorOption
	{
	public:
		ColorOption() : mFlags( CF_Foreground | CF_Background ) { updateMask(); }
		ColorOption( const int flags ) : mFlags( flags ) { updateMask(); }

		void On( const eColorFlag flag )
		{
			mFlags |= flag;
			updateMask();
		}
		void Off( const eColorFlag flag )
		{
			mFlags &= ( ~flag );
			updateMask();
		}

		uint8_t GetMask() const { return mMask; }
	private:
		void updateMask()
		{
			mMask = 0;

			if( mFlags & CF_Foreground )
			{
				static const uint8_t foreground_mask = ( static_cast<uint8_t>( -1 ) >> 4 );
				mMask |= foreground_mask;
			}
			if( mFlags & CF_Background )
			{
				static const uint8_t background_mask = ( ( static_cast<uint8_t>( -1 ) >> 4 ) << 4 );
				mMask |= background_mask;
			}
		}

	private:
		uint32_t mFlags;
		uint8_t mMask;
	};
}