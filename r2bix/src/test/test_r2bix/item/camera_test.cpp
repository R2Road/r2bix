#include "camera_test.h"

#include <conio.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "r2bix/r2bix_render_Camera.h"
#include "r2bix/r2bix_render_Texture.h"


namespace camera_test
{
	std::ostream& operator<<( std::ostream& o, const r2::PointInt& p )
	{
		o << "x : " << p.GetX() << "      " "y : " << p.GetY() << r2cm::linefeed;
		return o;
	}
	std::ostream& operator<<( std::ostream& o, const r2::Size<int>& s )
	{
		o << "s : " << s.GetWidth() << "      " "h : " << s.GetHeight() << r2cm::linefeed;
		return o;
	}

	r2cm::iItem::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera : Declaration";
		};
	}
	r2cm::iItem::DoFunctionT Declaration::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2::Point<int> position( 20, 30 ) );
			DECLARATION_MAIN( const r2::Size<int> size( 10, 50 ) );
			DECLARATION_MAIN( r2bix_render::Camera camera( position, size ) );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( position.GetX(), camera.GetX() );
				EXPECT_EQ( position.GetY(), camera.GetY() );
				EXPECT_EQ( position, camera.GetPoint() );
				EXPECT_EQ( size.GetWidth(), camera.GetWidth() );
				EXPECT_EQ( size.GetHeight(), camera.GetHeight() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( ( size + r2::Size<int>( -1, -1 ) ), camera.GetCameraSpaceRect().GetSize() );
				EXPECT_EQ( -( ( size.GetWidth() - 1 ) / 2 ), camera.GetCameraSpaceRect().GetOrigin().GetX() );
				EXPECT_EQ( -( ( size.GetHeight() - 1 ) / 2 ), camera.GetCameraSpaceRect().GetOrigin().GetY() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( ( size + r2::Size<int>( -1, -1 ) ), camera.GetRect().GetSize() );
				EXPECT_EQ( position.GetX() - ( ( size.GetWidth() - 1 ) / 2 ), camera.GetRect().GetOrigin().GetX() );
				EXPECT_EQ( position.GetY() - ( ( size.GetHeight() - 1 ) / 2 ), camera.GetRect().GetOrigin().GetY() );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_VALUE( camera.GetX() );
				OUTPUT_VALUE( camera.GetY() );
				OUTPUT_VALUE( camera.GetWidth() );
				OUTPUT_VALUE( camera.GetHeight() );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetOrigin().GetX() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetOrigin().GetY() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetSize().GetWidth() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetSize().GetHeight() );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( camera.GetRect().GetOrigin().GetX() );
				OUTPUT_VALUE( camera.GetRect().GetOrigin().GetY() );
				OUTPUT_VALUE( camera.GetRect().GetSize().GetWidth() );
				OUTPUT_VALUE( camera.GetRect().GetSize().GetHeight() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CameraPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Position";
		};
	}
	r2cm::iItem::DoFunctionT CameraPosition::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::Camera camera( { 20, 30 }, { 20, 10 } ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Show Camera Position" << r2cm::linefeed2;

				std::cout << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3 << r2cm::linefeed3;

				r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
				r2cm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}


			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2cm::iItem::DoFunctionT CameraRect::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			r2bix_render::Camera camera( { 20, 30 }, { 20, 10 } );

			{
				std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
				std::cout << r2cm::tab2 << "r2bix_render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Show Camera Rect" << r2cm::linefeed2;

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
					{
						r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				
				r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			r2cm::WindowUtility::MoveCursorPoint( { 0, 50 } );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CameraMove::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move";
		};
	}
	r2cm::iItem::DoFunctionT CameraMove::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::Camera camera( { 20, 30 }, { 19, 9 } ) );

			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Show Camera Rect" << r2cm::linefeed2;
			std::cout << "[ESC] Exit" << r2cm::linefeed;
			std::cout << "[Any Key] Move Camera" << r2cm::linefeed;

			std::cout << r2cm::split;

			const auto current_cursor_point = r2cm::WindowUtility::GetCursorPoint();
			int step = 0;
			int input = 0;
			do
			{
				r2cm::WindowUtility::MoveCursorPointWithClearBuffer( current_cursor_point );

				if( 0 == step )
				{
					camera.SetPoint( 30, 20 );
					step = 1;
				}
				else
				{
					camera.SetPoint( 20, 30 );
					step = 0;
				}

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
						{
							r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}

					r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
					std::cout << 'X';
				}

				r2cm::WindowUtility::MoveCursorPoint( { 0, 40 } );
				input = _getch();

			} while( 27 != input );

			return r2cm::eItemLeaveAction::None;
		};
	}
}