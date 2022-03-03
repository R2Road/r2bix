#include "pch.h"
#include "renderer_test.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Camera.h"
#include "render/r2render_iRenderable.h"

namespace renderer_test
{
	class TempRenderable : public r2render::iRenderable
	{
	public:
		TempRenderable( const int x, const int y, const uint32_t width, const char* chars) :
			mPoint( { x, y } )
			, mVisibleResource( width, chars )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const /*render_target*/ ) override
		{
			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			COORD pos = {
				static_cast<short>( mPoint.GetX() - camera->GetPoint().GetX() )
				, static_cast<short>( mPoint.GetY() - camera->GetPoint().GetY() )
			};
			SetConsoleCursorPosition( stdHandle, pos );

			int count = 0;
			for( const char element : mVisibleResource )
			{
				std::cout << element;

				++count;
				if( mVisibleResource.GetWidth() <= count )
				{
					count = 0;
					pos.Y += 1;
					SetConsoleCursorPosition( stdHandle, pos );
				}
			}
		}

	private:
		r2::PointInt mPoint;
		r2render::Texture mVisibleResource;
	};

	r2base::iTest::TitleFunc TestRenderable::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Renderable";
		};
	}
	r2base::iTest::DoFunc TestRenderable::GetDoFunction()
	{
		static TempRenderable tr( 8, 5, 6u, "######" "#    #" "#    #" "#    #" "#    #" "######" );
		auto& tr2 = tr;

		return [&tr2]( r2base::Director& )->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2render::Camera camera( { 0, 0 }, { 60, 30 } );
			tr2.Render( &camera, nullptr );

			return r2base::eTestEndAction::Pause;
		};
	}



	TestRenderer::TestRenderer() : mRenderer() {}

	r2base::iTest::TitleFunc TestRenderer::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Renderer";
		};
	}
	r2base::iTest::DoFunc TestRenderer::GetDoFunction()
	{
		auto& rd = GetInstance().mRenderer;
		rd.Clear();


		static r2render::Camera dummy_camera( { 0, 0 }, { 60, 30 } );
		rd.SetCamera( &dummy_camera );


		std::string str( "# " );
		str += GetInstance().GetTitleFunction()();
		str += " #";
		static TempRenderable tr0( 0, 0, static_cast<uint32_t>( str.length() ), str.c_str() );
		rd.Add( &tr0 );

		static TempRenderable tr1( 2, 2, 3u, "###" "# #" "###" );
		rd.Add( &tr1 );

		static TempRenderable tr2( 8, 3, 6u, "######" "#    #" "#    #" "#    #" "#    #" "######" );
		rd.Add( &tr2 );

		static TempRenderable tr3( 11, 5, 7u, "#######" "#     #" "#     #" "#     #" "#     #" "#######" );
		rd.Add( &tr3 );

		return [&rd]( r2base::Director& )->r2base::eTestEndAction
		{
			rd.Draw();

			return r2base::eTestEndAction::Pause;
		};
	}
}


namespace renderer_test
{
	class TempRenderable2 : public r2render::iRenderable
	{
	public:
		TempRenderable2( const int x, const int y, const uint32_t width, const char* chars ) :
			mPoint( { x, y } )
			, mVisibleResource( width, chars )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const /*render_target*/ ) override
		{
			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			COORD pos = {
				static_cast<short>( mPoint.GetX() - camera->GetPoint().GetX() )
				, static_cast<short>( mPoint.GetY() - camera->GetPoint().GetY() )
			};
			SetConsoleCursorPosition( stdHandle, pos );

			int count = 0;
			for( const char element : mVisibleResource )
			{
				std::cout << element;

				++count;
				if( mVisibleResource.GetWidth() <= count )
				{
					count = 0;
					pos.Y += 1;
					SetConsoleCursorPosition( stdHandle, pos );
				}
			}
		}

