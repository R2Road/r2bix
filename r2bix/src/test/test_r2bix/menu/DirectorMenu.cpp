#include "DirectorMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "../item/console_screen_buffer_test.h"
#include "../item/screen_buffer_manager_test.h"
#include "../item/director_defarred_task_queue_test.h"
#include "../item/director_scheduler_test.h"

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_InputKeyboardComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_utility_InputUtil.h"

r2tm::TitleFunctionT DirectorMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Director";
	};
}
r2tm::DescriptionFunctionT DirectorMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT DirectorMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', console_screen_buffer_test::Basic() );
		ret->AddItem( '2', screen_buffer_manager_test::Swap() );
		ret->AddItem( '3', screen_buffer_manager_test::OriginalBuffer() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'q', director_scheduler_test::Declaration() );
		ret->AddItem( 'w', director_defarred_task_queue_test::Declaration() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem(
			  32
			, []()->const char* { return "Director Test Scene"; }
			, []()->r2tm::eDoLeaveAction
		{
			r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

			//
			// Scene
			//
			r2bix_node::Node* root_node;
			{
				auto temp = r2bix_node::Node::Create( director );
				root_node = temp.get();

				director.Setup( std::move( temp ) );

				auto input_component = root_node->AddComponent<r2bix_component::InputKeyboardComponent>();

				//
				// ESC
				//
				input_component->SetCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
				{
					director.RequestAbort();
					r2bix_utility::ClearCInputBuffer();

					return true;
				} );

				//
				// A
				//
				input_component->SetCallback( r2bix_input::eKeyCode::VK_A, [&director]( r2bix_input::eKeyStatus )->bool
				{
					director.StartInputMode();

					return true;
				} );
				//
				// S
				//
				input_component->SetCallback( r2bix_input::eKeyCode::VK_S, [&director]( r2bix_input::eKeyStatus )->bool
				{
					director.EndInputMode();

					return true;
				} );

				input_component->Activate();
			}

			//
			// Background
			//
			{
				auto node = root_node->AddChild<r2bix_node::CustomTextureNode>();
				node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
				node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			}

			//
			// Process
			//
			director.Run();

			//
			// Terminate
			//
			director.Terminate();

			return r2tm::eDoLeaveAction::None;
		} );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}