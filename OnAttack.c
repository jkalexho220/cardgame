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
			generateCard(p, 0, SPELL_SING, true);
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
			updateHandPlayable(p);
		}
		case ATTACK_OVERKILL_HEALS:
		{
			trUnitSelectClear();
			trUnitSelect(""+attacker);
			if(mGetVar(attacker, "health") > 0 && mGetVar(target, "health") <= 0){
				mSetVar(attacker, "health", mGetVar(attacker, "health") + 2);
				deployAtTile(0, "Regeneration SFX", 1*mGetVar(attacker, "tile"));
				trSoundPlayFN("colossuseat.wav","1",-1,"","");
				trSoundPlayFN("meatgather1.wav","1",-1,"","");
			}
		}
		case ATTACK_RALLY:
		{
			if(trQuestVarGet("activePlayer") == p){
				trUnitSelectClear();
				trUnitSelect(""+attacker);
				trMutateSelected(kbGetProtoUnitID("General Melagius"));
				trUnitOverrideAnimation(39, 0, 0, 1, -1);
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "player") == p && mGetVarByQV("allUnits", "spell") == 0) {
						trUnitHighlight(0.1, false);
						mSetVarByQV("allUnits", "attack", mGetVarByQV("allUnits", "attack") + 1);
						deployAtTile(0, "Arkantos Boost SFX", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
				if(trQuestVarGet("chats_GeneralStore_0") == 0){
					trQuestVarSet("chats_GeneralStore_0", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>General Store</color>: To battle!");	
				}				
			}
		}
		case ATTACK_SPELL_DAMAGE:
		{
			if(trQuestVarGet("activePlayer") == (3-p)){
				trUnitSelectClear();
				trUnitSelect(""+attacker);
				trUnitOverrideAnimation(50, 0, 0, 1, -1);
				trQuestVarSet("p"+p+"spellDamage", trQuestVarGet("p"+p+"spellDamage") + 1);
				trQuestVarSet("p"+p+"spellDamageNonOracle", trQuestVarGet("p"+p+"spellDamageNonOracle") + 1);
				if(trQuestVarGet("chats_FireMage_0") == 0){
					trQuestVarSet("chats_FireMage_0", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Fire Mage</color>: You are only making me stronger!");
					trSoundPlayFN("pha2.wav","1",-1,"","");	
				}
			}
		}
		case ATTACK_ARCANE_MISSLE:
		{		
			yClearDatabase("randomEnemy");	
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == (3-p)) {
					yAddToDatabase("randomEnemy", "allUnits");
				}
			}
			trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("randomEnemy"), true);
			for(x=trQuestVarGet("temp"); >0) {
				yDatabaseNext("randomEnemy");
			}
			if (HasKeyword(LIGHTNING, 1*mGetVar(attacker, "keywords"))) {
				// too lazy to test this
				//lightning(1*trQuestVarGet("randomEnemy"), 1 + trQuestVarGet("p"+p+"spellDamage"), false);
				damageUnit(1*trQuestVarGet("randomEnemy"), 1 + trQuestVarGet("p"+p+"spellDamage"));
			} else {
				damageUnit(1*trQuestVarGet("randomEnemy"), 1 + trQuestVarGet("p"+p+"spellDamage"));				
			}
			deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("randomEnemy", "tile"));
		}
		case ATTACK_DRAW_CARD_ENEMY_COST:
		{
			drawCard(p);
			mSetVarByQV("next", "cost", xsMax(0, mGetVarByQV("next", "cost") - trCountUnitsInArea("128",(3-p),"Unit",45)));
		}
		case ATTACK_GET_ARCANE:
		{
			trQuestVarSetFromRand("spellChosen", SPELL_SPARK, SPELL_APOCALYPSE, true);
			generateCard(p, 0, 1*trQuestVarGet("spellChosen"));
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
			generateCard(p, 1*kbGetProtoUnitID("Minion"));
		}
		case ATTACK_SUMMON_ZOMBIE:
		{
			if (mGetVar(target, "health") <= 0) {
				deathSummonQueue(1*mGetVar(target, "tile"), p, "Minion");
			}
		}
		case ATTACK_SUMMON_TREE:
		{
			if (mGetVar(target, "health") <= 0) {
				deathSummonQueue(1*mGetVar(target, "tile"), p, "Walking Woods Marsh");
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
			generateCard(p, 1*kbGetProtoUnitID("Ornlu"));
		}
		case ATTACK_ANIMATE_TOWER:
		{
			trCameraShake(1.0, 0.5);
			trQuestVarSetFromRand("sound", 1, 5, true);
			trSoundPlayFN("ui\thunder"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
			deployAtTile(0, "Meteor Impact Ground", 1*mGetVar(target, "tile"));
			trQuestVarSet("next", deployAtTile(1, "Dwarf", 1*mGetVar(target, "tile")));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));
			trVectorSetUnitPos("end", "next");
			trVectorQuestVarSet("start", kbGetBlockPosition(""+attacker));
			trQuestVarSet("starty", 8);
			trVectorQuestVarSet("dir1", zGetUnitVector3d("start", "end"));
			trVectorQuestVarSet("dir2", zGetUnitVector("start", "end"));
			// rotating the vector dir2 by 90 degrees
			trQuestVarSet("temp", trQuestVarGet("dir2x"));
			trQuestVarSet("dir2x", 0.0 - trQuestVarGet("dir2z"));
			trQuestVarSet("dir2z", trQuestVarGet("temp"));

			trSetUnitOrientation(trVectorQuestVarGet("dir1"), trVectorQuestVarGet("dir2"), true);
			trUnitHighlight(3.0, false);
			yAddToDatabase("mirrorTowerLasers", "next");
			yAddUpdateVar("mirrorTowerLasers", "length", zDistanceBetweenVectors3d("start", "end") * 1.25);
			yAddUpdateVar("mirrorTowerLasers", "timeout", trTimeMS() + 1500);
			xsEnableRule("attack_animate_mirror_laser");
		}
		case ATTACK_TEAMWORK:
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+attacker));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (HasKeyword(ATTACK_TEAMWORK, 1*mGetVarByQV("allUnits", "OnAttack")) == false) { // no infinite loops for you
					if ((mGetVarByQV("allUnits", "player") == p) && (zDistanceToVectorSquared("allUnits", "pos") < 64)) {
						startAttack(1*trQuestVarGet("allUnits"), target);
					}
				}
			}
			deployAtTile(0, "Dust Large", 1*mGetVar(target, "tile"));
		}
		case ATTACK_SING:
		{
			if (mGetVarByQV("p"+p+"commander", "action") < ACTION_SLEEPING) {
				mSetVarByQV("p"+p+"commander", "action", ACTION_READY);
			}
		}
	}
}


rule attack_animate_mirror_laser
highFrequency
inactive
{
	if (yGetDatabaseCount("mirrorTowerLasers") > 0) {
		yDatabaseNext("mirrorTowerLasers", true);
		float scale = yGetVar("mirrorTowerLasers", "timeout") - trTimeMS();
		if (scale < 0) {
			trUnitDestroy();
			yRemoveFromDatabase("mirrorTowerLasers");
			yRemoveUpdateVar("mirrorTowerLasers", "length");
			yRemoveUpdateVar("mirrorTowerLasers", "timeout");
		} else {
			scale = scale / 75;
			trSetSelectedScale(scale, scale, yGetVar("mirrorTowerLasers", "length"));
		}
	} else {
		xsDisableRule("attack_animate_mirror_laser");
	}
}