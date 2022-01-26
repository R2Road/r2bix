#include "pch.h"
#include "r2_FrameBuffer.h"

#include <cassert>

namespace r2
{
	FrameBuffer::FrameBuffer( const std::size_t width, const std::size_t height ) :
		mGridIndexConverter( static_cast<int>( width + 1u ), static_cast<int>( height ) )
		, mChars(
			( width * height )		// for buffer
			+ ( 1u * height )		// for linefeed
			+ 1u					// for \0
			, 32					// Character : Space
		)
	{
		assert( 0u < width && 0u < height && "FrameBuffer::FrameBuffer" );

		//
		// 4 Linefeed
		//
		const auto target_x = mGridIndexConverter.GetWidth() - 1;
		for( int y = 0u; mGridIndexConverter.GetHeight() > y; ++y )
		{
			mChars[static_cast<std::size_t>( mGridIndexConverter.To_Linear( target_x, y ) )] = '\n';
		}

		//
		// End
		//
		*mChars.rbegin() = '\0';
	}

	void FrameBuffer::FillAll( const char c )
	{
		//
		// Fill
		//
		std::size_t current_x = 0u;
		const std::size_t target_x = mGridIndexConverter.GetWidth() - 1u;
		for( char& element : mChars )
		{
			if( target_x != current_x )
			{
				element = c;
				++current_x;
			}
			else
			{
				current_x = 0u;
			}
		}

		//
		// End
		//
		*mChars.rbegin() = '\0';
	}
}