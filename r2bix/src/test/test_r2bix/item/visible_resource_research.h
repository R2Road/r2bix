#pragma once

#include "r2cm/r2cm_iItem.h"

namespace visible_resource_research
{
	class DrawWithPosition : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};
}