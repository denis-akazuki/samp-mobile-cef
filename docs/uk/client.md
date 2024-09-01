Мова: [English](../en/client.md) | **Українська**

# SA:MP Mobile CEF

## Важлива інформація
- Усі логи клієнтської частини, включаючи логи WebView, зберігаються в папці `SAMP/cef.log`.
- Додаткові функції для роботи з клієнтською частиною відсутні; всі необхідні функції зазначені в наведених нижче інструкціях з установки.

## Установка і налаштування клієнтської частини (C++)

> [!WARNING]
> Наведені нижче приклади підходять для більшості проєктів, але можливі винятки.

- Експортуйте файли `client/cpp/libSAMPMobileCef.a` та `client/cpp/SAMPMobileCef.h` в папку `vendor/cef` вашого клієнта (папку необхідно створити вручну).
- У файлі `Android.mk` підключіть бібліотеку `libSAMPMobileCef.a`:
    ```makefile
    include $(PREBUILT_STATIC_LIBRARY)
    include $(CLEAR_VARS)
    LOCAL_MODULE    := libSAMPMobileCef 
    LOCAL_SRC_FILES := vendor/cef/libSAMPMobileCef.a

    LOCAL_STATIC_LIBRARIES := libSAMPMobileCef
    ```
- У файлі `main.cpp` підключіть заголовковий файл `SAMPMobileCef.h`:
    ```cpp
    #include "vendor/cef/SAMPMobileCef.h"
    ```
- У файлі `main.cpp`, в функції `InitSAMP`, задайте адресу кешу гри:
    ```cpp
    cef::setGamePath(g_pszStorage);
    ```
- У файлі `net/netgame.cpp` підключіть заголовковий файл `SAMPMobileCef.h` таким же способом, як і в файлі `main.cpp`.
- У файлі `net/netgame.cpp`, в конструкторі `CNetGame`, ініціалізуйте мережеву частину бібліотеки:
    ```cpp
    cef::initNetwork(m_pRakClient, ID_CUSTOM_CEF); // слід передати вказівник на RakClient і кастомний ID пакету для мережевого спілкування (наприклад, 252 або будь-який інший вільний у PacketEnumeration)
    ```
- У файлі `net/netgame.cpp`, в `CNetGame::UpdateNetwork`, додайте обробку раніше вказаного пакету:
    ```cpp
    switch (packetIdentifier)
    {
    ...
    case ID_CUSTOM_CEF: // раніше вказаний ID в initNetwork
        cef::handlePacket(pkt);
        break;
    }
    ```
- У файлі `net/netgame.cpp`, в `CNetGame::Packet_ConnectionSucceeded`, додайте обробку підключення до сервера:
    ```cpp
    cef::handleServerConnection(); // в кінець функції
    ```

## Установка і налаштування клієнтської частини (Java)

> [!WARNING]
> Наведені нижче приклади підходять для більшості проєктів, але можливі винятки.

- Експортуйте файл `client/java/sampmobilecef-...-release.aar` в `app/libs` (папку `libs` слід створити, якщо вона відсутня).
- У файлі `app/build.gradle` імпортуйте раніше експортовану бібліотеку:
    ```groovy
    dependencies {
        implementation files("libs/sampmobilecef-...-release.aar")
    }
    ```
- У файлі `NvEventQueueActivity` ініціалізуйте такі змінні:
    ```java
    private CefJavaManager mJavaManager = null;
    private CefClientManager mClientManager = null;
    ```
- У файлі `NvEventQueueActivity`, в функції `systemInit`, додайте ініціалізацію необхідних класів:
    ```java
    mJavaManager = new CefJavaManager(mRootFrame, getInstance());
    mClientManager = new CefClientManager(getInstance());

    mJavaManager.setClientManager(mClientManager);
    mClientManager.setJavaManager(mJavaManager);
    ```
- У файлі `NvEventQueueActivity`, в функції `setPauseState`, додайте функціонал для приховання/показу WebView під час зміни стану паузи:
    ```java
    public void setPauseState(boolean z2) {
        runOnUiThread(() -> {
            if (mJavaManager.isShow()) {
                if (z2)
                    mJavaManager.hideBrowserView();
                else
                    mJavaManager.showBrowserView();
            }
        });
    }
    ```

---
**Copyright © 2024 [Denis Akazuki](https://github.com/denis-akazuki).**
