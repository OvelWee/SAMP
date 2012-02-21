ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		case DIALOG_ADDBUILDING_NAME:
		{
			ShowPlayerDialog(playerID, DIALOG_ADDBUILDING_NAME, DIALOG_STYLE_INPUT, "Name eingeben", "Gebe den Name f�r das Geb�ude ein.", "Erstellen", "Zur�ck");
		}
		case DIALOG_ADDBUILDING_TYPE:
		{
			ShowPlayerDialog(playerID, DIALOG_ADDBUILDING_TYPE, DIALOG_STYLE_LIST, "Geb�udetyp ausw�hlen", "Bank\nHotel\nHaus", "Weiter", "Abbrechen");
		}
		case DIALOG_BUYHOUSE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "Dieses Haus kann noch gekauft werden.\n\nPreis: %s", price);
			ShowPlayerDialog(playerID, DIALOG_BUYHOUSE, DIALOG_STYLE_MSGBOX, "Haus kaufen", string, "Kaufen", "Abbrechen");
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "M�chtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", price);
			ShowPlayerDialog(playerID, DIALOG_BUYVEHICLE, DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
		}
		case DIALOG_HOUSEOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten");// Item 0
			format(options, sizeof(options), "%s\nVerkaufen", options);// Item 1
			ShowPlayerDialog(playerID, DIALOG_HOUSEOPTIONS, DIALOG_STYLE_LIST, "Hausoptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_ORDERVEHICLE:
		{
			ShowPlayerDialog(playerID, DIALOG_ORDERVEHICLE, DIALOG_STYLE_LIST, "Fahrzeug bestellen", "Landstalker\nBravura\nBuffalo\nLinerunner\nPerenniel\nSentinel\nFiretruck", "Bestellen", "Abbrechen");
		}
		case DIALOG_RADIO:
		{
			new stations[1024];
			mysql_query("SELECT * FROM `radiostations`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(stations))
				{
					format(stations, sizeof(stations), "%s\n", stations);
				}
				format(stations, sizeof(stations), "%s%s", stations, GetMySQLField("Name"));
			}
			ShowPlayerDialog(playerID, DIALOG_RADIO, DIALOG_STYLE_LIST, "Radiosender w�hlen", stations, "OK", "Abbrechen");
		}
		case DIALOG_REFUEL:
		{
			new string[256];
			new maximum[256];
			GetStringArg(2, maximum);
			format(string, sizeof(string), "Wie viel m�chtest du tanken (0 - %s)?", maximum);
			ShowPlayerDialog(playerID, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP1:
		{
			ShowPlayerDialog(playerID, DIALOG_REGISTER_STEP1, DIALOG_STYLE_PASSWORD, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort f�r deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP2:
		{
			ShowPlayerDialog(playerID, DIALOG_REGISTER_STEP2, DIALOG_STYLE_PASSWORD, "Passwort wiederholen", "Gebe erneut das Passwort ein.", "Registrieren", "Zur�ck");
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowPlayerDialog(playerID, DIALOG_RESTARTGAMEMODE, DIALOG_STYLE_MSGBOX, "Gamemode neustarten", "Soll der Gamemode wirklich neugestartet werden?", "Ja", "Nein");
		}
		case DIALOG_SELECTINTERIOR:
		{
			new interiors[2048];
			new string[256];
			new query[256];
			new startID = getarg(3);
			new page;
			if (startID)
			{
				page = 2;
			}
			else
			{
				page = 1;
			}
			format(query, sizeof(query), "SELECT * FROM `interiors` LIMIT %d,75", startID);
			mysql_query(query);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(interiors))
				{
					format(interiors, sizeof(interiors), "%s\n", interiors);
				}
				format(interiors, sizeof(interiors), "%s%s", interiors, GetMySQLField("Name"));
			}
			mysql_free_result();
			switch (page)
			{
				case 1:
				{
					format(interiors, sizeof(interiors), "%s\nWeiter", interiors);
				}
				case 2:
				{
					format(interiors, sizeof(interiors), "%s\nZur�ck", interiors);
				}
			}
			format(string, sizeof(string), "Ziel ausw�hlen (Seite %d)", page);
			SetPVarInt(playerID, "InteriorDialogID", getarg(2));
			ShowPlayerDialog(playerID, DIALOG_SELECTINTERIOR, DIALOG_STYLE_LIST, string, interiors, "OK", "Abbrechen");
		}
		case DIALOG_TELEPORTLOCATIONS:
		{
			new locations[2048];
			mysql_query("SELECT * FROM `teleports`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(locations))
				{
					format(locations, sizeof(locations), "%s\n", locations);
				}
				format(locations, sizeof(locations), "%s%s", locations, GetMySQLField("Name"));
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, DIALOG_TELEPORTLOCATIONS, DIALOG_STYLE_LIST, "Teleportieren", locations, "OK", "Abbrechen");
		}
	}
}

ShowInteriorDialog(playerID, dialogID)
{
	ShowDialog(playerID, DIALOG_SELECTINTERIOR, dialogID, 0);
}

OnInteriorDialogSelect(playerID, dialogID, interiorID)
{
	switch (dialogID)
	{
		case INTERIORDIALOG_ADDBUILDING:
		{
			if (interiorID)
			{
				SetPVarInt(playerID, "AddBuilding_InteriorID", interiorID);
				ShowDialog(playerID, DIALOG_ADDBUILDING_NAME);
			}
			else
			{
				DeletePVar(playerID, "AddBuilding_Type");
				ShowDialog(playerID, DIALOG_ADDBUILDING_TYPE);
			}
		}
		case INTERIORDIALOG_SHOWINTERIOR:
		{
			if (interiorID)
			{
				if (TeleportToInterior(playerID, interiorID))
				{
					SetPlayerVirtualWorld(playerID, 0);
				}
			}
		}
	}
}