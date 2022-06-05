#include "DevelopmentMenu.h"

#include "r2bix/r2base_Director.h"
#include "r2bix/r2base_VersionInfo.h"
#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "test/TestMainMenu.h"
#include "p2048/p2048_EntryScene.h"
#include "p2048mini/p2048mini_GameScene.h"
#include "pmr/pmr_CompanyScene.h"

r2cm::MenuUp DevelopmentMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, r2base::VersionInfo.String4Version_0_0_2
	) );

	{
		ret->AddItem(
			'1'
			, []()->const char* { return "Test"; }
			, []()->r2cm::eItemLeaveAction
			{
				// 2022.04.11 by R2Road
				// 인자로 넘어온 director 를 사용해도 되지만 아래 코드와의 일관성을 위해 새 r2cm::Director를 만들어 돌린다.

				//
				// Setup
				//
				r2cm::Director director;
				director.Setup( TestMainMenu::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'2'
			, []()->const char* { return p2048::EntryScene::GetTitle(); }
			, []()->r2cm::eItemLeaveAction
			{
				//
				// Setup
				//
				r2base::Director director;
				director.Setup( p2048::EntryScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'3'
			, []()->const char* { return pmr::CompanyScene::GetTitle(); }
			, []()->r2cm::eItemLeaveAction
			{
				//
				// Setup
				//
				r2base::Director director;
				director.Setup( pmr::CompanyScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2cm::eItemLeaveAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction
			{
				return r2cm::eItemLeaveAction::Exit;
			}
		);
	}

	return ret;
}