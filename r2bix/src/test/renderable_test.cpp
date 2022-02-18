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

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override
		{
			std::cout << "world space : my pos : " << mPosition.GetX() << "   " << mPosition.GetY() << r2::linefeed;
			std::cout << "world space : camera pos : " << camera->GetPoint().GetX() << "   " << camera->GetPoint().GetY() << r2::linefeed2;

			//
			// View Space My Position
			//
			const auto current_position = mPosition - camera->GetPoint();
			std::cout << "camera space : my pos : " << current_position.GetX() << "   " << current_position.GetY() << r2::linefeed2;

			//
			// View Space My Rect
			//
			auto current_rect = mVR.GetVisibleRect();
			current_rect.SetOrigin( current_rect.GetOrigin() + current_position );
			std::cout << "camera space : my rect : "
				<< current_rect.GetMinX() << "   " << current_rect.GetMinY() << r2::linefeed
				<< current_rect.GetMaxX() << "   " << current_rect.GetMaxY() << r2::linefeed2;

			//
			// View Space Camera Rect
			//
			std::cout << "camera space : camera rect : "
				<< camera->GetCameraSpaceRect().GetMinX() << "   " << camera->GetCameraSpaceRect().GetMinY() << r2::linefeed
				<< camera->GetCameraSpaceRect().GetMaxX() << "   " << camera->GetCameraSpaceRect().GetMaxY() << r2::linefeed2;

			//
			// Intersect
			//
			const auto intersect_rect = current_rect.IntersectsWithRect( camera->GetCameraSpaceRect() );
			std::cout << "intersect : intersect rect : "
				<< intersect_rect.GetMinX() << "   " << intersect_rect.GetMinY() << r2::linefeed
				<< intersect_rect.GetMaxX() << "   " << intersect_rect.GetMaxY() << r2::linefeed2;
		}

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

			RenderableObject renderable_object( pivot_position );
			r2render::Camera camera( { 20, 25 }, { 20, 10 } );

			r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::PointInt pivot_position( 20, 25 );" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject renderable_object( pivot_position );" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Renderable Object Rect" << r2::linefeed2;

				auto current_rect = renderable_object.mVR.GetVisibleRect();
				current_rect.SetOrigin( current_rect.GetOrigin() + renderable_object.mPosition );

				for( int y = current_rect.GetMinY(); current_rect.GetMaxY() > y; ++y )
				{
					for( int x = current_rect.GetMinX(); current_rect.GetMaxX() > x; ++x )
					{
						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '+';
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( renderable_object.mPosition.GetX() ), static_cast<short>( renderable_object.mPosition.GetY() ) } );
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

			system( "pause" );
			FillConsoleOutputCharacterA( GetStdHandle( STD_OUTPUT_HANDLE ), ' ', 40 * 120, { 0, 15 }, &ret );

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 15 } );

				std::cout << r2::tab << "+ Show Render Target" << r2::linefeed2;

				renderable_object.Render( &camera, &render_target );

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			return r2base::eTestEndAction::Pause;
		};
	}
}