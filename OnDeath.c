void checkKeys(int p = 0) {
	if (trQuestVarGet("p"+p+"loveKey") + trQuestVarGet("p"+p+"laserKey") + trQuestVarGet("p"+p+"toyKey") == 3) {
		trSoundPlayFN("cinematics\17_in\arrive.mp3","1",-1,"","");
		trSoundPlayFN("spybirth.wav","1",-1,"","");
		ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has collected all the keys!");
		addCardToDeck(p, "Statue of Lightning", SPELL_THE_CALLING);
		trQuestVarSet("p"+p+"loveKey", 0);
		trQuestVarSet("p"+p+"laserKey", 0);
		trQuestVarSet("p"+p+"toyKey", 0);
	}
}

void deathSummonQueue(int tile = 0, int p = 0, string proto = "", int hand = -1) {
	int push = modularCounterNext("deathSummonPush");
	trQuestVarSet("deathSummon"+push+"proto", kbGetProtoUnitID(proto));
	trQuestVarSet("deathSummon"+push+"player", p);
	trQuestVarSet("deathSummon"+push+"tile", tile);
	trQuestVarSet("deathSummon"+push+"hand", hand);
}

bool OnDeath(int event = -1, int unit = 0){
	int p = mGetVar(unit, "player");
	int count = 0;
	int target = 0;
	int tile = 0;
	int proto = 0;
	bool checkAgain = false;
	switch(event)
	{
		case DEATH_DRAW_CARD:
		{
			drawCard(p);
		}
		case DEATH_OPPONENT_DRAW_CARD:
		{
			drawCard(3-p);
		}
		case DEATH_EGG:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Phoenix Egg");
		}
		case DEATH_GET_ARCANE:
		{
			trQuestVarSetFromRand("spellChosen", SPELL_SPARK, SPELL_APOCALYPSE, true);
			generateCard(p, 0, 1*trQuestVarGet("spellChosen"));
		}
		case DEATH_SUMMON_ZOMBIE:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Minion");
		}
		case DEATH_SUMMON_SHADOW:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Shade of Hades");
		}
		case DEATH_GET_SCRAP:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, 0, SPELL_SCRAP_METAL);
			}
		}
		case DEATH_POISON_MIST:
		{
			for(x=0; < zGetVarByIndex("tiles", "neighborCount", 1*mGetVar(unit, "tile"))) {
				tile = zGetVarByIndex("tiles", "neighbor"+x, 1*mGetVar(unit, "tile"));
				target = zGetVarByIndex("tiles", "occupant", tile);
				if (target > 0) {
					if (mGetVar(target, "spell") == SPELL_NONE) {
						mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), DECAY));
						trUnitSelectClear();
						trUnitSelect(""+target);
						spyEffect("Poison SFX");
					}
				}
			}
			deployAtTile(0, "Lampades Blood", 1*mGetVar(unit, "tile"));
			trSoundPlayFN("lampadesblood.wav","1",-1,"","");
			trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
		}
		case DEATH_DARKNESS_RETURNS:
		{
			addCardToDeck(p, "Guardian");
			trSoundPlayFN("cinematics\32_out\kronosbehinddorrshort.mp3","1",-1,"","");
			deployAtTile(0, "Kronny Birth SFX", 1*mGetVar(unit, "tile"));
		}
		case DEATH_GET_ATTACK:
		{
			trQuestVarSet("p"+p+"yeebBonus", 1 + trQuestVarGet("p"+p+"yeebBonus"));
			mSetVarByQV("p"+p+"commander", "attack", 1 + mGetVarByQV("p"+p+"commander", "attack"));
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case DEATH_BOOM_SMALL:
		{
			deployAtTile(0, "Meteor Impact Ground", 1*mGetVarByQV("allUnits", "tile"));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+unit));
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (trQuestVarGet("allUnits") == unit) {
					continue;
				} else if (trDistanceToVectorSquared("allUnits", "pos") < 40) {
					startAttack(unit, 1*trQuestVarGet("allUnits"), false, false);
					checkAgain = true;
				}
			}
			trSoundPlayFN("meteorsmallhit.wav","1",-1,"","");
		}
		case DEATH_SUMMON_RANDOM:
		{
			for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
				proto = yDatabaseNext("p"+p+"deck");
				if (yGetVar("p"+p+"deck", "spell") == SPELL_NONE) {
					yRemoveFromDatabase("p"+p+"deck");
					break;
				}
			}
			deathSummonQueue(1*mGetVar(unit, "tile"), p, kbGetProtoUnitName(proto));
		}
		case DEATH_SUMMON_BEETLE:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Scarab");
			trQuestVarSetFromRand("sound", 1, 2, true);
			trSoundPlayFN("spiders"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
		}
		case DEATH_DAMAGE_ENEMY:
		{
			deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("p"+(3-p)+"commander", "tile"));
			damageUnit(1*trQuestVarGet("p"+(3-p)+"commander"), 2);
		}
		case DEATH_REDUCE_COST:
		{
			for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				mSetVarByQV("p"+p+"hand", "cost", mGetVarByQV("p"+p+"hand", "cost") - 1);
			}
			trSoundPlayFN("flamingweapons.wav","1",-1,"","");
		}
		case DEATH_SUMMON_FROM_HAND:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Hawk", mGetVar(unit, "attack"));
		}
		case DEATH_BOOST_HAND:
		{
			target = mGetVar(unit, "keywords");
			for(i=0; < NUM_KEYWORDS) {
				if (HasKeyword(i, target)) {
					for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
						yDatabaseNext("p"+p+"hand");
						if (mGetVarByQV("p"+p+"hand", "spell") == 0) {
							if (HasKeyword(i, mGetVarByQV("p"+p+"hand", "keywords")) == false) {
								mSetVarByQV("p"+p+"hand", "keywords", Keyword(i) + mGetVarByQV("p"+p+"hand", "keywords"));
							}
						}
					}
				}
			}
		}
		case DEATH_LOVE:
		{
			ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has acquired the LOVE key!");
			trSoundPlayFN("cinematics\17_in\weirdthing.mp3","1",-1,"","");
			trQuestVarSet("p"+p+"loveKey", 1);
			checkKeys(p);
		}
		case DEATH_LASERS:
		{
			ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has acquired the LASER key!");
			trSoundPlayFN("cinematics\17_in\weirdthing.mp3","1",-1,"","");
			trQuestVarSet("p"+p+"laserKey", 1);
			checkKeys(p);
		}
		case DEATH_TOYS:
		{
			ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has acquired the TOY key!");
			trSoundPlayFN("cinematics\17_in\weirdthing.mp3","1",-1,"","");
			trQuestVarSet("p"+p+"toyKey", 1);
			checkKeys(p);
		}
	}
	return (checkAgain);
}

