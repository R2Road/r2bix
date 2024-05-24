#include "tool_texture_editor_FileMakeNSelectScene.h"

#include "r2bix_ColorValue.h"
#include "r2bix_Director.h"

#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UISimpleButtonComponent.h"
#include "r2bix_component_UITextFieldComponent.h"

#include "r2bix_node_HollowRectNode.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_RectNode.h"
#include "r2bix_node_UIPannelNode.h"
#include "r2bix_node_UISimpleButtonNode.h"
#include "r2bix_node_UITextFieldNode.h"

#include "tool_texture_editor_EditorComponent.h"
#include "tool_texture_editor_EditorScene.h"

namespace tool_texture_editor
{
	r2bix_node::NodeUp FileMakeNSelectScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// Background
			//
			{
				auto node = ret->AddChild<r2bix_node::HollowRectNode>();
				node->mTransformComponent->SetPivotPoint( 0.f, 0.f );
				node->GetComponent<r2bix_component::HollowRectComponent>()->Set(
					  director.GetScreenSize().GetWidth()
					, director.GetScreenSize().GetHeight()
					, '#'
					, ' '
				);
			}
			//
			// Exit
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();
				component->SetCallback(
					r2bix_input::eKeyCode::VK_ESCAPE
					, [&director]( r2bix_input::eKeyStatus s )->bool
				{
					if( r2bix_input::eKeyStatus::Push == s )
					{
						director.RequestAbort();
						return true;
					}

					return false;
				}
				);
				component->Activate();
			}





			//
			// Main Menu
			//
			{
				//
				// Pannel
				//
				auto pn_node = ret->AddChild<r2bix_node::UIPannelNode>();
				{
					pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 28, 12 );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->Set( 0.f, 0.f, 50, 15 );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->mTransformComponent->SetPivotPoint( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, ' '
							, r2bix::eBackgroundColor::BG_Gray
						);
					}
				}

				//
				// Button
				//
				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, 3 );
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPivotPoint( 0.f, 0.f );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 40, 3 );
					{
						auto label_node = button_node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 20, 1 );
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "N E W" );
					}

					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i , r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto node = root->GetChildByName( "new" );
								if( node )
								{
									node->SetVisible( true );
								}

								return true;
							}
							
							return true;
						}
					);
				}

				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, 9 );
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPivotPoint( 0.f, 0.f );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 40, 3 );
					{
						auto label_node = button_node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 20, 1 );
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "O P E N" );
					}
				}
			}



			//
			// New
			//
			{
				//
				// Pannel
				//
				auto pn_node = ret->AddChild<r2bix_node::UIPannelNode>();
				pn_node->SetName( "new" );
				{
					pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 28, 12 );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->Set( 0.f, 0.f, 50, 15 );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->mTransformComponent->SetPivotPoint( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, ' '
							, r2bix::eBackgroundColor::BG_Gray
						);
					}
				}
				pn_node->SetVisible( false );

				//
				// Text Field
				//
				{
					auto node = pn_node->AddChild<r2bix_node::UITextFieldNode>();
					node->SetName( "file_name" );
					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 25, 3 );
					node->GetComponent<r2bix_component::UITextFieldComponent>()->Set( 20, "new_file~~~~~~~~~~~!" );
				}

				//
				// Generate
				//
				{
					auto node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 15, 8 );
					node->GetComponent<r2bix_component::TransformComponent>()->SetPivotPoint( 0.f, 0.f );
					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 10, 3 );
					{
						auto label_node = node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Generate" );
					}

					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i, r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto node = root->GetChildByName( "file_name" );
								if( node )
								{
									if( !node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText().empty() )
									{
										auto next_scene = tool_texture_editor::EditorScene::Create( root->GetDirector() );
										next_scene->GetComponent< tool_texture_editor::EditorComponent>()->SetFileName(
											node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText()
										);

										root->GetDirector().Setup( std::move( next_scene ) );
									}
								}

								return true;
							}

							return true;
						}
					);
				}

				//
				// Cancel
				//
				{
					auto node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 35, 8 );
					node->GetComponent<r2bix_component::TransformComponent>()->SetPivotPoint( 0.f, 0.f );
					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 10, 3 );
					{
						auto label_node = node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Cancel" );
					}

					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i, r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto node = root->GetChildByName( "new" );
								if( node )
								{
									node->SetVisible( false );
								}

								return true;
							}

							return true;
						}
					);
				}
			}
		}

		return ret;
	}
}