#pragma once

#include <stdint.h>

namespace r2base
{
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