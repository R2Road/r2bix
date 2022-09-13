#include "camera_test.h"

#include <conio.h>
#include <Windows.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "r2bix/r2render_Camera.h"
#include "r2bix/r2render_Texture.h"

namespace camera_test
{
	r2cm::iItem::TitleFunctionT CameraPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Position";
		};
	}
	r2cm::iItem::DoFunctionT CameraPosition::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2render::Camera camera( { 20, 30 }, { 20, 10 } ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Show Camera Position" << r2cm::linefeed2;

				std::cout << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3;

				r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
				r2cm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}


			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2cm::iItem::DoFunctionT CameraRect::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			r2render::Camera camera( { 20, 30 }, { 20, 10 } );

			{
				std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
				std::cout << r2cm::tab2 << "r2render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Show Camera Rect" << r2cm::linefeed2;

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
					{
						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CameraMove::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move";
		};
	}
	r2cm::iItem::DoFunctionT CameraMove::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			r2render::Camera camera( { 20, 30 }, { 19, 9 } );

			int step = 0;

			do
			{
				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

				std::cout << r2cm::split;

				{
					std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
					std::cout << r2cm::tab2 << "r2render::Camera camera( { 20, 30 }, { 19, 9 } );" << r2cm::linefeed;
				}

				std::cout << r2cm::split;

				{
					std::cout << r2cm::tab << "+ Show Camera Rect" << r2cm::linefeed2;

					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}

					SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
					std::cout << 'X';
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 40 } );

				std::cout << "[ESC] Exit" << r2cm::linefeed;
				std::cout << "[Any Key] Move Camera" << r2cm::linefeed2;

				const int input = _getch();
				if( 27 == input )
				{
					break;
				}
				else
				{
					system( "cls" );

					if( 0 == step )
					{
						camera.SetPoint( 30, 20 );
						step = 1;
					}
					else
					{
						camera.SetPoint( 20, 30 );
						step = 0;
					}
				}

			} while( true );

			return r2cm::eItemLeaveAction::None;
		};
	}
}