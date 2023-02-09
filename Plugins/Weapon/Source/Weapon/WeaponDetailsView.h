#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPON_API FWeaponDetailsView
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

public:
	static void OnRefresh() { RefreshByCheckBoxes = true; }
	static void OffRefresh() { RefreshByCheckBoxes = false; }

private:
	UClass* Type;

private:
	static bool RefreshByCheckBoxes;
};
