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
			auto result = mTextureContainer.emplace( "companyscene_image", TextureValueT( new ( std::nothrow ) r2render::Texture(
				50, 10,
				//		"1         2         3         4         5"
				//		"01234567890123456789012345678901234567890123456789"
				/* 0 */	"ttttttttttttttttttttttttttt                      |"
				/* 1 */	"t   d   tt   d   tt   d   t                      |"
				/* 2 */	"t ddddd tt ddddd tt  ddd  t                      |"
				/* 3 */	"t d d d tt d d  dtt  ddd  t                      |"
				/* 4 */	"t d d d tt d d  dtt   dd  t                      |"
				/* 5 */	"t ddddd ttd ddd dtt dddd  t                      |"
				/* 6 */	"t  d d  tt  dd   tt d   d t                      |"
				/* 7 */	"t  d d  tt d  d  ttd    d t                      |"
				/* 8 */	"t  d d  tt d   d ttd     dt                      |"
				/* 9 */	"ttttttttttttttttttttttttttt                      |"
			) ) );
			mTextureFrameContainer.emplace(
				"texture_001"
				, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
			);

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"dguy_walk_1"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 1, 6, 7 ) );

				frame_result = mTextureFrameContainer.emplace(
					"dguy_walk_2"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 10, 1, 6, 7 ) );

				frame_result = mTextureFrameContainer.emplace(
					"dguy_walk_3"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 19, 1, 6, 7 ) );
			}
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