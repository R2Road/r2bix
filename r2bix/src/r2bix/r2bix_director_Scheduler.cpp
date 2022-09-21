#include "r2bix_director_Scheduler.h"

#include "r2/r2_FPSTimer.h"
#include "r2bix_director_Config.h"

namespace r2bix_director
{
	const std::function<void()> MakeProcessor( const Config& config, const std::function<void( float )> scene_update_func, const std::function<void()> scene_render_func )
	{
		return [mUpdateTimer = r2::FPSTimer( config.UpdateFramePerSeconds ), mRenderTimer = r2::FPSTimer( config.UpdateFramePerSeconds ), scene_update_func, scene_render_func]() mutable
		{
			if( mUpdateTimer.Update() )
			{
				scene_update_func( mUpdateTimer.GetElapsedTime() );
			}

			if( mRenderTimer.Update() )
			{
				scene_render_func();
			}
		};
	}

	Scheduler::Scheduler( const Config& config, const std::function<void( float )> scene_update_func, const std::function<void()> scene_render_func ) :
		mProcessor( MakeProcessor( config, scene_update_func, scene_render_func ) )
	{}

	void Scheduler::Do()
	{
		mProcessor();
	}
}