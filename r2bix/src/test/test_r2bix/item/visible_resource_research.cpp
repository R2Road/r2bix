#include "pch.h"
#include "visible_resource_research.h"

#include <conio.h> // _kbhit(), _getch()
#include <Windows.h> // HANDLE, COORD, SetConsoleCursorPosition()

#include "r2cm/r2cm_constant.h"

#include "r2bix/r2render_Texture.h"

namespace visible_resource_research
{
	r2cm::iItem::TitleFuncT DrawWithPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Draw With Position";
		};
	}
	r2cm::iItem::DoFuncT DrawWithPosition::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			const r2render::Texture visible_resource( 10, 10, '0' );
			COORD pos = { 10, 11 };

			std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
			std::cout << r2cm::tab2 << "const r2render::Texture visible_resource( 10, 10, '0' );" << r2cm::linefeed;
			std::cout << r2cm::tab2 << "COORD pos = { 10, 11 };" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
				SetConsoleCursorPosition( stdHandle, pos );

				int count = 0;
				for( const char element : visible_resource )
				{
					std::cout << element;

					++count;
					if( visible_resource.GetWidth() <= count )
					{
						count = 0;
						pos.Y += 1;
						SetConsoleCursorPosition( stdHandle, pos );
					}
				}
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}