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

			{
				r2::FrameBuffer frame_buffer( 5, 5 );
				frame_buffer.FillAll( 'c' );

				for( const auto v : frame_buffer )
				{
					std::cout << v;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc DrawAtOnce::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Draw At Once";
		};
	}
	r2::iTest::DoFunc DrawAtOnce::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				r2::FrameBuffer frame_buffer( 5, 5 );
				frame_buffer.FillAll( 'c' );

				std::cout << &( *frame_buffer.begin() );
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}