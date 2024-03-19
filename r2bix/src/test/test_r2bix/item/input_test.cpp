#include "input_test.h"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_MachineInputCollector.h"
#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

#include "r2_RectInt.h"
#include "r2_FPSTimer.h"
#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

namespace input_test
{
	r2tm::TitleFunctionT MachineeInputCollector_Keyboard::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Machine Input Collector : Keyboard";
			};
	}
	r2tm::DoFunctionT MachineeInputCollector_Keyboard::GetDoFunction() const
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
					r2tm::WindowUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowUtility::CursorPoint temp_pos{ 20, 20 };

					r2tm::WindowUtility::MoveCursorPoint( pos );
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
								r2tm::WindowUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( temp_pos );
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


				r2::PointInt buffer_offset( 6, 10 );
				r2bix_input::MachineInputCollector machine_input_collector( buffer_offset );
				r2bix_input::ObservationKeyContainer observation_key_container( { 0x1B } ); // ESC
				machine_input_collector.AddObservationKeys( observation_key_container );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2bix_input::CursorPoint pos;
					r2bix_input::CursorPoint temp_pos;

					r2tm::WindowUtility::MoveCursorPoint( ( short )pos.GetX(), ( short )pos.GetY() );
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
								r2tm::WindowUtility::MoveCursorPoint( ( short )pos.GetX(), ( short )pos.GetY() );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( ( short )temp_pos.GetX(), ( short )temp_pos.GetY() );
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
						r2tm::WindowUtility::MoveCursorPoint( 0, 8 );
						std::cout << "      ";
						r2tm::WindowUtility::MoveCursorPoint( 0, 8 );
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



	r2tm::TitleFunctionT KeyboardInputListener_KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Listener : KeyStatus";
		};
	}
	r2tm::DoFunctionT KeyboardInputListener_KeyStatus::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[A] ..." << r2tm::linefeed;

			r2bix_input::InputManager input_manager( 0, 0 );
			r2bix_input::Listener4Keyboard keyboard_listener(
				0
				, {
					  0x1B		// esc
					, 0x41		// a
				}
			);

			input_manager.AddListener4Keyboard( &keyboard_listener );

			LS();

			{
				auto last_input_status = keyboard_listener.Get( 1 );
				while( 1 )
				{
					input_manager.Update();

					//
					// ESC
					//
					if( keyboard_listener.IsPushed( 0 ) )
					{
						break;
					}

					//
					// A
					//
					if( last_input_status != keyboard_listener.Get( 1 ) )
					{
						last_input_status = keyboard_listener.Get( 1 );
						std::cout << "status : " << static_cast<int>( last_input_status ) << r2tm::linefeed;
					}
				}
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}


	
	r2tm::TitleFunctionT KeyboardInputListener_Play::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Keyboard Listener : Play";
			};
	}
	r2tm::DoFunctionT KeyboardInputListener_Play::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ESC] Exit" << r2tm::linefeed;
				std::cout << "[WASD] Move" << r2tm::linefeed;

				r2bix_input::InputManager input_manager( 0, 0 );
				r2bix_input::Listener4Keyboard keyboard_listener(
					0
					, {
						  0x1B		// esc
						, 0x41		// a
						, 0x44		// d
						, 0x53		// s
						, 0x57		// w
					}
				);

				input_manager.AddListener4Keyboard( &keyboard_listener );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2tm::WindowUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowUtility::CursorPoint temp_pos{ 20, 20 };

					r2tm::WindowUtility::MoveCursorPoint( pos );
					std::cout << '@';

					while( 1 )
					{
						input_manager.Update();

						//
						// ESC
						//
						if( keyboard_listener.IsPushed( 0 ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = pos;

							if( keyboard_listener.HasInput( 1 ) )
							{
								--temp_pos.x;
							}
							if( keyboard_listener.HasInput( 2 ) )
							{
								++temp_pos.x;
							}
							if( keyboard_listener.HasInput( 4 ) )
							{
								--temp_pos.y;
							}
							if( keyboard_listener.HasInput( 3 ) )
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
								r2tm::WindowUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( temp_pos );
								std::cout << '@';

								pos = temp_pos;
							}
						}
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}



	r2tm::TitleFunctionT MouseListener_KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : KeyStatus";
		};
	}
	r2tm::DoFunctionT MouseListener_KeyStatus::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[  ESC  ] Exit" << r2tm::linefeed;
			std::cout << "[L Click] ..." << r2tm::linefeed;
			std::cout << "[R Click] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );
			r2bix_input::Listener4Keyboard keyboard_listener( 0, { r2bix_input::eKeyCode::VK_ESCAPE } );

			bool bLChanged = false;
			bool bRChanged = false;
			r2bix_input::eKeyStatus sl;
			r2bix_input::eKeyStatus sr;
			r2bix_input::Listener4Mouse mouse_listener( 0 );
			mouse_listener.SetKeyStatusChangedCallback( r2bix_input::eKeyCode::VK_LBUTTON, [&bLChanged, &sl]( const r2bix_input::eKeyStatus s )->bool{
				bLChanged = true;
				sl = s;

				return false;
			} );
			mouse_listener.SetKeyStatusChangedCallback( r2bix_input::eKeyCode::VK_RBUTTON, [&bRChanged, &sr]( const r2bix_input::eKeyStatus s )->bool{
				bRChanged = true;
				sr = s;

				return false;
			} );

			manager.AddListener4Keyboard( &keyboard_listener );
			manager.AddListener4Mouse( &mouse_listener );

			LS();

			{
				while( 1 )
				{
					manager.Update();

					//
					// ESC
					//
					if( keyboard_listener.IsPushed( 0 ) )
					{
						break;
					}

					//
					// Left Click
					//
					if( bLChanged )
					{
						bLChanged = false;
						std::cout << "key 0 status : " << static_cast< int >( sl ) << r2tm::linefeed;
					}

					//
					// Right Click
					//
					if( bRChanged )
					{
						bRChanged = false;
						std::cout << "\t\t\tkey 1 status : " << static_cast< int >( sr ) << r2tm::linefeed;
					}
				}
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MouseListener_Cursor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : Cursor";
		};
	}
	r2tm::DoFunctionT MouseListener_Cursor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ ESC  ] Exit" << r2tm::linefeed;
			std::cout << "[Cursor] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );
			r2bix_input::Listener4Keyboard keyboard_listener( 0, { r2bix_input::eKeyCode::VK_ESCAPE } );

			r2bix_input::CursorPoint c;
			bool bMoved = false;
			r2bix_input::Listener4Mouse mouse_listener( 0 );
			mouse_listener.SetCursorMovedCallback( [&c, &bMoved]( const r2bix_input::CursorPoint cursor_point )->bool{

				c = cursor_point;
				bMoved = true;

				return true;
			} );

			manager.AddListener4Keyboard( &keyboard_listener );
			manager.AddListener4Mouse( &mouse_listener );

			LS();

			{
				while( 1 )
				{
					manager.Update();

					//
					// ESC
					//
					if( keyboard_listener.IsPushed( 0 ) )
					{
						break;
					}

					//
					// Cursor Move
					//
					if( bMoved )
					{
						bMoved = false;

						r2tm::WindowUtility::MoveCursorPoint( 0, 10 );
						std::cout << "                                     ";

						r2tm::WindowUtility::MoveCursorPoint( 0, 10 );
						std::cout
							<< "X : "
							<< static_cast< int >( c.GetX() )
							<< "\tY : "
							<< static_cast< int >( c.GetY() )
							<< "         "
							<< r2tm::linefeed;
					}
				}
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InputManager_Order::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order";
		};
	}
	r2tm::DoFunctionT InputManager_Order::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "높은 Order 값을 가지면 목록의 앞으로 온다.");

			LS();

			DECLARATION_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUTPUT_SUBJECT( "Mouse" );

				LF();

				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_1( 2 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_3( 3 ) );

				LF();

				PROCESS_MAIN( m.AddListener4Mouse( &l_1 ) );
				PROCESS_MAIN( m.AddListener4Mouse( &l_2 ) );
				PROCESS_MAIN( m.AddListener4Mouse( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );

				LF();

				OUTPUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Mouse() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			{
				OUTPUT_SUBJECT( "Keyboard" );

				LF();

				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_1( 2, {} ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_2( 1, {} ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_3( 3, {} ) );

				LF();

				PROCESS_MAIN( m.AddListener4Keyboard( &l_1 ) );
				PROCESS_MAIN( m.AddListener4Keyboard( &l_2 ) );
				PROCESS_MAIN( m.AddListener4Keyboard( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_1);
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_2);

				LF();

				OUTPUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Keyboard() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}