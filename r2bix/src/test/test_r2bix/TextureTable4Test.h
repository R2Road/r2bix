#pragma once

#include "r2_SingletonWithStaticVariable.h"
#include "r2bix_table_TextureTableBase.h"

class TextureTable4Test : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticVariable<TextureTable4Test>
{
public:
	void Load() override;
};