#pragma once

#include "r2/r2_Singleton.h"
#include "r2bix/r2base_TextureTableBase.h"

class TextureTable4Test : public r2base::TextureTableBase, public r2::SingleTon<TextureTable4Test>
{
public:
	void Load() override;
};