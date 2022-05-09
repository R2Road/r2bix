#pragma once

#include "r2cm/r2cm_Singleton.h"
#include "r2bix/r2base_TextureTableBase.h"

class TextureTable4Test : public r2base::TextureTableBase, public r2cm::SingleTon<TextureTable4Test>
{
public:
	void Load() override;
};