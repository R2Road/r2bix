#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

namespace texture_frame_test
{
	class TextureFrameTest : public r2base::iTest, public r2base::SingleTon<TextureFrameTest>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}