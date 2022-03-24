#pragma once

#include <vector>

namespace p2048
{
	class Stage
	{
	public:
		using ContainerT = std::vector<int>;

		Stage( const uint32_t width, const uint32_t height );

	private:
		ContainerT mContainer;
	};
}