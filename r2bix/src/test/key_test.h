#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

namespace key_test
{
	class Basic : public r2base::iTest, public r2base::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}