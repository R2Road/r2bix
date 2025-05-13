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
					"> ī�޶�� ���𰡸� �� �ʿ� ����."
			"\n"	"> �䱸�ϴ� ��ġ�� �ڸ��ϰ�, �� �����͸� �� ������ ������ �ȴ�."
			"\n"	"> �� �Ϸ��� ������.";
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