package ru.rustore.unreal.pushclient

import ru.rustore.sdk.pushclient.common.logger.Logger
import ru.rustore.unreal.pushclient.callbacks.UnrealLogListener

object RuStoreUnrealLogger : Logger, UnrealLogListener {

    private var externLogger: UnrealLogListener? = null
    private var messages: MutableList<LogMessage> = ArrayList()

    @Synchronized
    fun setExternLogger(logger: UnrealLogListener?) {
        externLogger = logger
        ship()
    }

    fun getExternLogger() = externLogger

    override fun createLogger(tag: String): Logger = this

    @Synchronized
    override fun debug(message: String, throwable: Throwable?) {
        externLogger?.debug(message, throwable)
        collect(LogMessageType.DEBUG, message, throwable)
    }

    @Synchronized
    override fun error(message: String, throwable: Throwable?) {
        externLogger?.error(message, throwable)
        collect(LogMessageType.ERROR, message, throwable)
    }

    @Synchronized
    override fun info(message: String, throwable: Throwable?) {
        externLogger?.info(message, throwable)
        collect(LogMessageType.INFO, message, throwable)
    }

    @Synchronized
    override fun verbose(message: String, throwable: Throwable?) {
        externLogger?.verbose(message, throwable)
        collect(LogMessageType.VERBOSE, message, throwable)
    }

    @Synchronized
    override fun warn(message: String, throwable: Throwable?) {
        externLogger?.warn(message, throwable)
        collect(LogMessageType.WARN, message, throwable)
    }

    private fun collect(type: LogMessageType, message: String, throwable: Throwable?) {
        if (externLogger == null) {
            messages.add(LogMessage(type, message, throwable))
        }
    }

    private fun ship() {
        externLogger?.let { logger ->
            messages.forEach { message ->
                when (message.type) {
                    LogMessageType.DEBUG -> logger.debug(message.message, message.throwable)
                    LogMessageType.ERROR -> logger.error(message.message, message.throwable)
                    LogMessageType.INFO -> logger.info(message.message, message.throwable)
                    LogMessageType.VERBOSE -> logger.verbose(message.message, message.throwable)
                    LogMessageType.WARN -> logger.warn(message.message, message.throwable)
                }
            }
            messages.clear()
        }
    }
}
