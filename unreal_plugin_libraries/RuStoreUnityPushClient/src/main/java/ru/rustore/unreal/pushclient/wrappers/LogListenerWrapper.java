package ru.rustore.unreal.pushclient.wrappers;

import ru.rustore.unitysdk.core.IRuStoreListener;
import ru.rustore.unreal.pushclient.callbacks.UnrealLogListener;

public class LogListenerWrapper implements IRuStoreListener, UnrealLogListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeLogVerbose(long pointer, String message, Throwable throwable);
    private native void NativeLogDebug(long pointer, String message, Throwable throwable);
    private native void NativeLogInfo(long pointer, String message, Throwable throwable);
    private native void NativeLogWarn(long pointer, String message, Throwable throwable) ;
    private native void NativeLogError(long pointer, String message, Throwable throwable);

    public LogListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    private Throwable throwable(Throwable throwable) {
        return throwable != null? throwable : new Throwable();
    }

    @Override
    public void verbose(String message, Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogVerbose(cppPointer, message, throwable(throwable));
            }
        }
    }

    @Override
    public void debug(String message, Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogDebug(cppPointer, message, throwable(throwable));
            }
        }
    }

    @Override
    public void info(String message, Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogInfo(cppPointer, message, throwable(throwable));
            }
        }
    }

    @Override
    public void warn(String message, Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogWarn(cppPointer, message, throwable(throwable));
            }
        }
    }

    @Override
    public void error(String message, Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeLogError(cppPointer, message, throwable(throwable));
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
