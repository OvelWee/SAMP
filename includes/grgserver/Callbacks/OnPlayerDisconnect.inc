public OnPlayerDisconnect(playerid, reason)
{
	if (IsPlayerNPC(playerid))
	{
		return true;
	}
	else
	{
		if (reason == 1)
		{
			SavePlayer(playerid);
		}

		if (PVar:playerid[FLYCAM_DUMMYOBJECT])
		{
			DestroyDynamicObject(PVar:playerid[FLYCAM_DUMMYOBJECT]);
		}

		new reasonString[16];
		switch (reason)
		{
			case 0:
			{
				strcat(reasonString, "Timed out");
			}
			case 1:
			{
				strcat(reasonString, "Leaving");
			}
			case 2:
			{
				strcat(reasonString, "Kicked/Banned");
			}
			case 3:
			{
				strcat(reasonString, "Relogin");
			}
		}

		PlayerLoop(playerID)
		{
			if (!IsPlayerNPC(playerID) && playerID != playerid)
			{
				SendClientMessageEx(playerID, COLOR_JOINLEAVE, StringID:161("%p has left the server (%s)"), playerid, reasonString);
			}
		}

		DestroyPlayerProgressBar(playerid, PVar:playerid[PROGRESSBAR_NEEDS_ENERGY]);
		DestroyPlayerProgressBar(playerid, PVar:playerid[PROGRESSBAR_NEEDS_HUNGER]);
		DestroyPlayerProgressBar(playerid, PVar:playerid[PROGRESSBAR_NEEDS_THIRST]);

		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[NEEDS_TEXT]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[RADIOSTATION]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SPEEDO_COLUMN1]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SPEEDO_COLUMN2]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[VEHICLENAME]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SCREENFADER]);
	}

	StopAudioStreamForPlayer(playerid);
	ResetPlayerVariables(playerid);

	return true;
}