#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace camera_test
{
	class CameraPosition : public r2cm::iItem, public r2::SingleTon<CameraPosition>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraRect : public r2cm::iItem, public r2::SingleTon<CameraRect>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove : public r2cm::iItem, public r2::SingleTon<CameraMove>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}