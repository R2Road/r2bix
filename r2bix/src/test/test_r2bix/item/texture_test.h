#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace texture_test
{
	class FillCharacterAll : public r2cm::iItem, public r2cm::SingleTon<FillCharacterAll>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FillCharacter : public r2cm::iItem, public r2cm::SingleTon<FillCharacter>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FillColorAll : public r2cm::iItem, public r2cm::SingleTon<FillColorAll>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FillColor : public r2cm::iItem, public r2cm::SingleTon<FillColor>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FillColorWithMask : public r2cm::iItem, public r2cm::SingleTon<FillColorWithMask>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class BlendColor : public r2cm::iItem, public r2cm::SingleTon<BlendColor>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class FillCharacterDisuse : public r2cm::iItem, public r2cm::SingleTon<FillCharacterDisuse>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class InitWithChars_1 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class InitWithChars_3 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_3>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class InitWithChars_4 : public r2cm::iItem, public r2cm::SingleTon<InitWithChars_4>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}