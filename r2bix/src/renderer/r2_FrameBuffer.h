#pragma once

#include <vector>

#include "r2_GridIndexConverter.h"
#include "r2/r2_RectInt.h"

namespace r2
{
	class FrameBuffer
	{
	public:
		using ValueT = char;
		using ContainerT = std::vector<ValueT>;
		using ConstIteratorT = typename ContainerT::const_iterator;

		FrameBuffer( const std::size_t width, const std::size_t height );

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

		//
		//
		//
		void FillAll( const char c );

	private:
		const GridIndexConverter mGridIndexConverter;
		ContainerT mChars;
	};
}