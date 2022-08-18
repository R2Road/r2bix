#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace node_test
{
	class Basic : public r2cm::iItem, public r2cm::SingleTon<Basic>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Child_Count : public r2cm::iItem, public r2cm::SingleTon<Child_Count>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Child_Sequence : public r2cm::iItem, public r2cm::SingleTon<Child_Sequence>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Scene : public r2cm::iItem, public r2cm::SingleTon<Scene>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LabelS : public r2cm::iItem, public r2cm::SingleTon<LabelS>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LabelM : public r2cm::iItem, public r2cm::SingleTon<LabelM>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Sprite : public r2cm::iItem, public r2cm::SingleTon<Sprite>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class SpriteAnimation : public r2cm::iItem, public r2cm::SingleTon<SpriteAnimation>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CustomeTexture : public r2cm::iItem, public r2cm::SingleTon<CustomeTexture>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}