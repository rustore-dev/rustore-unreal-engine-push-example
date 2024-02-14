package ru.rustore.unreal.pushclient

enum class LogMessageType {
    DEBUG,
    ERROR,
    INFO,
    VERBOSE,
    WARN
}

data class LogMessage(
    val type: LogMessageType,
    val message: String,
    val throwable: Throwable?
)
