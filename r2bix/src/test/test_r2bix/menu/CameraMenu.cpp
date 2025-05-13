#include "CameraMenu.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test/test_r2bix/item/camera_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT CameraMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Camera";
	};
}
r2tm::DescriptionFunctionT CameraMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return 
					"> 카메라는 무언가를 할 필요 없다."
			"\n"	"> 요구하는 위치에 자리하고, 그 데이터를 잘 가지고만 있으면 된다."
			"\n"	"> 뭐 하려고 하지마.";
	};
}
r2tm::WriteFunctionT CameraMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', camera_test::Declaration() );
		mp->AddItem( '2', camera_test::CameraPosition() );
		mp->AddItem( '3', camera_test::CameraRect() );
		mp->AddItem( '4', camera_test::CameraMove() );


		mp->AddSplit();


		mp->AddMenu( 27, R2bixMenu() );
	};
}