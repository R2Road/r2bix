#include "test_camera_3d.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "r2bix_render_Camera3D.h"

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

				DECLARATION_MAIN( r2bix_render::Camera3D cam );

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

				DECLARATION_MAIN( using V = r2bix_render::Camera3D::Vec3 );
				DECLARATION_MAIN( r2bix_render::Camera3D cam );

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

					EXPECT_EQ( V( 0, 1, 0 ), cam.GetUp() );

					SS();

					DECLARATION_MAIN( const V v( 100, 0, 0 ) );
					PROCESS_MAIN( cam.SetUp( v ) );

					LF();

					EXPECT_EQ( V( 1, 0, 0 ), cam.GetUp() );
				}

				LS();

				return r2tm::eDoLeaveAction::Pause;
			};
	}
}