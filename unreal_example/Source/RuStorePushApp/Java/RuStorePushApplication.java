// Copyright Epic Games, Inc. All Rights Reserved.

package com.example.RuStorePushApp;

import android.util.Log;
import com.epicgames.ue4.GameApplication;
import ru.rustore.unreal.pushclient.RuStoreUnrealLoggerMode;
import ru.rustore.unreal.pushclient.RuStoreUnrealPushClient;
import ru.rustore.unreal.pushclient.UnrealClientIdType;

public class RuStorePushApplication extends GameApplication {

	private final String PROJECT_ID ="-Yv4b5cM2yfXm0bZyY6Rk7AHX8SrHmLI";
	//private final String PROJECT_ID ="6RUviJhYqgNXDXAIL5wqkAP1Rdnd4JmY";

	@Override
	public void onCreate() {
		super.onCreate();

		RuStoreUnrealPushClient.INSTANCE.init(
            this,
            PROJECT_ID,
			RuStoreUnrealLoggerMode.CUSTOM,
			null,
			null
        );
	}
}
