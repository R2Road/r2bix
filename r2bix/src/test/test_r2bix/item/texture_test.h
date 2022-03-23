#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace texture_test
{
	class FillAll : public r2cm::iItem, public r2::SingleTon<FillAll>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Fill : public r2cm::iItem, public r2::SingleTon<Fill>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class InitWithChars_1 : public r2cm::iItem, public r2::SingleTon<InitWithChars_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_2 : public r2cm::iItem, public r2::SingleTon<InitWithChars_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_3 : public r2cm::iItem, public r2::SingleTon<InitWithChars_3>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_4 : public r2cm::iItem, public r2::SingleTon<InitWithChars_4>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}