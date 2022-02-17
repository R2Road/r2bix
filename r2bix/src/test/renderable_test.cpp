#include "pch.h"
#include "renderable_test.h"

#include "base/r2base_eTestEndAction.h"

#include "render/r2_iRenderable.h"
#include "render/r2_VisibleResource.h"

namespace renderable_test
{
	class RenderableObject : r2::iRenderable
	{
	public:
		RenderableObject() : mVR( 10, 10, 'R' )
		{}

		void Render( const r2::Camera* const camera ) override {}

		r2::VisibleResource mVR;
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

			RenderableObject ro;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject ro;" << r2::linefeed;
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}