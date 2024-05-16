#include "render_test.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"
#include "r2bix_render_Camera.h"
#include "r2bix_render_Texture.h"

namespace render_test
{
	class RenderTestNode : r2bix_node::Node
	{
	public:
		RenderTestNode( r2bix::Director& director, const r2::PointInt& position, const r2::SizeInt size, const r2::PointInt rect_offset ) : r2bix_node::Node( director )
			, mPosition( position )
			, mTexture( size.GetWidth(), size.GetHeight() )
			, mRect( rect_offset.GetX(), rect_offset.GetY(), mTexture.GetWidth() - 1, mTexture.GetHeight() - 1 )
		{
			for( int y = 0; mTexture.GetHeight() > y; ++y )
			{
				for( int x = 0; mTexture.GetWidth() > x; ++x )
				{
					mTexture.FillCharacter( x, y, static_cast<char>( 48 + x ) );
				}
			}
		}

		void Render( const r2bix_render::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt /*offset*/ ) override
		{
			std::cout << "world space : my pos : " << mPosition.GetX() << "   " << mPosition.GetY() << r2tm::linefeed;
			std::cout << "world space : camera pos : " << camera->GetPoint().GetX() << "   " << camera->GetPoint().GetY() << r2tm::linefeed2;

			//
			// World Space : My Rect
			//
			{
				const r2::RectInt my_world_space_rect( mRect.GetOrigin() + mPosition, mRect.GetSize() );
				std::cout << "world space : my rect :"
					<< " " << my_world_space_rect.GetMinX() << " " << my_world_space_rect.GetMinY()
					<< " " << my_world_space_rect.GetMaxX() << " " << my_world_space_rect.GetMaxY()
					<< r2tm::linefeed2;

				if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
				{
					return;
				}
				else
				{
					std::cout << "===== My Rect Is Valid =====" << r2tm::linefeed2;
				}
			}

			//
			// Camera Space : My Position
			//
			const auto camera_space_my_position = mPosition - camera->GetPoint();
			std::cout << "camera space : my pos : " << camera_space_my_position.GetX() << "   " << camera_space_my_position.GetY() << r2tm::linefeed2;

			//
			// Render Target Space : My Position
			//
			const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();
			std::cout << "render target space : my pos : " << render_target_space_my_position.GetX() << "   " << render_target_space_my_position.GetY() << r2tm::linefeed2;

			//
			//
			//
			render_target->FillCharacter( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), 'A' );

			//
			// Render Target Space : My Rect
			//
			auto render_target_space_my_rect = mRect;
			std::cout << "local space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2tm::linefeed2;

			render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );
			std::cout << "render target space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2tm::linefeed2;

			//
			// Render Target Space : Intersect Rect
			//
			auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );
			std::cout << "render target space : intersect rect :"
				<< " " << render_target_space_intersect_rect.GetMinX() << " " << render_target_space_intersect_rect.GetMinY()
				<< " " << render_target_space_intersect_rect.GetMaxX() << " " << render_target_space_intersect_rect.GetMaxY()
				<< r2tm::linefeed2;

			//
			// Offset
			//
			const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
			std::cout << "draw offset : " << off_set_point.GetX() << "   " << off_set_point.GetY() << r2tm::linefeed2;

			{
				for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() >= y; ++y, ++ty )
				{
					for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() >= x; ++x, ++tx )
					{
						render_target->FillCharacter(
							x, y
							, mTexture.GetCharacter( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
						);
					}
				}
			}
		}

		r2::PointInt mPosition;
		r2bix_render::Texture mTexture;
		r2::RectInt mRect;
	};

	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Render Test";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Camera camera( 20, 25, 20, 10 ) );
			DECLARATION_MAIN( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_MAIN( r2bix::Director director( {} ) );
			DECLARATION_MAIN( RenderTestNode node( director, r2::PointInt{ 12, 26 }, r2::SizeInt{ 9, 9 }, r2::PointInt{ -4, -2 } ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Show : RenderTestNode, Camera Rect( #, X )" << r2tm::linefeed2;

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
						{
							r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}
				}

				{
					auto current_rect = node.mRect;
					current_rect.SetOrigin( current_rect.GetOrigin() + node.mPosition );

					for( int y = 0; current_rect.GetHeight() > y; ++y )
					{
						for( int x = 0; current_rect.GetWidth() > x; ++x )
						{
							r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( current_rect.GetMinX() + x ), static_cast<short>( current_rect.GetMinY() + y ) } );
							std::cout << node.mTexture.GetCharacter( x, y );
						}
					}
				}

				r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';

				r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( node.mPosition.GetX() ), static_cast<short>( node.mPosition.GetY() ) } );
				std::cout << '+';

				r2tm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}

			LS();

			system( "pause" );

			{
				r2tm::WindowUtility::MoveCursorPointWithClearBuffer( { 0, 13 } );

				std::cout << r2tm::tab << "+ Show Render Target" << r2tm::linefeed2;

				node.Render( &camera, &render_target, r2::PointInt::GetZERO() );

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						LF();
					}
				}

				r2tm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}