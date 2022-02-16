#include "pch.h"
#include "camera_test.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "render/r2_iRenderable.h"
#include "render/r2_VisibleResource.h"

#include "render/r2_Camera.h"
#include "render/r2_Renderer.h"

namespace camera_test
{
	r2base::iTest::TitleFunc CameraPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Position";
		};
	}
	r2base::iTest::DoFunc CameraPosition::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::Camera camera( { 20, 20, 60, 30 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::Camera camera( { 20, 20, 60, 30 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Position" << r2::linefeed2;

				std::cout << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3;

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2base::iTest::DoFunc CameraRect::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::Camera camera( { 14, 14, 60, 30 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::Camera camera( { 14, 14, 60, 30 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Rect" << r2::linefeed2;

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() > y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() > x; ++x )
					{
						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );

			return r2base::eTestEndAction::Pause;
		};
	}
}