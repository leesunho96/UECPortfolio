#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class WEAPON_API FWeaponCommand
	: public TCommands<FWeaponCommand>
{
public:
	FWeaponCommand();
	~FWeaponCommand();

	void RegisterCommands() override;

public:
	void Startup();

private:
	void ToolBar_Added(FToolBarBuilder& InBuilder);
	void ToolBar_Button_Clicked();

public:
	TSharedPtr<FExtender> Extender;

	TSharedPtr<FUICommandInfo> Id;
	TSharedPtr<FUICommandList> Command;
};
