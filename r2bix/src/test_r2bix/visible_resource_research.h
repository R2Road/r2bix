#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace visible_resource_research
{
	class DrawWithPosition : public r2cm::iItem, public r2::SingleTon<DrawWithPosition>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}