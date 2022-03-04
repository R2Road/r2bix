#include "pch.h"
#include "texture_test.h"

#include "test/r2test_eTestEndAction.h"

#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

namespace texture_test
{
	r2test::iItem::TitleFunc FillAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Fill All";
		};
	}
	r2test::iItem::DoFunc FillAll::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
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

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc Fill::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Fill";
		};
	}
	r2test::iItem::DoFunc Fill::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
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

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 1";
		};
	}
	r2test::iItem::DoFunc InitWithChars_1::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
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

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 2";
		};
	}
	r2test::iItem::DoFunc InitWithChars_2::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				const r2render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggghh" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2render::Texture texture( 5, \"aaaaaaabbbbbbbcccddddeeeeeeeefffggghh\" );" << r2::linefeed;

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

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc InitWithChars_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 3";
		};
	}
	r2test::iItem::DoFunc InitWithChars_3::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
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

			return r2test::eTestEndAction::Pause;
		};
	}



	r2test::iItem::TitleFunc InitWithChars_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Init With Chars 4";
		};
	}
	r2test::iItem::DoFunc InitWithChars_4::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
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

			return r2test::eTestEndAction::Pause;
		};
	}
}