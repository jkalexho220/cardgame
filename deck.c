/*
Fischer-Yates shuffle
*/
void shuffleDeck(int p = 0) {
	int i = 0;
	for(x=yGetDatabaseCount("p"+p+"deck")-1; >=0) {
		trQuestVarSetFromRand("pos", 0, x, true);
		i = trQuestVarGet("pos");
		trQuestVarSet("tempProto", yGetUnitAtIndex("p"+p+"deck", i));
		trQuestVarSet("tempSpell", yGetVarByIndex("p"+p+"deck", "spell", i));

		ySetUnitAtIndex("p"+p+"deck", i, yGetUnitAtIndex("p"+p+"deck", x));
		ySetVarByIndex("p"+p+"deck", "spell", i, yGetVarByIndex("p"+p+"deck", "spell", x));

		ySetUnitAtIndex("p"+p+"deck", x, 1*trQuestVarGet("tempProto"));
		ySetVarByIndex("p"+p+"deck", "spell", x, trQuestVarGet("tempSpell"));
	}
}
/* 
Updates the hand UI by highlighting cards that the user can
afford to play
*/
void updateHandPlayable(int p = 0) {
	for(x=zGetBankCount("p"+p+"handPos"); >0) {
		zBankNext("p"+p+"handPos", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	int cost = 0;
	trQuestVarSet("p"+p+"minionDiscount", trCountUnitsInArea("128",p,"Throwing Axeman",45));
	trQuestVarSet("p"+p+"spellDiscount", trCountUnitsInArea("128",p,"Priest",45));
	for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
		yDatabaseNext("p"+p+"hand");
		cost = mGetVarByQV("p"+p+"hand", "cost");
		if (mGetVarByQV("p"+p+"hand", "spell") > 0) {
			cost = cost - trQuestVarGet("p"+p+"spellDiscount");
		} else {
			cost = cost - trQuestVarGet("p"+p+"minionDiscount");
		}
		if (HasKeyword(OVERFLOW, 1*mGetVarByQV("p"+p+"hand", "keywords"))) {
			cost = cost - trQuestVarGet("p"+p+"manaflow");
		}
		if (cost <= trQuestVarGet("p"+p+"mana")) {
			trUnitSelectClear();
			trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
			trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
		}
	}
}

void addCardToDeck(int p = 0, string proto = "", int spell = 0) {
	if (spell == 0) {
		trQuestVarSet("proto", kbGetProtoUnitID(proto));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", 0);
	} else {
		trQuestVarSet("proto", kbGetProtoUnitID("Statue of Lightning"));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", spell);
	}
}

void addCardToDeckByIndex(int p = 0, int card = 0) {
	int spell = CardToSpell(card);
	if (spell == 0) {
		trQuestVarSet("proto", CardToProto(card));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", 0);
	} else {
		trQuestVarSet("proto", kbGetProtoUnitID("Statue of Lightning"));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", spell);
	}	
}

/* 
This function should only be called if there is room in the hand!
*/
void addCardToHand(int p = 0, int proto = 0, int spell = 0, bool fleeting = false) {
	trQuestVarSet("next", CardInstantiate(p, proto, spell));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true); 
	
	if (spell > SPELL_NONE) {
		proto = kbGetProtoUnitID("Statue of Lightning");
	}

	yAddToDatabase("p"+p+"hand", "next");
	
	trUnitHighlight(3, true);

	if (fleeting) {
		mSetVarByQV("next", "keywords", SetBit(1*trQuestVarGet("card_" + proto + "_Keywords"), FLEETING));
	}

	if ((trCountUnitsInArea("128",p,"Heka Gigantes",45) > 0) && (spell == SPELL_NONE)) {
		mSetVarByQV("next", "keywords", SetBit(1*trQuestVarGet("card_" + proto + "_Keywords"), OVERFLOW));
	}

	// Find an empty position in the hand to place the unit.
	for(x=zGetBankCount("p"+p+"handPos"); >0) {
		zBankNext("p"+p+"handPos");
		if (zGetVar("p"+p+"handPos", "occupied") == 0) {
			zSetVar("p"+p+"handPos", "occupied", 1);
			yAddUpdateVar("p"+p+"hand", "pos", trQuestVarGet("p"+p+"handPos"));
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trMutateSelected(kbGetProtoUnitID("Dwarf"));
			trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"handPos"));

			trUnitChangeProtoUnit(kbGetProtoUnitName(proto));


			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));

			break;
		}
	}
	if (spell > SPELL_NONE) {
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("next"), true);
		float scale = 0.2 + xsSqrt(trQuestVarGet("spell_"+spell+"_cost")) * 0.4;
		trSetSelectedScale(0.75, scale, 0.75);
		trUnitSetAnimationPath(1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
	}
}

