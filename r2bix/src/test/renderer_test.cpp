#include "pch.h"
#include "renderer_test.h"

#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "render/r2_Camera.h"
#include "render/r2_iRenderable.h"

namespace renderer_test
{
	class TempRenderable : public r2::iRenderable
	{
	public:
		TempRenderable( const int x, const int y, const uint32_t width, const char* chars) :
			mPoint( { x, y } )
			, mVisibleResource( width, chars )
		{}

		void Render( const r2::Camera* const camera ) override
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
		r2::VisibleResource mVisibleResource;
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

		return [&tr2]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2::Camera camera;
			tr2.Render( &camera);

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


		static r2::Camera dummy_camera;
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

		return [&rd]()->r2base::eTestEndAction
		{
			rd.Draw();

			return r2base::eTestEndAction::Pause;
		};
	}
}