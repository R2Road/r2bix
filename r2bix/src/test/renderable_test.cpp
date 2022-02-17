#include "pch.h"
#include "renderable_test.h"

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

			const r2::PointInt pivot_position( 20, 30 );

			RenderableObject ro( pivot_position );
			r2render::Camera camera( { 20, 30 }, { 20, 10 } );

			r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::PointInt pivot_position( 20, 30 );" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject ro( pivot_position );" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2::linefeed;
			}

			std::cout << r2::split;

			{

			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}