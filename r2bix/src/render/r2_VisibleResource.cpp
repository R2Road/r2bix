#include "pch.h"
#include "r2_VisibleResource.h"

#include <algorithm>
#include <cassert>

namespace r2
{
	VisibleResource::VisibleResource( const std::string_view str ) :
		mGridIndexConverter( static_cast<int>( str.length() ), 1 )
		, mChars( mGridIndexConverter.GetWidth() * mGridIndexConverter.GetHeight(), 32 )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < mGridIndexConverter.GetWidth() && 0u < mGridIndexConverter.GetHeight() );

		//std::copy( str.begin(), str.end(), mChars.begin() );

		memcpy_s( &mChars[0], mChars.size(), str.data(), str.size() );
	}
	VisibleResource::VisibleResource( const uint32_t width, const std::string_view str ) :
		mGridIndexConverter( width, static_cast<int>( str.length() < 0 ? 1 : ( str.length() / width ) + ( str.length() % width < 1 ? 0 : 1 ) ) )
		, mChars( mGridIndexConverter.GetWidth() * mGridIndexConverter.GetHeight(), 32 )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < mGridIndexConverter.GetWidth() && 0u < mGridIndexConverter.GetHeight() );
		memcpy_s( &mChars[0], mChars.size(), str.data(), str.size() );
	}
	VisibleResource::VisibleResource( const uint32_t width, uint32_t height ) :
		mGridIndexConverter( width, height )
		, mChars( width * height, 32 )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < width && 0u < height );
	}
	VisibleResource::VisibleResource( const uint32_t width, const uint32_t height, const char fill_char ) :
		mGridIndexConverter( width, height )
		, mChars( width * height, fill_char )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < width && 0u < height );
	}
	VisibleResource::VisibleResource( const uint32_t width, const uint32_t height, const std::string_view str ) :
		mGridIndexConverter( width, height )
		, mChars( width * height, 32 )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < width && 0u < height );
		memcpy_s( &mChars[0], mChars.size(), str.data(), std::min( str.size(), mChars.size() ) );
	}
	VisibleResource::VisibleResource( const uint32_t width, uint32_t height, const char fill_char, const std::string_view str ) :
		mGridIndexConverter( width, height )
		, mChars( width * height, fill_char )
		, mVisibleRect( 0, 0, mGridIndexConverter.GetWidth(), mGridIndexConverter.GetHeight() )
	{
		assert( 0u < width && 0u < height );
		memcpy_s( &mChars[0], mChars.size(), str.data(), std::min( str.size(), mChars.size() ) );
	}

	VisibleResource::ValueT VisibleResource::Get( const uint32_t x, const uint32_t y ) const
	{
		const auto target_linear_index = mGridIndexConverter.To_Linear( x, y );

		return mChars[target_linear_index];
	}
	std::string_view VisibleResource::GetLine( const uint32_t y ) const
	{
		std::string_view temp( &mChars[0] );
		return temp.substr( mGridIndexConverter.To_Linear( 0, y ), mGridIndexConverter.GetWidth() );
	}

	void VisibleResource::FillAll( const char c )
	{
		for( char& element : mChars )
		{
			element = c;
		}
	}

	void VisibleResource::Fill( const uint32_t x, const uint32_t y, const char c )
	{
		const auto target_linear_index = mGridIndexConverter.To_Linear( x, y );

		mChars[target_linear_index] = c;
	}
}