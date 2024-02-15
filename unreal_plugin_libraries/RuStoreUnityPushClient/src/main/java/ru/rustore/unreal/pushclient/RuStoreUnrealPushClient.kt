package ru.rustore.unreal.pushclient

import android.app.Application
import com.vk.push.common.clientid.ClientId
import com.vk.push.common.clientid.ClientIdCallback
import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult
import ru.rustore.sdk.core.tasks.OnCompleteListener
import ru.rustore.sdk.pushclient.RuStorePushClient
import ru.rustore.sdk.pushclient.common.logger.DefaultLogger
import ru.rustore.sdk.pushclient.common.logger.Logger
import ru.rustore.sdk.pushclient.messaging.exception.PushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.messaging.model.TestNotificationPayload
import ru.rustore.sdk.pushclient.utils.resolveForPush
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener
import ru.rustore.unitysdk.pushclient.EnumConverter
import ru.rustore.unitysdk.pushclient.RuStoreUnityMessagingServiceListener
import ru.rustore.unitysdk.pushclient.callbacks.DeleteTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.GetTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.SendTestNotificationListener
import ru.rustore.unitysdk.pushclient.callbacks.SubscribeTopicListener
import ru.rustore.unreal.pushclient.callbacks.UnrealLogListener

object RuStoreUnrealPushClient : UnrealLogListener {

	private val METRIC_TYPE = "unreal"

	private var allowErrorHandling: Boolean = false
	private var serviceListener: RuStoreUnityMessagingServiceListener? = null

	private var messages: MutableList<RemoteMessage> = ArrayList()
	private var errors: MutableList<PushClientException> = ArrayList()

	private var logListener: UnrealLogListener? = null

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

	fun init(allowNativeErrorHandling: Boolean, serviceListener: RuStoreUnityMessagingServiceListener?, logListener: UnrealLogListener?) {
		this.allowErrorHandling = allowNativeErrorHandling

		this.serviceListener = serviceListener

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

		this.logListener = logListener
		RuStoreUnrealLogger.setExternLogger(this)
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

	fun onError(errors: List<PushClientException>) {
		if (serviceListener == null){
			this.errors.addAll(errors)
		}
		serviceListener?.OnError(errors)
	}

	@JvmStatic
	fun init(application: Application, projectId: String, loggerMode: RuStoreUnrealLoggerMode?, clientIdType: UnrealClientIdType?, clientIdValue: String?) {
		val clientIdCallback = clientIdType?.let {
			clientIdValue?.let {
				ClientIdCallback {
					EnumConverter.convert(clientIdType)?.let { type ->
						ClientId(
							clientIdType = type,
							clientIdValue = clientIdValue
						)
					}
				}
			}
		}

		val logger: Logger = when(loggerMode) {
			RuStoreUnrealLoggerMode.LOGCAT -> DefaultLogger()
			RuStoreUnrealLoggerMode.CUSTOM -> RuStoreUnrealLogger
			else -> DefaultLogger()
		}

		RuStorePushClient.init(
			application = application,
			projectId = projectId,
			internalConfig = mapOf("type" to METRIC_TYPE),
			logger = logger,
			testModeEnabled = isTestModeEnabled,
			clientIdCallback = clientIdCallback
		)
	}

	private fun handleError(throwable: Throwable) {
		if (allowErrorHandling && throwable is RuStoreException) {
			PlayerProvider.getCurrentActivity()?.let{ activity ->
				throwable.resolveForPush(activity)
			}
		}
	}

	override fun verbose(message: String?, throwable: Throwable?) {
		logListener?.verbose(message, throwable)
	}

	override fun debug(message: String?, throwable: Throwable?) {
		logListener?.debug(message, throwable)
	}

	override fun info(message: String?, throwable: Throwable?) {
		logListener?.info(message, throwable)
	}

	override fun warn(message: String?, throwable: Throwable?) {
		logListener?.warn(message, throwable)
	}

	override fun error(message: String?, throwable: Throwable?) {
		logListener?.error(message, throwable)
	}
}
