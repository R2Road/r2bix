#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace texture_table_test
{
	class TextureTable_1 : public r2cm::iItem, public r2::SingleTon<TextureTable_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureTable_2 : public r2cm::iItem, public r2::SingleTon<TextureTable_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureTable_3 : public r2cm::iItem, public r2::SingleTon<TextureTable_3>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}