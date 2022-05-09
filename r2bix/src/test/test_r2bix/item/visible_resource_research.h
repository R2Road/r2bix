#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace visible_resource_research
{
	class DrawWithPosition : public r2cm::iItem, public r2cm::SingleTon<DrawWithPosition>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}