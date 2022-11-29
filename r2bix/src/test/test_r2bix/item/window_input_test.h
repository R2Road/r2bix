#pragma once

#include "r2cm/r2cm_iItem.h"

namespace window_input_test
{
	class KeyStatus : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};

	class TestKeyboardInputCollector : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};
}