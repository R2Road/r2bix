#include "pch.h"
#include "texture_frame_test.h"

#include "base/r2base_eTestEndAction.h"
#include "base/r2base_Inspector.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace texture_frame_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::Texture texture( 7,
				"1111111"
				"1222222"
				"1233333"
				"1234444"
				"1234555"
				"1234566"
				"1234567"
			);

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture texture( 7, ... )" << r2::linefeed;

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

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc VisibleRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Rect";
		};
	}
	r2base::iTest::DoFunc VisibleRect::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::Texture texture( 7,
				"1111111"
				"1222222"
				"1233333"
				"1234444"
				"1234555"
				"1234566"
				"1234567"
			);
			r2render::TextureFrame texture_frame( &texture );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 7, ... )" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::TextureFrame texture_frame( &texture );" << r2::linefeed2;
			}

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

			{
				auto rect = texture_frame.GetVisibleRect();
				rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );
				rect.SetSize( rect.GetSize().GetWidth() - 4, rect.GetSize().GetHeight() - 2 );
				texture_frame.SetVisibleRect( rect );

				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "auto rect = texture_frame.GetVisibleRect();" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetSize( rect.GetSize().GetWidth() - 4, rect.GetSize().GetHeight() - 2 );" << r2::linefeed;
				std::cout << r2::tab2 << "texture_frame.SetVisibleRect( rect );" << r2::linefeed2;

				std::cout << r2::tab2 << "rect :"
					<< " " << rect.GetMinX()
					<< " " << rect.GetMinY()
					<< " " << rect.GetMaxX()
					<< " " << rect.GetMaxY()
					<< r2::linefeed2;

				EXPECT_EQ( texture.Get( texture_frame.GetVisibleRect().GetMinX(), texture_frame.GetVisibleRect().GetMinY() ), texture_frame.Get( 0, 0 ) );
				std::cout << r2::linefeed2;

				std::cout << r2::tab << "+ View Texture Frame with TextureFrame::SetVisibleRect" << r2::linefeed2;

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

			return r2base::eTestEndAction::Pause;
		};
	}
}