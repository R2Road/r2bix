#pragma once

#include <string_view>
#include <vector>

#include "r2_GridIndexConverter.h"
#include "r2/r2_RectInt.h"

namespace r2
{
	class VisibleResource
	{
	public:
		using ValueT = char;
		using ContainerT = std::vector<ValueT>;
		using ConstIteratorT = typename ContainerT::const_iterator;

		explicit VisibleResource( const std::string_view str );
		explicit VisibleResource( const uint32_t width, const std::string_view str );
		explicit VisibleResource( const uint32_t width, const uint32_t height );
		explicit VisibleResource( const uint32_t width, const uint32_t height, const char fill_char );
		explicit VisibleResource( const uint32_t width, const uint32_t height, const std::string_view str );
		explicit VisibleResource( const uint32_t width, const uint32_t height, const char fill_char, const std::string_view str );

	public:
		//
		// Iteration
		//
		ConstIteratorT begin() const { return mChars.begin(); }
		ConstIteratorT end() const { return mChars.end(); }

		//
		// Getter
		//
		int GetWidth() const { return mGridIndexConverter.GetWidth(); }
		int GetHeight() const { return mGridIndexConverter.GetHeight(); }

		int GetXEnd() const { return mGridIndexConverter.GetWidth() - 1; }
		int GetYEnd() const { return mGridIndexConverter.GetHeight() - 1; }

		const r2::RectInt& GetVisibleRect() const { return mVisibleRect; }
		const ContainerT& GetContainer() const { return mChars; }
		ValueT Get( const uint32_t x, const uint32_t y ) const;
		std::string_view GetLine( const uint32_t y ) const;


		//
		//
		//
		void FillAll( const char c );
		void Fill( const uint32_t x, const uint32_t y, const char c );
		void SetVisibleRect( const r2::RectInt& rect ) { mVisibleRect = rect; }

	private:
		const GridIndexConverter mGridIndexConverter;
		ContainerT mChars;
		r2::RectInt mVisibleRect;
	};
}