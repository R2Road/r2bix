#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace component_test
{
	class ComponentID : public r2cm::iItem, public r2::SingleTon<ComponentID>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Component_Add_Get : public r2cm::iItem, public r2::SingleTon<Component_Add_Get>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureRenderComponentTest_1 : public r2cm::iItem, public r2::SingleTon<TextureRenderComponentTest_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class TextureRenderComponentTest_2 : public r2cm::iItem, public r2::SingleTon<TextureRenderComponentTest_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class LabelComponentTest : public r2cm::iItem, public r2::SingleTon<LabelComponentTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureFrameRenderComponentTest : public r2cm::iItem, public r2::SingleTon<TextureFrameRenderComponentTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TextureFrameAnimationComponentTest : public r2cm::iItem, public r2::SingleTon<TextureFrameAnimationComponentTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}