#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace camera_test
{
	class Declaration : public r2cm::iItem, public r2cm::SingleTon<Declaration>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CameraPosition : public r2cm::iItem, public r2cm::SingleTon<CameraPosition>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CameraRect : public r2cm::iItem, public r2cm::SingleTon<CameraRect>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CameraMove : public r2cm::iItem, public r2cm::SingleTon<CameraMove>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}