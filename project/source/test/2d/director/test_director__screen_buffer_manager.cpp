#include "test_director__screen_buffer_manager.h"

#include <conio.h>

#include "r2/r2_fps_timer.hpp"

#include "r2bix_director_ScreenBufferManager.h"
#include "r2bix_render_Texture.h"
#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

namespace test_director__screen_buffer_manager
{
	r2tm::TitleFunctionT Swap::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Screen Buffer Manager : Swap";
		};
	}
	r2tm::DoFunctionT Swap::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( r2bix_director::ScreenBufferManager s );

			LS();

			{
				DECL_MAIN( r2bix_render::Texture t( " " ) );

				LF();

				PROC_MAIN( t.Reset( "Screen Buffer 1" ) );
				PROC_MAIN( s.Write2BackBuffer( 0, 0, &t) );

				LF();

				PROC_MAIN( s.Swap() );

				LF();

				PROC_MAIN( t.Reset( "                   Screen Buffer 2" ) );
				PROC_MAIN( s.Write2BackBuffer( 0, 0, &t ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "[ESC] End" << r2tm::linefeed;
			}

			LS();

			{
				r2::FPSTimer timer( 10 );

				int key_code = -1;
				do
				{
					if( timer.Update() )
					{
						s.Swap();
					}

					if( _kbhit() )
					{
						key_code = _getch();
					}

				} while( 27 != key_code );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}