#include "pch.h"
#include "miniaudio_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// # Miniaudio REF : https://miniaud.io/docs/manual/index.html

namespace miniaudio_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );

			std::cout << r2::split;

			{
				PROCESS_MAIN( result = ma_engine_init( nullptr, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT EngineConfig::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine Config";
		};
	}
	r2cm::iItem::DoFuncT EngineConfig::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );
			DECLARATION_MAIN( ma_engine_config engine_config );

			std::cout << r2::split;

			{
				PROCESS_MAIN( engine_config = ma_engine_config_init() );
				
				OUTPUT_MAIN( engine_config.listenerCount );                    /* Must be between 1 and MA_ENGINE_MAX_LISTENERS. */
				OUTPUT_MAIN( engine_config.channels );                         /* The number of channels to use when mixing and spatializing. When set to 0, will use the native channel count of the device. */
				OUTPUT_MAIN( engine_config.sampleRate );                       /* The sample rate. When set to 0 will use the native channel count of the device. */
				OUTPUT_MAIN( engine_config.periodSizeInFrames );               /* If set to something other than 0, updates will always be exactly this size. The underlying device may be a different size, but from the perspective of the mixer that won't matter.*/
				OUTPUT_MAIN( engine_config.periodSizeInMilliseconds );         /* Used if periodSizeInFrames is unset. */
				OUTPUT_MAIN( engine_config.gainSmoothTimeInFrames );           /* The number of frames to interpolate the gain of spatialized sounds across. If set to 0, will use gainSmoothTimeInMilliseconds. */
				OUTPUT_MAIN( engine_config.gainSmoothTimeInMilliseconds );     /* When set to 0, gainSmoothTimeInFrames will be used. If both are set to 0, a default value will be used. */
				OUTPUT_MAIN( engine_config.noAutoStart );                      /* When set to true, requires an explicit call to ma_engine_start(). This is false by default, meaning the engine will be started automatically in ma_engine_init(). */
				OUTPUT_MAIN( engine_config.noDevice );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( result = ma_engine_init( &engine_config, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}