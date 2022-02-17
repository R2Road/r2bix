#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

#include "render/r2render_Camera.h"
#include "render/r2render_Renderer.h"

namespace animation_test
{
	class Basic : public r2base::iTest, public r2base::SingleTon<Basic>
	{
	public:
		Basic();

		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;

	private:
		r2::Camera mCamera;
		r2::Renderer mRenderer;
	};
}