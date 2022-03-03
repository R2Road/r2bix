#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

namespace flickering_research
{
	class OneByOne : public r2test::iTest, public r2base::SingleTon<OneByOne>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class OneByOne_WithOut_CLS : public r2test::iTest, public r2base::SingleTon<OneByOne_WithOut_CLS>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class LineByLine : public r2test::iTest, public r2base::SingleTon<LineByLine>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PageByPage : public r2test::iTest, public r2base::SingleTon<PageByPage>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PageByPage_WithOut_CLS_1 : public r2test::iTest, public r2base::SingleTon<PageByPage_WithOut_CLS_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class PageByPage_WithOut_CLS_2 : public r2test::iTest, public r2base::SingleTon<PageByPage_WithOut_CLS_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}