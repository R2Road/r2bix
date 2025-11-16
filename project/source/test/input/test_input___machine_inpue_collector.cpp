#include "test_input___machine_inpue_collector.hpp"

#include <algorithm>

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"
#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "r2bix_input_MachineInputCollector.h"

#include "helper/r2bixprinter_cursor_point.hpp"

namespace test_input___machine_inpue_collector
{
	r2tm::TitleFunctionT MachineInputCollector_Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Machine Input Collector : Declaration";
		};
	}
	r2tm::DoFunctionT MachineInputCollector_Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( r2bix_input::CursorPoint::ValueT x = 10 );
			DECL_MAIN( r2bix_input::CursorPoint::ValueT y = 20 );

			LS();

			{
				OUT_SUBJECT( "생성자 1" );

				LF();

				DECL_MAIN( r2bix_input::MachineInputCollector c( x, y ) );

				LF();

				EXPECT_EQ( x, c.GetOffsetX() );
				EXPECT_EQ( y, c.GetOffsetY() );
				EXPECT_EQ( r2bix_input::CursorPoint( x, y ), c.GetOffset() );

				LF();

				OUT_VALUE( c.GetOffset() );
			}

			LS();

			{
				OUT_SUBJECT( "생성자 2" );

				LF();

				DECL_MAIN( r2bix_input::MachineInputCollector c( r2bix_input::CursorPoint( x, y ) ) );

				LF();

				EXPECT_EQ( x, c.GetOffsetX() );
				EXPECT_EQ( y, c.GetOffsetY() );
				EXPECT_EQ( r2bix_input::CursorPoint( x, y ), c.GetOffset() );

				LF();

				OUT_VALUE( c.GetOffset() );
			}

			LS();			

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MachineInputCollector_Size_Binary::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Machine Input Collector : Size / Binary";
		};
	}
	r2tm::DoFunctionT MachineInputCollector_Size_Binary::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();


			DECL_MAIN( r2bix_input::MachineInputCollector c( 0, 0 ) );

			LF();

			{
				OUT_SIZE( c );

				LF();

				OUT_BINARY( c );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MachineInputCollector_Keyboard::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Machine Input Collector : Keyboard";
			};
	}
	r2tm::DoFunctionT MachineInputCollector_Keyboard::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ESC] Exit" << r2tm::linefeed;
				std::cout << "[WASD] Move" << r2tm::linefeed;

				r2bix_input::MachineInputCollector machine_input_collector( 0, 0 );
				r2bix_input::ObservationKeyContainer observation_key_container( {
					0x1B		// esc
					, 0x41		// a
					, 0x44		// d
					, 0x53		// s
					, 0x57		// w
				} );

				machine_input_collector.AddObservationKeys( observation_key_container );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2tm::WindowsUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowsUtility::CursorPoint temp_pos{ 20, 20 };

					r2tm::WindowsUtility::MoveCursorPoint( pos );
					std::cout << '@';

					while( 1 )
					{
						machine_input_collector.Collect();

						//
						// ESC
						//
						if( machine_input_collector.HasInput( 0x1B ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = pos;

							if( machine_input_collector.HasInput( 0x41 ) )
							{
								--temp_pos.x;
							}
							if( machine_input_collector.HasInput( 0x44 ) )
							{
								++temp_pos.x;
							}
							if( machine_input_collector.HasInput( 0x57 ) )
							{
								--temp_pos.y;
							}
							if( machine_input_collector.HasInput( 0x53 ) )
							{
								++temp_pos.y;
							}
							if( !stage_area.IsIn( temp_pos.x, temp_pos.y ) )
							{
								temp_pos.x = std::clamp( temp_pos.x, static_cast< short >( stage_area.GetMinX() ), static_cast< short >( stage_area.GetMaxX() ) );
								temp_pos.y = std::clamp( temp_pos.y, static_cast< short >( stage_area.GetMinY() ), static_cast< short >( stage_area.GetMaxY() ) );
							}

							if( temp_pos.x != pos.x || temp_pos.y != pos.y )
							{
								r2tm::WindowsUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowsUtility::MoveCursorPoint( temp_pos );
								std::cout << '@';

								pos = temp_pos;
							}
						}
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}



	r2tm::TitleFunctionT MachineInputCollector_Mouse::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Machine Input Collector : Mouse";
			};
	}
	r2tm::DoFunctionT MachineInputCollector_Mouse::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ ESC ] Exit" << r2tm::linefeed;
				std::cout << "[MOUSE] Move" << r2tm::linefeed;


				r2::PointInt buffer_offset( 1, 2 );
				r2bix_input::MachineInputCollector machine_input_collector( buffer_offset );
				r2bix_input::ObservationKeyContainer observation_key_container( { 0x1B } ); // ESC
				machine_input_collector.AddObservationKeys( observation_key_container );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2bix_input::CursorPoint pos;
					r2bix_input::CursorPoint temp_pos;

					r2tm::WindowsUtility::MoveCursorPoint( ( short )pos.GetX(), ( short )pos.GetY() );
					std::cout << '@';

					while( 1 )
					{
						machine_input_collector.Collect();

						//
						// ESC
						//
						if( machine_input_collector.HasInput( 0x1B ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = machine_input_collector.GetCursorPoint();

							if( !stage_area.IsIn( temp_pos ) )
							{
								temp_pos = stage_area.Clamp( temp_pos );
							}

							if( temp_pos != pos )
							{
								r2tm::WindowsUtility::MoveCursorPoint( ( short )pos.GetX(), ( short )pos.GetY() );
								std::cout << ' ';
								r2tm::WindowsUtility::MoveCursorPoint( ( short )temp_pos.GetX(), ( short )temp_pos.GetY() );
								std::cout << '@';

								pos = temp_pos;
							}
						}

						//
						// # 2024.03.11 by R
						// Mouse Move Flag 의 가시적인 문제점
						//  > 커서 단위로 CursorPoint 값을 만들다 보니 일정 이상의 이동량이 발생하지 않으면 CursorPoint 가 그대로 이기 때문에
						//  > Mouse가 이동하는 중임에도 값이 Off 로 나온다.
						//  > 한 프레임에 폰트 가로 세로 이상의 움직임을 꾸준히 보여야 On 으로 유지된다는 것이다.
						// 기능적으로는 문제 없다.
						//
						r2tm::WindowsUtility::MoveCursorPoint( 0, 8 );
						std::cout << "      ";
						r2tm::WindowsUtility::MoveCursorPoint( 0, 8 );
						std::cout
							<< machine_input_collector.GetCursorPoint().GetX() << " " << machine_input_collector.GetCursorPoint().GetY()
							<< "\t" << ( machine_input_collector.IsMouseMoved() ? "Move" : "Stay" ) << "\n"
							<< "Offset " << buffer_offset.GetX() << ", " << buffer_offset.GetY() << "\n"
							;
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}
}