#pragma once

namespace r2bix
{

	//
	// 2022.05.06 by R
	//
	// �������� �ʰ� ��̰� �۾��� �̾�� �� �ֵ��� ��� ����� ������ ��.
	//

	static struct
	{

		const char* const String4VersionRule =
					"### Version Rule ###"
			"\n"
			"\n"	"> " "1.0.0.0.0"  " : "  "�ϼ�?"
			"\n"	"> " "0.1.0.0.0"  " : "  "Road �Ϸ�"
			"\n"	"> " "0.0.1.0.0"  " : "  "Road �۾� ��� 1�� �Ϸ�"
			"\n"	"> " "0.0.0.1.0"  " : "  "���� ����.���� ��� ����"
			"\n"	"> " "0.0.0.0.1"  " : "  "����ڰ� ���� ������ ���� �Ǵ� ��ȭ"
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
			"\n"	"[o] " "Texture : Color : �� ���ڿ� ����, ���� ���� ����"
			"\n"	"[o] " "Texture : Character : ���� ��ȿ��. ���ۿ� ���ڸ� ������� ����"
			"\n"	"[o] " "Render : Color Mask : ����� ������ ���� ��ȿ�� ó��."
			"\n"	"[o] " "Render : Color Blend"
			"\n"	"[o] " "Audio : ���̺귯�� ���� �� �׽�Ʈ( ���, �ߴ� ���� �⺻ ���� )"
			"\n"	"[o] " "Split The Render And Update Process"
			"\n"	"[o] " "Scheduler : r2bix::Director�� r2::FPSTimer �� std::this_thread::sleep_for( CPU ��뷮 ���� ) ���� ����"
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