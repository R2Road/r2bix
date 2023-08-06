#include "TextureTable4Test.h"

#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"

void TextureTable4Test::Load()
{
	if( !mTextureContainer.empty() )
	{
		return;
	}

	{
		auto result = mTextureContainer.emplace( "test_texture_001", TextureValueT( new ( std::nothrow ) r2bix_render::Texture(
			50, 10,
			//		"1         2         3         4         5"
			//		"01234567890123456789012345678901234567890123456789"
			/* 0 */	"ttttttttttttttttttttttttttt                      |"
			/* 1 */	"t***d***tt***d***tt***d***t                      |"
			/* 2 */	"t*ddddd*tt*ddddd*tt**ddd**t                      |"
			/* 3 */	"t*d*d*d*tt*d*d**dtt**ddd**t                      |"
			/* 4 */	"t*d*d*d*tt*d*d**dtt***dd**t                      |"
			/* 5 */	"t*ddddd*ttd*ddd*dtt*dddd**t                      |"
			/* 6 */	"t**d*d**tt**dd***tt*d***d*t                      |"
			/* 7 */	"t**d*d**tt*d**d**ttd****d*t                      |"
			/* 8 */	"t**d*d**tt*d***d*ttd*****dt                      |"
			/* 9 */	"ttttttttttttttttttttttttttt                      |"
		) ) );
		mTextureFrameContainer.emplace(
			"texture_001"
			, TextureFrameValueT( new ( std::nothrow ) r2bix_render::TextureFrame( result.first->second.get() ) )
		);

		{
			auto frame_result = mTextureFrameContainer.emplace(
				"dguy_walk_1"
				, TextureFrameValueT( new ( std::nothrow ) r2bix_render::TextureFrame( result.first->second.get() ) )
			);
			frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 1, 6, 7 ) );

			frame_result = mTextureFrameContainer.emplace(
				"dguy_walk_2"
				, TextureFrameValueT( new ( std::nothrow ) r2bix_render::TextureFrame( result.first->second.get() ) )
			);
			frame_result.first->second->SetVisibleRect( r2::RectInt( 10, 1, 6, 7 ) );

			frame_result = mTextureFrameContainer.emplace(
				"dguy_walk_3"
				, TextureFrameValueT( new ( std::nothrow ) r2bix_render::TextureFrame( result.first->second.get() ) )
			);
			frame_result.first->second->SetVisibleRect( r2::RectInt( 19, 1, 6, 7 ) );
		}
	}
}