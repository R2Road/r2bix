#pragma once

#include "test/r2test_iTest_Deprecated.h"
#include "base/r2base_Singleton.h"

namespace window_input_test
{
	class TestKeyboardInputCollector : public r2test::iTest_Deprecated, public r2base::SingleTon<TestKeyboardInputCollector>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}