#include "miniaudio_test.h"

#include <chrono>
#include <conio.h>
#include <iomanip>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// # Miniaudio REF : https://miniaud.io/docs/manual/index.html

#include "r2bix_utility_PathUtil.h"
#include "r2tm/r2tm_WindowUtility.h"

namespace miniaudio_test
{
	r2tm::TitleFunctionT Engine_Init::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Init";
		};
	}
	r2tm::DoFunctionT Engine_Init::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );

			LS();

			{
				PROCESS_MAIN( result = ma_engine_init( nullptr, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			LS();

			{
				EXPECT_TRUE( engine.ownsResourceManager );
				EXPECT_TRUE( engine.ownsDevice );

				LF();

				OUTPUT_VALUE( ma_engine_get_channels( &engine ) );
				OUTPUT_VALUE( ma_engine_get_sample_rate( &engine ) );
				OUTPUT_VALUE( ma_engine_get_listener_count( &engine ) );
			}

			LS();

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Engine_Config::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Config";
		};
	}
	r2tm::DoFunctionT Engine_Config::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );
			DECLARATION_MAIN( ma_engine_config engine_config );

			LS();

			{
				PROCESS_MAIN( engine_config = ma_engine_config_init() );
				
				OUTPUT_VALUE( engine_config.listenerCount );                    /* Must be between 1 and MA_ENGINE_MAX_LISTENERS. */
				OUTPUT_VALUE( engine_config.channels );                         /* The number of channels to use when mixing and spatializing. When set to 0, will use the native channel count of the device. */
				OUTPUT_VALUE( engine_config.sampleRate );                       /* The sample rate. When set to 0 will use the native channel count of the device. */
				OUTPUT_VALUE( engine_config.periodSizeInFrames );               /* If set to something other than 0, updates will always be exactly this size. The underlying device may be a different size, but from the perspective of the mixer that won't matter.*/
				OUTPUT_VALUE( engine_config.periodSizeInMilliseconds );         /* Used if periodSizeInFrames is unset. */
				OUTPUT_VALUE( engine_config.gainSmoothTimeInFrames );           /* The number of frames to interpolate the gain of spatialized sounds across. If set to 0, will use gainSmoothTimeInMilliseconds. */
				OUTPUT_VALUE( engine_config.gainSmoothTimeInMilliseconds );     /* When set to 0, gainSmoothTimeInFrames will be used. If both are set to 0, a default value will be used. */
				OUTPUT_VALUE( engine_config.noAutoStart );                      /* When set to true, requires an explicit call to ma_engine_start(). This is false by default, meaning the engine will be started automatically in ma_engine_init(). */
				OUTPUT_VALUE( engine_config.noDevice );
			}

			LS();

			{
				PROCESS_MAIN( result = ma_engine_init( &engine_config, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			LS();

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Engine_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Volume";
		};
	}
	r2tm::DoFunctionT Engine_Volume::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound );

			LS();

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				LF();

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				LF();

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			LS();

			{
				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				float current_volume = 1.f;

				bool bRun = true;
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2tm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2tm::linefeed;
					std::cout << "[ESC] End " << r2tm::linefeed2;

					switch( _getch() )
					{
					case '1':
						PROCESS_MAIN( current_volume -= 0.5f );
						PROCESS_MAIN( ma_engine_set_volume( &engine, current_volume ) );
						break;
					case '2':
						PROCESS_MAIN( current_volume += 0.5f );
						PROCESS_MAIN( ma_engine_set_volume( &engine, current_volume ) );
						break;

					case 27: // ESC
						bRun = false;
						r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Engine_PlaySound::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Play Sound";
		};
	}
	r2tm::DoFunctionT Engine_PlaySound::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine )
				EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			LS();

			{
				std::cout << r2tm::tab << "+ fire and forget" << r2tm::linefeed2;

				PROCESS_MAIN( result = ma_engine_play_sound( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), nullptr ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			LS();

			{
				std::cout << "[Any Key] End " << r2tm::linefeed2;
				_getch();
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Engine_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Time";
		};
	}
	r2tm::DoFunctionT Engine_Time::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			LS();

			DECLARATION_SUB( ma_sound sound );

			LS();

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				PROCESS_SUB( ma_sound_set_looping( &sound, true ) );
				PROCESS_SUB( ma_sound_start( &sound ) );
			}

			LS();

			OUTPUT_VALUE( ma_engine_get_sample_rate( &engine ) );

			LS();

			{
				std::cout << "[Any Key] End" << r2tm::linefeed2;

				DECLARATION_MAIN( int64_t engine_time = 0ll );

				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				const auto system_start_time_point = std::chrono::system_clock::now();
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					PROCESS_MAIN( engine_time = ma_engine_get_time( &engine ) );
					printf( "Engine Time : %20lld \n", engine_time );

					std::chrono::duration<double> default_time = std::chrono::system_clock::now() - system_start_time_point;
					printf( "System Time : %20.3f \n", default_time.count() );

					if( _kbhit() )
					{
						break;
					}
				} while( true );
			}

			LS();

			{
				PROCESS_SUB( ma_sound_uninit( &sound ) );
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_Init_Load::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Init, Load";
		};
	}
	r2tm::DoFunctionT Sound_Init_Load::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound );

			LS();

			{
				std::cout << r2tm::tab << "+ 파일 없다." << r2tm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, "", 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_DOES_NOT_EXIST, result );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ 파일 있다." << r2tm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeSFXPath( "test_sfx_01.wav" ).c_str() , 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_Play::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Play";
		};
	}
	r2tm::DoFunctionT Sound_Play::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound );

			LS();

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				LF();

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );
			}

			LS();

			{
				std::cout << "[1] Play" << r2tm::linefeed;
				std::cout << "[2] Pause" << r2tm::linefeed;
				std::cout << "[3] Stop" << r2tm::linefeed;
				std::cout << "[ESC] End " << r2tm::linefeed2;

				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{

					switch( input )
					{
					case '1':
						PROCESS_MAIN( ma_sound_start( &sound ) );
						break;
					case '2':
						PROCESS_MAIN( ma_sound_stop( &sound ) );
						break;
					case '3':
						PROCESS_MAIN( ma_sound_stop( &sound ) );
						PROCESS_MAIN( ma_sound_seek_to_pcm_frame( &sound, 0 ) );
						break;
					}

					input = _getch();
					r2tm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_coord );

				} while( 27 != input );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_Duplicate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Duplicate";
		};
	}
	r2tm::DoFunctionT Sound_Duplicate::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << r2tm::tab << "ma_sound_init_copy 를 사용한 이후 종료시에 memory leak 이 검출된다." << r2tm::linefeed;

			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound_orig );
			DECLARATION_MAIN( ma_sound sound_duplicated );

			LS();

			{
				std::cout << r2tm::tab << "+ Load" << r2tm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound_orig ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Duplicate" << r2tm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_copy( &engine, &sound_orig, 0, NULL, &sound_duplicated ) );
				EXPECT_EQ( MA_SUCCESS, result );

				PROCESS_MAIN( ma_sound_start( &sound_duplicated ) );
			}

			LS();

			{
				std::cout << "[Any Key] End " << r2tm::linefeed2;
				_getch();
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_stop( &sound_duplicated ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_duplicated ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_orig ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Volume";
		};
	}
	r2tm::DoFunctionT Sound_Volume::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound );

			LS();

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				LF();

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				LF();

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			LS();

			{
				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				float current_volume = ma_sound_get_volume( &sound );

				bool bRun = true;
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2tm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2tm::linefeed;
					std::cout << "[ESC] End " << r2tm::linefeed2;

					switch( _getch() )
					{
					case '1':
						PROCESS_MAIN( current_volume -= 0.5f );
						PROCESS_MAIN( ma_sound_set_volume( &sound, current_volume ) );
						break;
					case '2':
						PROCESS_MAIN( current_volume += 0.5f );
						PROCESS_MAIN( ma_sound_set_volume( &sound, current_volume ) );
						break;

					case 27: // ESC
						bRun = false;
						r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Time";
		};
	}
	r2tm::DoFunctionT Sound_Time::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			LS();

			DECLARATION_SUB( ma_sound sound );

			LS();

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				PROCESS_SUB( ma_sound_set_looping( &sound, true ) );
				PROCESS_SUB( ma_sound_start( &sound ) );
			}

			LS();

			{
				std::cout << "[1] Play" << r2tm::linefeed;
				std::cout << "[2] Stop" << r2tm::linefeed;
				std::cout << "[ESC] End " << r2tm::linefeed2;

				DECLARATION_MAIN( ma_int64 engine_time = 0ll );
				DECLARATION_MAIN( ma_int64 sound_time = 0ll );
				const auto system_start_time_point = std::chrono::system_clock::now();

				LF();

				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					PROCESS_MAIN( engine_time = ma_engine_get_time( &engine ) );
					printf( "Engine Time : %20lld \n", engine_time );

					PROCESS_MAIN( sound_time = ma_sound_get_time_in_pcm_frames( &sound ) );
					printf( "Sound Time : %20lld \n", sound_time );

					std::chrono::duration<double> default_time = std::chrono::system_clock::now() - system_start_time_point;
					printf( "System Time : %20.3f \n", default_time.count() );

					if( _kbhit() )
					{
						switch( _getch() )
						{
						case '1':
							ma_sound_start( &sound );
							break;
						case '2':
							ma_sound_stop( &sound );
							break;

						case 27: // ESC
							bRun = false;
							r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 5 } );
							break;
						}
					}
				} while( bRun );
			}

			LS();

			{
				PROCESS_SUB( ma_sound_uninit( &sound ) );
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sound_FadeIn::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : FadeIn";
		};
	}
	r2tm::DoFunctionT Sound_FadeIn::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound );

			LS();

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				LF();

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );
			}

			LS();

			std::cout << "Volume : " << std::setw( 10 ) << ma_sound_get_volume( &sound ) << r2tm::linefeed;
			std::cout << "[1] Play" << r2tm::linefeed;
			std::cout << "[2] Stop" << r2tm::linefeed;
			std::cout << "[ESC] End " << r2tm::linefeed2;

			{
				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				int input = 0;
				do
				{
					
					switch( input )
					{
					case '1':
						PROCESS_MAIN( ma_sound_set_fade_in_milliseconds( &sound, 0, -1, 2000 ) );
						PROCESS_MAIN( ma_sound_start( &sound ) );
						break;
					case '2':
						PROCESS_MAIN( ma_sound_stop( &sound ) );
						PROCESS_MAIN( ma_sound_seek_to_pcm_frame( &sound, 0 ) );
						break;
					}

					input = _getch();
					r2tm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_coord );

				} while( 27 != input );

				r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 7 } );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Group_Init::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Init";
		};
	}
	r2tm::DoFunctionT Group_Init::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			LS();

			{
				DECLARATION_MAIN( ma_sound_group sound_group );

				LF();

				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				LF();

				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Group_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Volume";
		};
	}
	r2tm::DoFunctionT Group_Volume::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound_1 );
			DECLARATION_MAIN( ma_sound sound_2 );
			DECLARATION_MAIN( ma_sound_group sound_group );

			LS();

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				LF();

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, &sound_group, NULL, &sound_1 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_1, 0.1f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_1, true ) );
				PROCESS_SUB( ma_sound_start( &sound_1 ) );
				
				LF();
				
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "TinyWorlds_Forest_Ambience.mp3" ).c_str(), 0, &sound_group, NULL, &sound_2 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_2, 1.0f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_2, true ) );
				PROCESS_SUB( ma_sound_start( &sound_2 ) );
			}

			LS();

			{
				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				float current_volume = 1.f;

				bool bRun = true;
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2tm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2tm::linefeed;
					std::cout << "[ESC] End " << r2tm::linefeed2;

					switch( _getch() )
					{
					case '1':
						PROCESS_MAIN( current_volume -= 0.5f );
						PROCESS_MAIN( ma_sound_group_set_volume( &sound_group, current_volume ) );
						break;
					case '2':
						PROCESS_MAIN( current_volume += 0.5f );
						PROCESS_MAIN( ma_sound_group_set_volume( &sound_group, current_volume ) );
						break;

					case 27: // ESC
						bRun = false;
						r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound_1 ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_2 ) );
				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Group_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Time";
		};
	}
	r2tm::DoFunctionT Group_Time::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			LS();

			DECLARATION_MAIN( ma_sound sound_1 );
			DECLARATION_MAIN( ma_sound sound_2 );
			DECLARATION_MAIN( ma_sound_group sound_group );

			LS();

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				LF();

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, &sound_group, NULL, &sound_1 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_1, 0.1f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_1, true ) );
				PROCESS_SUB( ma_sound_start( &sound_1 ) );

				LF();

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2bix_utility::MakeBGMPath( "TinyWorlds_Forest_Ambience.mp3" ).c_str(), 0, &sound_group, NULL, &sound_2 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_2, 1.0f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_2, true ) );
				PROCESS_SUB( ma_sound_start( &sound_2 ) );
			}

			LS();

			{
				std::cout << "[Any Key] End " << r2tm::linefeed2;

				DECLARATION_MAIN( ma_int64 group_time = 0ll );
				const auto pivot_coord = r2tm::WindowUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2tm::WindowUtility::MoveCursorPoint( pivot_coord );

					PROCESS_MAIN( group_time = ma_sound_get_time_in_pcm_frames( &sound_group ) );
					printf( "Groupd Time : %20lld \n", group_time );

					if( _kbhit() )
					{
						switch( _getch() )
						{
						case '1':
							ma_sound_start( &sound_group );
							break;
						case '2':
							ma_sound_stop( &sound_group );
							break;

						case 27: // ESC
							bRun = false;
							r2tm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 2 } );
							break;

						default:
							continue;
						}
					}
				} while( bRun );
			}

			LS();

			{
				PROCESS_MAIN( ma_sound_uninit( &sound_1 ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_2 ) );
				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			LS();

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}