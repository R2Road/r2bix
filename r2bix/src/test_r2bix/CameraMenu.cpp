#include "pch.h"
#include "CameraMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "camera_test.h"

r2cm::MenuUp CameraMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
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
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}