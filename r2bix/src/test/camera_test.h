#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

#include "renderer/r2_Camera.h"
#include "renderer/r2_Renderer.h"

namespace camera_test
{
	class CameraRect : public r2::iTest, public r2::SingleTon<CameraRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove1 : public r2::iTest, public r2::SingleTon<CameraMove1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove2 : public r2::iTest, public r2::SingleTon<CameraMove2>
	{
	public:
		CameraMove2();

	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;

	private:
		r2::Camera mCamera;
		r2::Renderer mRenderer;
	};
}