#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace node_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Label : public r2cm::iItem, public r2::SingleTon<Label>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}