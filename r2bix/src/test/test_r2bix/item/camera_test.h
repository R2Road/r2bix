#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace camera_test
{
	class CameraPosition : public r2cm::iItem, public r2cm::SingleTon<CameraPosition>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CameraRect : public r2cm::iItem, public r2cm::SingleTon<CameraRect>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CameraMove : public r2cm::iItem, public r2cm::SingleTon<CameraMove>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}