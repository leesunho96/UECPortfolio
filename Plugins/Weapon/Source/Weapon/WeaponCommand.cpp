#include "WeaponCommand.h"
#include "WeaponStyle.h"
#include "LevelEditor.h"
#include "Modules/ModuleManager.h"

#include "WeaponAssetEditor.h"

FWeaponCommand::FWeaponCommand()
	: TCommands("Weapon", FText::FromString("Weapon Asset Editor"), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

void FWeaponCommand::Startup()
{
	FWeaponCommand::RegisterCommands();

	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolbar = FToolBarExtensionDelegate::CreateRaw(this, &FWeaponCommand::ToolBar_Added);
	Extender->AddToolBarExtension("Settings", EExtensionHook::After, Command, toolbar);

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

FWeaponCommand::~FWeaponCommand()
{
	if (Command.IsValid())
		Command.Reset();

	if (Extender.IsValid())
		Extender.Reset();
}

void FWeaponCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(Id, "Weapon", "Weapon Asset Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	Command->MapAction(Id, FExecuteAction::CreateRaw(this, &FWeaponCommand::ToolBar_Button_Clicked), FCanExecuteAction());
}

void FWeaponCommand::ToolBar_Added(FToolBarBuilder& InBuilder)
{
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton(Id, NAME_None, FText::FromString("Weapon"), FText::FromString("Weapon Asset Editor"), FWeaponStyle::Get()->ToolBar_Icon, NAME_None);
}

void FWeaponCommand::ToolBar_Button_Clicked()
{
	FWeaponAssetEditor::OpenWindow();
}