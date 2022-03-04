#pragma once

#include "test/r2test_iItem.h"
#include "base/r2base_Singleton.h"

namespace framebuffer_test
{
	class Basic : public r2cm::iItem, public r2base::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}