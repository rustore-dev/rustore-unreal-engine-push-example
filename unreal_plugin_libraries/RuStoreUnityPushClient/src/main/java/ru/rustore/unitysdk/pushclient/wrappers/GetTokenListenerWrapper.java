package ru.rustore.unitysdk.pushclient.wrappers;

import ru.rustore.unitysdk.core.IRuStoreListener;
import ru.rustore.unitysdk.pushclient.callbacks.GetTokenListener;

public class GetTokenListenerWrapper implements IRuStoreListener, GetTokenListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, String response);
    private native void NativeOnFinalize(long pointer);

    public GetTokenListenerWrapper(long cppPointer) {
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
    public void OnSuccess(String response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnSuccess(cppPointer, response);
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
