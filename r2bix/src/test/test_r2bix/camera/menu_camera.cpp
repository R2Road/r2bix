#include "menu_camera.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_camera.h"
#include "test_camera_3d.h"

#include "test/test_r2bix/menu_r2bix.h"

r2tm::TitleFunctionT Menu_Camera::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Camera";
	};
}
r2tm::DescriptionFunctionT Menu_Camera::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return 
					"> 카메라는 무언가를 할 필요 없다."
			"\n"	"> 요구하는 위치에 자리하고, 그 데이터를 잘 가지고만 있으면 된다."
			"\n"	"> 뭐 하려고 하지마.";
	};
}
r2tm::WriteFunctionT Menu_Camera::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_camera::Declaration() );
		mp->AddItem( '2', test_camera::CameraPosition() );
		mp->AddItem( '3', test_camera::CameraRect() );
		mp->AddItem( '4', test_camera::CameraMove() );


		mp->AddLineFeed();


		mp->AddItem( 'q', test_camera_3d::Declaration() );
		mp->AddItem( 'w', test_camera_3d::Basic() );
		mp->AddItem( 'e', test_camera_3d::Move() );
		mp->AddItem( 'r', test_camera_3d::Rotation() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}