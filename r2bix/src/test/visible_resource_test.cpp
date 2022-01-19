#include "pch.h"
#include "visible_resource_test.h"

#include <Windows.h>

#include "base/r2_eTestResult.h"

#include "renderer/r2_Camera.h"
#include "renderer/r2_iRenderable.h"
#include "renderer/r2_VisibleResource.h"

namespace visible_resource_test
{
	r2::iTest::TitleFunc FillAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Fill All";
		};
	}
	r2::iTest::DoFunc FillAll::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2::VisibleResource visible_resource( 30, 20, '0' );

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2::VisibleResource visible_resource( 30, 20, '0' );" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : visible_resource )
				{
					std::cout << element;

					++x;
					if( visible_resource.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc Fill::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Fill";
		};
	}
	r2::iTest::DoFunc Fill::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::VisibleResource vr( 30, 20 );
			vr.Fill( 0, 0, '0' );
			vr.Fill( vr.GetXEnd(), 0, '0' );
			vr.Fill( vr.GetXEnd(), vr.GetYEnd(), '0' );
			vr.Fill( 0, vr.GetYEnd(), '0' );

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2::VisibleResource vr( 30, 20 );" << r2::linefeed;
			std::cout << r2::tab2 << "vr.Fill( 0, 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "vr.Fill( vr.GetXEnd(), 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "vr.Fill( vr.GetXEnd(), vr.GetYEnd(), '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "vr.Fill( 0, vr.GetYEnd(), '0' );" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : vr )
				{
					std::cout << element;

					++x;
					if( vr.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Init With Chars 1";
		};
	}
	r2::iTest::DoFunc InitWithChars_1::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;
			
			std::size_t x = 0;

			{
				const r2::VisibleResource visible_resource( "Init With Chars" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::VisibleResource visible_resource( \"Init With Chars\" );" << r2::linefeed;

				std::cout << r2::split;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				for( const char element : visible_resource )
				{
					std::cout << element;

					++x;
					if( visible_resource.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Init With Chars 2";
		};
	}
	r2::iTest::DoFunc InitWithChars_2::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				const r2::VisibleResource visible_resource( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::VisibleResource visible_resource( 5, \"aaaaaaabbbbbbbcccddddeeeeeeeefffggg\" );" << r2::linefeed;

				std::cout << r2::split;

				std::cout << r2::tab << "+ View" << r2::linefeed2;

				std::size_t x = 0;
				for( const char element : visible_resource )
				{
					std::cout << element;

					++x;
					if( visible_resource.GetWidth() <= x )
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

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc VisibleRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Visible Rect";
		};
	}
	r2::iTest::DoFunc VisibleRect::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				r2::VisibleResource vr( 5, "aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg" );

				auto rect = vr.GetVisibleRect();
				rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );
				rect.SetSize( rect.GetSize().GetWidth() - 2, rect.GetSize().GetHeight() - 1 );
				vr.SetVisibleRect( rect );

				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::VisibleResource vr( 5, \"aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg\" );" << r2::linefeed2;
				std::cout << r2::tab2 << "auto rect = vr.GetVisibleRect();" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetOrigin( rect.GetOrigin().GetX() + 2, rect.GetOrigin().GetY() + 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "rect.SetSize( rect.GetSize().GetWidth() - 2, rect.GetSize().GetHeight() - 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "vr.SetVisibleRect( rect );" << r2::linefeed;

				std::cout << r2::split;

				std::cout << r2::tab << "+ View All" << r2::linefeed2;

				std::size_t cur_x = 0;
				for( const char element : vr )
				{
					std::cout << element;

					++cur_x;
					if( vr.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2::linefeed;
				}

				std::cout << r2::split;

				std::cout << r2::tab << "+ View With Rect" << r2::linefeed2;

				for( int y = vr.GetVisibleRect().GetMinY(); y < vr.GetVisibleRect().GetMaxY(); ++y )
				{
					for( int x = vr.GetVisibleRect().GetMinX(); x < vr.GetVisibleRect().GetMaxX(); ++x )
					{
						std::cout << vr.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}