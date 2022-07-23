#include "CameraMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/test_r2bix/item/camera_test.h"

#include "test/test_r2bix/R2bixMenu.h"

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
		ret->AddItem( '1', camera_test::CameraPosition::GetInstance() );
		ret->AddItem( '2', camera_test::CameraRect::GetInstance() );
		ret->AddItem( '3', camera_test::CameraMove::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}