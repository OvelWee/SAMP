UpdatePayDay()
{
	// TODO: Muss �berpr�ft werden Welcher Job
	// TODO: Muss �berpr�ft werden ob ihm der Job Geh�rt
	// TODO: Float Money auf den preis (Wen normaler mitarbeiter = Merit) (Wen Boss also dem es geh�rt = BossMerit) setzen
	new Float:money = 5600.21;
	SendClientMessage(playerid, COLOR_INFO, "PayDay!");
	FormatNew:string[30]("Dein Lohn betr�gt $%s", money);
	SendClientMessage(playerid, COLOR_INFO, string);
	SetUserDBValue(playerid, "BankMoney", Float2Str(floatadd(floatstr(GetUserDBValue(playerid, "BankMoney")), money)));
	printf ("Loading UpdatePayDay");
}