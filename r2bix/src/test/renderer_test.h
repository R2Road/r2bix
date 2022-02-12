#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

#include "renderer/r2_Renderer.h"
#include "renderer/r2_VisibleResource.h"

namespace renderer_test
{
	class TestRenderable : public r2base::iTest, public r2base::SingleTon<TestRenderable>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};



	class TestRenderer : public r2base::iTest, public r2base::SingleTon<TestRenderer>
	{
	public:
		TestRenderer();

	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;

	private:
		r2::Renderer mRenderer;
	};
}