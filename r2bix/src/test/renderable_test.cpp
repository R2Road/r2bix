#include "pch.h"
#include "renderable_test.h"

#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Camera.h"
#include "render/r2render_iRenderable.h"
#include "render/r2render_VisibleResource.h"

namespace renderable_test
{
	class RenderableObject : r2render::iRenderable
	{
	public:
		RenderableObject( const r2::PointInt& position ) :
			mPosition( position )
			, mVR( 10, 10, 'R' )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override {}

		r2::PointInt mPosition;
		r2render::VisibleResource mVR;
	};

	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			const r2::PointInt pivot_position( 20, 25 );

			RenderableObject ro( pivot_position );
			r2render::Camera camera( { 20, 25 }, { 20, 10 } );

			r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::PointInt pivot_position( 20, 25 );" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject ro( pivot_position );" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Renderable Object Rect" << r2::linefeed2;

				auto current_rect = ro.mVR.GetVisibleRect();
				current_rect.SetOrigin( current_rect.GetOrigin() + ro.mPosition );

				for( int y = current_rect.GetMinY(); current_rect.GetMaxY() > y; ++y )
				{
					for( int x = current_rect.GetMinX(); current_rect.GetMaxX() > x; ++x )
					{
						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '+';
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( ro.mPosition.GetX() ), static_cast<short>( ro.mPosition.GetY() ) } );
				std::cout << 'O';

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			std::cout << r2::split;

			system( "pause" );
			DWORD ret;
			FillConsoleOutputCharacterA( GetStdHandle( STD_OUTPUT_HANDLE ), ' ', 40 * 120, { 0, 15 }, &ret );

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 15 } );

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

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}