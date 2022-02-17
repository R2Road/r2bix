#include "pch.h"
#include "r2render_FrameBuffer.h"

#include <cassert>

namespace r2
{
	FrameBuffer::FrameBuffer( const uint32_t width, const uint32_t height ) :
		mGridIndexConverter( static_cast<int>( width ), static_cast<int>( height ) )
		, mChars(
			( width * height )		// for buffer
			+ 1u					// for \0
			, 32					// Fill : Character : Space
		)
	{
		assert( 0u < width && 0u < height && "FrameBuffer::FrameBuffer" );

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
		std::fill( mChars.begin(), mChars.end(), c );

		//
		// End
		//
		*mChars.rbegin() = '\0';
	}
}