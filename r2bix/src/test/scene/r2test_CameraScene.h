#pragma once

#include <memory>

namespace r2test
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class CameraMenu
{
private:
	CameraMenu() = delete;

public:
	static const char* GetTitle() { return "Camera"; }
	static r2test::MenuUp Create( r2test::Director& director );
};