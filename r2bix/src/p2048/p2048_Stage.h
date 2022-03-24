#pragma once

#include <vector>

#include "r2/r2_GridIndexConverter.h"

namespace p2048
{
	class Stage
	{
	public:
		using ContainerT = std::vector<int>;

		Stage( const uint32_t width, const uint32_t height );

		//
		// Getter
		//
		uint32_t GetWidth() const { return mGridIndexConverter.GetWidth(); }
		uint32_t GetHeight() const { return mGridIndexConverter.GetHeight(); }

	private:
		r2::GridIndexConverter mGridIndexConverter;
		ContainerT mContainer;
	};
}