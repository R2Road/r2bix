#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

namespace texture_frame_test
{
	class Basic : public r2test::iTest, public r2base::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect_1 : public r2test::iTest, public r2base::SingleTon<VisibleRect_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect_2 : public r2test::iTest, public r2base::SingleTon<VisibleRect_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}