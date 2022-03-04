#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

namespace rect_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}