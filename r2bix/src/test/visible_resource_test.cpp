#include "pch.h"
#include "visible_resource_test.h"

#include <Windows.h>

#include "base/r2_eTestResult.h"

#include "renderer/r2_Camera.h"
#include "renderer/r2_iRenderable.h"

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
			vr.Fill( vr.GetWidth() - 1u, 0, '0' );
			vr.Fill( vr.GetWidth() - 1u, vr.GetHeight() - 1u, '0' );
			vr.Fill( 0, vr.GetHeight() - 1u, '0' );

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2::VisibleResource visible_resource( 30, 20 );" << r2::linefeed;
			std::cout << r2::tab2 << "visible_resource.Fill( 0, 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "visible_resource.Fill( vr.GetWidth() - 1u, 0, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "visible_resource.Fill( vr.GetWidth() - 1u, vr.GetHeight() - 1u, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "visible_resource.Fill( 0, vr.GetHeight() - 1u, '0' );" << r2::linefeed;

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



	r2::iTest::TitleFunc InitWithChars::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Init With Chars";
		};
	}
	r2::iTest::DoFunc InitWithChars::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;
			
			std::size_t x = 0;

			{
				const r2::VisibleResource visible_resource_1( "Init With Chars" );

				for( const char element : visible_resource_1 )
				{
					std::cout << element;

					++x;
					if( visible_resource_1.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			{
				const r2::VisibleResource visible_resource_2( 5, "aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg" );

				x = 0;
				for( const char element : visible_resource_2 )
				{
					std::cout << element;

					++x;
					if( visible_resource_2.GetWidth() <= x )
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



	VisibleRect::VisibleRect() :
		mVisibleResource( 5, "aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg" )
	{}

	r2::iTest::TitleFunc VisibleRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Visible Rect";
		};
	}
	r2::iTest::DoFunc VisibleRect::GetDoFunction()
	{
		auto visible_rect = GetInstance().mVisibleResource.GetVisibleRect();
		visible_rect.SetOrigin( visible_rect.GetOrigin().GetX() + 2, visible_rect.GetOrigin().GetY() + 1 );
		visible_rect.SetSize( visible_rect.GetSize().GetWidth() - 2, visible_rect.GetSize().GetHeight() - 1 );
		GetInstance().mVisibleResource.SetVisibleRect( visible_rect );


		return [&vr = GetInstance().mVisibleResource]()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
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
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
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