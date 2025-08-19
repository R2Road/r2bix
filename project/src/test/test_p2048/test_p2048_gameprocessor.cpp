#include "test_p2048_gameprocessor.h"

#include <conio.h>
#include <iomanip>

#include "r2bix_Director.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "p2048/p2048_GameProcessor.h"
#include "p2048/p2048_Stage.h"

#include "r2utility_Operator4Direction4SequentialWithPoint.h"

namespace test_p2048_gameprocessor
{
	void PrintStage( const p2048::Stage& stage )
	{
		int val = 0;
		for( uint32_t y = 0; stage.GetHeight() > y; ++y )
		{
			for( uint32_t x = 0; stage.GetWidth() > x; ++x )
			{
				val = stage.GetNumber( x, y );

				std::cout << std::setw( 2 ) << std::right << val;
				std::cout << std::setw( 1 ) << std::left; // roll back

				std::cout << r2tm::tab;
			}

			LF();
		}
	}



	r2tm::TitleFunctionT MoveReadyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GameProcessor : Move Ready";
		};
	}
	r2tm::DoFunctionT MoveReadyTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( p2048::Stage stage( 4, 4 ) );

			LS();

			{
				DECL_MAIN( r2::Direction4Sequential move_dir );
				DECL_MAIN( const r2::PointInt center_point( stage.GetWidth() / 2, stage.GetHeight() / 2 ) );
				DECL_MAIN( r2::PointInt pivot_point_1 );
				DECL_MAIN( r2::PointInt pivot_point_2 );

				LF();

				const auto pivot_coord = r2tm::WindowsUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2tm::WindowsUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Press [W, A, S, D]" << r2tm::linefeed2;

					switch( _getch() )
					{
					case 97: // L
						PROC_MAIN( move_dir.SetState( r2::Direction4Sequential::eState::Left ) );
						break;
					case 100: // R
						PROC_MAIN( move_dir.SetState( r2::Direction4Sequential::eState::Right ) );
						break;
					case 119: // U
						PROC_MAIN( move_dir.SetState( r2::Direction4Sequential::eState::Down ) ); // swap D 4 ez look
						break;
					case 115: // D
						PROC_MAIN( move_dir.SetState( r2::Direction4Sequential::eState::Up ) ); // swap U 4 ez look
						break;

					case 27: // ESC
						bRun = false;
						break;

					default:
						continue;
					}

					LF();

					if( bRun )
					{
						{
							PROC_MAIN( pivot_point_1 = center_point + r2::PointInt( center_point.GetX() * move_dir.GetX(), center_point.GetY() * move_dir.GetY() ) );
							PROC_MAIN( pivot_point_1.SetX( std::clamp( pivot_point_1.GetX(), 0, static_cast<int32_t>( stage.GetMaxX() ) ) ) );
							PROC_MAIN( pivot_point_1.SetY( std::clamp( pivot_point_1.GetY(), 0, static_cast<int32_t>( stage.GetMaxY() ) ) ) );
						}

						LF();

						{
							PROC_MAIN( pivot_point_2.Set( pivot_point_1.GetX() * std::abs( move_dir.GetX() ), pivot_point_1.GetY() * std::abs( move_dir.GetY() ) ) );
						}

						LF();

						stage.ClearAll();
						PROC_MAIN( stage.Add( pivot_point_1.GetX(), pivot_point_1.GetY(), 1 ) );
						PROC_MAIN( stage.Add( pivot_point_2.GetX(), pivot_point_2.GetY(), 2 ) );
						PROC_MAIN( stage.Add( center_point.GetX(), center_point.GetY(), 7 ) );
						PROC_MAIN( PrintStage( stage ) );

						LF();

						stage.ClearAll();

						auto reverse_dir = move_dir;
						reverse_dir.Rotate( true );
						reverse_dir.Rotate( true );
						for( int loop_count = 0; stage.IsIn( pivot_point_2.GetX(), pivot_point_2.GetY() ); ++loop_count )
						{
							for( uint32_t y = 0; stage.GetHeight() > y; ++y )
							{
								for( uint32_t x = 0; stage.GetWidth() > x; ++x )
								{
									r2::PointInt temp_point( x * std::abs( move_dir.GetX() ), y * std::abs( move_dir.GetY() ) );

									if( pivot_point_2.GetX() == temp_point.GetX() && pivot_point_2.GetY() == temp_point.GetY() )
									{
										PROC_MAIN( stage.Add( x, y, loop_count ) );
									}
								}
							}

							pivot_point_2 += reverse_dir;
						}
						PROC_MAIN( PrintStage( stage ) );
					}
				} while( bRun );
			}

			LS();

			return r2tm::eDoLeaveAction::None;
		};
	}



	r2tm::TitleFunctionT MoveTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GameProcessor : Move";
		};
	}
	r2tm::DoFunctionT MoveTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( p2048::Stage stage( 4, 4 ) );
			DECL_MAIN( p2048::GameProcessor game_processor( &stage ) );

			LS();

			{
				PROC_MAIN( stage.Add( 0, 0, 1 ) );
				PROC_MAIN( stage.Add( 0, 1, 2 ) );
				PROC_MAIN( stage.Add( 3, 0, 3 ) );
				PROC_MAIN( stage.Add( 0, 3, 4 ) );
				PROC_MAIN( stage.Add( 3, 3, 8 ) );
				PROC_MAIN( PrintStage( stage ) );
			}

			LS();


			{
				const auto pivot_coord = r2tm::WindowsUtility::GetCursorPoint();
				bool bRun = true;
				do
				{
					r2tm::WindowsUtility::MoveCursorPoint( pivot_coord );

					std::cout << "Press [W, A, S, D]" << r2tm::linefeed2;

					bool has_moved = false;
					switch( _getch() )
					{
					case 97: // L
						PROC_MAIN( has_moved = game_processor.Move( r2::Direction4Sequential::eState::Left ).has_moved );
						break;
					case 100: // R
						PROC_MAIN( has_moved = game_processor.Move( r2::Direction4Sequential::eState::Right ).has_moved );
						break;
					case 119: // U
						PROC_MAIN( has_moved = game_processor.Move( r2::Direction4Sequential::eState::Down ).has_moved ); // swap D 4 ez look
						break;
					case 115: // D
						PROC_MAIN( has_moved = game_processor.Move( r2::Direction4Sequential::eState::Up ).has_moved ); // swap U 4 ez look
						break;

					case 27: // ESC
						bRun = false;
						break;

					default:
						continue;
					}

					LF();

					PROC_MAIN( PrintStage( stage ) );
					std::cout << ( has_moved ? "Move Success" : "Move Failed" ) << r2tm::linefeed;

				} while( bRun );
			}

			LS();

			return r2tm::eDoLeaveAction::None;
		};
	}



	r2tm::TitleFunctionT MergeTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GameProcessor : Merge";
		};
	}
	r2tm::DoFunctionT MergeTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( p2048::Stage stage( 4, 1 ) );
			DECL_MAIN( p2048::GameProcessor game_processor( &stage ) );

			LS();

			{
				stage.Add( 0, 0, 2 );
				stage.Add( 1, 0, 1 );
				stage.Add( 2, 0, 1 );
				PROC_MAIN( PrintStage( stage ) );
			}

			LS();

			{
				DECL_MAIN( const auto move_result = game_processor.Move( r2::Direction4Sequential::eState::Right ) );
				PROC_MAIN( PrintStage( stage ) );

				LF();

				EXPECT_EQ( 2, stage.GetNumber( 2, 0 ) );
				EXPECT_EQ( 2, stage.GetNumber( 3, 0 ) );

				LF();

				EXPECT_EQ( 2, game_processor.GetSum4Merged() );
			}

			LS();

			{
				DECL_MAIN( const auto move_result = game_processor.Move( r2::Direction4Sequential::eState::Right ) );
				PROC_MAIN( PrintStage( stage ) );

				LF();

				EXPECT_EQ( 4, stage.GetNumber( 3, 0 ) );

				LF();

				EXPECT_EQ( 4, game_processor.GetSum4Merged() );
			}

			LS();

			{
				PROC_MAIN( stage.Add( 0, 0, 4 ) );
				PROC_MAIN( stage.Add( 1, 0, 4 ) );
				PROC_MAIN( stage.Add( 2, 0, 4 ) );
				PROC_MAIN( PrintStage( stage ) );

				LF();

				DECL_MAIN( const auto move_result = game_processor.Move( r2::Direction4Sequential::eState::Right ) );
				PROC_MAIN( PrintStage( stage ) );

				LF();

				EXPECT_EQ( 8, stage.GetNumber( 2, 0 ) );
				EXPECT_EQ( 8, stage.GetNumber( 3, 0 ) );

				LF();

				EXPECT_EQ( 16, game_processor.GetSum4Merged() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MovableCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GameProcessor : Movable Check";
		};
	}
	r2tm::DoFunctionT MovableCheck::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << r2tm::tab << "+ Node : 주변의 숫자가 0 이거나 같다면 이동 한다." << r2tm::linefeed;

			LS();

			DECL_MAIN( p2048::Stage stage( 2, 2 ) );
			DECL_MAIN( p2048::GameProcessor game_processor( &stage ) );

			LS();

			{
				stage.Add( 0, 0, 7 );
				stage.Add( 0, 1, 7 );
				stage.Add( 1, 0, 7 );
				stage.Add( 1, 1, 7 );
				PrintStage( stage );
				EXPECT_TRUE( game_processor.IsMovable() );
			}

			LS();

			{
				stage.Add( 0, 0, 1 );
				stage.Add( 0, 1, 2 );
				stage.Add( 1, 0, 7 );
				stage.Add( 1, 1, 7 );
				PrintStage( stage );
				EXPECT_TRUE( game_processor.IsMovable() );
			}

			LS();

			{
				stage.Add( 0, 0, 1 );
				stage.Add( 0, 1, 7 );
				stage.Add( 1, 0, 2 );
				stage.Add( 1, 1, 7 );
				PrintStage( stage );
				EXPECT_TRUE( game_processor.IsMovable() );
			}

			LS();

			{
				stage.Add( 0, 0, 1 );
				stage.Add( 0, 1, 2 );
				stage.Add( 1, 0, 3 );
				stage.Add( 1, 1, 7 );
				PrintStage( stage );
				EXPECT_FALSE( game_processor.IsMovable() );
			}

			LS();

			{
				stage.Add( 0, 0, 1 );
				stage.Add( 0, 1, 2 );
				stage.Add( 1, 0, 3 );
				stage.Add( 1, 1, 0 );
				PrintStage( stage );
				EXPECT_TRUE( game_processor.IsMovable() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}