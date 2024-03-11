#pragma once

#include "r2_SingletonWithStaticFunction.h"
#include "r2bix_table_TextureTableBase.h"

class TextureTable4Test : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticFunction<TextureTable4Test>
{
public:
	void Load() override;
};