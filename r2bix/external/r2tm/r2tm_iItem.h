#pragma once

#include "r2tm_MenuConstant.h"

namespace r2tm
{
	class iItem
	{
	public:
		virtual ~iItem() {}

		virtual r2tm::TitleFunctionT GetTitleFunction() const = 0;
		virtual r2tm::DoFunctionT GetDoFunction() const = 0;
	};
}