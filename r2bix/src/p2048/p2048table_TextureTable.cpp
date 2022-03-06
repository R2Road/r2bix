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

	r2render::TextureFrame* const TextureTable::GetTextureFrame( const char* const key_name ) const
	{
		auto itr = mTextureFrameContainer.find( key_name );
		if( mTextureFrameContainer.end() != itr )
		{
			return itr->second.get();
		}

		static r2render::Texture temp_texture( "Invalid Texture" );
		static r2render::TextureFrame temp_texture_frame( &temp_texture );
		return &temp_texture_frame;
	}
}