#pragma once

#include "test/r2test_iItem.h"
#include "base/r2base_Singleton.h"

namespace camera_test
{
	class CameraPosition : public r2test::iItem, public r2base::SingleTon<CameraPosition>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraRect : public r2test::iItem, public r2base::SingleTon<CameraRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove : public r2test::iItem, public r2base::SingleTon<CameraMove>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}