#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace component_test
{
	class RenderTest : public r2cm::iItem, public r2::SingleTon<RenderTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureRenderComponentTest : public r2cm::iItem, public r2::SingleTon<TextureRenderComponentTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}