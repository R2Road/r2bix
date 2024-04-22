#pragma once

namespace projecta
{

	//
	// 2024.04.22 by R
	//
	// 무리하지 않고 즐겁게 작업을 이어나갈 수 있도록 모든 방안을 강구할 것.
	//

	static struct
	{

		const char VersionNumber_1 = '0';
		const char VersionNumber_2 = '0';
		const char VersionNumber_3 = '0';

		const char String4Version[14] = { 'P', 'r', 'o', 'j',  'e', 'c', 't', 'A', VersionNumber_1, '.', VersionNumber_2, '.', VersionNumber_3, '\0' };

		const char* const String4Road2Version_0_0_1 =
					"### Road 2 Version 0.0.1 ###"
			"\n"
			"\n"	"[ ] " "Stage : Field"
		;

	} VersionInfo;
}