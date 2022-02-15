#include "pch.h"
#include "framebuffer_test.h"

#include "base/r2base_eTestEndAction.h"

#include "renderer/r2_FrameBuffer.h"

namespace framebuffer_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::FrameBuffer frame_buffer( 3, 3 );
			frame_buffer.FillAll( 'c' );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::FrameBuffer frame_buffer( 3, 3 );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::cout << &( *frame_buffer.begin() ) << r2::linefeed;
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}