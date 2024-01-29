package ru.rustore.unitysdk.pushclient.wrappers;

import ru.rustore.unitysdk.core.IRuStoreListener;
import ru.rustore.unitysdk.pushclient.callbacks.UnityLogListener;

public class LogListenerWrapper implements IRuStoreListener, UnityLogListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeLog(long pointer, String logString);
    private native void NativeLogWarning(long pointer, String logString);
    private native void NativeLogError(long pointer, String logString);
    private native void NativeLogException(long pointer, Throwable throwable);

    public LogListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void Log(String logString) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLog(cppPointer, logString);
            }
        }
    }

    @Override
    public void LogWarning(String logString) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogWarning(cppPointer, logString);
            }
        }
    }

    @Override
    public void LogError(String logString) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogError(cppPointer, logString);
            }
        }
    }

    @Override
    public void LogException(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogException(cppPointer, throwable);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
