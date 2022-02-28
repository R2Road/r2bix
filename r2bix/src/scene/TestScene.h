#pragma once

#include <functional>
#include <string_view>
#include <vector>

#include "base/r2base_iNode.h"

namespace r2base
{
	enum class eTestEndAction;

	class iTest;
	class Director;
}

using TestSceneUp = std::unique_ptr<class TestScene>;
class TestScene : public r2base::Node
{
private:
	struct TestInfo
	{
		TestInfo(
			const char key_code
			, const std::function<const char*( )> name_function
			, const std::function<const r2base::eTestEndAction()> test_function
		) :
			KeyCode( key_code )
			, NameFunction( name_function )
			, TestFunction( test_function )
		{}

		char KeyCode;
		std::function<const char*()> NameFunction;
		std::function<const r2base::eTestEndAction()> TestFunction;
	};

	using TestContainerT = std::vector<TestInfo>;

public:
	TestScene( r2base::Director& director, const char* title_string, const char* description_string = "" );

	//
	// Override
	//
private:
	bool Init() override;
public:
	void Update() override;

private:
	void ShowInformation() const;
	void showTitle() const;
	void showDescription() const;
	void showMenu() const;

	r2base::eTestEndAction RunTest( const int key_code );

public:
	void AddChild( const char key_code, r2base::iTest& test_obj );
	void AddChild( const char key_code, const std::function<const char*( )> func_title, const std::function<const r2base::eTestEndAction()> func_test );
	void AddLineFeed();
	void AddSplit();

protected:
	std::string_view mTitleString;
	std::string_view mDescriptionString;

	TestContainerT mTests;
};