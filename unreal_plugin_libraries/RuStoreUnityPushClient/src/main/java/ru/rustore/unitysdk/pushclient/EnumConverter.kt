package ru.rustore.unitysdk.pushclient

import com.vk.push.common.clientid.ClientIdType

object EnumConverter {
    fun getClientIdTypeFromString(value: String?): ClientIdType? {
        return try {
            value?.let {
                ClientIdType.valueOf(it)
            }
        } catch (e: IllegalArgumentException) {
            null
        }
    }
}
