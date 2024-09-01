/*
	EN: Server include of CEF library for SA:MP Mobile.
	UK: Серверний заголовний файл бібліотеки CEF для SA:MP Mobile.

	Copyright © 2024 Denis Akazuki <https://github.com/denis-akazuki>

	EN: Out of respect, please do not delete this comment if you use code from this project.
	UK: З поваги, будь ласка, не видаляйте цей коментар, якщо використовуєте код із цього проєкту.
*/

#if !defined SAMPMOBILECEF_INC_
	#define SAMPMOBILECEF_INC_

	#if !defined PAWNRAKNET_INC_
		#error "[CEF] Pawn.RakNet (https://github.com/katursis/Pawn.RakNet) is not included in the gamemode."
	#endif
	
	#if !defined _json_included
		#error "[CEF] JSON (https://github.com/Southclaws/pawn-json) is not included in the gamemode."
	#endif
	
	#if !defined SetGVarString
		#error "[CEF] gvar (https://github.com/samp-incognito/samp-gvar-plugin) is not included in the gamemode."
	#endif

	#define CEF_PREFIX "[CEF] "
	#define CEF_INC_VERSION "1.0.0"

	#if !defined CEF_MAX_EVENT_NAME_LENGTH
		#define CEF_MAX_EVENT_NAME_LENGTH 48
	#endif
	#if !defined CEF_MAX_EVENT_CALLBACK_LENGTH
		#define CEF_MAX_EVENT_CALLBACK_LENGTH 64
	#endif
	#if !defined CEF_MAX_EVENT_DATA_LENGTH
		#define CEF_MAX_EVENT_DATA_LENGTH 2048
	#endif

	new cef_packet_id = -1;
	new cef_initialized_players[MAX_PLAYERS];

	enum
	{
		RPC_InitBrowser = 1,
		RPC_DestroyBrowser,
		RPC_ShowBrowser,
		RPC_HideBrowser,
		RPC_SetBrowserUrl,
		RPC_ChangeBrowserFocus,
		RPC_ServerEvent,

		RPC_LibraryInit,
		RPC_BrowserInit,
		RPC_ClientEvent,
	};

	stock IsPacketIdSet()
	{
		if (cef_packet_id == -1)
		{
			printf("%s Unable to continue work of CEF include. Cef package id was not specified", CEF_PREFIX);
			return false;
		}
		
		return true;
	}

	stock CefSetPacketId(packet_id)
	{
		cef_packet_id = packet_id;
		
		printf("%s Include version: %s", CEF_PREFIX, CEF_INC_VERSION);
		printf("%s New cef packet id: %d", CEF_PREFIX, cef_packet_id);
	}

	stock CefInitBrowser(playerid, const url[])
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_InitBrowser,
			PR_UINT16, strlen(url),
			PR_STRING, url
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefDestroyBrowser(playerid)
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_DestroyBrowser
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefShowBrowser(playerid)
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_ShowBrowser
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefHideBrowser(playerid)
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_HideBrowser
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefSetBrowserUrl(playerid, const url[])
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_SetBrowserUrl,
			PR_UINT16, strlen(url),
			PR_STRING, url
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefChangeBrowserFocus(playerid, bool:is_focused)
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_ChangeBrowserFocus,
			PR_BOOL, is_focused
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefSendEvent(playerid, const event_name[], const event_data[])
	{
		if (!IsPacketIdSet())
			return;
		
		new BitStream:bs = BS_New();
		
		BS_WriteValue(
			bs,
			PR_UINT16, cef_packet_id,
			PR_UINT32, _:RPC_ServerEvent,
			PR_UINT16, strlen(event_name),
			PR_STRING, event_name,
			PR_UINT16, strlen(event_data),
			PR_STRING, event_data
		);
		PR_SendPacket(bs, playerid, PR_HIGH_PRIORITY, PR_RELIABLE);
		
		BS_Delete(bs);
	}

	stock CefRegisterEventCallback(const event_name[], const callback[])
	{
		if (!IsPacketIdSet())
			return;
		
		if (strlen(callback) > CEF_MAX_EVENT_CALLBACK_LENGTH) {
			printf("%s Callback function name can't be higher than %d (event: %s)", CEF_PREFIX, CEF_MAX_EVENT_CALLBACK_LENGTH, event_name);
			return;
		}
		
		if (GetGVarType(event_name) != GLOBAL_VARTYPE_NONE)
		{
			DeleteGVar(event_name);
		}
		
		SetGVarString(event_name, callback);
	}
	
	stock CefIsPlayerHasLibrary(playerid)
	{
		if (!IsPacketIdSet())
			return false;
		
		return cef_initialized_players[playerid];
	}

	public OnIncomingPacket(playerid, packetid, BitStream:bs)
	{
		if (IsPacketIdSet() && packetid == cef_packet_id)
		{
			new rpc_id;

			BS_IgnoreBits(bs, 16);
			BS_ReadValue(bs, PR_UINT32, rpc_id);
				
			switch (rpc_id)
			{
				case RPC_LibraryInit:
				{
					cef_initialized_players[playerid] = 1;
				}
				case RPC_BrowserInit:
				{
					new is_init, error_code;
					
					BS_ReadValue(bs, PR_BOOL, is_init);
					BS_ReadValue(bs, PR_INT16, error_code);
					
					CallLocalFunction("OnCefBrowserInit", "ddd", playerid, is_init, error_code);
				}
				case RPC_ClientEvent:
				{
					new event_name_length;
					new event_name[CEF_MAX_EVENT_NAME_LENGTH];
					event_name[0] = EOS;
					
					BS_ReadValue(bs, PR_UINT16, event_name_length);
					BS_ReadValue(bs, PR_STRING, event_name, event_name_length);
					
					new event_data_length;
					new event_data[CEF_MAX_EVENT_DATA_LENGTH];
					event_data[0] = EOS;
					
					BS_ReadValue(bs, PR_UINT16, event_data_length);
					BS_ReadValue(bs, PR_STRING, event_data, event_data_length);
					
					if (GetGVarType(event_name) != GLOBAL_VARTYPE_NONE)
					{					
						new event_callback[CEF_MAX_EVENT_CALLBACK_LENGTH];
						event_callback[0] = EOS;
						GetGVarString(event_name, event_callback, sizeof event_callback);

						CallLocalFunction(event_callback, "is", playerid, event_data);
					}
				}
			}
		}
		
		#if defined Cef_OnIncomingPacket
			Cef_OnIncomingPacket(playerid, packetid, bs);
		#endif
		
		return 1;
	}
	#if defined _ALS_OnIncomingPacket
		#undef OnIncomingPacket
	#else
		#define _ALS_OnIncomingPacket
	#endif
	#define OnIncomingPacket Cef_OnIncomingPacket
	#if defined Cef_OnIncomingPacket
		forward Cef_OnIncomingPacket(playerid, packetid, BitStream:bs);
	#endif
	
	public OnPlayerConnect(playerid)
	{
		cef_initialized_players[playerid] = 0;
		
		#if defined Cef_OnPlayerConnect
			Cef_OnPlayerConnect(playerid);
		#endif
		
		return 1;
	}
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect Cef_OnPlayerConnect
	#if defined Cef_OnPlayerConnect
		forward Cef_OnPlayerConnect(playerid);
	#endif
	
	public OnPlayerDisconnect(playerid, reason)
	{
		cef_initialized_players[playerid] = -1;
		
		#if defined Cef_OnPlayerDisconnect
			Cef_OnPlayerDisconnect(playerid, reason);
		#endif
		
		return 1;
	}
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect Cef_OnPlayerDisconnect
	#if defined Cef_OnPlayerDisconnect
		forward Cef_OnPlayerDisconnect(playerid, reason);
	#endif
	
	forward OnCefBrowserInit(playerid, is_init, error_code);

#endif