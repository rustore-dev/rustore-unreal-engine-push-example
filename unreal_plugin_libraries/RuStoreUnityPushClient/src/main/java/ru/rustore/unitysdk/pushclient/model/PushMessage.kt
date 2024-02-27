package ru.rustore.unitysdk.pushclient.model

data class PushMessage(
    val messageId: String?,
    val priority: Int,
    val ttl: Int,
    val collapseKey: String?,
    val data: Map<String, String>,
    val rawData: ByteArray?,
    val notification: PushNotification?
) {
    fun GetDataElement(key: String): String {
        return data[key] ?: ""
    }

    fun GetRawDataSize(): Int {
        data.entries.toTypedArray()
        return rawData?.size ?: 0
    }

    fun GetRawDataElement(index: Int): Byte {
        return rawData?.get(index) ?: 0
    }
}
