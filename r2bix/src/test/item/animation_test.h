#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

#include "render/r2render_Camera.h"
#include "render/r2render_Renderer.h"

namespace animation_test
{
	class Basic : public r2test::iTest_Deprecated, public r2base::SingleTon<Basic>
	{
	public:
		Basic();

		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;

	private:
		r2render::Camera mCamera;
		r2render::Renderer mRenderer;
	};
}