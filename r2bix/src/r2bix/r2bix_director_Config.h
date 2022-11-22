#pragma once

#include <stdint.h>

namespace r2bix_director
{
	struct Config
	{
		const int32_t ScreenBufferSize_Width = 107;
		const int32_t ScreenBufferSize_Height = 53;

		enum class eScheduleType
		{
			Infinite,
			Sleep,
		};
		const eScheduleType ScheduleType = eScheduleType::Infinite;

		const int32_t UpdateFramePerSeconds = 30u;
		const int32_t RenderFramePerSeconds = 30u;

	};
}