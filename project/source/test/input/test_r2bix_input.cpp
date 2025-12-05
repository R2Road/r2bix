#include "test_r2bix_input.hpp"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"
#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

namespace test_input
{
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
				long long frame = 0ll;
				do
				{

					input_manager.Update();

					//
					// A
					//
					if( bAChanged )
					{
						bAChanged = false;
						std::cout << "status : " << static_cast<int>( as ) << "    " << frame << r2tm::linefeed;
					}

					++frame;

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

			OUT_NOTE( "같은 Order 값이면 늦게 추가된 리스너가 목록의 앞으로 온다." );

			LS();

			DECL_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUT_SUBJECT( "Mouse" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l_1( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_3( 1 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Mouse() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			{
				OUT_SUBJECT( "Keyboard" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Keyboard l_1( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_3( 1 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_1 );

				LF();

				OUT_COMMENT( "Z ORder" );
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

			OUT_NOTE( "높은 Order 값을 가지면 목록의 앞으로 온다.");

			LS();

			DECL_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUT_SUBJECT( "Mouse" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l_1( 2 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_3( 3 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Mouse() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			{
				OUT_SUBJECT( "Keyboard" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Keyboard l_1( 2 ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_3( 3 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_1);
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_2);

				LF();

				OUT_COMMENT( "Z ORder" );
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