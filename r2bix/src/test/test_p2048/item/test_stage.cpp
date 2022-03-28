#include "pch.h"
#include "test_stage.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_Director.h"
#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"
#include "utility/r2utility_WindowUtil.h"

#include "p2048/p2048_Stage.h"

void PrintStage( const p2048::Stage& stage )
{
	int val = -1;
	for( uint32_t y = 0; stage.GetHeight() > y; ++y )
	{
		for( uint32_t x = 0; stage.GetWidth() > x; ++x )
		{
			val = stage.Get( x, y );

			if( -1 == val )
			{
				std::cout << "X";
			}
			else
			{
				std::cout << val;
			}

			std::cout << r2::tab;
		}

		std::cout << r2::linefeed;
	}
}

namespace test_stage
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 6, 5 ) );
			EXPECT_EQ( 6, stage.GetWidth() );
			EXPECT_EQ( 5, stage.GetHeight() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( stage.Add( 2, 2, 64 ) );
				EXPECT_EQ( 64, stage.Get( 2, 2 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;


			{
				PROCESS_MAIN( stage.Remove( 2, 2 ) );
				EXPECT_EQ( -1, stage.Get( 2, 2 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT MoveReadyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Move Ready";
		};
	}
	r2cm::iItem::DoFuncT MoveReadyTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 4 ) );
			PROCESS_MAIN( PrintStage( stage ) );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( r2::Direction4 move_dir );
				DECLARATION_MAIN( const r2::PointInt center_point( stage.GetWidth() / 2, stage.GetHeight() / 2 ) );
				DECLARATION_MAIN( r2::PointInt pivot_point_1 );
				DECLARATION_MAIN( r2::PointInt pivot_point_2 );

				std::cout << r2::linefeed;

				const auto pivot_coord = r2utility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2utility::SetCursorPoint( pivot_coord );

					std::cout << "Press [W, A, S, D]" << r2::linefeed2;

					switch( _getch() )
					{
					case 97: // L
						PROCESS_MAIN( move_dir.SetState( r2::Direction4::eState::Left ) );
						break;
					case 100: // R
						PROCESS_MAIN( move_dir.SetState( r2::Direction4::eState::Right ) );
						break;
					case 119: // U
						PROCESS_MAIN( move_dir.SetState( r2::Direction4::eState::Down ) ); // swap D 4 ez look
						break;
					case 115: // D
						PROCESS_MAIN( move_dir.SetState( r2::Direction4::eState::Up ) ); // swap U 4 ez look
						break;

					case 27: // ESC
						bRun = false;
						break;

					default:
						continue;
					}

					std::cout << r2::linefeed;

					if( bRun )
					{
						{
							PROCESS_MAIN( pivot_point_1 = center_point + r2::PointInt( center_point.GetX() * move_dir.GetPoint().GetX(), center_point.GetY() * move_dir.GetPoint().GetY() ) );
							PROCESS_MAIN( pivot_point_1.SetX( std::clamp( pivot_point_1.GetX(), 0, static_cast<int32_t>( stage.GetMaxX() ) ) ) );
							PROCESS_MAIN( pivot_point_1.SetY( std::clamp( pivot_point_1.GetY(), 0, static_cast<int32_t>( stage.GetMaxY() ) ) ) );
						}

						std::cout << r2::linefeed;

						{
							PROCESS_MAIN( pivot_point_2.Set( pivot_point_1.GetX() * std::abs( move_dir.GetPoint().GetX() ), pivot_point_1.GetY() * std::abs( move_dir.GetPoint().GetY() ) ) );
						}

						std::cout << r2::linefeed;

						stage.ClearAll();
						PROCESS_MAIN( stage.Add( pivot_point_1.GetX(), pivot_point_1.GetY(), 1 ) );
						PROCESS_MAIN( stage.Add( pivot_point_2.GetX(), pivot_point_2.GetY(), 2 ) );
						PROCESS_MAIN( stage.Add( center_point.GetX(), center_point.GetY(), 0 ) );
						PROCESS_MAIN( PrintStage( stage ) );

						std::cout << r2::linefeed;

						stage.ClearAll();
						for( int y = 0; stage.GetHeight() > y; ++y )
						{
							for( int x = 0; stage.GetWidth() > x; ++x )
							{
								r2::PointInt temp_point( x * std::abs( move_dir.GetPoint().GetX() ), y * std::abs( move_dir.GetPoint().GetY() ) );

								if( pivot_point_2.GetX() == temp_point.GetX() && pivot_point_2.GetY() == temp_point.GetY() )
								{
									PROCESS_MAIN( stage.Add( x, y, 7 ) );
								}
							}
						}
						PROCESS_MAIN( PrintStage( stage ) );
					}
				} while( bRun );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::None;
		};
	}



	r2cm::iItem::TitleFuncT MoveTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Move";
		};
	}
	r2cm::iItem::DoFuncT MoveTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 4 ) );

			std::cout << r2::split;

			{
				PROCESS_MAIN( stage.Add( 0, 0, 2 ) );
				PROCESS_MAIN( stage.Add( 3, 0, 4 ) );
				PROCESS_MAIN( stage.Add( 0, 3, 8 ) );
				PROCESS_MAIN( stage.Add( 3, 3, 16 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;


			{
				PROCESS_MAIN( stage.Move( r2::Direction4::eState::Right ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}