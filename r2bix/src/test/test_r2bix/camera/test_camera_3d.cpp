#include "test_camera_3d.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "r2_Math.h"

#include "r2bix_Camera3D.h"

#include "r2helper_STDPrinter4Quaternion.h"
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
				OUTPUT_SUBJECT( "�⺻ ������" );

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

			{
				OUTPUT_VALUE( r2bix::Camera3D::WORLD_FRONT );
				OUTPUT_VALUE( r2bix::Camera3D::WORLD_UP );
				OUTPUT_VALUE( r2bix::Camera3D::WORLD_RIGHT );
			}

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
				OUTPUT_SUBJECT( "Front" );

				LF();

				EXPECT_EQ( r2bix::Camera3D::WORLD_FRONT, cam.GetFront() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Up" );

				LF();

				EXPECT_EQ( r2bix::Camera3D::WORLD_UP, cam.GetUp() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Right" );

				LF();

				EXPECT_EQ( r2bix::Camera3D::WORLD_RIGHT, cam.GetRight() );
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



	r2tm::TitleFunctionT Vectors::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : Vectors";
		};
	}
	r2tm::DoFunctionT Vectors::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );
			DECLARATION_MAIN( const r2::Radian radian( r2::deg2rad( r2::Degree( 90.f ) ) ) );

			LS();

			EXPECT_EQ( r2bix::Camera3D::WORLD_FRONT, cam.GetFront() );
			EXPECT_EQ( r2bix::Camera3D::WORLD_RIGHT, cam.GetRight() );
			EXPECT_EQ( r2bix::Camera3D::WORLD_UP, cam.GetUp() );

			LS();

			{
				OUTPUT_SUBJECT( "Y" );

				LF();

				{
					PROCESS_MAIN( cam.RotationY( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( -r2::VEC3_X, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetRight() );
					EXPECT_EQ( r2bix::Camera3D::WORLD_UP, cam.GetUp() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y + X" );

				LF();

				{
					PROCESS_MAIN( cam.RotationX( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( r2::VEC3_Y, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetRight() );
					EXPECT_EQ( r2::VEC3_X, cam.GetUp() );
				}
			}

			LS();

			{
				OUTPUT_SUBJECT( "Y + X + Z" );

				LF();

				{
					PROCESS_MAIN( cam.RotationZ( radian ) );
					PROCESS_MAIN( cam.UpdateVectors() );

					LF();

					EXPECT_EQ( r2::VEC3_Y, cam.GetFront() );
					EXPECT_EQ( -r2::VEC3_X, cam.GetRight() );
					EXPECT_EQ( -r2::VEC3_Z, cam.GetUp() );
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ViewTransform::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera3D : ViewTransform";
		};
	}
	r2tm::DoFunctionT ViewTransform::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Camera3D cam );

			LS();

			{
				OUTPUT_SUBJECT( "����" );

				LF();

				PROCESS_MAIN( cam.SetPosition( r2bix::Camera3D::Vec3( 0, 0, 10 ) ) );
				PROCESS_MAIN( cam.SetRotationY( r2::deg2rad( r2::Degree( -45.f ) ) ) );
				PROCESS_MAIN( cam.UpdateVectors() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "����" );

				LF();

				DECLARATION_MAIN( r2bix::Camera3D::Vec3 vs( 1, 0, 9 ) );
				DECLARATION_MAIN( r2bix::Camera3D::Mat4 view_mat = cam.GetViewMatrix() );

				LF();

				PROCESS_MAIN( vs = view_mat * vs );

				LF();

				EXPECT_EP_EQ( 0, vs.x );
				EXPECT_EP_EQ( 0, vs.y );
				EXPECT_EP_EQ( -r2::length( r2::Vector3( 1, 0, 1 ) ), vs.z );

				LF();

				OUTPUT_VALUE( vs );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}