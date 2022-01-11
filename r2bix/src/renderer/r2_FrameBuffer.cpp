#include "pch.h"
#include "r2_FrameBuffer.h"

#include <cassert>

namespace r2
{
	FrameBuffer::FrameBuffer( const std::size_t width, const std::size_t height ) :
		mGridIndexConverter( width + 1u, height )
		, mChars( ( width + 1u ) * height, 32 )
	{
		assert( 0u < width && 0u < height && "FrameBuffer::FrameBuffer" );

		//
		// 4 linefeed
		//
		const auto target_x = mGridIndexConverter.GetWidth() - 1u;
		for( std::size_t y = 0u; mGridIndexConverter.GetHeight() > y; ++y )
		{
			mChars[static_cast<std::size_t>( mGridIndexConverter.To_Linear( target_x, y ) )] = '\n';
		}
	}

	void FrameBuffer::FillAll( const char c )
	{
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
	}
}