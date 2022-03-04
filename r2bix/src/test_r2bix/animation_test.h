#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

#include "render/r2render_Camera.h"
#include "render/r2render_Renderer.h"

namespace animation_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
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