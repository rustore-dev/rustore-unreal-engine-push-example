package ru.rustore.unitysdk.pushclient.wrappers;

import ru.rustore.unitysdk.core.IRuStoreListener;
import ru.rustore.unitysdk.pushclient.callbacks.SendTestNotificationListener;

public class SendTestNotificationListenerWrapper implements IRuStoreListener, SendTestNotificationListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer);
    private native void NativeOnFinalize(long pointer);

    public SendTestNotificationListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnSuccess(cppPointer);
            }
        }
    }

    @Override
    protected void finalize() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnFinalize(cppPointer);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
