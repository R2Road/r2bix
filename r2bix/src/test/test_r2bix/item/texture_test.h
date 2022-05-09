#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace texture_test
{
	class FillAll : public r2cm::iItem, public r2cm::SingleTon<FillAll>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Fill : public r2cm::iItem, public r2cm::SingleTon<Fill>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class InitWithChars_1 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_2 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_3 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_3>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class InitWithChars_4 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_4>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}