#include "menu_camera.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_camera.h"

#include "test/test_r2bix/R2bixMenu.h"

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
					"> ī�޶�� ���𰡸� �� �ʿ� ����."
			"\n"	"> �䱸�ϴ� ��ġ�� �ڸ��ϰ�, �� �����͸� �� ������ ������ �ȴ�."
			"\n"	"> �� �Ϸ��� ������.";
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


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}