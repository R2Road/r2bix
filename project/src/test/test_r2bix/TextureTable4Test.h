#pragma once

#include "r2_singleton_with_static_method.hpp"
#include "r2bix_table_TextureTableBase.h"

class TextureTable4Test : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticMethod<TextureTable4Test>
{
public:
	void Load() override;
};