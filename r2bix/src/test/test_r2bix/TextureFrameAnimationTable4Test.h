#pragma once

#include "r2cm/r2cm_Singleton.h"
#include "r2bix/r2base_TextureFrameAnimationTableBase.h"

class TextureFrameAnimationTable4Test : public r2base::TextureFrameAnimationTableBase, public r2cm::SingleTon<TextureFrameAnimationTable4Test>
{
public:
	void Load() override;
};