#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace window_input_test
{
	class KeyStatus : public r2cm::iItem, public r2cm::SingleTon<KeyStatus>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TestKeyboardInputCollector : public r2cm::iItem, public r2cm::SingleTon<TestKeyboardInputCollector>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}