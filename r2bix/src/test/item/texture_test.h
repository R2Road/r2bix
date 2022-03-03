#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

namespace texture_test
{
	class FillAll : public r2base::iTest, public r2base::SingleTon<FillAll>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class Fill : public r2base::iTest, public r2base::SingleTon<Fill>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class InitWithChars_1 : public r2base::iTest, public r2base::SingleTon<InitWithChars_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_2 : public r2base::iTest, public r2base::SingleTon<InitWithChars_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_3 : public r2base::iTest, public r2base::SingleTon<InitWithChars_3>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_4 : public r2base::iTest, public r2base::SingleTon<InitWithChars_4>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}