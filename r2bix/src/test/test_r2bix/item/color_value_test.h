#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace color_value_test
{
	class Basic : public r2cm::iItem, public r2cm::SingleTon<Basic>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class ColorMaskOption_Generate : public r2cm::iItem, public r2cm::SingleTon<ColorMaskOption_Generate>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class ColorMaskOption_On_Off : public r2cm::iItem, public r2cm::SingleTon<ColorMaskOption_On_Off>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class ColorMaskOption_Mask : public r2cm::iItem, public r2cm::SingleTon<ColorMaskOption_Mask>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}