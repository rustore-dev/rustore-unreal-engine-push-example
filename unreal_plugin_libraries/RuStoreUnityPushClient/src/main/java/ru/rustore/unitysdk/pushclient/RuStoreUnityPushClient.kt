package ru.rustore.unitysdk.pushclient

import android.app.Application
import com.vk.push.common.clientid.ClientId
import com.vk.push.common.clientid.ClientIdCallback
import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult
import ru.rustore.sdk.core.tasks.OnCompleteListener
import ru.rustore.sdk.pushclient.RuStorePushClient
import ru.rustore.sdk.pushclient.messaging.exception.RuStorePushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.messaging.model.TestNotificationPayload
import ru.rustore.sdk.pushclient.utils.resolveForPush
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener
import ru.rustore.unitysdk.pushclient.callbacks.DeleteTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.GetTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.SendTestNotificationListener
import ru.rustore.unitysdk.pushclient.callbacks.SubscribeTopicListener
import ru.rustore.unitysdk.pushclient.callbacks.UnityLogListener

object RuStoreUnityPushClient : UnityLogListener  {

	private var allowErrorHandling: Boolean = false
	private var serviceListener: RuStoreUnityMessagingServiceListener? = null

	private var messages: MutableList<RemoteMessage> = ArrayList()
	private var errors: MutableList<RuStorePushClientException> = ArrayList()

	private var logListener: UnityLogListener? = null

	private var isTestModeEnabled = false

	@JvmStatic
	fun runInTestMode() {
		isTestModeEnabled = true
	}

	fun setErrorHandling(allowErrorHandling: Boolean) {
		this.allowErrorHandling = allowErrorHandling
	}

	fun getErrorHandling() : Boolean {
		return allowErrorHandling
	}

	fun setListener(listener: RuStoreUnityMessagingServiceListener?) {
		this.serviceListener = listener
	}

	fun init(allowNativeErrorHandling: Boolean, serviceListener: RuStoreUnityMessagingServiceListener?, logListener: UnityLogListener?) {
		this.allowErrorHandling = allowNativeErrorHandling

		this.serviceListener = serviceListener
		this.logListener = logListener

		if (messages.isNotEmpty()) {
			messages.forEach {
				serviceListener?.OnMessageReceived(it)
			}
			messages.clear()
		}

		if (errors.isNotEmpty()) {
			serviceListener?.OnError(errors)
			errors.clear()
		}
	}

	fun checkPushAvailability(listener: FeatureAvailabilityListener) {
		RuStorePushClient.checkPushAvailability()
			.addOnCompleteListener(object : OnCompleteListener<FeatureAvailabilityResult> {
				override fun onFailure(throwable: Throwable) {
					handleError(throwable)
					listener.OnFailure(throwable)
				}

				override fun onSuccess(result: FeatureAvailabilityResult) {
					listener.OnSuccess(result)
				}
			})
	}

	fun getToken(listener: GetTokenListener) {
		RuStorePushClient.getToken().addOnCompleteListener(object : OnCompleteListener<String> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: String) {
				listener.OnSuccess(result)
			}
		})
	}

	fun deleteToken(listener: DeleteTokenListener) {
		RuStorePushClient.deleteToken().addOnCompleteListener(object : OnCompleteListener<Unit> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: Unit) {
				listener.OnSuccess()
			}
		})
	}

	fun subscribeToTopic(topicName: String, listener: SubscribeTopicListener) {
		RuStorePushClient.subscribeToTopic(topicName).addOnCompleteListener(object : OnCompleteListener<Unit> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: Unit) {
				listener.OnSuccess()
			}
		})
	}

	fun unsubscribeFromTopic(topicName: String, listener: SubscribeTopicListener) {
		RuStorePushClient.unsubscribeFromTopic(topicName).addOnCompleteListener(object : OnCompleteListener<Unit> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: Unit) {
				listener.OnSuccess()
			}
		})
	}

	fun sendTestNotification(testNotificationPayload: TestNotificationPayload, listener: SendTestNotificationListener) {
		if (isTestModeEnabled) {
			RuStorePushClient.sendTestNotification(testNotificationPayload).addOnCompleteListener(object : OnCompleteListener<Unit> {
				override fun onFailure(throwable: Throwable) {
					handleError(throwable)
					listener.OnFailure(throwable)
				}

				override fun onSuccess(result: Unit) {
					listener.OnSuccess()
				}
			})
		}
	}

	fun onNewToken(token: String) {
		serviceListener?.OnNewToken(token)
	}

	fun onMessageReceived(message: RemoteMessage) {
		if (serviceListener == null) {
			messages.add(message)
		}
		serviceListener?.OnMessageReceived(message)
	}

	fun onDeletedMessages() {
		serviceListener?.OnDeletedMessages()
	}

	fun onError(errors: List<RuStorePushClientException>) {
		if (serviceListener == null){
			this.errors.addAll(errors)
		}
		serviceListener?.OnError(errors)
	}

	@JvmStatic
	fun init(projectId: String, metricType: String, clientIdType: String?, clientIdValue: String?) {
		val clientIdCallback = clientIdType?.let {
			ClientIdCallback {
				EnumConverter.getClientIdTypeFromString(clientIdType)?.let { type ->
					ClientId(
						clientIdType = type,
						clientIdValue = clientIdValue.orEmpty()
					)
				}
			}
		}

		PlayerProvider.getCurrentActivity()?.run {
			RuStorePushClient.init(
				application = application,
				projectId = projectId,
				internalConfig = mapOf("type" to metricType),
				logger = UnityLogger(this.javaClass.simpleName),
				testModeEnabled = isTestModeEnabled,
				clientIdCallback = clientIdCallback
			)
		}
	}

	private fun handleError(throwable: Throwable) {
		if (allowErrorHandling && throwable is RuStoreException) {
			PlayerProvider.getCurrentActivity()?.let{ activity ->
				throwable.resolveForPush(activity)
			}
		}
	}

	override fun Log(logString: String?) {
		logListener?.Log(logString)
	}

	override fun LogWarning(logString: String?) {
		logListener?.LogWarning(logString)
	}

	override fun LogError(logString: String?) {
		logListener?.LogError(logString)
	}

	override fun LogException(throwable: Throwable?) {
		logListener?.LogException(throwable)
	}
}
