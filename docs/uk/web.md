Мова: [English](../en/web.md) | **Українська**

# SA:MP Mobile CEF

## Важлива інформація
- Детальний спосіб роботи з функціоналом, упаковки та читання даних можете знайти у [**простому прикладі**](../../example/web/). У разі виникнення труднощів у реалізації вашого задуму - [**пишіть сюди**](https://github.com/denis-akazuki/samp-mobile-cef/issues).

## Список функцій
### `Cef.registerEventCallback(eventName, callbackFunctionName)`
Реєструє функцію зворотного виклику для зазначеної події CEF.

- **Параметри**:
  - `eventName` (String): Назва події, на яку буде реагувати функція.
  - `callbackFunctionName` (String): Ім'я функції зворотного виклику (колбеку), яка буде викликана при виникненні події.

### `Cef.sendEvent(eventName, eventData)`
Відправляє подію на сервер.

- **Параметри**:
  - `eventName` (String): Назва відправленої події.
  - `eventData` (String): Упаковані дані JSON, які будуть передані у події.

---
**Copyright © 2024 [Denis Akazuki](https://github.com/denis-akazuki).**
