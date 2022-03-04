#include "pch.h"
#include "texture_frame_test.h"

#include "test/r2test_eTestEndAction.h"
#include "test/r2test_Inspector.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

#include "p2048/p2048table_TextureTable.h"

namespace
{
	const r2render::Texture& GetDummyTexture()
	{
		static const r2render::Texture texture( 7,
			"1111111"
			"1222222"
			"1233333"
			"1234444"
			"1234555"
			"1234566"
			"1234567"
		);

		return texture;
	}
}

namespace texture_frame_test
{
	r2test::iItem::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Basic";
		};
	}
	r2test::iItem::DoFunc Basic::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::Texture& texture = GetDummyTexture();

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture& texture = GetDummyTexture();" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View Texture" << r2::linefeed2;

				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			r2render::TextureFrame texture_frame( &texture );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::TextureFrame texture_frame( &texture );" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << texture_frame.GetMinX()
					<< " " << texture_frame.GetMinY()
					<< " " << texture_frame.GetMaxX()
					<< " " << texture_frame.GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( texture.Get( 0, 0 ), texture_frame.Get( 0, 0 ) );
				EXPECT_EQ( '1', texture_frame.Get( 0, 0 ) );

				EXPECT_EQ( texture.Get( 6, 6 ), texture_frame.Get( 6, 6 ) );
				EXPECT_EQ( '7', texture_frame.Get( 6, 6 ) );

			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View Texture Frame" << r2::linefeed2;

				for( int y = 0; y < texture_frame.GetHeight(); ++y )
				{
					for( int x = 0; x < texture_frame.GetWidth(); ++x )
					{
						std::cout << texture_frame.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc VisibleRect_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 1";
		};
	}
	r2test::iItem::DoFunc VisibleRect_1::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::Texture& texture = GetDummyTexture();
			r2render::TextureFrame texture_frame( &texture );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture& texture = GetDummyTexture();" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::TextureFrame texture_frame( &texture );" << r2::linefeed2;

				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				texture_frame.SetVisibleRect( { 2, 1, 3, 5 } );

				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "texture_frame.SetVisibleRect( { 2, 1, 3, 5 } );" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << texture_frame.GetMinX()
					<< " " << texture_frame.GetMinY()
					<< " " << texture_frame.GetMaxX()
					<< " " << texture_frame.GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( texture.Get( texture_frame.GetMinX(), texture_frame.GetMinY() ), texture_frame.Get( 0, 0 ) );
				std::cout << r2::linefeed;

				for( int y = 0; y < texture_frame.GetHeight(); ++y )
				{
					for( int x = 0; x < texture_frame.GetWidth(); ++x )
					{
						std::cout << texture_frame.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc VisibleRect_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 2";
		};
	}
	r2test::iItem::DoFunc VisibleRect_2::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::Texture& texture = GetDummyTexture();
			r2render::TextureFrame texture_frame( &texture );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture& texture = GetDummyTexture();" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::TextureFrame texture_frame( &texture );" << r2::linefeed2;

				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				texture_frame.SetVisibleRect( { -3, -3, 5, 5 } );

				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "texture_frame.SetVisibleRect( { -3, -3, 5, 5 } );" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << texture_frame.GetMinX()
					<< " " << texture_frame.GetMinY()
					<< " " << texture_frame.GetMaxX()
					<< " " << texture_frame.GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( '1', texture_frame.Get( 0, 0 ) );
				std::cout << r2::linefeed;

				for( int y = 0; y < texture_frame.GetHeight(); ++y )
				{
					for( int x = 0; x < texture_frame.GetWidth(); ++x )
					{
						std::cout << texture_frame.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				texture_frame.SetVisibleRect( { 3, 3, 5, 5 } );

				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "texture_frame.SetVisibleRect( { 3, 3, 5, 5 } );" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << texture_frame.GetMinX()
					<< " " << texture_frame.GetMinY()
					<< " " << texture_frame.GetMaxX()
					<< " " << texture_frame.GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( '4', texture_frame.Get( 0, 0 ) );
				std::cout << r2::linefeed;

				for( int y = 0; y < texture_frame.GetHeight(); ++y )
				{
					for( int x = 0; x < texture_frame.GetWidth(); ++x )
					{
						std::cout << texture_frame.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc VisibleRect_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 3";
		};
	}
	r2test::iItem::DoFunc VisibleRect_3::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::TextureFrame* const texture_frame = p2048table::TextureTable::GetInstance().GetTitleTexture();

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::TextureFrame* const texture_frame = p2048table::TextureTable::GetInstance().GetTitleTexture();" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << texture_frame->GetMinX()
					<< " " << texture_frame->GetMinY()
					<< " " << texture_frame->GetMaxX()
					<< " " << texture_frame->GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( '8', texture_frame->Get( 62, 6 ) );
				std::cout << r2::linefeed;

				for( int y = 0; y < texture_frame->GetHeight(); ++y )
				{
					for( int x = 0; x < texture_frame->GetWidth(); ++x )
					{
						std::cout << texture_frame->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2test::eTestEndAction::Pause;
		};
	}
}