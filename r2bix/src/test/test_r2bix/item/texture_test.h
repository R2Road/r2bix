#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace texture_test
{
	class FillCharacterAll : public r2cm::iItem, public r2cm::SingleTon<FillCharacterAll>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class FillCharacter : public r2cm::iItem, public r2cm::SingleTon<FillCharacter>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class FillColorAll : public r2cm::iItem, public r2cm::SingleTon<FillColorAll>
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