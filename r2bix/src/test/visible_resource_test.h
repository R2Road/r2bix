#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace visible_resource_test
{
	class FillAll : public r2::iTest, public r2::SingleTon<FillAll>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class Fill : public r2::iTest, public r2::SingleTon<Fill>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class InitWithChars_1 : public r2::iTest, public r2::SingleTon<InitWithChars_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_2 : public r2::iTest, public r2::SingleTon<InitWithChars_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_3 : public r2::iTest, public r2::SingleTon<InitWithChars_3>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_4 : public r2::iTest, public r2::SingleTon<InitWithChars_4>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect : public r2::iTest, public r2::SingleTon<VisibleRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}