#pragma once

#include "r2_singleton_with_static_method.hpp"
#include "r2bix_table_TextureFrameAnimationTableBase.h"

class TextureFrameAnimationTable4Test : public r2bix_table::TextureFrameAnimationTableBase, public r2::SingletonWithStaticMethod<TextureFrameAnimationTable4Test>
{
public:
	void Load() override;
};