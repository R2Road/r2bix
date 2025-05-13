#if defined( DEBUG ) || defined( _DEBUG )
	#include "vld/include/vld.h"
#endif

#include "r2bix_DebugConfig.h"
#include "r2bix_VersionInfo.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_WindowsUtility.h"

#include "DevelopmentMenu.h"

int main()
{
	//
	// Environment : Title
	//
	r2tm::WindowsUtility::ChangeTitle( r2bix::VersionInfo.String4Version );

	//
	// Environment : Size
	//
	r2tm::WindowsUtility::Resize( 960, 960 );

	//
	// Environment : Position
	//
	r2tm::WindowsUtility::Move( 0, 0 );

	//
	// Environment : Quick Edit Off
	//
	r2tm::WindowsUtility::QuickEditEnable( false );

	//
	// R2bix Debug Config
	//
	r2bix::DebugConfig::GetInstance().SetRenderConfig( { true } );

	//
	// Setup
	//
	r2tm::Director director;
	director.Setup( DevelopmentMenu() );

	//
	// Process
	//
	director.Run();

	return 0;
}
