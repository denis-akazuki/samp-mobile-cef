Language: **English** | [Українська](../uk/client.md)

# SA:MP Mobile CEF

## Important Information
- All client-side logs, including WebView logs, are saved in the `SAMP/cef.log` folder.
- There are no additional functions for working with the client part; all necessary functions are specified in the installation instructions below.

## Installation and Configuration of the Client (C++)

> [!WARNING]
> The examples provided below are suitable for most projects, but exceptions are possible.

- Export the `client/cpp/libSAMPMobileCef.a` and `client/cpp/SAMPMobileCef.h` files to your client's `vendor/cef` folder (this folder needs to be created manually).
- In the `Android.mk` file, include the `libSAMPMobileCef.a` library:
    ```makefile
    include $(PREBUILT_STATIC_LIBRARY)
    include $(CLEAR_VARS)
    LOCAL_MODULE    := libSAMPMobileCef 
    LOCAL_SRC_FILES := vendor/cef/libSAMPMobileCef.a

    LOCAL_STATIC_LIBRARIES := libSAMPMobileCef
    ```
- In the `main.cpp` file, include the `SAMPMobileCef.h` header file:
    ```cpp
    #include "vendor/cef/SAMPMobileCef.h"
    ```
- In the `main.cpp` file, in the `InitSAMP` function, set the game cache path:
    ```cpp
    cef::setGamePath(g_pszStorage);
    ```
- In the `net/netgame.cpp` file, include the `SAMPMobileCef.h` header file in the same way as in the `main.cpp` file.
- In the `net/netgame.cpp` file, in the `CNetGame` constructor, initialize the network part of the library:
    ```cpp
    cef::initNetwork(m_pRakClient, ID_CUSTOM_CEF); // a pointer to RakClient and a custom packet ID for network communication should be passed (e.g., 252 or any other free in PacketEnumeration)
    ```
- In the `net/netgame.cpp` file, in `CNetGame::UpdateNetwork`, add processing for the previously specified packet:
    ```cpp
    switch (packetIdentifier)
    {
    ...
    case ID_CUSTOM_CEF: // the previously specified ID in initNetwork
        cef::handlePacket(pkt);
        break;
    }
    ```
- In the `net/netgame.cpp` file, in `CNetGame::Packet_ConnectionSucceeded`, add server connection handling:
    ```cpp
    cef::handleServerConnection(); // at the end of the function
    ```

## Installation and Configuration of the Client (Java)

> [!WARNING]
> The examples provided below are suitable for most projects, but exceptions are possible.

- Export the `client/java/sampmobilecef-...-release.aar` file to `app/libs` (the `libs` folder should be created if it does not exist).
- In the `app/build.gradle` file, import the previously exported library:
    ```groovy
    dependencies {
        implementation files("libs/sampmobilecef-...-release.aar")
    }
    ```
- In the `NvEventQueueActivity` file, initialize the following variables:
    ```java
    private CefJavaManager mJavaManager = null;
    private CefClientManager mClientManager = null;
    ```
- In the `NvEventQueueActivity` file, in the `systemInit` function, add the initialization of the necessary classes:
    ```java
    mJavaManager = new CefJavaManager(mRootFrame, getInstance());
    mClientManager = new CefClientManager(getInstance());

    mJavaManager.setClientManager(mClientManager);
    mClientManager.setJavaManager(mJavaManager);
    ```
- In the `NvEventQueueueActivity` file, in the `setPauseState` function, add functionality to hide/show the WebView while the pause state is changing:
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
