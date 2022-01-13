#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace visible_resource_research
{
	class DrawWithPosition : public r2::iTest, public r2::SingleTon<DrawWithPosition>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}