Плагин RuStorePush предоставляет функциональность для включения в приложение push-уведомлений через сервисы RuStore.

Репозиторий содержит плагины "RuStoreCore" и "RuStorePush", а также минимальный проект с примерами использования и настроек. Поддерживаются версии UE 4.26 и выше.

Для подключения в свой проект необходимо:

1. Поместить плагины "RuStoreCore" и "RuStorePush" в папку "Plugins" внутри своего проекта. При удачном подключении "RuStore Core" и "RuStore Push" появятся в списке плагинов (Edit → Plugins → Project → Mobile).

2. В файле *YourProject*.Build.cs в списке PublicDependencyModuleNames подключить модули "RuStoreCore" и "RuStorePush".

3. В настройках проекта (Edit → Project Settings → Android) установить параметр Minimum SDK Version на уровень не ниже 24 и параметр Target SDK Version - не ниже 31.

Минификация приложения (ProGuard/R8) в данный момент не поддерживается. Все необходимые настройки gradle и зависимости проекта прописаны в файлах "RuStoreCore_UPL_Android.xml" и "RuStorePush_UPL_Android.xml".
