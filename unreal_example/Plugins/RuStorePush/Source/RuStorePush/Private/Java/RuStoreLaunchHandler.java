// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStorePush;

import android.content.Intent;

public class RuStoreLaunchHandler
{
	private static volatile boolean bIsHasExtra = false;

	public static boolean GetHasExtra() {
		return bIsHasExtra;
	}

	public static void OnNewIntent(Intent intent) {
		if (intent != null && intent.getExtras() != null) {
			bIsHasExtra = true;
		} else {
			bIsHasExtra = false;
		}
	}
}
