package ru.rustore.unreal.pushclient.callbacks;

public interface UnrealLogListener {
    void verbose(String message, Throwable throwable);
    void debug(String message, Throwable throwable);
    void info(String message, Throwable throwable);
    void warn(String message, Throwable throwable) ;
    void error(String message, Throwable throwable);
}
