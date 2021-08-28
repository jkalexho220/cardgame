void OnAttack(int attacker = 0, int target = 0, int event = 0) {
	int p = mGetVar(attacker, "player");
	int spell = 0;
	int count = 0;
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
		case ATTACK_DISCOUNT:
		{
			trUnitSelectClear();
			trUnitSelect(""+attacker);
			trUnitOverrideAnimation(52,0,0,1,-1);
			for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand", true);
				if (mGetVarByQV("p"+p+"hand", "spell") > 0) {
					spell = mGetVarByQV("p"+p+"hand", "spell");
					mSetVarByQV("p"+p+"hand", "cost", xsMax(0, mGetVarByQV("p"+p+"hand", "cost") - 1));
					trUnitChangeName("("+1*mGetVarByQV("p"+p+"hand","cost")+") " + trStringQuestVarGet("spell_"+spell+"_name"));
				}
			}
			updateHandPlayable();
		}
		case ATTACK_GET_ARCANE:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				trQuestVarSetFromRand("spellChosen", SPELL_SPARK, SPELL_APOCALYPSE, true);
				addCardToHand(p, 0, 1*trQuestVarGet("spellChosen"), false);
				updateHandPlayable(p);
			}
		}
		case ATTACK_YEET:
		{
			if ((trQuestVarGet("activePlayer") == p) == false) {
				if ((mGetVar(target, "health") > 0) && (mGetVar(target, "spell") == 0)) {
					trSoundPlayFN("shockwave.wav","1",-1,"","");
					trSoundPlayFN("suckup2.wav","1",-1,"","");
					deployAtTile(0, "Tremor", 1*mGetVar(target, "tile"));
					deployAtTile(0, "Dust Large", 1*mGetVar(target, "tile"));
					returnToHand(target);
				}
			}
		}
		case ATTACK_GET_MANAFLOW:
		{
			trQuestVarSet("p"+p+"manaflow", 1 + trQuestVarGet("p"+p+"manaflow"));
		}
		case ATTACK_RETURN:
		{
			if ((mGetVar(target, "health") > 0) && (mGetVar(target, "spell") == SPELL_NONE)) {
				deployAtTile(0, "Meteor Impact Water", 1*mGetVar(target, "tile"));
				trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
				trSoundPlayFN("suckup1.wav","1",-1,"","");
				returnToHand(target);
			}
		}
		case ATTACK_PUSH:
		{
			if (mGetVar(target, "health") > 0) {
				deployAtTile(0, "Meteor Impact Water", 1*mGetVar(target, "tile"));
				trSoundPlayFN("shockwave.wav","1",-1,"","");
				trSoundPlayFN("meteorsplash.wav","1",-1,"","");
				trVectorQuestVarSet("end", kbGetBlockPosition(""+target));
				trVectorQuestVarSet("start", kbGetBlockPosition(""+attacker));
				trVectorQuestVarSet("dir", zGetUnitVector("start", "end"));
				pushUnit(target, "dir");
			}
		}
		case ATTACK_GET_ZOMBIE:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, kbGetProtoUnitID("Minion"), 0, false);
				updateHandPlayable(p);
			}
		}
		case ATTACK_SUMMON_ZOMBIE:
		{
			if (mGetVar(target, "health") <= 0) {
				deathSummonQueue(1*mGetVar(target, "tile"), p, "Minion");
			}
		}
		case ATTACK_POISON:
		{
			if ((mGetVar(target, "spell") == SPELL_NONE) && (mGetVar(target, "health") > 0)) {
				mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), DECAY));
				trUnitSelectClear();
				trUnitSelect(""+target);
				spyEffect("Poison SFX");
				trSoundPlayFN("lampadesblood.wav","1",-1,"","");
				trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
			}
		}
		case ATTACK_GET_MINION:
		{
			if (mGetVar(target, "health") <= 0) {
				if (yGetDatabaseCount("p"+p+"hand") < 10) {
					addCardToHand(p, 1*mGetVar(target, "proto"));
					updateHandPlayable(p);
				}
			}
		}
		case ATTACK_GET_FENRIS:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, kbGetProtoUnitID("Ornlu"), 0, false);
				updateHandPlayable(p);
			}
		}
	}
}