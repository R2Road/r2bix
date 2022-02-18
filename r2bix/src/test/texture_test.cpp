#include "pch.h"
#include "texture_test.h"

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace texture_test
{
	r2base::iTest::TitleFunc FillAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Fill All";
		};
	}
	r2base::iTest::DoFunc FillAll::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::Texture texture( 30, 20, '0' );

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture texture( 30, 20, '0' );" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc Fill::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Fill";
		};
	}
	r2base::iTest::DoFunc Fill::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			r2render::Texture texture( 30, 20 );
			texture.Fill( 0, 0, '0' );
			texture.Fill( texture.GetXEnd(), 0, '0' );
			texture.Fill( texture.GetXEnd(), texture.GetYEnd(), '0' );
			texture.Fill( 0, texture.GetYEnd(), '0' );

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture texture( 30, 20 );" << r2::linefeed;
			std::cout << r2::tab2 << "texture.Fill( 0, 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "texture.Fill( texture.GetXEnd(), 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "texture.Fill( texture.GetXEnd(), texture.GetYEnd(), '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "texture.Fill( 0, texture.GetYEnd(), '0' );" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 1";
		};
	}
	r2base::iTest::DoFunc InitWithChars_1::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;
			
			std::size_t x = 0;

			{
				const r2render::Texture texture( "Init With Chars" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( \"Init With Chars\" );" << r2::linefeed;

				std::cout << r2::split;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 2";
		};
	}
	r2base::iTest::DoFunc InitWithChars_2::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				const r2render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 5, \"aaaaaaabbbbbbbcccddddeeeeeeeefffggg\" );" << r2::linefeed;

				std::cout << r2::split;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc InitWithChars_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 3";
		};
	}
	r2base::iTest::DoFunc InitWithChars_3::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				const r2render::Texture texture( 8, 8, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 8, 8, '#', \"aaaaaaabbbbbbbcccddddeeeeeeeefffggg\" );" << r2::linefeed3;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				const r2render::Texture texture( 3, 3, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 3, 3, '#', \"aaaaaaabbbbbbbcccddddeeeeeeeefffggg\" );" << r2::linefeed3;

				std::cout << r2::tab << "+ View : Overflow Test" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc InitWithChars_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 4";
		};
	}
	r2base::iTest::DoFunc InitWithChars_4::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				const r2render::Texture texture( 7, 7, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 7, 7, \"aaaaaaabbbbbbbcccddddeeeeeeeefffggg\" );" << r2::linefeed3;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++x;
					if( texture.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc TextureFrameTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame";
		};
	}
	r2base::iTest::DoFunc TextureFrameTest::GetDoFunction()
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

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture texture( 5, ... )" << r2::linefeed;
			std::cout << r2::tab2 << "r2render::TextureFrame texture_frame( &texture );" << r2::linefeed;

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
				std::cout << r2::tab << "+ View With Rect" << r2::linefeed2;

				auto rect = texture.GetVisibleRect();
				rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );
				rect.SetSize( rect.GetSize().GetWidth() - 2, rect.GetSize().GetHeight() - 1 );
				texture.SetVisibleRect( rect );

				std::cout << r2::tab2 << "auto rect = texture.GetVisibleRect();" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetSize( rect.GetSize().GetWidth() - 2, rect.GetSize().GetHeight() - 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "texture.SetVisibleRect( rect );" << r2::linefeed2;

				for( int y = texture.GetVisibleRect().GetMinY(); y < texture.GetVisibleRect().GetMaxY(); ++y )
				{
					for( int x = texture.GetVisibleRect().GetMinX(); x < texture.GetVisibleRect().GetMaxX(); ++x )
					{
						std::cout << texture.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}