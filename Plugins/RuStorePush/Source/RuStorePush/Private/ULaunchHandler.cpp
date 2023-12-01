// Copyright Epic Games, Inc. All Rights Reserved.

#include "ULaunchHandler.h"
#include "AndroidJavaClass.h"

using namespace RuStoreSDK;

bool ULaunchHandler::GetLaunchIntentHasExtra()
{
    auto clientJavaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStorePush/RuStoreLaunchHandler");
    bool bHasExtra = clientJavaClass->CallStaticBool("GetHasExtra");

    return bHasExtra;
}
