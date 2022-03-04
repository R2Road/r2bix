#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

#include "render/r2render_Renderer.h"
#include "render/r2render_Texture.h"

namespace renderer_test
{
	class TestRenderable : public r2cm::iItem, public r2::SingleTon<TestRenderable>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};



	class TestRenderer : public r2cm::iItem, public r2::SingleTon<TestRenderer>
	{
	public:
		TestRenderer();

	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;

	private:
		r2render::Renderer mRenderer;
	};



	class CameraMove1 : public r2cm::iItem, public r2::SingleTon<CameraMove1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove2 : public r2cm::iItem, public r2::SingleTon<CameraMove2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}