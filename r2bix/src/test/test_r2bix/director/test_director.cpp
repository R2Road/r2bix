#include "test_director.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "r2bix_Director.h"

namespace test_director
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Director : Declaration";
			};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				OUTPUT_SUBJECT( "Config 를 인자로 받는 생성자." );

				LS();

				DECLARATION_MAIN( r2bix_director::Config c );
				DECLARATION_MAIN( r2bix::Director d( c ) );

				LS();

				{
					EXPECT_EQ( c.ScreenSize_Width, d.GetScreenSize().GetWidth() );
					EXPECT_EQ( c.ScreenSize_Height, d.GetScreenSize().GetHeight() );

					LF();

					EXPECT_EQ( c.ScreenOffset_X, d.GetScreenOffset().GetX() );
					EXPECT_EQ( c.ScreenOffset_Y, d.GetScreenOffset().GetY() );

					LF();

					EXPECT_EQ( &d, &d.GetRootNode().GetDirector() );
				}

				LS();

				return r2tm::eDoLeaveAction::Pause;
			};
	}



	r2tm::TitleFunctionT Size::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : Size";
		};
	}
	r2tm::DoFunctionT Size::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::Config c );
			DECLARATION_MAIN( r2bix::Director d( c ) );

			LS();

			{
				OUTPUT_SIZE( d );

				LF();

				OUTPUT_BINARY( d );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}