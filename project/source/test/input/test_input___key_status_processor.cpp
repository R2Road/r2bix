#include "test_input___key_status_processor.hpp"

#include <algorithm>

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"

#include "r2tm/r2tm_color_modifier.hpp"
#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "r2bix_input_Constant.hpp"
#include "r2bix_input_KeyStatusProcessor.hpp"
#include "r2bix_input_MachineInputSignals.hpp"

#include "helper/r2bixprinter_cursor_point.hpp"

namespace test_input___key_status_processor
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key Status Processor : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_SUBJECT( "생성자 : 기본" );

				LF();

				DECL_MAIN( r2bix_input::KeyStatusProcessor p );

				LF();

				EXPECT_TRUE( r2bix_input::eKeyStep::None == p.GetStep( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_FALSE( p.IsPushed( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_FALSE( p.IsRelease( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_FALSE( p.HasInput( r2bix_input::eKeyCode::VK_0 ) );

				LF();

				OUT_SUBJECT( "전체 Key Status 출력" );

				LF();

				{
					int i = 0;
					for( const auto& info : p )
					{
						std::cout << static_cast< int >( info.GetStep() );

						++i;
						if( ( i % 32 ) == 0 )
						{
							LF();
						}
					}
				}

				LF2();

				OUT_SUBJECT( "전체 Key Changed 출력" );

				LF();

				{
					int i = 0;
					for( const auto& info : p )
					{
						std::cout << static_cast< int >( info.GetChanged() );

						++i;
						if( ( i % 32 ) == 0 )
						{
							LF();
						}
					}
				}

				LF();
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Size_Binary::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key Status Processor : Size / Binary";
		};
	}
	r2tm::DoFunctionT Size_Binary::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECL_MAIN( r2bix_input::KeyStatusProcessor p );

				LF();

				OUT_SIZE( p );

				LF();

				OUT_BINARY( p );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Update::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key Status Processor : Update";
		};
	}
	r2tm::DoFunctionT Update::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUT_STRING( "[ ESC ] Exit" );
			OUT_STRING( "[  1  ] Do" );

			LS();

			{
				r2bix_input::MachineInputSignals signals( 0, 0 );
				r2bix_input::KeyStatusProcessor key_status_processor;

				const r2tm::WindowsUtility::CursorPoint pivot_cursor_point = r2tm::WindowsUtility::GetCursorPoint();

				r2::FPSTimer fps_timer( 30u );
				bool last_changed = false;

				do
				{
					if( fps_timer.Update() )
					{
						signals.Collect();
						key_status_processor.Update( signals );

						if( key_status_processor.GetChanged( r2bix_input::eKeyCode::VK_1 ) )
						{
							last_changed = true;

							std::cout
								<< "status : " << ( ( int )key_status_processor.GetStep( r2bix_input::eKeyCode::VK_1 ) )
								<< "   "
								<< "changed : " << ( ( int )key_status_processor.GetChanged( r2bix_input::eKeyCode::VK_1 ) )
								<< r2tm::linefeed;
						}
						else if( last_changed )
						{
							last_changed = false;

							std::cout
								<< "status : " << ( ( int )key_status_processor.GetStep( r2bix_input::eKeyCode::VK_1 ) )
								<< "   "
								<< "changed : " << ( ( int )key_status_processor.GetChanged( r2bix_input::eKeyCode::VK_1 ) )
								<< "    ---입력 없음"
								<< r2tm::linefeed;
						}
					}

				} while( !key_status_processor.HasInput( r2bix_input::eKeyCode::VK_ESCAPE ) );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}