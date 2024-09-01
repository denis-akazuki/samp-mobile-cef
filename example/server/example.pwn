#include <open.mp> // or #include <a_samp> for basic SA-MP server

#include <Pawn.RakNet>
#include <json>
#include <gvar>
#include <SAMPMobileCef>

#define CEF_PACKET_ID 252

enum
{
    ALERT_SET_SKIN = 1
};

main()
{
    print("CEF Example Server");
    print("GitHub: https://github.com/denis-akazuki/samp-mobile-cef");
}

forward OnAlertResponse(playerid, event_data[]);
public OnAlertResponse(playerid, event_data[])
{
    CefChangeBrowserFocus(playerid, false);

    new Node:event_data_node, Node:element_buffer_node;

    JSON_Parse(event_data, event_data_node);

    new alert_id;
    JSON_ArrayObject(event_data_node, 0, element_buffer_node);
    JSON_GetNodeInt(element_buffer_node, alert_id);

    new bool:response;
    JSON_ArrayObject(event_data_node, 1, element_buffer_node);
    JSON_GetNodeBool(element_buffer_node, response);

    switch (alert_id)
    {
        case ALERT_SET_SKIN:
        {
            if (!response)
                return 1;

            SetPlayerSkin(playerid, 150);
            SendClientMessage(playerid, -1, "[CEF] New skin: 150");
        }
    }

    return 1;
}

public OnCefBrowserInit(playerid, is_init, error_code)
{
    if (!is_init)
    {
        SendClientMessage(playerid, -1, "[CEF] It looks like you don't have CEF support!");
        return 1;
    }

    SendClientMessage(playerid, -1, "[CEF] All is okay!");
    CefShowBrowser(playerid);

    return 1;
}

public OnGameModeInit()
{
    CefSetPacketId(CEF_PACKET_ID);
    CefRegisterEventCallback("alert_response", "OnAlertResponse");

    return 1;
}

public OnGameModeExit()
{
    return 1;
}

public OnPlayerConnect(playerid)
{
    /* EN: android_asset - app/src/main/assets/ directory in Android application */
    /* EN: To store interfaces in the game cache directory, you can use: file://Android/data/your.package.name/files/ (not tested). */
    /* UK: android_asset - директорія app/src/main/assets/ в Android застосунку */
    /* UK: Для зберігання інтерфейсів у директорії кешу гри можна використовувати: file://Android/data/your.package.name/files/ (не перевірено). */
    CefInitBrowser(playerid, "file:///android_asset/cef/index.html");
    CefChangeBrowserFocus(playerid, false);

    SetSpawnInfo(playerid, NO_TEAM, 0, 2481.2441, -1911.9337, 21.4856, 90.0000, WEAPON_SAWEDOFF, 36, WEAPON_UZI, 150, WEAPON_FIST, 0);
    SpawnPlayer(playerid);

    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    CefDestroyBrowser(playerid);

    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    SpawnPlayer(playerid);

    return 1;
}

public OnPlayerSpawn(playerid)
{
    TogglePlayerControllable(playerid, true);

    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    if (!strcmp(cmdtext, "/change_skin", true))
    {
        if (CefIsPlayerHasLibrary(playerid))
        {
            new Node:event_data_node = JSON_Array(
                JSON_Int(ALERT_SET_SKIN),
                JSON_String("Change skin"),
                JSON_String("Do you want to change the skin to female?")
            );

            new event_data[CEF_MAX_EVENT_DATA_LENGTH];
            JSON_Stringify(event_data_node, event_data);

            CefSendEvent(playerid, "alert_show", event_data);
            CefChangeBrowserFocus(playerid, true);
        }
        return 1;
    }

    return 0;
}
