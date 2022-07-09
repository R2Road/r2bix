#include "miniaudio_test.h"

#include <chrono>
#include <conio.h>
#include <iomanip>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// # Miniaudio REF : https://miniaud.io/docs/manual/index.html

#include "r2bix/r2utility_FileUtil.h"
#include "r2cm/r2cm_WindowUtility.h"

namespace miniaudio_test
{
	r2cm::iItem::TitleFunctionT Engine_Init::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Init";
		};
	}
	r2cm::iItem::DoFunctionT Engine_Init::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_engine_init( nullptr, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( engine.ownsResourceManager );
				EXPECT_TRUE( engine.ownsDevice );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( ma_engine_get_channels( &engine ) );
				OUTPUT_VALUE( ma_engine_get_sample_rate( &engine ) );
				OUTPUT_VALUE( ma_engine_get_listener_count( &engine ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Engine_Config::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Config";
		};
	}
	r2cm::iItem::DoFunctionT Engine_Config::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );
			DECLARATION_MAIN( ma_engine_config engine_config );

			std::cout << r2cm::split;

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

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_engine_init( &engine_config, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Engine_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Volume";
		};
	}
	r2cm::iItem::DoFunctionT Engine_Volume::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			std::cout << r2cm::split;

			{
				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				float current_volume = 1.f;

				bool bRun = true;
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2cm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2cm::linefeed;
					std::cout << "[ESC] End " << r2cm::linefeed2;

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
						r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Engine_PlaySound::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Play Sound";
		};
	}
	r2cm::iItem::DoFunctionT Engine_PlaySound::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine )
				EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ fire and forget" << r2cm::linefeed2;

				PROCESS_MAIN( result = ma_engine_play_sound( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), nullptr ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2cm::split;

			{
				std::cout << "[Any Key] End " << r2cm::linefeed2;
				_getch();
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Engine_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Engine : Time";
		};
	}
	r2cm::iItem::DoFunctionT Engine_Time::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_sound sound );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				PROCESS_SUB( ma_sound_set_looping( &sound, true ) );
				PROCESS_SUB( ma_sound_start( &sound ) );
			}

			std::cout << r2cm::split;

			OUTPUT_VALUE( ma_engine_get_sample_rate( &engine ) );

			std::cout << r2cm::split;

			{
				std::cout << "[Any Key] End" << r2cm::linefeed2;

				DECLARATION_MAIN( int64_t engine_time = 0ll );

				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				const auto system_start_time_point = std::chrono::system_clock::now();
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

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

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_sound_uninit( &sound ) );
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sound_Init_Load::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Init, Load";
		};
	}
	r2cm::iItem::DoFunctionT Sound_Init_Load::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 파일 없다." << r2cm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, "", 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_DOES_NOT_EXIST, result );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 파일 있다." << r2cm::linefeed2;

				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeSFXPath( "test_sfx_01.wav" ).c_str() , 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sound_Play::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Play";
		};
	}
	r2cm::iItem::DoFunctionT Sound_Play::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << "[1] Play" << r2cm::linefeed;
				std::cout << "[2] Pause" << r2cm::linefeed;
				std::cout << "[3] Stop" << r2cm::linefeed;
				std::cout << "[ESC] End " << r2cm::linefeed2;

				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
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
					r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_coord );

				} while( 27 != input );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sound_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Volume";
		};
	}
	r2cm::iItem::DoFunctionT Sound_Volume::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_start( &sound ) );
			}

			std::cout << r2cm::split;

			{
				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				float current_volume = ma_sound_get_volume( &sound );

				bool bRun = true;
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2cm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2cm::linefeed;
					std::cout << "[ESC] End " << r2cm::linefeed2;

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
						r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sound_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : Time";
		};
	}
	r2cm::iItem::DoFunctionT Sound_Time::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_sound sound );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				PROCESS_SUB( ma_sound_set_looping( &sound, true ) );
				PROCESS_SUB( ma_sound_start( &sound ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << "[1] Play" << r2cm::linefeed;
				std::cout << "[2] Stop" << r2cm::linefeed;
				std::cout << "[ESC] End " << r2cm::linefeed2;

				DECLARATION_MAIN( ma_int64 engine_time = 0ll );
				DECLARATION_MAIN( ma_int64 sound_time = 0ll );
				const auto system_start_time_point = std::chrono::system_clock::now();

				std::cout << r2cm::linefeed;

				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

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
							r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 5 } );
							break;
						}
					}
				} while( bRun );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_sound_uninit( &sound ) );
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sound_FadeIn::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sound : FadeIn";
		};
	}
	r2cm::iItem::DoFunctionT Sound_FadeIn::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( result = ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, NULL, NULL, &sound ) );
				EXPECT_EQ( MA_SUCCESS, result );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_set_looping( &sound, true ) );
			}

			std::cout << r2cm::split;

			std::cout << "Volume : " << std::setw( 10 ) << ma_sound_get_volume( &sound ) << r2cm::linefeed;
			std::cout << "[1] Play" << r2cm::linefeed;
			std::cout << "[2] Stop" << r2cm::linefeed;
			std::cout << "[ESC] End " << r2cm::linefeed2;

			{
				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
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
					r2cm::WindowUtility::MoveCursorPointWithClearBuffer( pivot_coord );

				} while( 27 != input );

				r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 7 } );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Group_Init::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Init";
		};
	}
	r2cm::iItem::DoFunctionT Group_Init::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_engine engine );
			EXPECT_EQ( MA_SUCCESS, ma_engine_init( nullptr, &engine ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( ma_sound_group sound_group );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Group_Volume::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Volume";
		};
	}
	r2cm::iItem::DoFunctionT Group_Volume::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound_1 );
			DECLARATION_MAIN( ma_sound sound_2 );
			DECLARATION_MAIN( ma_sound_group sound_group );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, &sound_group, NULL, &sound_1 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_1, 0.1f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_1, true ) );
				PROCESS_SUB( ma_sound_start( &sound_1 ) );
				
				std::cout << r2cm::linefeed;
				
				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "TinyWorlds_Forest_Ambience.mp3" ).c_str(), 0, &sound_group, NULL, &sound_2 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_2, 1.0f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_2, true ) );
				PROCESS_SUB( ma_sound_start( &sound_2 ) );
			}

			std::cout << r2cm::split;

			{
				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				float current_volume = 1.f;

				bool bRun = true;
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Volume : " << std::setw( 10 ) << current_volume << r2cm::linefeed;
					std::cout << "[1, 2] Volume Change " << r2cm::linefeed;
					std::cout << "[ESC] End " << r2cm::linefeed2;

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
						r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 6 } );
						break;

					default:
						continue;
					}
				} while( bRun );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound_1 ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_2 ) );
				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Group_Time::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Group : Time";
		};
	}
	r2cm::iItem::DoFunctionT Group_Time::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( ma_result result );
			DECLARATION_SUB( ma_engine engine );
			PROCESS_SUB( result = ma_engine_init( nullptr, &engine ) );
			EXPECT_EQ( MA_SUCCESS, result );

			std::cout << r2cm::split;

			DECLARATION_MAIN( ma_sound sound_1 );
			DECLARATION_MAIN( ma_sound sound_2 );
			DECLARATION_MAIN( ma_sound_group sound_group );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( MA_SUCCESS, ma_sound_group_init( &engine, 0, nullptr, &sound_group ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "Joth_8bit_Bossa.mp3" ).c_str(), 0, &sound_group, NULL, &sound_1 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_1, 0.1f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_1, true ) );
				PROCESS_SUB( ma_sound_start( &sound_1 ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( MA_SUCCESS, ma_sound_init_from_file( &engine, r2utility::MakeBGMPath( "TinyWorlds_Forest_Ambience.mp3" ).c_str(), 0, &sound_group, NULL, &sound_2 ) );
				PROCESS_SUB( ma_sound_set_volume( &sound_2, 1.0f ) );
				PROCESS_SUB( ma_sound_set_looping( &sound_2, true ) );
				PROCESS_SUB( ma_sound_start( &sound_2 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << "[Any Key] End " << r2cm::linefeed2;

				DECLARATION_MAIN( ma_int64 group_time = 0ll );
				const auto pivot_coord = r2cm::WindowUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2cm::WindowUtility::MoveCursorPoint( pivot_coord );

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
							r2cm::WindowUtility::MoveCursorPoint( { pivot_coord.x, pivot_coord.y + 2 } );
							break;

						default:
							continue;
						}
					}
				} while( bRun );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( ma_sound_uninit( &sound_1 ) );
				PROCESS_MAIN( ma_sound_uninit( &sound_2 ) );
				PROCESS_MAIN( ma_sound_group_uninit( &sound_group ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( ma_engine_uninit( &engine ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}