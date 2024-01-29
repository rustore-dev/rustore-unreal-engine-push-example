package ru.rustore.unitysdk.pushclient

import android.util.Log
import ru.rustore.sdk.pushclient.common.logger.Logger

class UnityLogger (
    private val tag: String? = null,
) : Logger {

    override fun verbose(message: String, throwable: Throwable?) {
        Log.v(tag, message, throwable)
        RuStoreUnityPushClient.Log("[V] $tag $message");
        logException(throwable)
    }

    override fun debug(message: String, throwable: Throwable?) {
        Log.d(tag, message, throwable)
        RuStoreUnityPushClient.Log("[D] $tag $message");
        logException(throwable)
    }

    override fun info(message: String, throwable: Throwable?) {
        Log.i(tag, message, throwable)
        RuStoreUnityPushClient.Log("[I] $tag $message");
        logException(throwable)
    }

    override fun warn(message: String, throwable: Throwable?) {
        Log.w(tag, message, throwable)
        RuStoreUnityPushClient.LogWarning("[W] $tag $message");
        logException(throwable)
    }

    override fun error(message: String, throwable: Throwable?) {
        Log.e(tag, message, throwable)
        RuStoreUnityPushClient.LogError("[E] $tag $message");
        logException(throwable)
    }

    private fun logException(throwable: Throwable?) {
        if (throwable != null) {
            RuStoreUnityPushClient.LogException(throwable)
        }
    }

    override fun createLogger(tag: String): Logger {
        val newTag = if (this.tag != null) {
            "${this.tag}:$tag"
        } else {
            tag
        }
        return UnityLogger(newTag)
    }
}
