package ru.rustore.unitysdk.pushclient

import com.vk.push.common.clientid.ClientIdType
import ru.rustore.unreal.pushclient.UnrealClientIdType

object EnumConverter {
    fun convert(value: String?): ClientIdType? =
        try {
            value?.let {
                ClientIdType.valueOf(it)
            }
        } catch (e: IllegalArgumentException) {
            null
        }

    fun convert(value: UnrealClientIdType?): ClientIdType? =
        when(value) {
            UnrealClientIdType.GAID -> ClientIdType.GAID
            UnrealClientIdType.OAID -> ClientIdType.OAID
            else -> null
        }
}
