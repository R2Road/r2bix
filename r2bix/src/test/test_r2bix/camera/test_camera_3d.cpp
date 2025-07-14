#include "test_camera_3d.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "r2bix_render_Camera3D.h"


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
}