	private:
		r2::PointInt mPoint;
		r2render::Texture mVisibleResource;
	};

	r2base::iTest::TitleFunc CameraMove1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move 1";
		};
	}
	r2base::iTest::DoFunc CameraMove1::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::Camera camera( { 0, 0 }, { 60, 30 } );
			r2render::Renderer renderer;

			renderer.Clear();
			renderer.SetCamera( &camera );

			{
				std::string str( "# " );
				str += GetInstance().GetTitleFunction()( );
				str += " #";
				static TempRenderable2 tr( 0, 0, static_cast<uint32_t>( str.length() ), str.c_str() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[ESC] Return to Root" );
				static TempRenderable2 tr( 0, 1, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[W,A,S,D] Move Camera" );
				static TempRenderable2 tr( 0, 2, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				static TempRenderable2 tr( 2, 4, 3u, "###" "# #" "###" );
				renderer.Add( &tr );
			}

			{
				static TempRenderable2 tr( 11, 7, 7u, "#######" "#     #" "#     #" "#     #" "#     #" "#######" );
				renderer.Add( &tr );
			}

			int x = 0;
			int y = 0;
			bool process = true;
			do
			{
				renderer.Draw();

				switch( _getch() )
				{
				case 'w': // up
					y -= 1;
					break;
				case 's': // down
					y += 1;
					break;
				case 'a': // left
					x -= 1;
					break;
				case 'd': // right
					x += 1;
					break;

				case 27: // ESC
					process = false;
					break;
				}

				camera.SetPoint( x, y );
			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
}


namespace renderer_test
{
	class Renderable4CameraTest : public r2render::iRenderable
	{
	public:
		Renderable4CameraTest( const int x, const int y, const uint32_t width, const char* chars ) :
			mVisibleResource( width, chars )
			, mRect( { x, y, mVisibleResource.GetWidth(), mVisibleResource.GetHeight() } )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const /*render_target*/ ) override
		{
			if( !camera->GetRect().IntersectsRect( mRect ) )
			{
				return;
			}

			const auto visible_rect = camera->GetRect().IntersectsWithRect( mRect );

			const COORD pivot_pos = {
				static_cast<short>( visible_rect.GetMinX() - camera->GetX() )
				, static_cast<short>( visible_rect.GetMinY() - camera->GetY() )
			};

			const int resource_offset_y = visible_rect.GetMinY() - mRect.GetMinY();
			const int resource_offset_x = visible_rect.GetMinX() - mRect.GetMinX();

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			for( int y = 0; y < visible_rect.GetHeight(); ++y )
			{
				for( int x = 0; x < visible_rect.GetWidth(); ++x )
				{
					SetConsoleCursorPosition( stdHandle, {
						pivot_pos.X + static_cast<short>( x )
						, pivot_pos.Y + static_cast<short>( y ) }
					);

					std::cout << mVisibleResource.Get(
						resource_offset_x + x
						, resource_offset_y + y
					);
				}
			}
		}

	private:
		r2render::Texture mVisibleResource;
		r2::RectInt mRect;
	};

	r2base::iTest::TitleFunc CameraMove2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move 2";
		};
	}
	r2base::iTest::DoFunc CameraMove2::GetDoFunction()
	{
		return[]( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::Camera camera( { 0, 0 }, { 60, 30 } );

			r2render::Renderer renderer;
			renderer.Clear();
			renderer.SetCamera( &camera );

			{
				std::string str( "# " );
				str += GetInstance().GetTitleFunction()( );
				str += " #";
				static Renderable4CameraTest tr( 0, 0, static_cast<uint32_t>( str.length() ), str.c_str() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[ESC] Return to Root" );
				static Renderable4CameraTest tr( 0, 1, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[W,A,S,D] Move Camera" );
				static Renderable4CameraTest tr( 0, 2, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				static Renderable4CameraTest tr( 2, 4, 3u, "###" "# #" "###" );
				renderer.Add( &tr );
			}

			{
				static Renderable4CameraTest tr( 11, 7, 7u, "#######" "#     #" "#     #" "#     #" "#     #" "#######" );
				renderer.Add( &tr );
			}

			int x = 0;
			int y = 0;
			bool process = true;
			do
			{
				renderer.Draw();

				switch( _getch() )
				{
				case 'w': // up
					y -= 1;
					break;
				case 's': // down
					y += 1;
					break;
				case 'a': // left
					x -= 1;
					break;
				case 'd': // right
					x += 1;
					break;

				case 27: // ESC
					process = false;
					break;
				}

				camera.SetPoint( x, y );
			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
}