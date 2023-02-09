#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

struct FWeaponRowData
{
	int Index;
	FString Context;
	class UCWeaponAsset* Asset;

	FWeaponRowData()
	{

	}

	FWeaponRowData(int32 InIndex, FString InContext, class UCWeaponAsset* InAsset)
	{
		Index = InIndex;
		Context = InContext;
		Asset = InAsset;
	}

	static TSharedPtr<FWeaponRowData> Make(int32 InIndex, FString InContext, class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InIndex, InContext, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr;

///////////////////////////////////////////////////////////////////////////////

typedef SListView<FWeaponRowDataPtr> SWeaponListViewRow;

class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
{
public:
	SLATE_BEGIN_ARGS(SWeaponTableRow){}
	SLATE_ARGUMENT(FWeaponRowDataPtr, Row)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);

protected:
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Row;
};

///////////////////////////////////////////////////////////////////////////////

DECLARE_DELEGATE_OneParam(FOnWeaponListViewSelectedItem, FWeaponRowDataPtr);

class WEAPON_API SWeaponListView
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponListView) {}
	SLATE_EVENT(FOnWeaponListViewSelectedItem, OnWeaponListViewSelectedItem)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

public:
	bool HasDataPtrs() { return RowDatas.Num() > 0; }
	
	FWeaponRowDataPtr GetRowDataPtrByName(FString InName);
	FWeaponRowDataPtr GetFirstDataPtr() { return RowDatas[0]; }

	void SelectDataPtr(class UCWeaponAsset* InAsset);
	FString SelectedRowDataPtrName();

private:
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable);

	FText GetAssetCount() const;

	void OnTextChanged(const FText& InText);
	void OnTextCommitted(const FText& InText, ETextCommit::Type InType);

	void OnSelectionChanged(FWeaponRowDataPtr InPtr, ESelectInfo::Type InType);

private:
	void ReadAssets();

private:
	FOnWeaponListViewSelectedItem OnWeaponListViewSelectedItem;

private:
	TArray<FWeaponRowDataPtr> RowDatas;
	TSharedPtr<SWeaponListViewRow> ListView;

	FText SearchText;
	TSharedPtr<SSearchBox> SearchBox;
};
