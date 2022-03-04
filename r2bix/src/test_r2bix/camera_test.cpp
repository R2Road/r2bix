#include "pch.h"
#include "camera_test.h"

#include <conio.h>
#include <Windows.h>

#include "r2cm/r2cm_eTestEndAction.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "render/r2render_iRenderable.h"
#include "render/r2render_Texture.h"

#include "render/r2render_Camera.h"
#include "render/r2render_Renderer.h"

namespace camera_test
{
	r2cm::iItem::TitleFuncT CameraPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Position";
		};
	}
	r2cm::iItem::DoFuncT CameraPosition::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::Camera camera( { 20, 30 }, { 20, 10 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Position" << r2::linefeed2;

				std::cout << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3;

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2cm::iItem::DoFuncT CameraRect::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::Camera camera( { 20, 30 }, { 20, 10 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Rect" << r2::linefeed2;

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

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT CameraMove::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move";
		};
	}
	r2cm::iItem::DoFuncT CameraMove::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			r2render::Camera camera( { 20, 30 }, { 19, 9 } );

			int step = 0;

			do
			{
				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

				std::cout << r2::split;

				{
					std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
					std::cout << r2::tab2 << "r2render::Camera camera( { 20, 30 }, { 19, 9 } );" << r2::linefeed;
				}

				std::cout << r2::split;

				{
					std::cout << r2::tab << "+ Show Camera Rect" << r2::linefeed2;

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

				std::cout << "[ESC] Exit" << r2::linefeed;
				std::cout << "[Any Key] Move Camera" << r2::linefeed2;

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

			return r2cm::eTestEndAction::None;
		};
	}
}