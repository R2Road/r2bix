#pragma once

namespace r2bix
{

	//
	// 2022.05.06 by R
	//
	// 무리하지 않고 즐겁게 작업을 이어나갈 수 있도록 모든 방안을 강구할 것.
	//

	static struct
	{

		const char* const String4VersionRule =
					"### Version Rule ###"
			"\n"
			"\n"	"> " "1.0.0.0.0"  " : "  "완성?"
			"\n"	"> " "0.1.0.0.0"  " : "  "Road 완료"
			"\n"	"> " "0.0.1.0.0"  " : "  "Road 작업 목록 1개 완료"
			"\n"	"> " "0.0.0.1.0"  " : "  "버그 수정.기존 기능 개선"
			"\n"	"> " "0.0.0.0.1"  " : "  "사용자가 변경 사항을 몰라도 되는 변화"
		;



		const char VersionNumber_1 = '0';
		const char VersionNumber_2 = '2';
		const char VersionNumber_3 = '1';
		const char VersionNumber_4 = '0';
		const char VersionNumber_5 = '0';

		const char String4Version[19] = { 'r', '2', 'b', 'i', 'x', ' ', ':', ' ', 'v', VersionNumber_1, '.', VersionNumber_2, '.', VersionNumber_3, '.', VersionNumber_4, '.', VersionNumber_5, '\0' };



		const char* const String4Road2Version_0_3_0_0_0 =
					"### Road 2 Version 0.3.0.0.0 ###"
			"\n"
			"\n"	"+ " "System"
			"\n"	"\t"	"> "	"Director"
			"\n"	"\t"	"\t"	"[o] " "Add : Deffard Task Queue"
			"\n"	"\t"	"> "	"Input"
			"\n"	"\t"	"\t"	"[~] " "Keyboard"
			"\n"	"\t"	"\t"	"[~] " "Mouse"
			"\n"	"+ " "Preset Node"
			"\n"	"\t"	"> "	"UI"
			"\n"	"\t"	"\t"	"[o] " "Add : UIButtonNode"
			"\n"	"\t"	"\t"	"[o] " "Add : UIPannelNode"
			"\n"	"\t"	"\t"	"[o] " "Add : UITextFieldNode"
			"\n"	"\t"	"\t"	"[o] " "Add : UISimpleButtonNode"
			"\n"	"\t"	"> "	"Node"
			"\n"	"\t"	"\t"	"[o] " "Add : RectNode"
			"\n"	"\t"	"\t"	"[o] " "Add : HollowRectNode"
			"\n"	"+ " "Tool"
			"\n"	"\t"	"> "	"Texture Editor"
			"\n"	"\t"	"\t"	"[~] " "Add"
			"\n"	"\t"	"> "	"Texture Viewer"
			"\n"	"\t"	"\t"	"[ ] " "Add"
			"\n"	"+ " "ETC"
			"\n"	"\t"	"> "	"Json"
			"\n"	"\t"	"\t"	"[o] " "Import : RapidJson"

			//"\n\n"	"------------------------------------------" "\n"

			//"\n"	"[ ] " "FSM"
			//"\n"	"[ ] " "B-Tree"
			//"\n"	"[ ] " "Node Delete And Caching Pipe Line"
			//"\n"	"[ ] " "Split Scene Graph Struct And Update Process"
			//"\n"	"[ ] " "Make Simple Texture Adventure"
			//"\n"	"[ ] " "Script"
			//"\n"	"[ ] " "Korean"
			//"\n"	"[ ] " "Audio : Pre Load"
		;

		const char* const String4Road2Version_0_0_2_0 =
					"### Road 2 Version 0.0.2.0 ###"
			"\n"
			"\n"	"[o] " "Texture : Color : 각 문자에 전경, 원경 색상 지정"
			"\n"	"[o] " "Texture : Character : 글자 유효성. 버퍼에 글자를 기록할지 여부"
			"\n"	"[o] " "Render : Color Mask : 전경과 원경의 색상 유효성 처리."
			"\n"	"[o] " "Render : Color Blend"
			"\n"	"[o] " "Audio : 라이브러리 선택 및 테스트( 재생, 중단 등의 기본 사항 )"
			"\n"	"[o] " "Split The Render And Update Process"
			"\n"	"[o] " "Scheduler : r2bix::Director에 r2::FPSTimer 와 std::this_thread::sleep_for( CPU 사용량 감소 ) 선택 적용"
		;

		const char* const String4Road2Version_0_0_1_0 =
					"### Road 2 Version 0.0.1.0 ###"
			"\n"
			"\n"	"[o] " "Double Buffering"
			"\n"	"[o] " "Input"
			"\n"	"[o] " "Render Pipe Line"
			"\n"	"[o] " "Scene Node"
			"\n"	"[o] " "Component"
			"\n"	"[o] " "Make Simple Puzzle Game"
		;



		const char* const String4Road2NextVersion = String4Road2Version_0_3_0_0_0;

	} VersionInfo;
}