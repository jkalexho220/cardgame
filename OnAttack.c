void OnAttack(int attacker = 0, int target = 0, int event = 0) {
	int p = yGetVarByIndex("allUnits", "player", attacker);
	switch(event)
	{
		case ATTACK_DRAW_CARD:
		{
			drawCard(p);
		}
		case ATTACK_STUN_TARGET:
		{
			stunUnit(target);
			trQuestVarSetFromRand("sound", 1, 3, true);
			trSoundPlayFN("crushmetal"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
		}
	}
}