#include "test_input.h"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_MachineInputCollector.h"
#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

#include "r2_RectInt.h"
#include "r2_FPSTimer.h"
#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

namespace test_input
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



	r2tm::TitleFunctionT ObservationKey::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "ObservationKey";
		};
	}
	r2tm::DoFunctionT ObservationKey::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_input::ObservationKey o );

			LF();

			OUTPUT_SIZE( o );

			LF();

			OUTPUT_BINARY( o );

			LS();

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

			bool bPlay = true;
			r2bix_input::Listener4Keyboard keyboard_listener;
			keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStatus )->bool
			{
				bPlay = false;
				return false;
			} );

			bool bAChanged = false;
			r2bix_input::eKeyStatus as = r2bix_input::eKeyStatus::None;
			keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_A, [&bAChanged, &as]( r2bix_input::eKeyStatus s )->bool
			{
				bAChanged = true;
				as = s;
				return false;
			} );

			input_manager.AddListener( &keyboard_listener );

			LS();

			{
				do
				{

					input_manager.Update();

					//
					// A
					//
					if( bAChanged )
					{
						bAChanged = false;
						std::cout << "status : " << static_cast<int>( as ) << r2tm::linefeed;
					}

				} while( bPlay );
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

				bool bPlay = true;
				r2bix_input::Listener4Keyboard keyboard_listener;
				keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStatus )->bool
				{
					bPlay = false;
					return false;
				} );

				r2tm::WindowsUtility::CursorPoint new_pos{ 20, 20 };
				keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_A, [&new_pos]( r2bix_input::eKeyStatus )->bool
				{
					--new_pos.x;
					return false;
				} );
				keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_D, [&new_pos]( r2bix_input::eKeyStatus )->bool
				{
					++new_pos.x;
					return false;
				} );
				keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_S, [&new_pos]( r2bix_input::eKeyStatus )->bool
				{
					++new_pos.y;
					return false;
				} );
				keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_W, [&new_pos]( r2bix_input::eKeyStatus )->bool
				{
					--new_pos.y;
					return false;
				} );

				input_manager.AddListener( &keyboard_listener );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );

					r2tm::WindowsUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowsUtility::MoveCursorPoint( pos );
					std::cout << '@';

					do
					{

						if( fps_timer.Update() )
						{
							input_manager.Update();

							if( !stage_area.IsIn( new_pos.x, new_pos.y ) )
							{
								new_pos.x = std::clamp( new_pos.x, static_cast< short >( stage_area.GetMinX() ), static_cast< short >( stage_area.GetMaxX() ) );
								new_pos.y = std::clamp( new_pos.y, static_cast< short >( stage_area.GetMinY() ), static_cast< short >( stage_area.GetMaxY() ) );
							}

							if( new_pos.x != pos.x || new_pos.y != pos.y )
							{
								r2tm::WindowsUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowsUtility::MoveCursorPoint( new_pos );
								std::cout << '@';

								pos = new_pos;
							}
						}

					} while( bPlay );
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
			std::cout << "[M Click] ..." << r2tm::linefeed;
			std::cout << "[R Click] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );

			bool bPlay = true;
			r2bix_input::Listener4Keyboard keyboard_listener;
			keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStatus )->bool
			{
				bPlay = false;
				return false;
			} );

			bool bLChanged = false;
			bool bMChanged = false;
			bool bRChanged = false;
			r2bix_input::eKeyStatus sl;
			r2bix_input::eKeyStatus sm;
			r2bix_input::eKeyStatus sr;
			r2bix_input::Listener4Mouse mouse_listener;
			mouse_listener.AddObservationKey( r2bix_input::eKeyCode::VK_LBUTTON );
			mouse_listener.AddObservationKey( r2bix_input::eKeyCode::VK_MBUTTON );
			mouse_listener.AddObservationKey( r2bix_input::eKeyCode::VK_RBUTTON );
			mouse_listener.SetCallback4KeyStatusChanged( [&bLChanged, &sl, &bMChanged, &sm, &bRChanged, &sr]( const int key_index, const r2bix_input::eKeyStatus s )->bool
			{
				switch( key_index )
				{
				case 0:
					bLChanged = true;
					sl = s;
					break;
				case 1:
					bMChanged = true;
					sm = s;
					break;
				case 2:
					bRChanged = true;
					sr = s;
					break;
				}

				return false;
			} );

			manager.AddListener( &keyboard_listener );
			manager.AddListener( &mouse_listener );

			LS();

			{
				do
				{
					manager.Update();

					//
					// Left Click
					//
					if( bLChanged )
					{
						bLChanged = false;
						std::cout << "key 0 status : " << static_cast< int >( sl ) << r2tm::linefeed;
					}

					//
					// Middle Click
					//
					if( bMChanged )
					{
						bMChanged = false;
						std::cout << "\t\t\tkey 2 status : " << static_cast< int >( sm ) << r2tm::linefeed;
					}

					//
					// Right Click
					//
					if( bRChanged )
					{
						bRChanged = false;
						std::cout << "\t\t\t\t\t\tkey 3 status : " << static_cast< int >( sr ) << r2tm::linefeed;
					}
				} while( bPlay );
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

			bool bPlay = true;
			r2bix_input::Listener4Keyboard keyboard_listener;
			keyboard_listener.SetCallback4KeyStatusChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStatus )->bool
			{
				bPlay = false;
				return false;
			} );

			r2bix_input::CursorPoint c;
			bool bMoved = false;
			r2bix_input::Listener4Mouse mouse_listener;
			mouse_listener.SetCallback4CursorMoved( [&c, &bMoved]( const r2bix_input::CursorPoint cursor_point )->bool{

				c = cursor_point;
				bMoved = true;

				return true;
			} );

			manager.AddListener( &keyboard_listener );
			manager.AddListener( &mouse_listener );

			LS();

			{
				do
				{
					manager.Update();

					//
					// Cursor Move
					//
					if( bMoved )
					{
						bMoved = false;

						r2tm::WindowsUtility::MoveCursorPoint( 0, 10 );
						std::cout << "                                     ";

						r2tm::WindowsUtility::MoveCursorPoint( 0, 10 );
						std::cout
							<< "X : "
							<< static_cast< int >( c.GetX() )
							<< "\tY : "
							<< static_cast< int >( c.GetY() )
							<< "         "
							<< r2tm::linefeed;
					}
				} while( bPlay );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InputManager_Order1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order 1";
		};
	}
	r2tm::DoFunctionT InputManager_Order1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "같은 Order 값이면 늦게 추가된 리스너가 목록의 앞으로 온다." );

			LS();

			DECLARATION_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUTPUT_SUBJECT( "Mouse" );

				LF();

				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_1( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Mouse l_3( 1 ) );

				LF();

				PROCESS_MAIN( m.AddListener( &l_1 ) );
				PROCESS_MAIN( m.AddListener( &l_2 ) );
				PROCESS_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );

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

				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_1( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_2( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_3( 1 ) );

				LF();

				PROCESS_MAIN( m.AddListener( &l_1 ) );
				PROCESS_MAIN( m.AddListener( &l_2 ) );
				PROCESS_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_1 );

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



	r2tm::TitleFunctionT InputManager_Order2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order 2";
		};
	}
	r2tm::DoFunctionT InputManager_Order2::GetDoFunction() const
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

				PROCESS_MAIN( m.AddListener( &l_1 ) );
				PROCESS_MAIN( m.AddListener( &l_2 ) );
				PROCESS_MAIN( m.AddListener( &l_3 ) );

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

				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_1( 2 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_2( 1 ) );
				DECLARATION_MAIN( r2bix_input::Listener4Keyboard l_3( 3 ) );

				LF();

				PROCESS_MAIN( m.AddListener( &l_1 ) );
				PROCESS_MAIN( m.AddListener( &l_2 ) );
				PROCESS_MAIN( m.AddListener( &l_3 ) );

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