#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class RapidjsonMenu
{
private:
	RapidjsonMenu() = delete;

public:
	static const char* GetTitle() { return "Rapidjson Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};