void addCardToHandByIndex(int p = 0, int card = 0, bool fleeting = false) {
	int spell = CardToSpell(card);
	int proto = CardToProto(card)	;
	addCardToHand(p, proto, spell, fleeting);
}


void drawCard(int p = 0, bool fleeting = false) {
	if (yGetDatabaseCount("p"+p+"deck") <= 0) {
		trQuestVarSet("p"+p+"fatigue", 1 + trQuestVarGet("p"+p+"fatigue"));
		damageUnit(1*trQuestVarGet("p"+p+"commander"), trQuestVarGet("p"+p+"fatigue"));
		ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has no more cards! " + 1*trQuestVarGet("p"+p+"fatigue") + " damage");
		trQuestVarSetFromRand("sound", 1, 5, true);
		trSoundPlayFN("lightningstrike"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
		if (mGetVarByQV("p"+p+"commander", "health") <= 0) {
			trQuestVarSet("p"+p+"drawCards", 0);
			trQuestVarSet("p"+p+"defeated", 1);
			xsEnableRule("match_end");
		}
	} else {
		int proto = yDatabaseNext("p"+p+"deck");
		if (yGetDatabaseCount("p"+p+"hand") < 10) {
			if (trCurrentPlayer() == p) {
				trSoundPlayFN("ui\scroll.wav","1",-1,"","");
			}
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				ChatLog(p, "Drew " + trStringQuestVarGet("card_" + proto + "_Name"));
			} else {
				ChatLog(p, "Drew " + trStringQuestVarGet("spell_" + 1*yGetVar("p"+p+"deck", "spell") + "_Name"));
			}
			addCardToHand(p, proto, 1*yGetVar("p"+p+"deck", "spell"), fleeting);
		} else {
			if (trCurrentPlayer() == p) {
				trSoundPlayFN("cantdothat.wav","1",-1,"","");
			}
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("card_" + proto + "_Name"));
			} else {
				ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("spell_" + 1*yGetVar("p"+p+"deck", "spell") + "_Name"));
			}

		}
		yRemoveFromDatabase("p"+p+"deck");
		yRemoveUpdateVar("p"+p+"deck", "spell");

		updateRoxasHealth(p);
		updateHandPlayable(p);
		updateMana();
	}
}

void generateCard(int p = 0, int proto = 0, int spell = 0, bool fleeting = false) {
	if (yGetDatabaseCount("p"+p+"hand") < 10) {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("ui\scroll.wav","1",-1,"","");
		}
		if (spell == 0) {
			ChatLog(p, "Created " + trStringQuestVarGet("card_" + proto + "_Name"));
		} else {
			ChatLog(p, "Created " + trStringQuestVarGet("spell_" + spell + "_Name"));
		}
		addCardToHand(p, proto, spell, fleeting);
		updateHandPlayable(p);
		updateMana();
	} else {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("cantdothat.wav","1",-1,"","");
		}
		if (spell == 0) {
			ChatLog(p, "Hand full! Burned created " + trStringQuestVarGet("card_" + proto + "_Name"));
		} else {
			ChatLog(p, "Hand full! Burned created " + trStringQuestVarGet("spell_" + spell + "_Name"));
		}
	}
}

rule initializeHand
highFrequency
active
{
	zBankInit("p1handPos", 849, 10);
	zBankInit("p2handPos", 859, 10);

	trVectorQuestVarSet("p1deck", xsVectorSet(1,0,1));
	trVectorQuestVarSet("p2deck", xsVectorSet(119,0,119));

	xsDisableRule("initializeHand");
}


rule card_draw
highFrequency
active
{
	// We want to give the trCountUnitsInArea some time to update
	if (trTimeMS() > trQuestVarGet("card_draw_next")) {
		trQuestVarSet("card_draw_next", trTimeMS() + 500);
		for(p=2; >0) {
			if (trQuestVarGet("p"+p+"drawCards") > 0) {
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") - 1);
				drawCard(p);
				if (trQuestVarGet("p"+p+"drawCards") == 0) {
					updateHandPlayable(1*trQuestVarGet("activePlayer"));
				}
			}
		}
	}
}