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

			r2::Camera camera;
			camera.SetPoint( { 14, 14 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::Camera camera;" << r2::linefeed;
				std::cout << r2::tab2 << "camera.SetPoint( { 14, 14 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Rect" << r2::linefeed2;

				HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() > y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() > x; ++x )
					{
						SetConsoleCursorPosition( stdHandle, { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				std::cout << r2::linefeed;
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}