#pragma once

#include "r2/r2_Singleton.h"
#include "r2bix/r2base_TextureFrameAnimationTableBase.h"

class TextureFrameAnimationTable4Test : public r2base::TextureFrameAnimationTableBase, public r2::SingleTon<TextureFrameAnimationTable4Test>
{
public:
	void Load() override;
};