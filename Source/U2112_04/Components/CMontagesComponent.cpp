#include "Components/CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

//#define LOG_UCMontagesComponent 1

UCMontagesComponent::UCMontagesComponent()
{
	
}

void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(DataTable);

	Owner = Cast<ACharacter>(GetOwner());


	TArray<FMontagesData*> datas;
	DataTable->GetAllRows<FMontagesData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontagesData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}//for(data)
	}

#if LOG_UCMontagesComponent
	for (FMontagesData* data : Datas)
	{
		if (data == nullptr)
			continue;

		FString str;
		str.Append(StaticEnum<EStateType>()->GetValueAsString(data->Type));
		str.Append(" / ");
		str.Append(data->Montage->GetPathName());
		CLog::Log(str);
	}
#endif
}

void UCMontagesComponent::PlayDeadMode()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	CheckNull(Owner);

	FMontagesData* data = Datas[(int32)InType];
	if (!!data && !!data->Montage)
		Owner->PlayAnimMontage(data->Montage, data->PlayRatio);
}