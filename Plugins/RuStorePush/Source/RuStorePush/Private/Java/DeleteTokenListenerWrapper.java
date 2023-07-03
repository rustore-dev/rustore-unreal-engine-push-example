// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStorePush;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.unitysdk.pushclient.callbacks.DeleteTokenListener;

import android.util.Log;

public class DeleteTokenListenerWrapper implements IRuStoreListener, DeleteTokenListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer);
    private native void NativeOnFinalize(long pointer);

    public DeleteTokenListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "DeleteToken: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "DeleteToken: Success message");
                NativeOnSuccess(cppPointer);
            }
        }
    }

    @Override
    protected void finalize() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "DeleteToken: Finalize");
                NativeOnFinalize(cppPointer);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            Log.e("rustore", "FeatureAvailabilityResult: Dispose pointer");
            cppPointer = 0;
        }
    }
}
