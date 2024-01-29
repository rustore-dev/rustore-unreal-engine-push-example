package ru.rustore.unitysdk.pushclient.callbacks;

public interface GetTokenListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess(String response);
}