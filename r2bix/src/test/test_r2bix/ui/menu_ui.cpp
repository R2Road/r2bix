#include "menu_ui.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "r2bix/r2bix_Director.h"

#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_InputKeyboardComponent.h"
#include "r2bix/r2bix_component_RectComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_component_UIControlComponent.h"
#include "r2bix/r2bix_component_UIPannelComponent.h"
#include "r2bix/r2bix_component_UISimpleButtonComponent.h"
#include "r2bix/r2bix_component_UITextFieldComponent.h"

#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_RectNode.h"
#include "r2bix/r2bix_node_UIPannelNode.h"
#include "r2bix/r2bix_node_UISimpleButtonNode.h"
#include "r2bix/r2bix_node_UITextFieldNode.h"

#include "../menu_r2bix.h"

r2tm::TitleFunctionT UIMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "UI";
	};
}
r2tm::DescriptionFunctionT UIMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT UIMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
			mp->AddItem(
				32
				, []()->const char* { return "UI Test Scene"; }
				, []()->r2tm::eDoLeaveAction
				{
					r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

					//
					// Scene
					//
					r2bix_node::Node* scene;
					{
						auto temp = r2bix_node::Node::Create( director );
						scene = temp.get();

						director.Setup( std::move( temp ) );

						auto input_component = scene->AddComponent<r2bix_component::InputKeyboardComponent>();
						input_component->SetCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
						{
							director.RequestAbort();

							return false;
						} );

						input_component->Activate();
					}

					//
					// Background
					//
					{
						auto node = scene->AddChild<r2bix_node::CustomTextureNode>();
						node->mTransformComponent->SetPivot( 0.f, 0.f );
						node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 51, 51, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
					}

					//
					// Test
					//
					r2bix_component::UIControlComponent::Slot4CursorResponseT slot_cursor_response;
					r2bix_component::UIControlComponent::Slot4KeyResponseT slot_key_response;
					{
						//
						// Pannel
						//
						auto pn_node = scene->AddChild<r2bix_node::UIPannelNode>();
						{
							pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 15, 12 );
							pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 23, 15 );
							{
								auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
								rect_node->mTransformComponent->SetPivot( 0.5f, 0.5f );
								rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
									  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
									, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
									, "Pannel "
								);
							}
						}


						//
						// Text Field
						//
						{
							auto text_field_node = pn_node->AddChild<r2bix_node::UITextFieldNode>();
							text_field_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, -3 );
							text_field_node->GetComponent<r2bix_component::TransformComponent>()->SetPivot( 1.f, 1.f );
							text_field_node->GetComponent<r2bix_component::UITextFieldComponent>()->Set( 20, "ui    text    field~~!");
							{
								auto custom_texture_component = text_field_node->GetComponent<r2bix_component::CustomTextureComponent>();

								slot_cursor_response.SetCallback( [custom_texture_component]( r2bix_ui::eCursorStatus s )->bool
								{
									switch( s )
									{
									case r2bix_ui::eCursorStatus::CursorOver:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
										break;
									case r2bix_ui::eCursorStatus::CursorMove:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
										break;
									case r2bix_ui::eCursorStatus::CursorLeave:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
										break;
									}

									return false;
								} );
								text_field_node->GetComponent<r2bix_component::UIControlComponent>()->ConnectSlot4CursorResponse( &slot_cursor_response );

								slot_key_response.SetCallback( [custom_texture_component]( int, r2bix_ui::eKeyStatus s )->bool
								{
									switch( s )
									{
									case r2bix_ui::eKeyStatus::Push:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightAqua );
										break;
									case r2bix_ui::eKeyStatus::Pressed:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightYellow );
										break;
									case r2bix_ui::eKeyStatus::Release:
										custom_texture_component->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightPurple );
										break;
									}

									return false;
								} );
								text_field_node->GetComponent<r2bix_component::UIControlComponent>()->ConnectSlot4KeyResponse( &slot_key_response );
							}
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
				}
			);



		mp->AddSplit();



		mp->AddMenu( 27, Menu_R2bix() );
	};
}