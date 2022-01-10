#include "pch.h"
#include "framebuffer_test.h"

#include "base/r2_eTestResult.h"

namespace framebuffer_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer - Basic";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}