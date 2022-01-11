#include "pch.h"
#include "flickering_research.h"

#include <conio.h>
#include <string_view>

#include "base/r2_eTestResult.h"

#include "renderer/r2_VisibleResource.h"

namespace flickering_research
{
	r2::iTest::TitleFunc OneByOne::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print One By One";
		};
	}
	r2::iTest::DoFunc OneByOne::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			r2::VisibleResource visible_resource( 19, 19 );
			visible_resource.FillAll( 'a' );

			bool process = true;
			do
			{
				system( "cls" );

				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
				std::cout << "[Any Key] End" << r2::linefeed;

				std::cout << r2::split;

				int current_x = 0;
				for( const auto v : visible_resource )
				{
					if( visible_resource.GetWidth() <= current_x )
					{
						std::cout << r2::linefeed;
						current_x = 0;
					}

					std::cout << v;

					++current_x;
				}

				std::cout << r2::linefeed << r2::split;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}



	r2::iTest::TitleFunc Try_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering Try_1";
		};
	}
	r2::iTest::DoFunc Try_1::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			r2::VisibleResource visible_resource( 19, 19 );
			visible_resource.FillAll( 'a' );

			std::string_view str_view;

			bool process = true;
			do
			{
				system( "cls" );

				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
				std::cout << "[Any Key] End" << r2::linefeed2;

				std::cout << r2::split;

				for( int current_y = 0; visible_resource.GetHeight() > current_y; ++current_y )
				{
					std::cout << visible_resource.GetLine( current_y ) << r2::linefeed;
				}

				std::cout << r2::linefeed << r2::split;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2::eTestResult::RunTest_Without_Pause;
		};
	}
}