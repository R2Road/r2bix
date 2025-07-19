#include "test_camera_3d.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "r2_Math.h"

#include "r2bix_Camera3D.h"

#include "r2helper_STDPrinter4Radian.h"
#include "r2helper_STDPrinter4Vector3.h"

namespace test_camera_3d
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUTPUT_SUBJECT( "기본 생성자" );

				SS();

				DECLARATION_MAIN( r2bix::Camera3D cam );

				SS();

				{
					OUTPUT_SIZE( cam );

					LF();

					OUTPUT_BINARY( cam );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Camera3D : Basic";
			};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( using V = r2bix::Camera3D::Vec3 );
			DECLARATION_MAIN( r2bix::Camera3D cam );

			LS();

			{
				OUTPUT_SUBJECT( "Position" );

				LF();

				EXPECT_EQ( V( 0, 0, 0 ), cam.GetPosition() );

				SS();

				DECLARATION_MAIN( const V v( 10, 20, 30 ) );
				PROCESS_MAIN( cam.SetPosition( v ) );

				LF();

				EXPECT_EQ( v, cam.GetPosition() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Up" );

				LF();

				EXPECT_EQ( r2bix::Camera3D::WORLD_UP, cam.GetUp() );

				SS();

				DECLARATION_MAIN( const V v( 100, 0, 0 ) );
				PROCESS_MAIN( cam.SetUp( v ) );

				LF();

				EXPECT_EQ( V( 1, 0, 0 ), cam.GetUp() );

				LF();

				OUTPUT_NOTE( "normalize 적용" );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Front" );

				LF();

				EXPECT_EQ( r2bix::Camera3D::WORLD_FRONT, cam.GetFront() );

				SS();

				DECLARATION_MAIN( const V v( 0, 0, -100 ) );
				PROCESS_MAIN( cam.SetFront( v ) );

				LF();

				EXPECT_EQ( v, cam.GetFront() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Move::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Move";
		};
	}
	r2tm::DoFunctionT Move::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( using V = r2bix::Camera3D::Vec3 );
			DECLARATION_MAIN( r2bix::Camera3D cam );

			LF();

			DECLARATION_MAIN( const V v( 10, 20, 30 ) );

			LS();

			{
				OUTPUT_SUBJECT( "Move" );

				LF();

				EXPECT_EQ( V( 0, 0, 0 ), cam.GetPosition() );

				SS();

				{
					PROCESS_MAIN( cam.Move( v ) );

					LF();

					EXPECT_EQ( v, cam.GetPosition() );
				}

				SS();
				
				{
					PROCESS_MAIN( cam.Move( v ) );

					LF();

					EXPECT_EQ( v + v, cam.GetPosition() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Rotation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Rotation";
		};
	}
	r2tm::DoFunctionT Rotation::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );
			DECLARATION_MAIN( const r2::Radian radian( r2::deg2rad( r2::Degree( 30.f ) ) ) );

			LS();

			{
				OUTPUT_SUBJECT( "X" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationX() );

				SS();

				{
					PROCESS_MAIN( cam.RotationX( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationX() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationY() );

				SS();

				{
					PROCESS_MAIN( cam.RotationY( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationY() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Z" );

				LF();

				EXPECT_EQ( r2::Radian(), cam.GetRotationZ() );

				SS();

				{
					PROCESS_MAIN( cam.RotationZ( radian ) );

					LF();

					EXPECT_EQ( radian, cam.GetRotationZ() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}