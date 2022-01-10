#include "pch.h"
#include "framebuffer_test.h"

#include "base/r2_eTestResult.h"

#include "renderer/r2_FrameBuffer.h"

namespace framebuffer_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Basic";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::FrameBuffer frame_buffer( 19, 19 );
			frame_buffer.FillAll( 'c' );

			{
				int current_x = 0;
				for( const auto v : frame_buffer )
				{
					if( frame_buffer.GetWidth() <= current_x )
					{
						std::cout << r2::linefeed;
						current_x = 0;
					}

					std::cout << v;

					++current_x;
				}
			}
			std::cout << r2::linefeed;

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}