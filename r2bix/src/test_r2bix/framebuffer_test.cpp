#include "pch.h"
#include "framebuffer_test.h"

#include "r2cm/r2cm_eTestEndAction.h"

#include "render/r2render_FrameBuffer.h"

namespace framebuffer_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Basic";
		};
	}
	r2cm::iItem::DoFunc Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::FrameBuffer frame_buffer( 3, 3 );
			frame_buffer.FillAll( 'c' );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::FrameBuffer frame_buffer( 3, 3 );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::cout << &( *frame_buffer.begin() ) << r2::linefeed;
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}