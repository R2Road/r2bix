#include "visible_resource_research.h"

#include <conio.h> // _kbhit(), _getch()

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "r2bix_render_Texture.h"

namespace visible_resource_research
{
	r2tm::TitleFunctionT DrawWithPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Draw With Position";
		};
	}
	r2tm::DoFunctionT DrawWithPosition::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture visible_resource( 10, 10, '0' ) );

			LS();

			{
				DECLARATION_MAIN( r2tm::WindowUtility::CursorPoint pos );
				PROCESS_MAIN( pos.x = 15 );
				PROCESS_MAIN( pos.y = 15 );
				PROCESS_MAIN( r2tm::WindowUtility::MoveCursorPoint( pos ) );

				int count = 0;
				for( const char element : visible_resource )
				{
					std::cout << element;

					++count;
					if( visible_resource.GetWidth() <= count )
					{
						count = 0;
						pos.y += 1;
						r2tm::WindowUtility::MoveCursorPoint( pos );
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}