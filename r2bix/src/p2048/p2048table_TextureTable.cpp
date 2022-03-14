#include "pch.h"
#include "p2048table_TextureTable.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace p2048table
{
	void TextureTable::Load()
	{
		if( !mTextureContainer.empty() )
		{
			return;
		}

		{
			auto result = mTextureContainer.emplace( "title_image", TextureValueT( new ( std::nothrow ) r2render::Texture(
				71, 9,
				//		"1         2         3         4         5         6         7         "
				//		"0123456789012345678901234567890123456789012345678901234567890123456789"
				/* 0 */ "#######################################################################"
				/* 1 */ "#                                                                     #"
				/* 2 */ "#      22222            00000            4  4             88888       #"
				/* 3 */ "#     2     2          0     0          4   4            8     8      #"
				/* 4 */ "#       2222           0     0          4   4             88888       #"
				/* 5 */ "#     22               0     0          4444444          8     8      #"
				/* 6 */ "#     2222222           00000               4             88888       #"
				/* 7 */ "#                                                                     #"
				/* 8 */ "#######################################################################"
			) ) );
			mTextureFrameContainer.emplace(
				"title_image"
				, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
			);
		}
	}
}