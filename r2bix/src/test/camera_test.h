#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

#include "render/r2_Camera.h"
#include "render/r2_Renderer.h"

namespace camera_test
{
	class CameraRect : public r2base::iTest, public r2base::SingleTon<CameraRect>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove1 : public r2base::iTest, public r2base::SingleTon<CameraMove1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class CameraMove2 : public r2base::iTest, public r2base::SingleTon<CameraMove2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}