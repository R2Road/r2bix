#include "pch.h"
#include "r2_FrameBuffer.h"

#include <cassert>

namespace r2
{
	FrameBuffer::FrameBuffer( const std::size_t width, const std::size_t height ) :
		mGridIndexConverter( width, height )
		, mChars( width * height, 32 )
	{
		assert( 0u < width && 0u < height && "FrameBuffer::FrameBuffer" );
	}

	void FrameBuffer::FillAll( const char c )
	{
		for( char& element : mChars )
		{
			element = c;
		}
	}
}