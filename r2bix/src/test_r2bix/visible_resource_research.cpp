#include "pch.h"
#include "visible_resource_research.h"

#include <conio.h> // _kbhit(), _getch()
#include <Windows.h> // HANDLE, COORD, SetConsoleCursorPosition()

#include "r2cm/r2cm_eTestEndAction.h"

#include "render/r2render_Texture.h"

namespace visible_resource_research
{
	r2cm::iItem::TitleFunc DrawWithPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Draw With Position";
		};
	}
	r2cm::iItem::DoFunc DrawWithPosition::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2render::Texture visible_resource( 10, 10, '0' );
			COORD pos = { 10, 11 };

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "const r2render::Texture visible_resource( 10, 10, '0' );" << r2::linefeed;
			std::cout << r2::tab2 << "COORD pos = { 10, 11 };" << r2::linefeed;

			std::cout << r2::split;

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

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}