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
			trSoundPlayFN("woodcrush"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
		}
		case ATTACK_GET_WINDSONG:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, 0, SPELL_SING, true);
				updateHandPlayable(p);
			}
		}
		case ATTACK_BLOCK_DEATH:
		{
			if(yGetVarByIndex("allUnits", "health", target)<=0 && yGetVarByIndex("allUnits", "OnDeath", target)>0){
				ySetVarByIndex("allUnits", "OnDeath", target, 0);
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetUnitAtIndex("allUnits", target)));
				DeploySober("Olympus Temple SFX", "pos");
				trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
			}
		}
	}
}