#pragma once

namespace psnake
{

	//
	// 2022.05.06 by R
	//
	// �������� �ʰ� ��̰� �۾��� �̾�� �� �ֵ��� ��� ����� ������ ��.
	//

	static struct
	{

		const char VersionNumber_1 = '0';
		const char VersionNumber_2 = '0';
		const char VersionNumber_3 = '0';

		const char String4Version[20] = { 'S', 'n', 'a', 'k',  'e', 'S', 'n', 'a', 'k',  'e', ' ', ':', ' ', 'v', VersionNumber_1, '.', VersionNumber_2, '.', VersionNumber_3, '\0' };

		const char* const String4Road2Version_0_0_1 =
					"### Road 2 Version 0.0.1 ###"
			"\n"
			"\n"	"[ ] " "Stage : Field"
			"\n"	"[ ] " "Snake : View - Dot"
			"\n"	"[ ] " "Snake : Move - with W A S D"
			"\n"	"[ ] " "Item : Growth Up"
			"\n"	"[ ] " "Snake : Growth"
		;

	} VersionInfo;
}