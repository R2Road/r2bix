#include "pch.h"
#include "renderable_test.h"

#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Camera.h"
#include "render/r2render_iRenderable.h"
#include "render/r2render_Texture.h"

namespace renderable_test
{
	class RenderableObject : r2render::iRenderable
	{
	public:
		RenderableObject( const r2::PointInt& position, const r2::RectInt& rect ) :
			mPosition( position )
			, mRect( rect )
			, mTexture( mRect.GetWidth(), mRect.GetHeight() )
		{
			for( int y = 0; mRect.GetHeight() > y; ++y )
			{
				for( int x = 0; mRect.GetWidth() > x; ++x )
				{
					mTexture.Fill( x, y, static_cast<char>( 49 + y ) );
				}
			}
		}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override
		{
			std::cout << "world space : my pos : " << mPosition.GetX() << "   " << mPosition.GetY() << r2::linefeed;
			std::cout << "world space : camera pos : " << camera->GetPoint().GetX() << "   " << camera->GetPoint().GetY() << r2::linefeed2;

			//
			// World Space : My Rect
			//
			{
				const r2::RectInt my_world_space_rect( mRect.GetOrigin() + mPosition, mRect.GetSize() );
				std::cout << "world space : my rect :"
					<< " " << my_world_space_rect.GetMinX() << " " << my_world_space_rect.GetMinY()
					<< " " << my_world_space_rect.GetMaxX() << " " << my_world_space_rect.GetMaxY()
					<< r2::linefeed2;

				if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
				{
					return;
				}
				else
				{
					std::cout << "===== My Rect Is Valid =====" << r2::linefeed2;
				}
			}

			//
			// Camera Space : My Position
			//
			const auto camera_space_my_position = mPosition - camera->GetPoint();
			std::cout << "camera space : my pos : " << camera_space_my_position.GetX() << "   " << camera_space_my_position.GetY() << r2::linefeed2;

			//
			// Render Target Space : My Position
			//
			const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();
			std::cout << "render target space : my pos : " << render_target_space_my_position.GetX() << "   " << render_target_space_my_position.GetY() << r2::linefeed2;

			//
			//
			//
			render_target->Fill( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), 'A' );

			//
			// Render Target Space : My Rect
			//
			auto render_target_space_my_rect = mRect;
			std::cout << "local space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2::linefeed2;

			render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );
			std::cout << "render target space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2::linefeed2;

			//
			// Render Target Space : Intersect Rect
			//
			auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );
			std::cout << "render target space : intersect rect :"
				<< " " << render_target_space_intersect_rect.GetMinX() << " " << render_target_space_intersect_rect.GetMinY()
				<< " " << render_target_space_intersect_rect.GetMaxX() << " " << render_target_space_intersect_rect.GetMaxY()
				<< r2::linefeed2;

			//
			// Offset
			//
			const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
			std::cout << "draw offset : " << off_set_point.GetX() << "   " << off_set_point.GetY() << r2::linefeed2;

			{
				for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() > y; ++y, ++ty )
				{
					for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() > x; ++x, ++tx )
					{
						render_target->Fill(
							x, y
							, mTexture.Get( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
						);
					}
				}
			}
		}

		r2::PointInt mPosition;
		r2::RectInt mRect;
		r2render::Texture mTexture;
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
			
			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			RenderableObject renderable_object( { 12, 24 }, { -4, -2, 9, 9 } );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject renderable_object( { 12, 24 }, { -4, -2, 9, 9 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show : Renderable Object Rect( +, O ), Camera Rect( #, X )" << r2::linefeed2;

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() > y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() > x; ++x )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}
				}

				{
					auto current_rect = renderable_object.mRect;
					current_rect.SetOrigin( current_rect.GetOrigin() + renderable_object.mPosition );

					for( int y = current_rect.GetMinY(); current_rect.GetMaxY() > y; ++y )
					{
						for( int x = current_rect.GetMinX(); current_rect.GetMaxX() > x; ++x )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '+';
						}
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( renderable_object.mPosition.GetX() ), static_cast<short>( renderable_object.mPosition.GetY() ) } );
				std::cout << 'O';

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			std::cout << r2::split;

			DWORD ret;
			system( "pause" );
			FillConsoleOutputCharacterA( GetStdHandle( STD_OUTPUT_HANDLE ), ' ', 40 * 120, { 0, 13 }, &ret );

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 13 } );

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