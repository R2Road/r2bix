#include "r2bix_ColorMaskOption.h"

namespace r2bix
{
	void updateMask( const uint32_t mask_flags, uint8_t* out_mask_value )
	{
		*out_mask_value = 0;

		if( mask_flags & CMF_Foreground )
		{
			static const uint8_t foreground_mask = ( static_cast<uint8_t>( -1 ) >> 4 );
			*out_mask_value |= foreground_mask;
		}
		if( mask_flags & CMF_Background )
		{
			static const uint8_t background_mask = ( ( static_cast<uint8_t>( -1 ) >> 4 ) << 4 );
			*out_mask_value |= background_mask;
		}
	}

	ColorMaskOption::ColorMaskOption() : mMaskFlags( CMF_Foreground | CMF_Background )
	{
		updateMask( mMaskFlags, &mMask );
	}
	ColorMaskOption::ColorMaskOption( const int flags ) : mMaskFlags( flags )
	{
		updateMask( mMaskFlags, &mMask );
	}

	void ColorMaskOption::On( const eColorMaskFlag flag )
	{
		mMaskFlags |= flag;
		updateMask( mMaskFlags, &mMask );
	}
	void ColorMaskOption::Off( const eColorMaskFlag flag )
	{
		mMaskFlags &= ( ~flag );
		updateMask( mMaskFlags, &mMask );
	}
}