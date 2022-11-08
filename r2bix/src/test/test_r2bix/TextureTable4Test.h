#pragma once

#include "r2cm/r2cm_Singleton.h"
#include "r2bix/r2bix_table_TextureTableBase.h"

class TextureTable4Test : public r2bix_table::TextureTableBase, public r2cm::SingleTon<TextureTable4Test>
{
public:
	void Load() override;
};