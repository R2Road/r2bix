#pragma once

#include "test/r2test_iItem.h"
#include "base/r2base_Singleton.h"

namespace window_input_test
{
	class TestKeyboardInputCollector : public r2test::iItem, public r2base::SingleTon<TestKeyboardInputCollector>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}