void removeDeadUnits() {
	bool checkAgain = false;
	int pointer = 0;
	int p = 0;
	checkAgain = false;
	for(y=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (mGetVarByQV("allUnits", "health") <= 0 && mGetVarByQV("allUnits", "OnDeath") > 0) {
			pointer = yGetPointer("allUnits");
			/*
			OnDeath events.
			*/
			int events = 1*mGetVarByQV("allUnits", "OnDeath");
			mSetVarByQV("allUnits", "OnDeath", 0);
			int n = 1*xsPow(2, DEATH_EVENT_COUNT - 1);
			for(x=DEATH_EVENT_COUNT - 1; >=0) {
				if (events >= n) {
					checkAgain = OnDeath(x, 1*trQuestVarGet("allUnits")) || checkAgain;
					events = events - n;
				}
				n = n / 2;
			}
			ySetPointer("allUnits", pointer);
		}
	}
	if (checkAgain) {
		xsEnableRule("chain_reaction_death");
		trQuestVarSet("chainReactionDeath", 1);
	} else {
		trQuestVarSet("chainReactionDeath", 0);
	}
	
	trQuestVarSet("p1deathCount", 0);
	trQuestVarSet("p2deathCount", 0);
	int proto = 0;
	for(y=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		if (trQuestVarGet("allUnits") >= 128) {
			ThrowError("removeDeadUnits() - Invalid unit! " + 1*trQuestVarGet("allUnits"));
		}
		if (mGetVarByQV("allUnits", "health") <= 0) {
			proto = mGetVarByQV("allUnits", "proto");
			if ((kbProtoUnitIsUnitType(proto, 937)) ||
				(proto == kbGetProtoUnitID("Lampades")) ||
				(proto == kbGetProtoUnitID("Carcinos")) ||
				(proto == kbGetProtoUnitID("Scarab")) ||
				(proto == kbGetProtoUnitID("Arkantos God")) ||
				(proto == kbGetProtoUnitID("Eitri")) ||
				(proto == kbGetProtoUnitID("Ape of Set")) ||
				(proto == kbGetProtoUnitID("Spider Egg"))) {
				trDamageUnitPercent(-100);
				trUnitChangeProtoUnit("Spy Eye");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("allUnits"));
				trMutateSelected(1*mGetVarByQV("allUnits", "proto"));
				trUnitOverrideAnimation(6, 0, false, true, -1);
			} else {
				trUnitDelete(false);
			}
			
			int tile = mGetVarByQV("allUnits", "tile");
			zSetVarByIndex("tiles", "occupant", tile, 0);
			if (HasKeyword(GUARD, 1*mGetVarByQV("allUnits", "keywords"))) {
				tileGuard(tile, false);
			}
			p = mGetVarByQV("allUnits", "player");
			trQuestVarSet("p"+p+"deathCount", 1 + trQuestVarGet("p"+p+"deathCount"));
			mSetVarByQV("allUnits", "stunSFX", 0);
			yRemoveFromDatabase("allUnits");
		}
	}
	
	for (x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		switch(1*mGetVarByQV("allUnits", "proto"))
		{
			case kbGetProtoUnitID("Einheriar"):
			{
				p = mGetVarByQV("allUnits","player");
				if (trQuestVarGet("p"+p+"deathCount") > 0) {
					mSetVarByQV("allUnits", "attack", trQuestVarGet("p"+p+"deathCount") + mGetVarByQV("allUnits", "attack"));
					mSetVarByQV("allUnits", "health", trQuestVarGet("p"+p+"deathCount") + mGetVarByQV("allUnits", "health"));
					mSetVarByQV("allUnits", "scale", 0.25*trQuestVarGet("p"+p+"deathCount") + mGetVarByQV("allUnits", "scale"));
					scaleUnit(1*trQuestVarGet("allUnits"));
				}
			}
		}
	}
	
	for(p=2; >0) {
		if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_ANRAHEIR) {
			trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") + trQuestVarGet("p"+p+"deathCount"));
			updateHandPlayable(p);
		}
	}
	
	/*
	summon units from deathrattles on a first-come-first-served basis
	If multiple summons conflict on the same tile, the first one gets it.
	*/
	int pop = 0;
	int unit = 0;
	int cost = 0;
	while (trQuestVarGet("deathSummonPush") != trQuestVarGet("deathSummonPop")) {
		pop = modularCounterNext("deathSummonPop");
		if (zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("deathSummon"+pop+"tile")) == 0) {
			// if summon from hand (Capricorn effect)
			if (trQuestVarGet("deathSummon"+pop+"hand") >= 0) {
				p = trQuestVarGet("deathSummon"+pop+"player");
				unit = -1;
				cost = 0;
				for(i=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					if (mGetVarByQV("p"+p+"hand", "spell") == 0) {
						if (mGetVarByQV("p"+p+"hand", "cost") <= trQuestVarGet("deathSummon"+pop+"hand")) {
							if (mGetVarByQV("p"+p+"hand", "cost") > cost) {
								unit = yGetPointer("p"+p+"hand");
								cost = mGetVarByQV("p"+p+"hand", "cost");
							}
						}
					}
				}
				if (unit > 0) {
					ySetPointer("p"+p+"hand", unit);
					yAddToDatabase("allUnits", "p"+p+"hand");
					unit = trQuestVarGet("p"+p+"hand");
					teleportToTile(unit, 1*trQuestVarGet("deathSummon"+pop+"tile"));

					zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
					yRemoveFromDatabase("p"+p+"hand");
					
					zSetVarByIndex("tiles", "occupant", 1*trQuestVarGet("deathSummon"+pop+"tile"), unit);
				}
			} else {
				unit = summonAtTile(1*trQuestVarGet("deathSummon"+pop+"tile"),
					1*trQuestVarGet("deathSummon"+pop+"player"),
					1*trQuestVarGet("deathSummon"+pop+"proto"));
			}
			if (HasKeyword(CHARGE, 1*mGetVar(unit, "keywords"))) {
				mSetVar(unit, "action", ACTION_READY);
			} else {
				mSetVar(unit, "action", ACTION_SLEEPING);
			}
		}
	}
	updateAuras();
	
	if (mGetVarByQV("p1commander", "health") <= 0) {
		trQuestVarSet("p1defeated", 1);
		xsEnableRule("match_end");
	}
	if (mGetVarByQV("p2commander", "health") <= 0) {
		trQuestVarSet("p2defeated", 1);
		xsEnableRule("match_end");
	}
}



