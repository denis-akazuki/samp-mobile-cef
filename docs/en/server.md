Language: **English** | [Українська](../uk/server.md)

# SA:MP Mobile CEF

## Important Information
- If the length of the information you send to/from the callback exceeds the limit specified in `SAMPMobileCef.inc` (default is 2048), it is possible to extend it manually:
> [!NOTE]
> The client-side uses dynamic memory allocation, so **length restrictions only apply to the server-side**. For the convenience of developers, the ability to manually extend the length of data on the server-side has been added.
```pawn
/* Use this method before including the SAMPMobileCef.inc header file */
#define CEF_MAX_EVENT_NAME_LENGTH 64 // extend the maximum length of the callback name (default is 48)
#define CEF_MAX_EVENT_CALLBACK_LENGTH 72 // extend the maximum length of the callback function name (default is 64)
#define CEF_MAX_EVENT_DATA_LENGTH 4096 // extend the maximum length of callback data (default is 2048)
```
- It is highly discouraged to use all the memory allocated for callback data (2048 characters). Always leave some free space when sending data to the callback (on both sides). If this is not possible, extend the memory using the method above.

## Installation and Setup of the Server-side
- Export the `server/SAMPMobileCef.inc` file to the `pawno/include` directory (Windows)
- Install the following dependencies: [`Pawn.RakNet`](https://github.com/katursis/Pawn.RakNet), [`pawn-json`](https://github.com/Southclaws/pawn-json), and [`SA-MP GVar Plugin`](https://github.com/samp-incognito/samp-gvar-plugin)
- Include the previously installed plugins and the `SAMPMobileCef.inc` header file in the game mode:
    ```pawn
    #include <Pawn.RakNet>
    #include <json>
    #include <gvar>
    #include <SAMPMobileCef>
    ```
- For convenience, declare the `CEF_PACKET_ID` macro with the network packet ID:
    ```pawn
    #define CEF_PACKET_ID 252 // or any other ID that you specified during the client-side setup
    ```
- In the `OnGameModeInit` public, call the `OnGameModeInit` function:
    ```pawn
    public OnGameModeInit()
    {
        CefSetPacketId(CEF_PACKET_ID); // previously declared macro with the network packet ID
        
        return 1;
    }
    ```
- A detailed way of working with functionality, packaging, and reading data can be found in the [**simple example**](../../example/server/example.pwn). If you encounter difficulties implementing your idea - [**write here**](https://github.com/denis-akazuki/samp-mobile-cef/issues).

## List of Functions
### `CefSetPacketId(packet_id)`
Sets the network packet ID for interacting with CEF.

- **Parameters**:
  - `packet_id` (int): The packet ID to be used for CEF.

### `CefInitBrowser(playerid, url[])`
Initializes the browser for the specified player.

> [!NOTE]
> You should not recreate the browser every time it is used. Initialize it once when the player connects and use it for further purposes.

- **Parameters**:
  - `playerid` (int): The player ID.
  - `url` (string): The URL to be loaded in the browser.

### `CefDestroyBrowser(playerid)`
Destroys the browser for the specified player.

- **Parameters**:
  - `playerid` (int): The player ID.

### `CefShowBrowser(playerid)`
Shows the browser to the specified player.

- **Parameters**:
  - `playerid` (int): The player ID.

### `CefHideBrowser(playerid)`
Hides the browser for the specified player.

- **Parameters**:
  - `playerid` (int): The player ID.

### `CefSetBrowserUrl(playerid, url[])`
Sets the browser URL for the specified player.

- **Parameters**:
  - `playerid` (int): The player ID.
  - `url` (string): The URL to be loaded in the browser.

### `CefChangeBrowserFocus(playerid, is_focused)`
Changes the focus (clickability) state of the browser for the specified player. By default, the browser is initialized with focus (clickability) enabled.

- **Parameters**:
  - `playerid` (int): The player ID.
  - `is_focused` (bool): `true` if the browser should be focused (clickable), `false` otherwise.

### `CefSendEvent(playerid, event_name[], event_data[])`
Sends an event to the browser for the specified player.

- **Parameters**:
  - `playerid` (int): The player ID.
  - `event_name` (string): The name of the event.
  - `event_data` (string): The packed JSON data.

### `CefRegisterEventCallback(event_name[], callback[])`
Registers a callback function for the specified event.

- **Parameters**:
  - `event_name` (string): The name of the event.
  - `callback` (string): The name of the callback function that will be executed when the event is received from the client.

### `CefIsPlayerHasLibrary(playerid)`
Checks if the specified player has the CEF library.

> [!WARNING]
> Do not use this function in the `OnPlayerConnect` public. The client may not have time to send the player's information at the time of connection.

- **Parameters**:
  - `playerid` (int): The player ID.
- **Returns**: `true` if the CEF library is present, `false` otherwise.

## List of Callbacks
### `OnCefBrowserInit(playerid, is_init, error_code)`
Called after loading the URL specified during initialization (or manual change).

- **Parameters**:
  - `playerid` (int): The player ID.
  - `is_init` (bool): `true` if the URL was successfully loaded, `false` otherwise.
  - `error_code` (int): `-1` for successful URL loading, `0` in case of an unknown error, or `HTTP status code`.

---
**Copyright © 2024 [Denis Akazuki](https://github.com/denis-akazuki).**
