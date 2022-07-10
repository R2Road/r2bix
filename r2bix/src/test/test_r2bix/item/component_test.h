#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace component_test
{
	class ComponentID : public r2cm::iItem, public r2cm::SingleTon<ComponentID>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Component_Add_Get : public r2cm::iItem, public r2cm::SingleTon<Component_Add_Get>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class TextureRenderComponentTest_1 : public r2cm::iItem, public r2cm::SingleTon<TextureRenderComponentTest_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class TextureRenderComponentTest_2 : public r2cm::iItem, public r2cm::SingleTon<TextureRenderComponentTest_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class TextureRenderComponentTest_3 : public r2cm::iItem, public r2cm::SingleTon<TextureRenderComponentTest_3>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CustomTextureComponentTest : public r2cm::iItem, public r2cm::SingleTon<CustomTextureComponentTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LabelSComponentTest : public r2cm::iItem, public r2cm::SingleTon<LabelSComponentTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LabelMComponentTest : public r2cm::iItem, public r2cm::SingleTon<LabelMComponentTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class TextureFrameRenderComponentTest_1 : public r2cm::iItem, public r2cm::SingleTon<TextureFrameRenderComponentTest_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class TextureFrameRenderComponentTest_2 : public r2cm::iItem, public r2cm::SingleTon<TextureFrameRenderComponentTest_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class TextureFrameAnimationComponentTest_1 : public r2cm::iItem, public r2cm::SingleTon<TextureFrameAnimationComponentTest_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
	class TextureFrameAnimationComponentTest_2 : public r2cm::iItem, public r2cm::SingleTon<TextureFrameAnimationComponentTest_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class ActionProcessComponentTest: public r2cm::iItem, public r2cm::SingleTon<ActionProcessComponentTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}