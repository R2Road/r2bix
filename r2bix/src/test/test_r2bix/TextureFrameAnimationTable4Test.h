#pragma once

#include "r2_SingletonWithStaticVariable.h"
#include "r2bix_table_TextureFrameAnimationTableBase.h"

class TextureFrameAnimationTable4Test : public r2bix_table::TextureFrameAnimationTableBase, public r2::SingletonWithStaticVariable<TextureFrameAnimationTable4Test>
{
public:
	void Load() override;
};