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

		{
			auto result = mTextureContainer.emplace( "test_texture_001", TextureValueT( new ( std::nothrow ) r2render::Texture(
				50, 10,
			//		"         1         2         3         4         5"
			//		"12345678901234567890123456789012345678901234567890"
			/* 1 */	"ttttttttt                                        |"
			/* 2 */	"t   d   t                                        |"
			/* 3 */	"t ddddd t                                        |"
			/* 4 */	"td  d  dt                                        |"
			/* 5 */	"td  d  dt                                        |"
			/* 6 */	"t  ddd  t                                        |"
			/* 7 */	"t d   d t                                        |"
			/* 8 */	"t d   d t                                        |"
			/* 9 */	"t d   d t                                        |"
			/* 0 */	"ttttttttt                                        |"
			) ) );
			mTextureFrameContainer.emplace(
				"texture_001"
				, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
			);

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"dguy"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 1, 7, 8 ) );
			}
		}
	}

	r2render::Texture* const TextureTable::GetTexture( const char* const key_name ) const
	{
		auto itr = mTextureContainer.find( key_name );
		if( mTextureContainer.end() != itr )
		{
			return itr->second.get();
		}

		static r2render::Texture temp_texture( "Invalid Texture" );
		return &temp_texture;
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