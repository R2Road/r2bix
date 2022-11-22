#pragma once

#include <stdint.h>

namespace r2bix_director
{
	struct Config
	{
		const int ScreenBufferSize_Width = 107;
		const int ScreenBufferSize_Height = 53;

		enum class eScheduleType
		{
			Infinite,
			Sleep,
		};
		const eScheduleType ScheduleType = eScheduleType::Infinite;

		const int UpdateFramePerSeconds = 30u;
		const int RenderFramePerSeconds = 30u;

	};
}