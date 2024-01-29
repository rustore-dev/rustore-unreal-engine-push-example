package ru.rustore.unitysdk.pushclient.callbacks;

public interface SubscribeTopicListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess();
}