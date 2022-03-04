#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

namespace camera_test
{
	class CameraPosition : public r2cm::iItem, public r2::SingleTon<CameraPosition>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraRect : public r2cm::iItem, public r2::SingleTon<CameraRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove : public r2cm::iItem, public r2::SingleTon<CameraMove>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}