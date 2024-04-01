package ru.rustore.unreal.pushclient

import android.app.Application
import com.vk.push.common.clientid.ClientId
import com.vk.push.common.clientid.ClientIdCallback
import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.sdk.pushclient.RuStorePushClient
import ru.rustore.sdk.pushclient.common.logger.DefaultLogger
import ru.rustore.sdk.pushclient.common.logger.Logger
import ru.rustore.sdk.pushclient.messaging.exception.RuStorePushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.utils.resolveForPush
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener
import ru.rustore.unitysdk.pushclient.EnumConverter
import ru.rustore.unitysdk.pushclient.RuStoreUnityMessagingServiceListener
import ru.rustore.unitysdk.pushclient.callbacks.DeleteTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.GetTokenListener
import ru.rustore.unitysdk.pushclient.callbacks.SubscribeTopicListener
import ru.rustore.unreal.pushclient.callbacks.UnrealLogListener

object RuStoreUnrealPushClient : UnrealLogListener {

	private const val METRIC_TYPE = "unreal"

	private var allowErrorHandling: Boolean = false
	private var serviceListener: RuStoreUnityMessagingServiceListener? = null

	private var messages: MutableList<RemoteMessage> = ArrayList()
	private var errors: MutableList<RuStorePushClientException> = ArrayList()

	private var logListener: UnrealLogListener? = null

	fun setErrorHandling(allowErrorHandling: Boolean) {
		this.allowErrorHandling = allowErrorHandling
	}

	fun getErrorHandling() : Boolean {
		return allowErrorHandling
	}

	fun setListener(listener: RuStoreUnityMessagingServiceListener?) {
		this.serviceListener = listener
	}

	fun initListeners(allowNativeErrorHandling: Boolean, serviceListener: RuStoreUnityMessagingServiceListener?, logListener: UnrealLogListener?) {
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
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun getToken(listener: GetTokenListener) {
		RuStorePushClient.getToken()
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun deleteToken(listener: DeleteTokenListener) {
		RuStorePushClient.deleteToken()
			.addOnSuccessListener {
				listener.OnSuccess()
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun subscribeToTopic(topicName: String, listener: SubscribeTopicListener) {
		RuStorePushClient.subscribeToTopic(topicName)
			.addOnSuccessListener {
				listener.OnSuccess()
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun unsubscribeFromTopic(topicName: String, listener: SubscribeTopicListener) {
		RuStorePushClient.unsubscribeFromTopic(topicName)
			.addOnSuccessListener {
				listener.OnSuccess()
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
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
			testModeEnabled = false,
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
