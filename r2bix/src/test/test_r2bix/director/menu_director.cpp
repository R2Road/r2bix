#include "menu_director.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test/test_r2bix/menu_r2bix.h"

#include "test_director__screen_buffer_manager.h"
#include "test_director__defarred_task_queue.h"
#include "test_director__scheduler.h"

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_InputKeyboardComponent.h"
#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_LabelSNode.h"
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
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_director__screen_buffer_manager::Swap() );


		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'q', director_scheduler_test::Declaration() );
		mp->AddItem( 'w', director_defarred_task_queue_test::Declaration() );
		mp->AddItem( 'e', director_defarred_task_queue_test::Size() );
		mp->AddItem( 'r', director_defarred_task_queue_test::Add() );
		mp->AddItem( 't', director_defarred_task_queue_test::Process() );
		mp->AddItem( 'y', director_defarred_task_queue_test::TaskBringsTask() );


		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem(
			  32
			, []()->const char* { return "Director Test Scene"; }
			, []()->r2tm::eDoLeaveAction
		{
			r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

			
			r2bix_node::Node* root_node;
			{
				//
				// Scene
				//
				auto temp = r2bix_node::Node::Create( director );
				root_node = temp.get();

				director.Setup( std::move( temp ) );



				//
				// Background
				//
				{
					auto node = root_node->AddChild<r2bix_node::CustomTextureNode>();
					node->mTransformComponent->SetPivot( 0.f, 0.f );
					node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
				}



				//
				// Label
				//
				auto label_node = root_node->AddChild<r2bix_node::LabelSNode>();
				{
					label_node->mTransformComponent->SetPosition( 2, 2 );
					label_node->mTransformComponent->SetPivot( 0.f, 0.f );
					label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Label Node" );
				}



				//
				// Input
				//
				auto input_component = root_node->AddComponent<r2bix_component::InputKeyboardComponent>();
				{
					//
					// ESC
					//
					input_component->SetCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
					{
						director.RequestAbort();

						return true;
					} );

					//
					// A
					//
					input_component->SetCallback( r2bix_input::eKeyCode::VK_A, [&director, label_node]( r2bix_input::eKeyStatus s )->bool
					{
						if( r2bix_input::eKeyStatus::Push == s )
						{
							std::string str = director.StartTextInputMode( 10, 10, 5 );

							label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( str );
						}

						return true;
					} );

					input_component->Activate();
				}
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


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}