#include "pch.h"
#include "p2048table_TextureTable.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace p2048table
{
	TextureTable::TextureTable() : mTextureContainer()
	{}

	void TextureTable::Load()
	{
		mTextureContainer.emplace( "title_image", ValueT( new ( std::nothrow ) r2render::Texture(
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
	}

	r2render::TextureFrame* const TextureTable::GetTitleTexture() const
	{
		static r2render::Texture texture( 71, 9,
			"#######################################################################"
			"#                                                                     #"
			"#      22222            00000            4  4             88888       #"
			"#     2     2          0     0          4   4            8     8      #"
			"#       2222           0     0          4   4             88888       #"
			"#     22               0     0          4444444          8     8      #"
			"#     2222222           00000               4             88888       #"
			"#                                                                     #"
			"#######################################################################"
		);
		static r2render::TextureFrame texture_frame( &texture );

		return &texture_frame;
	}
}