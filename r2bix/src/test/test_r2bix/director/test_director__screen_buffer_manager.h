#pragma once

#include "r2tm/r2tm_iItem.h"

namespace test_director__screen_buffer_manager
{
	class Swap : public r2tm::iItem
	{
	public:
		r2tm::TitleFunctionT GetTitleFunction() const override;
		r2tm::DoFunctionT GetDoFunction() const override;
	};
}