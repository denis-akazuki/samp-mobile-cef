Language: **English** | [Українська](../uk/web.md)

# SA:MP Mobile CEF

## Important Information
- A detailed way to work with functionality, packaging, and reading data can be found in the [**simple example**](../../example/web/). If you encounter difficulties in implementing your idea - [**write here**](https://github.com/denis-akazuki/samp-mobile-cef/issues).

## List of Functions
### `Cef.registerEventCallback(eventName, callbackFunctionName)`
Registers a callback function for the specified CEF event.

- **Parameters**:
  - `eventName` (String): The name of the event that the function will respond to.
  - `callbackFunctionName` (String): The name of the callback function that will be called when the event occurs.

### `Cef.sendEvent(eventName, eventData)`
Sends an event to the server.

- **Parameters**:
  - `eventName` (String): The name of the event being sent.
  - `eventData` (String): The packaged JSON data that will be transmitted with the event.

---
**Copyright © 2024 [Denis Akazuki](https://github.com/denis-akazuki).**
