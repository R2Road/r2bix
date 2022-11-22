#pragma once

#include <functional>

namespace r2bix_director
{
	struct Config;

	class Scheduler
	{
	private:
		using ProcessorT = std::function<void()>;

	public:
		using UpdateFunctionT = std::function<void( float )>;
		using RenderFunctionT = std::function<void()>;

	public:
		Scheduler( const Config& config, const UpdateFunctionT& scene_update_func, const RenderFunctionT& scene_render_func );

		void Do();

	private:
		const ProcessorT mProcessor;
	};
}