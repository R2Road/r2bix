#pragma once
#include "r2base_ColorMaskOption.h"

namespace r2base
{
	ColorMaskOption::ColorMaskOption() : mMaskFlags( CMF_Foreground | CMF_Background )
	{
		updateMask();
	}
	ColorMaskOption::ColorMaskOption( const int flags ) : mMaskFlags( flags )
	{
		updateMask();
	}

	void ColorMaskOption::On( const eColorMaskFlag flag )
	{
		mMaskFlags |= flag;
		updateMask();
	}
	void ColorMaskOption::Off( const eColorMaskFlag flag )
	{
		mMaskFlags &= ( ~flag );
		updateMask();
	}
}