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
			trUnitOverrideAnimation(52,0,false,true,-1);
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
				mSetVar(attacker, "maxHealth", mGetVar(attacker, "maxHealth") + 2);
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
				trUnitOverrideAnimation(39, 0, false, true, -1);
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
				trUnitOverrideAnimation(50, 0, false, true, -1);
				trQuestVarSet("p"+p+"spellDamage", trQuestVarGet("p"+p+"spellDamage") + 1);
				trQuestVarSet("p"+p+"spellDamageNonOracle", trQuestVarGet("p"+p+"spellDamageNonOracle") + 1);
				if(trQuestVarGet("chats_FireMage_0") == 0){
					trQuestVarSet("chats_FireMage_0", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Fire Mage</color>: You are only making me stronger!");
					trSoundPlayFN("pha2.wav","1",-1,"","");
				}
			}
		}
		/*
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
		*/
		case ATTACK_POLYMORPH:
		{
			if ((mGetVar(target, "health") > 0) && (mGetVar(target, "spell") == SPELL_NONE)) {
				trSoundPlayFN("pigpower.wav","1",-1,"","");
				trUnitSelectClear();
				trUnitSelect(""+target);
				trMutateSelected(kbGetProtoUnitID("Hero Boar 2"));
				deployAtTile(0, "Curse SFX", mGetVar(target, "tile"));
				mSetVar(target, "proto", kbGetProtoUnitID("Hero Boar 2"));
				mSetVar(target, "spell", 0);
				mSetVar(target, "cost", 1);
				mSetVar(target, "attack", 1);
				mSetVar(target, "health", 1);
				mSetVar(target, "speed", 2);
				mSetVar(target, "range", 1);
				mSetVar(target, "keywords", 0);
				mSetVar(target, "onAttack", 0);
				mSetVar(target, "onDeath", 0);
				mSetVar(target, "scale", 1);
				mSetString(target, "ability", "");
			}
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
			trQuestVarSet("p"+p+"manaflow", 2 + trQuestVarGet("p"+p+"manaflow"));
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
				trVectorQuestVarSet("dir", trGetUnitVector("start", "end"));
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
		case ATTACK_MILL:
		{
			trQuestVarSet("p1drawCards", 1 + trQuestVarGet("p1drawCards"));
			trQuestVarSet("p2drawCards", 1 + trQuestVarGet("p2drawCards"));
		}
		case ATTACK_BOOST_HAND:
		{
			for(i=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				mSetVarByQV("p"+p+"hand", "attack", 1 + mGetVarByQV("p"+p+"hand", "attack"));
			}
			trSoundPlayFN("wolfhowl.wav","1",-1,"","");
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
			trVectorQuestVarSet("dir1", trGetUnitVector3d("start", "end"));
			trVectorQuestVarSet("dir2", rotationMatrix(trGetUnitVector("start", "end"), 0.0, 1.0));
			
			trSetUnitOrientation(trVectorQuestVarGet("dir1"), trVectorQuestVarGet("dir2"), true);
			trUnitHighlight(3.0, false);
			yAddToDatabase("mirrorTowerLasers", "next");
			yAddUpdateVar("mirrorTowerLasers", "length", trDistanceBetweenVectors3d("start", "end") * 1.25);
			yAddUpdateVar("mirrorTowerLasers", "timeout", trTimeMS() + 1500);
			xsEnableRule("attack_animate_mirror_laser");
		}
		case ATTACK_SPLASH:
		{
			trCameraShake(0.5, 0.5);
			trQuestVarSetFromRand("sound", 1, 5, true);
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
			spell = mGetVar(target, "tile");
			deployAtTile(0, "Meteor Impact Ground", spell);
			for (x=0; < zGetVarByIndex("tiles", "neighborCount", spell)) {
				count = zGetVarByIndex("tiles", "neighbor"+x, spell);
				target = zGetVarByIndex("tiles", "occupant", count);
				if (target > 0) {
					damageUnit(target, mGetVar(attacker, "attack"));
				}
			}
		}
		case ATTACK_TEAMWORK:
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+attacker));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (HasKeyword(ATTACK_TEAMWORK, 1*mGetVarByQV("allUnits", "OnAttack")) == false) { // no infinite loops for you
					if ((mGetVarByQV("allUnits", "player") == p) && (trDistanceToVectorSquared("allUnits", "pos") < 64)) {
						startAttack(1*trQuestVarGet("allUnits"), target);
					}
				}
			}
			deployAtTile(0, "Dust Large", 1*mGetVar(target, "tile"));
		}
		case ATTACK_POSSESSED:
		{
			startAttack(1*trQuestVarGet("p"+p+"commander"), target);
		}
		case ATTACK_SING:
		{
			if (mGetVarByQV("p"+p+"commander", "action") < ACTION_SLEEPING) {
				mSetVarByQV("p"+p+"commander", "action", ACTION_READY);
			}
		}
		case ATTACK_NICKONHAWK:
		{
			int proto = 0;
			int manaCost = trQuestVarGet("p"+p+"mana");			
			
			while(manaCost >= 0){
				for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
					proto = yDatabaseNext("p"+p+"deck");
					if (yGetVar("p"+p+"deck", "spell") == SPELL_NONE && trQuestVarGet("card_"+proto+"_cost") == manaCost) {
						yRemoveFromDatabase("p"+p+"deck");
						break;
					}
					proto = 0;
				}
				if(proto > 0){
					trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - trQuestVarGet("card_"+proto+"_cost"));
					updateMana();
					updateHandPlayable(p);
					manaCost = -1;
				} else {
					manaCost = manaCost - 1;
				}			
			}		
			
			if(proto > 0){
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				yClearDatabase("odyTiles");
				findAvailableTiles(1*mGetVar(attacker, "tile"), 1, "odyTiles", false);
				if(yGetDatabaseCount("odyTiles") > 0){
					int activeUnit = summonAtTile(1*yDatabaseNext("odyTiles"),p,proto);			
					if(HasKeyword(CHARGE, 1*mGetVar(activeUnit, "keywords")) == true){
						mSetVar(activeUnit, "action", ACTION_READY);
						if((proto == kbGetProtoUnitID("Hero Greek Argo")) && (trQuestVarGet("chats_Argo_0") == 0)){
							trFadeOutAllSounds(0.0);
							trQuestVarSet("chats_Argo_0", 1);
							trSoundPlayFN("dialog\en\ajax097.mp3","1",-1,"","");
							ChatLog(0, "<color={Playercolor("+p+")}>Hawk's Captain</color>: Do I always have to watch your back?");
							MusicHigh();
						}
					} else {
						mSetVar(activeUnit, "action", ACTION_SLEEPING);				
					}	
				} else {
					ChatLog(1, "No space to summon!");
				}
			} else {
				ChatLog(1, "Nothing to summon!");
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
		} else {
			scale = scale / 75;
			trSetSelectedScale(scale, scale, yGetVar("mirrorTowerLasers", "length"));
		}
	} else {
		xsDisableRule("attack_animate_mirror_laser");
	}
}
