#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace utility_test
{
	class StringSize : public r2cm::iItem, public r2cm::SingleTon<StringSize>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class StringDecomposition : public r2cm::iItem, public r2cm::SingleTon<StringDecomposition>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}