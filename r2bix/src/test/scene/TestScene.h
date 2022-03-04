#pragma once

#include <functional>
#include <string_view>
#include <vector>

#include "node/r2node_SceneNode.h"

namespace r2base
{
	class Director;
}

namespace r2test
{
	enum class eTestEndAction;
	class iTest_Deprecated;
}

using TestSceneUp = std::unique_ptr<class TestScene>;
class TestScene : public r2node::SceneNode
{
private:
	struct TestInfo
	{
		TestInfo(
			const char key_code
			, const std::function<const char*()> name_function
			, const std::function<const r2test::eTestEndAction( r2base::Director& )> test_function
		) :
			KeyCode( key_code )
			, NameFunction( name_function )
			, TestFunction( test_function )
		{}

		char KeyCode;
		std::function<const char*()> NameFunction;
		std::function<const r2test::eTestEndAction( r2base::Director& )> TestFunction;
	};

	using TestContainerT = std::vector<TestInfo>;

public:
	TestScene( r2base::Director& director, const char* title_string, const char* description_string = "" );

	//
	// Override
	//
public:
	void Update() override;

private:
	void ShowInformation() const;
	void showTitle() const;
	void showDescription() const;
	void showMenu() const;

	r2test::eTestEndAction RunTest( const int key_code );

public:
	void AddChild( const char key_code, r2test::iTest_Deprecated& test_obj );
	void AddChild( const char key_code, const std::function<const char*( )> func_title, const std::function<const r2test::eTestEndAction( r2base::Director& )> func_test );
	void AddLineFeed();
	void AddSplit();

protected:
	std::string_view mTitleString;
	std::string_view mDescriptionString;

	TestContainerT mTests;
};