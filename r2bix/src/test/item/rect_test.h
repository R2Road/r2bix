#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

namespace rect_test
{
	class Basic : public r2test::iTest, public r2base::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}