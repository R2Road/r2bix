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
				"#######################################################################"
				"#                                                                     #"
				"#      22222            00000            4  4             88888       #"
				"#     2     2          0     0          4   4            8     8      #"
				"#       2222           0     0          4   4             88888       #"
				"#     22               0     0          4444444          8     8      #"
				"#     2222222           00000               4             88888       #"
				"#                                                                     #"
				"#######################################################################"
			) ) );
			mTextureFrameContainer.emplace(
				"title_image"
				, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
			);
		}
	}
}