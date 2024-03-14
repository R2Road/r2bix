#include "input_test.h"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_MachineInputCollector.h"
#include "r2bix_input_KeyboardListener.h"
#include "r2bix_input_MouseListener.h"

#include "r2_RectInt.h"
#include "r2_FPSTimer.h"
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
				r2bix_input::ObservationKeys observation_keys( {
					0x1B		// esc
					, 0x41		// a
					, 0x44		// d
					, 0x53		// s
					, 0x57		// w
					} );

				machine_input_collector.AddObservationKeys( observation_keys );

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
				r2bix_input::ObservationKeys observation_keys( { 0x1B } ); // ESC
				machine_input_collector.AddObservationKeys( observation_keys );

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
						// Mouse Move Flag �� �������� ������
						//  > Ŀ�� ������ CursorPoint ���� ����� ���� ���� �̻��� �̵����� �߻����� ������ CursorPoint �� �״�� �̱� ������
						//  > Mouse�� �̵��ϴ� ���ӿ��� ���� Off �� ���´�.
						//  > �� �����ӿ� ��Ʈ ���� ���� �̻��� �������� ������ ������ On ���� �����ȴٴ� ���̴�.
						// ��������δ� ���� ����.
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
			r2bix_input::KeyboardListener keyboard_listener( {
				0x1B		// esc
				, 0x41		// a
			} );

			input_manager.AddKeyboardListener( &keyboard_listener );

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
				r2bix_input::KeyboardListener keyboard_listener( {
					0x1B		// esc
					, 0x41		// a
					, 0x44		// d
					, 0x53		// s
					, 0x57		// w
					} );

				input_manager.AddKeyboardListener( &keyboard_listener );

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

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[A] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );
			r2bix_input::KeyboardListener keyboard_listener( { r2bix_input::eKeyCode::VK_ESCAPE } );
			r2bix_input::MouseListener mouse_listener( false, true, true );

			manager.AddKeyboardListener( &keyboard_listener );
			manager.AddMouseListener( &mouse_listener );

			LS();

			{
				auto last_input_status_0 = mouse_listener.Get( 0 );
				auto last_input_status_1 = mouse_listener.Get( 1 );
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
					if( last_input_status_0 != mouse_listener.Get( 0 ) )
					{
						last_input_status_0 = mouse_listener.Get( 0 );
						std::cout << "key 0 status : " << static_cast< int >( last_input_status_0 ) << r2tm::linefeed;
					}

					//
					// Right Click
					//
					if( last_input_status_1 != mouse_listener.Get( 1 ) )
					{
						last_input_status_1 = mouse_listener.Get( 1 );
						std::cout << "\t\t\tkey 1 status : " << static_cast< int >( last_input_status_1 ) << r2tm::linefeed;
					}
				}
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}