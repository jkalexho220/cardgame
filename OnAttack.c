void OnAttack(int attacker = 0, int target = 0, int event = 0) {
	int p = mGetVar(attacker, "player");
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
			if(mGetVar(target, "health")<=0 && mGetVar(target, "OnDeath")>0){
				mSetVar(target, "OnDeath", 0);
				deployAtTile(0, "Olympus Temple SFX", 1*mGetVar(target, "tile"));
				trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
			}
		}
		case ATTACK_ANIMATE_ORACLE:
		{
			trUnitSelectClear();
			trUnitSelect(""+attacker);
			trUnitOverrideAnimation(52,0,0,1,-1);
		}
	}
}