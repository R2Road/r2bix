#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace flickering_research
{
	class OneByOne : public r2::iTest, public r2::SingleTon<OneByOne>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class LineByLine : public r2::iTest, public r2::SingleTon<LineByLine>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PageByPage : public r2::iTest, public r2::SingleTon<PageByPage>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PageByPage_WithOut_CLS : public r2::iTest, public r2::SingleTon<PageByPage_WithOut_CLS>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}