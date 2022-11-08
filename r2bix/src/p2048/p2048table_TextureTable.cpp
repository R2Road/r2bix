#include "p2048table_TextureTable.h"

#include "r2bix/r2bix_render_Texture.h"
#include "r2bix/r2bix_render_TextureFrame.h"

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
				50,
				//		"          1         2         3         4         "
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
				71,
				//		"          1         2         3         4         5         6         7"
				//		"01234567890123456789012345678901234567890123456789012345678901234567890"
				/* 0 */ "#######################################################################"
				/* 1 */ "#                                                                     #"
				/* 2 */ "#                                                                     #"
				/* 3 */ "#                                                                     #"
				/* 4 */ "#                                                                     #"
				/* 5 */ "#                                                                     #"
				/* 6 */ "#                                                                     #"
				/* 7 */ "#                                                                     #"
				/* 8 */ "#######################################################################"
				/* 9 */ "                                                                       "
				/* 0 */ "  22222   00000   4  4    88888                                        "
				/* 1 */ " 2     2 0     0 4   4   8     8                                       "
				/* 2 */ "   2222  0     0 4   4    88888                                        "
				/* 3 */ " 22      0     0 4444444 8     8                                       "
				/* 4 */ " 2222222  00000      4    88888                                        "
				/* 5 */ "                                                                       "
			) ) );

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"title_frame"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 0, 0, 70, 8 ) );

				frame_result = mTextureFrameContainer.emplace(
					"title_2"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 1, 10, 6, 4 ) );

				frame_result = mTextureFrameContainer.emplace(
					"title_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 9, 10, 6, 4 ) );

				frame_result = mTextureFrameContainer.emplace(
					"title_4"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 17, 10, 6, 4 ) );

				frame_result = mTextureFrameContainer.emplace(
					"title_8"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 25, 10, 6, 4 ) );
			}
		}

		{
			auto result = mTextureContainer.emplace( "p2048_image", TextureValueT( new ( std::nothrow ) r2render::Texture(
				60,
				//		"          1         2         3         4         5         6         7"
				//		"01234567890123456789012345678901234567890123456789012345678901234567890"
				/* 0 */ "                                                            "
				/* 1 */ "   ###    ###    # #   #####    ###   #   #  #####   ###    "
				/* 2 */ "  #      #   #  # # #  #       #   #  #   #  #      #   #   "
				/* 3 */ "  # ###  ### #  # # #  #####   #   #  #   #  #####  ####    "
				/* 4 */ "  #   #  #   #  # # #  #       #   #   # #   #      #   #   "
				/* 5 */ "   ###   #   #  # # #  # ###    ###     #    # ###  #   #   "
				/* 6 */ "                                                            "
				/* 7 */ " 22222    00000    4  4     88888                           "
				/* 8 */ "2     2  0     0  4   4    8     8  M                       "
				/* 9 */ "  2222   0     0  4   4     88888   I                       "
				/* 0 */ "22       0     0  4444444  8     8  N                       "
				/* 1 */ "2222222   00000       4     88888   I                       "
				/* 2 */ "                                                            "
				/* 3 */ "[   ESC   ] Exit                                            "
				/* 4 */ "[ W,A,S,D ] Move Number                                     "
				/* 5 */ "[    R    ] Restart                                         "
				/* 6 */ "[   TAB   ] History                                         "
				/* 7 */ "                                                            "
				/* 8 */ "  #   #   ###   #   #    #   #   #####  #   #   B           "
				/* 9 */ "  #   #  #   #  #   #    # # #     #    ##  #   B           "
				/* 0 */ "   # #   #   #  #   #    # # #     #    # # #   B           "
				/* 1 */ "    #    #   #  #   #    # # #     #    #  ##   B           "
				/* 2 */ "    #     ###    ###      # #    #####  #   #   B           "
				/* 3 */ "                                                            "
			) ) );

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"keyinfo_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 0, 13, 22, 3 ) );
			}

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"game_over_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( r2::RectInt( 0, 0, 58, 6 ) );
			}

			{
				auto frame_result = mTextureFrameContainer.emplace(
					"you_win_0"
					, TextureFrameValueT( new ( std::nothrow ) r2render::TextureFrame( result.first->second.get() ) )
				);
				frame_result.first->second->SetVisibleRect( 0, 17, 47, 22 );
			}
		}
	}
}