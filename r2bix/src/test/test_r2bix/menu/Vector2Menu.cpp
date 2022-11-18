#include "Vector2Menu.h"

#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/item/vector2_test.h"

#include "GeometryMenu.h"

r2cm::MenuUp Vector2Menu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu( director, GetTitle() ) );

	{
		ret->AddItem( '1', vector2_test::Declaration::GetInstance() );
		ret->AddItem( '2', vector2_test::OperatorPlus::GetInstance() );
		ret->AddItem( '3', vector2_test::OperatorPlusEqual::GetInstance() );
		ret->AddItem( '4', vector2_test::OperatorMinus::GetInstance() );
		ret->AddItem( '5', vector2_test::OperatorMinusEqual::GetInstance() );
		ret->AddItem( '6', vector2_test::OperatorMultiply_With_Scalar::GetInstance() );
		ret->AddItem( '7', vector2_test::OperatorMultiplyEqual_With_Scalar::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<GeometryMenu>( 27 );
	}

	return ret;
}