package ru.rustore.unitysdk.pushclient.callbacks;

public interface UnityLogListener {

    public void Log(String logString);
    public void LogWarning(String logString);
    public void LogError(String logString);
    public void LogException(Throwable throwable);
}
