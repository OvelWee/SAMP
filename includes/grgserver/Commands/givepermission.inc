PCMD:givepermission[SERVERADMIN](playerID, params[], StringID:103("Give permissions to a player"))
{
	new targetPlayerID;
	new permissionString[16];
	if (sscanf(params, "us[16]", targetPlayerID, permissionString))
	{
		CmdUsageMsg(playerID, "givepermission", "PlayerID/Name", "Admin|Mapper|Moderator|Navi|NPCAdmin|ServerAdmin|SpawnVehicle|Teleport");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		new permissionsArray[30][30];
		new permission[30];
		explode(permissionString, permissionsArray, ',', sizeof(permissionsArray));
		for (new permissionIndex = 0; permissionIndex < sizeof(permissionsArray); permissionIndex++)
		{
			permission = permissionsArray[permissionIndex];
			if (strcmp(permission, "userId", true))
			{
				new newState = true;
				if (permission[0] == '-')
				{
					strdel(permission, 0, 1);
					newState = false;
				}
				new permissionID = GetPermissionByName(permission);
				if (permissionID == -1)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:381("Invalid permission: %s"), permission);
				}
				else
				{
					if (permissions[targetPlayerID][enum_permission:permissionID] == newState)
					{
						if (newState)
						{
							SendClientMessageEx(playerID, COLOR_ERROR, StringID:70("%p already has the permission '%s'!"), targetPlayerID, permission);
						}
						else
						{
							SendClientMessageEx(playerID, COLOR_ERROR, StringID:71("%p does not have the permission '%s' so it can not be removed!"), targetPlayerID, permission);
						}
						return COMMAND_ERROR;
					}
					MySQLQuery("SELECT `userId` FROM `permissions` WHERE `userId` = '%d'", PVar:targetPlayerID[USERID]);
					mysql_store_result();
					new rows = mysql_num_rows();
					mysql_free_result();
					if (rows)
					{
						MySQLQuery("UPDATE `permissions` SET `%s` = '%d' WHERE `userId` = '%d'", MySQLEscapeString(permission), newState, PVar:targetPlayerID[USERID]);
					}
					else
					{
						MySQLQuery("INSERT INTO `permissions` (`userId`, `%s`) VALUES('%d', '%d')", MySQLEscapeString(permission), PVar:targetPlayerID[USERID], newState);
					}
					permissions[targetPlayerID][enum_permission:permissionID] = newState;
					if (newState)
					{
						SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:72("You got the permission '%s' from %p"), permission, playerID);
						SendClientMessageEx(playerID, COLOR_INFO, StringID:73("You gave the permission '%s' to %p"), permission, targetPlayerID);
						printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerID));
					}
					else
					{
						SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:74("%p has revoked the permission '%s' from you"), playerID, permission);
						SendClientMessageEx(playerID, COLOR_INFO, StringID:75("You have revoked the permission '%s' from %p"), permission, targetPlayerID);
						printf("%s has revoked the permission %s of %s", GetPlayerNameEx(playerID), permission, GetPlayerNameEx(targetPlayerID));
					}
				}
			}
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}