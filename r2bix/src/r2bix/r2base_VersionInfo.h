#pragma once

namespace r2base
{

	//
	// 2022.05.06 by R
	//
	// 무리하지 않고 즐겁게 작업을 이어나갈 수 있도록 모든 방안을 강구할 것.
	//

	struct
	{
		const char VersionNumber_1 = 0;
		const char VersionNumber_2 = 0;
		const char VersionNumber_3 = 1;

		const char* const String4Version_0_0_1 =
					"### Road 2 Version 0.0.1 ###"
			"\n\n"	"[o] " "Double Buffering"
			"\n"	"[o] " "Input"
			"\n"	"[o] " "Render Pipe Line"
			"\n"	"[o] " "Scene Node"
			"\n"	"[o] " "Component"
			"\n"	"[o] " "Make Simple Puzzle Game"
		;

		const char* const String4Version_0_0_2 =
					"### Road 2 Version 0.0.2 ###"
			"\n\n"	"[ ] " "Split The Render And Update Process"
			"\n"	"[ ] " "Audio"
			"\n"	"[ ] " "Node Delete And Caching Pipe Line"
			"\n"	"[ ] " "Texture Viewer"
			"\n"	"[ ] " "Texture Editor"
			"\n"	"[ ] " "Color"
			"\n"	"[ ] " "Korean"

			"\n\n"	"------------------------------------------"

			"\n\n"	"[ ] " "Json"
			"\n"	"[ ] " "Script"
		;
	} VersionInfo;
}