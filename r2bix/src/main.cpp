#include "pch.h"

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "test/scene/DevelopScene.h"
#include "utility/r2utility_WindowUtil.h"

int main()
{
	//
	// Environment : Title
	//
	r2utility::ChangeWindowTitle( L"r2bix" );

	//
	// Environment : Size
	//
	r2utility::ResizeWindow( 960, 960 );

	//
	// Environment : Position
	//
	r2utility::MoveWindow( 0, 0 );

	//
	// Setup
	//
	r2base::Director director;
	director.Setup( DevelopScene::Create( director ) );

	//
	// Process
	//
	director.Update();

	return 0;
}
