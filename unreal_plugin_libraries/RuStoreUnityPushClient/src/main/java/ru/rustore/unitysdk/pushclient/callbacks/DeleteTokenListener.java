package ru.rustore.unitysdk.pushclient.callbacks;

public interface DeleteTokenListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess();
}