void returnToHand(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	zSetVarByIndex("tiles", "occupant", 1*mGetVar(unit, "tile"), 0);
	if (HasKeyword(GUARD, 1*mGetVar(unit, "keywords"))) {
		tileGuard(1*mGetVar(unit, "tile"), false);
	}
	deployAtTile(0, "Vortex Start linked", 1*mGetVar(unit, "tile"));
	if (yGetDatabaseCount("p"+p+"hand") < 10) {
		ChatLog(p, trStringQuestVarGet("card_" + proto + "_Name") + " returned to hand.");
		for(x=yGetDatabaseCount("allUnits"); >0) {
			if (yDatabaseNext("allUnits") == unit) {
				yRemoveFromDatabase("allUnits");
				break;
			}
		}
		trSoundPlayFN("hitpointsmax.wav","1",-1,"","");
		trUnitSelectClear();
		trUnitSelect(""+unit);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		mSetVar(unit, "played", 0);
		addCardToHand(p, proto, 0, false);
		updateAuras();
		updateHandPlayable();
	} else {
		trSoundPlayFN("cantdothat.wav","1",-1,"","");
		ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("card_" + proto + "_Name"));
		mSetVar(unit, "health", 0);
		damageUnit(unit, 999);
		removeDeadUnits();
	}
}

rule chain_reaction_death
highFrequency
inactive
{
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) {
		xsDisableSelf();
		removeDeadUnits();
	}
}
