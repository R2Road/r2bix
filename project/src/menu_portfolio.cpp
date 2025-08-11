#include "menu_portfolio.hpp"

#include "r2tm/r2tm_MenuProcessor.h"

#include "r2bix_Director.h"
#include "r2bix_utility_InputUtil.h"

#include "p2048/p2048_EntryScene.h"
#include "tool/texture_editor/tool_texture_editor_EntryScene.h"
#include "test/test_r2bix/camera/test_camera_3d.h"

#include "menu_dev.hpp"

r2tm::TitleFunctionT Menu_Portfolio::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Portfolio";
	};
}
r2tm::DescriptionFunctionT Menu_Portfolio::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return (
			      "  "  "주요 코드는 프로젝트의 r2bix 폴더 안에 있습니다."
			"\n"
			"\n"  "  "  "키보드 조작으로 지정된 기능이 실행됩니다."
			"\n"
			"\n"  "  "  "터미널 환경에서 게임을 만들기 위한 프레임 워크 입니다."
			"\n"  "  "  "더블버퍼링 기반의 조악한 2D 기능이 준비되어있습니다."
			"\n"  "  "  "현재 3D 와 UI 기능을 작업중입니다."
		);
	};
}
r2tm::WriteFunctionT Menu_Portfolio::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMessage( "2D 기능 테스트를 위한 2048 게임 입니다.", r2tm::eColor::FG_Yellow );
		mp->AddMessage( "https://play2048.co/", r2tm::eColor::FG_Yellow );
		mp->AddMessage( "위 사이트에서 플레이 하고 기능을 유추해 제작했습니다.", r2tm::eColor::FG_Yellow );
		mp->AddItem(
			'1'
			, []()->const char* { return p2048::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( { 107, 53, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );
				director.Setup( p2048::EntryScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				//
				// Terminate
				//
				director.Terminate();

				//
				// Clear Input
				// > 이 함수를 호출하지 않으면 _getch() 가 앞에 입력됐던 키에 반응 한다.
				// > r2tm 환경으로 돌아갔을 때 미리 입력된 키가 작동한다.
				//
				r2bix_utility::ClearCInputBuffer();

				return r2tm::eDoLeaveAction::None;
			}
		);



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMessage( "UI 기능 테스트를 위해 작업중인 Texture Editor 입니다.", r2tm::eColor::FG_Yellow );
		mp->AddMessage( "UI 기능은 Label, Button, Pannel, TextField 등이 구현되어있습니다.", r2tm::eColor::FG_Yellow );
		mp->AddItem(
			'q'
			, []()->const char* { return tool_texture_editor::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( tool_texture_editor::EntryScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				//
				// Terminate
				//
				director.Terminate();

				//
				// Clear Input
				// > 이 함수를 호출하지 않으면 _getch() 가 앞에 입력됐던 키에 반응 한다.
				// > r2tm 환경으로 돌아갔을 때 미리 입력된 키가 작동한다.
				//
				r2bix_utility::ClearCInputBuffer();

				return r2tm::eDoLeaveAction::None;
			}
		);



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMessage( "작업중인 3D 기능의 카메라 데모 입니다.", r2tm::eColor::FG_Yellow );
		mp->AddItem( 'a', test_camera_3d::Demo() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMessage( "이 프로젝트의 개발 메뉴로 이동합니다.", r2tm::eColor::FG_Yellow );
		mp->AddMenu( 32, Menu_Dev() );



		mp->AddSplit();



		mp->AddExit( 27 );
	};
}