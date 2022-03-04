#include "pch.h"
#include "r2test_CameraScene.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "test/item/camera_test.h"

r2test::MenuUp CameraMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
		director
		, GetTitle(),
				"> ī�޶�� ���𰡸� �� �ʿ� ����."
		"\n"	"> �䱸�ϴ� ��ġ�� �ڸ��ϰ�, �� �����͸� �� ������ ������ �ȴ�."
		"\n"	"> �� �Ϸ��� ������."
	) );

	{
		ret->AddChild( '1', camera_test::CameraPosition::GetInstance() );
		ret->AddChild( '2', camera_test::CameraRect::GetInstance() );
		ret->AddChild( '3', camera_test::CameraMove::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( TestRootMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
	}

	return ret;
}