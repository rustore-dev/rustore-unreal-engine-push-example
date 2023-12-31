## RuStore Unreal Engine плагин для подключения пуш-уведомлений

### [🔗 Документация разработчика](https://help.rustore.ru/rustore/for_developers/developer-documentation/sdk_push-notifications)

Плагин RuStorePush предоставляет функциональность для включения в приложение push-уведомлений через сервисы RuStore.

Репозиторий содержит плагины “RuStorePush” и “RuStoreCore”, а также демонстрационное приложение с примерами использования и настроек. Поддерживаются версии UE 4.26 и выше.


### Установка плагина в свой проект

1. Скопируйте содержимое папки _“Plugins”_ в папку _“Plugins”_ внутри своего проекта. Перезапустите Unreal Engine, в списке плагинов (Edit → Plugins → Project → Mobile) отметьте плагины “RuStorePush” и “RuStoreCore”.

2. В файле _“YourProject.Build.cs”_ в списке PublicDependencyModuleNames подключите модули модули “RuStoreCore” и “RuStorePush”.

3. В настройках проекта (Edit → Project Settings → Android) установить параметр Minimum SDK Version на уровень не ниже 24 и параметр Target SDK Version - не ниже 31.


### Сборка примера приложения

1. В файле ресурсов _“Source / RuStorePushApp / projectid.xml”_ в параметре “rustore_project_id” укажите ID проекта, который можно получить в системе [RuStore Консоль](https://console.rustore.ru/waiting). Для этого на странице приложения перейдите в раздел «Push-уведомления» и выберите “Проекты”.

2. В настройках проекта (Edit → Project Settings → Platforms → Android) укажите имя пакета “Android Package Name” и параметры подписи “Distribution Signing” вашего приложения в RuStore. Подробная информация о публикации приложений в RuStore доступна на странице [help](https://help.rustore.ru/rustore/for_developers/publishing_and_verifying_apps).


### Техническая поддержка

Дополнительная помощь и инструкции доступны на странице [help.rustore.ru](https://help.rustore.ru/).
