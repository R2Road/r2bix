#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

namespace window_input_test
{
	class TestKeyboardInputCollector : public r2cm::iItem, public r2::SingleTon<TestKeyboardInputCollector>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}