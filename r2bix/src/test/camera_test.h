#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

namespace camera_test
{
	class CameraRect : public r2base::iTest, public r2base::SingleTon<CameraRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}