#include "pch.h"
#include "p2048minitable_TextureTable.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace p2048minitable
{
	void TextureTable::Load()
	{
		if( !mTextureContainer.empty() )
		{
			return;
		}

		{
			auto result = mTextureContainer.emplace( "p2048mini_image", TextureValueT( new ( std::nothrow ) r2render::Texture(
				71,
				//		"          1         2         3         4         5         6         7"
				//		"01234567890123456789012345678901234567890123456789012345678901234567890"
				/* 0 */ "###########                                                            "
				/* 1 */ "#        ##   ###    ###    # #   #####     ###   #   #  #####   ###   "
				/* 2 */ "#        ##  #      #   #  # # #  #        #   #  #   #  #      #   #  "
				/* 3 */ "#        ##  # ###  ### #  # # #  #####    #   #  #   #  #####  ####   "
				/* 4 */ "###########  #   #  #   #  # # #  #        #   #   # #   #      #   #  "
				/* 5 */ "              ###   #   #  # # #  # ###     ###     #    # ###  #   #  "
				/* 6 */ "                                                                       "
				/* 7 */ "  22222    00000    4  4     88888                                     "
				/* 8 */ " 2     2  0     0  4   4    8     8                                    "
				/* 9 */ "   2222   0     0  4   4     88888                                     "
				/* 0 */ " 22       0     0  4444444  8     8                                    "
				/* 1 */ " 2222222   00000       4     88888                                     "
				/* 2 */ "                                                                       "
				/* 3 */ "[ESC] Exit                                                             "
				/* 4 */ "[W,A,S,D] Move Number                                                  "
				/* 5 */ "[R] Restart                                                            "
			) ) );

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"number_frame_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 1, 7, 2 ) );
			}

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"title_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 7, 33, 4 ) );
			}

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"keyinfo_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 0, 13, 20, 2 ) );
			}

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"game_over_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 11, 0, 59, 6 ) );
			}
		}
	}
}