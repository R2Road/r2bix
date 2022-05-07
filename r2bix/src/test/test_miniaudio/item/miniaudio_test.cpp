#include "pch.h"
#include "miniaudio_test.h"

#include <conio.h>
#include <iomanip>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// # Miniaudio REF : https://miniaud.io/docs/manual/index.html

#include "r2bix/r2utility_FileUtil.h"
#include "r2bix/r2utility_WindowUtil.h"

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



	r2cm::iItem::TitleFuncT Sound_Load::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Load";
		};
	}
	r2cm::iItem::DoFuncT Sound_Load::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 파일 없다." << r2::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, "", 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_DOES_NOT_EXIST, result );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 파일 있다." << r2::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeSFXPath( "test_sfx_01.wav" ).c_str() , 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Sound_Play::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Play";
		};
	}
	r2cm::iItem::DoFuncT Sound_Play::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "TinyWorlds_Forest_Ambience.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			std::cout << r2::split;

			{
				std::cout << "Any Key : Sound Stop" << r2::linefeed;
				_getch();

				PROCESS_MAIN( ma_sound_stop( &sound ) );
			}

			std::cout << r2::split;

			{
				std::cout << "Any Key : UnInit" << r2::linefeed;
				_getch();

				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Sound_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Volume";
		};
	}
	r2cm::iItem::DoFuncT Sound_Volume::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			std::cout << r2::split;

			{
				const auto pivot_coord = r2utility::GetCursorPoint();
				float current_volume = ma_sound_get_volume( &sound );

				bool bRun = true;
				do
				{
					r2utility::SetCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2::linefeed;
					std::cout << "[1, 2] Volume Change " << r2::linefeed2;
					std::cout << "[ESC] End " << r2::linefeed2;

					switch( _getch() )
					{
					case '1':
						current_volume -= 0.5f;
						ma_sound_set_volume( &sound, current_volume );
						break;
					case '2':
						current_volume += 0.5f;
						ma_sound_set_volume( &sound, current_volume );
						break;

					case 27: // ESC
						bRun = false;
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}