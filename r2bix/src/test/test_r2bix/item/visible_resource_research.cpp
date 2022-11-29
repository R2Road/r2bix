#include "visible_resource_research.h"

#include <conio.h> // _kbhit(), _getch()

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "r2bix/r2bix_render_Texture.h"

namespace visible_resource_research
{
	r2cm::iItem::TitleFunctionT DrawWithPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Draw With Position";
		};
	}
	r2cm::iItem::DoFunctionT DrawWithPosition::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture visible_resource( 10, 10, '0' ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2cm::WindowUtility::CursorPoint pos );
				PROCESS_MAIN( pos.x = 15 );
				PROCESS_MAIN( pos.y = 15 );
				PROCESS_MAIN( r2cm::WindowUtility::MoveCursorPoint( pos ) );

				int count = 0;
				for( const char element : visible_resource )
				{
					std::cout << element;

					++count;
					if( visible_resource.GetWidth() <= count )
					{
						count = 0;
						pos.y += 1;
						r2cm::WindowUtility::MoveCursorPoint( pos );
					}
				}
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}