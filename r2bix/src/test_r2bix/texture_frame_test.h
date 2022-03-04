#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

namespace texture_frame_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect_1 : public r2cm::iItem, public r2::SingleTon<VisibleRect_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect_2 : public r2cm::iItem, public r2::SingleTon<VisibleRect_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class VisibleRect_3 : public r2cm::iItem, public r2::SingleTon<VisibleRect_3>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}