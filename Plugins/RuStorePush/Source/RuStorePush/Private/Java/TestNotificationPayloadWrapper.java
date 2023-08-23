// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreBilling;

import java.util.HashMap;
import java.util.Map;
import ru.rustore.sdk.pushclient.messaging.model.TestNotificationPayload;

public class TestNotificationPayloadWrapper
{
    public static TestNotificationPayload CreateTestNotificationPayload(
        String title,
        String body,
        String imgUrl,
        String[] dataKeys,
        String[] dataValues
    ) {
        Map<String, String> data = new HashMap<>();

        int length = Math.min(dataKeys.length, dataValues.length);
        for (int i = 0; i < length; i++) {
            data.put(dataKeys[i], dataValues[i]);
        }

        return new TestNotificationPayload(
                title,
                body,
                imgUrl,
                data
            );
    }
}
