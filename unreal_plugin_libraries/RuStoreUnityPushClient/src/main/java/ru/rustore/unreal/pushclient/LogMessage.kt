package ru.rustore.unreal.pushclient

data class LogMessage(
    val type: LogMessageType,
    val message: String,
    val throwable: Throwable?
)
