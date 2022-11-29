#pragma once

#include "r2/r2_SingletonWithStaticVariable.h"
#include "r2bix/r2bix_table_TextureFrameAnimationTableBase.h"

class TextureFrameAnimationTable4Test : public r2bix_table::TextureFrameAnimationTableBase, public r2::SingletonWithStaticVariable<TextureFrameAnimationTable4Test>
{
public:
	void Load() override;
};