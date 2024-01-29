// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStorePush;

import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import com.Plugins.RuStorePush.RuStoreLaunchHandler;

public class RuStorePushActivity extends AppCompatActivity {

    private static final String ue4 = "com.epicgames.ue4.GameActivity";
    private static final String ue5 = "com.epicgames.unreal.GameActivity";

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Class<?> gameActivityClass = null;
        try {
            gameActivityClass = Class.forName(ue4);
        } catch (ClassNotFoundException ex1)
        {
            try {
                gameActivityClass = Class.forName(ue5);
            } catch (ClassNotFoundException ex2) { }
        }

        if (gameActivityClass != null)
        {
            RuStoreLaunchHandler.OnNewIntent(getIntent());

            Intent newIntent = new Intent(this, gameActivityClass);
            startActivity(newIntent);
        }

        finish();
    }
}
