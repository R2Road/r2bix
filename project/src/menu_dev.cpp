#include "menu_dev.hpp"

#include <string>

#include "r2_version_info.hpp"
#include "r2bix_Director.h"
#include "r2bix_VersionInfo.h"
#include "r2tm/r2tm_MenuProcessor.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "test/test_p2048/P2048Menu.h"
#include "test/test_r2bix/menu_r2bix.h"

#include "tool/menu_tool.hpp"

#include "view/menu_view.h"

r2tm::TitleFunctionT Menu_Dev::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
				std::string( "Development" )
			+	" : <" + r2bix::VersionInfo.String4Version + ">"
			+	", <" + r2tm::VersionInfo.String4Version + ">"
			+	", <" + r2::VersionInfo.String4Version + ">"
		;
		return ret.c_str();
	};
}
r2tm::DescriptionFunctionT Menu_Dev::GetDescriptionFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
			std::string()

			+ r2bix::VersionInfo.String4VersionRule
			+ "\n"
			  "\n"
			  "\n"
			+ r2bix::VersionInfo.String4Road2NextVersion
		;
		return ret.c_str();
	};
}
r2tm::WriteFunctionT Menu_Dev::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMenu( '1', Menu_R2bix() );
		mp->AddMenu( '2', Menu_Tool() );



		mp->AddLineFeed();

		

		mp->AddMenu( 'a', P2048Menu() );



		mp->AddLineFeed();



		mp->AddMenu( 32, Menu_View() );


		
		mp->AddSplit();



		mp->AddExit( 27 );
	};
}