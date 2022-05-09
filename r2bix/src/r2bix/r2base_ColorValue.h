#pragma once

namespace r2base
{
	enum eForegroundColor
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

	enum eBackgroundColor
	{
		BG_Black = 16,
		BG_Blue,
		BG_Green,
		BG_Aqua,
		BG_Red,
		BG_Purple,
		BG_Yellow,
		BG_White,
		BG_Gray,
		BG_LightBlue,
		BG_LightGreen,
		BG_LightAqua,
		BG_LightLed,
		BG_LightPurple,
		BG_LightYellow,
		BG_BrightWhite,
	};

	union ColorValue
	{
		unsigned short total_color = eForegroundColor::FG_Aqua | eBackgroundColor::BG_Gray;

		unsigned char foreground_color;
		unsigned char background_color;
	};
}