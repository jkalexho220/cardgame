const int BOT_PHASE_CARD_CHOOSE = 0;
const int BOT_PHASE_CARD_PLAY = 1;
const int BOT_PHASE_UNIT_CHOOSE = 2;
const int BOT_PHASE_UNIT_MOVE = 3;
const int BOT_PHASE_UNIT_ATTACK = 4;
const int BOT_PHASE_SPELL_PLAY = 5;

const int BOT_PERSONALITY_DEFAULT = 0;	// Default bot, moves and attacks
const int BOT_PERSONALITY_TRAINING = 1; // Doesn't move
const int BOT_PERSONALITY_CIVILIAN = 2; // Doesn't attack
const int BOT_PERSONALITY_DECORATIVE = 3; // Doesn't play

void InitBot(int personality = 0){
	switch(personality)
	{
		case BOT_PERSONALITY_DEFAULT:
		{
			trQuestVarSet("botNoMove", 0);
			trQuestVarSet("botNoAttack", 0);
		}
		
		case BOT_PERSONALITY_TRAINING:
		{
			trQuestVarSet("botNoMove", 1);
			trQuestVarSet("botNoAttack", 0);
		}
		
		case BOT_PERSONALITY_CIVILIAN:
		{
			trQuestVarSet("botNoMove", 0);
			trQuestVarSet("botNoAttack", 1);
		}
		
		case BOT_PERSONALITY_DECORATIVE:
		{
			trQuestVarSet("botNoMove", 1);
			trQuestVarSet("botNoAttack", 1);
		}
	}
}

rule Bot1
highFrequency
inactive
{
	if (true){
		trQuestVarSet("botTimeNext", trTimeMS() + 300);
		trQuestVarSet("botClick", -1);
		
		if(trQuestVarGet("botNoMove") == 1 && trQuestVarGet("botNoAttack") == 1){
			// End Turn
			trQuestVarSet("botPhase", -1);
			trQuestVarSet("botThinking", 47);
		} else if (trQuestVarGet("castDone") == CASTING_IN_PROGRESS) {
			trQuestVarSet("botPhase", BOT_PHASE_SPELL_PLAY);
		}

		
		switch(1*trQuestVarGet("botPhase"))
		{
			case BOT_PHASE_CARD_CHOOSE:
			{
				if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SELECT) {
					trQuestVarSet("botActiveKeywords", 0);
					int maxCardCost = -1;
					int spell = 0;
					for(x=yGetDatabaseCount("p2hand"); >0) {
						yDatabaseNext("p2hand");
						if (mGetVarByQV("p2hand", "cost") <= trQuestVarGet("p2mana")) {
							// Bot plays cast in desc order of their cost
							int currentCardCost = mGetVarByQV("p2hand", "cost");
							// Bot loves Airdrop
							if(HasKeyword(AIRDROP, 1*mGetVarByQV("p2hand", "keywords"))){
								currentCardCost = currentCardCost + 9000;
							}
							if(currentCardCost > maxCardCost){
								maxCardCost = currentCardCost;
								trQuestVarSet("botActiveKeywords", 1*mGetVarByQV("p2hand", "keywords"));
								trVectorSetUnitPos("botClickPos", "p2hand");
								spell = 1*mGetVarByQV("p2hand", "spell");
							}	
						}
					}
					if(maxCardCost > -1){
						// Bot Click Left	
						trQuestVarSet("botClick", LEFT_CLICK);
						if (spell > 0) {
							trQuestVarSet("botPhase", BOT_PHASE_SPELL_PLAY);
						} else {
							trQuestVarSet("botPhase", BOT_PHASE_CARD_PLAY);
						}
						trQuestVarSet("botSpellPop", 0);
					} else {
						trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);
					}	
				} else {
					// Wait until gameplay phase is GAMEPLAY_SELECT
					trQuestVarSet("botClick", 0);
				}
			}

			case BOT_PHASE_SPELL_PLAY:
			{
				if (trQuestVarGet("castDone") == CASTING_NOTHING) {
					trQuestVarSet("botPhase", BOT_PHASE_CARD_CHOOSE);
				} else if (trQuestVarGet("castDone") == CASTING_CANCEL) {
					trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);
				} else if (trQuestVarGet("castPop") > trQuestVarGet("botSpellPop")) {
					trQuestVarSet("botSpellPop", trQuestVarGet("castPop"));
					if (yGetDatabaseCount("castTargets") > 0) {
						trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("castTargets"), true);
						for(x=trQuestVarGet("botRandom"); >0) {
							yDatabaseNext("castTargets");
						}
						trQuestVarSet("castTargetUnit", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("castTargets")));
						trVectorSetUnitPos("botClickPos", "castTargetUnit");
						trQuestVarSet("botClick", LEFT_CLICK);
					} else if (yGetDatabaseCount("castTiles") > 0) {
						trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("castTiles"), true);
						for(x=trQuestVarGet("botRandom"); >0) {
							yDatabaseNext("castTiles");
						}
						trVectorSetUnitPos("botClickPos", "castTiles");
						trQuestVarSet("botClick", LEFT_CLICK);
					} else {
						trQuestVarSet("botClick", RIGHT_CLICK);
					}
				} else {
					// Wait until spellcasting system is ready for selection
					trQuestVarSet("botClick", 0);
				}
			}
			
			case BOT_PHASE_CARD_PLAY:
			{
				if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SUMMONING) {
					// Bot tries to play a unit but there are no tiles where to summon it, skip playing cards
					if(yGetDatabaseCount("summonLocations") == 0){
						trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);
						// Bot Click Right 
						trQuestVarSet("botClick", RIGHT_CLICK);
					} else {
						trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("summonLocations"), true);
					}
					
					for (x=trQuestVarGet("botRandom"); >0) {
						yDatabaseNext("summonLocations");
					}
					// Bot summons a unit
					trVectorSetUnitPos("botClickPos", "summonLocations");
					// Bot Click Left
					trQuestVarSet("botClick", LEFT_CLICK);
					trQuestVarSet("botPhase", BOT_PHASE_CARD_CHOOSE);
				} else {
					// Wait until gameplay phase is GAMEPLAY_SUMMONING
					trQuestVarSet("botClick", 0);
				}
			}
			
			case BOT_PHASE_UNIT_CHOOSE:
			{
				if (trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK) {
					trVectorQuestVarSet("botClickPos", xsVectorSet(110,0,110));
					trQuestVarSet("botClick", LEFT_CLICK);
				} else if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SELECT) {
					trQuestVarSet("botActiveUnit", 0);
					trQuestVarSet("botActiveIndex", -1);
					trQuestVarSet("botActiveKeywords", 0);
					trQuestVarSet("botActiveSpeed", 0);
					trQuestVarSet("botActiveRange", 0);
					trQuestVarSet("botActiveFury", 0);
					int maxUnitCost = -1;
					for(x=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits", true);
						if (mGetVarByQV("allUnits", "action") == ACTION_READY && mGetVarByQV("allUnits", "player") == 2) {
							int currentUnitCost = mGetVarByQV("allUnits", "cost");
							if(currentUnitCost > maxUnitCost){
								maxUnitCost = currentUnitCost;
								trQuestVarSet("botActiveUnit", trQuestVarGet("allUnits"));
								trQuestVarSet("botActiveIndex", yGetPointer("allUnits"));
								trQuestVarSet("botActiveKeywords", 1*mGetVarByQV("allUnits", "keywords"));
								trQuestVarSet("botActiveSpeed", 1*mGetVarByQV("allUnits", "speed"));
								trQuestVarSet("botActiveRange", 1*mGetVarByQV("allUnits", "range"));
								if(HasKeyword(FURIOUS, 1*trQuestVarGet("botActiveKeywords"))){
									trQuestVarSet("botActiveFury", 1);
								}					
								trVectorSetUnitPos("botClickPos", "allUnits");
								trVectorSetUnitPos("botMovePos", "allUnits");
							}	
						}
					}
					if(maxUnitCost > -1){
						// Bot Click Left
						trQuestVarSet("botClick", LEFT_CLICK);
						trQuestVarSet("botPhase", BOT_PHASE_UNIT_MOVE);
					} else {
						// End Turn
						trQuestVarSet("botClick", -1);
						trQuestVarSet("botThinking", 47);
					}
				} else {
					// Wait until gameplayPhase is GAMEPLAY_SELECT
					trQuestVarSet("botClick", 0);
				}
			}
			
			case BOT_PHASE_UNIT_MOVE:
			{
				if (trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK) {
					if(trQuestVarGet("botNoMove")==0){
						yClearDatabase("botReachable");
						trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("botActiveUnit"), true));
						findAvailableTiles(findNearestTile("pos"), trQuestVarGet("botActiveSpeed"), "botReachable", HasKeyword(ETHEREAL, 1*trQuestVarGet("botActiveKeywords")));
						if((yGetDatabaseCount("botReachable") == 0) || (trQuestVarGet("botActiveSpeed") == 0)) {
							// Nowhere to move
							mSetVar(1*trQuestVarGet("botActiveIndex"), "action", ACTION_DONE);
						} else {
							trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("botReachable"), true);
							for(x=trQuestVarGet("botRandom"); >0) {
								yDatabaseNext("botReachable");
							}
							trVectorSetUnitPos("botClickPos", "botReachable");
							trVectorSetUnitPos("botMovePos", "botReachable");
							trQuestVarSet("botClick", RIGHT_CLICK);
						}
					}
					trQuestVarSet("botPhase", BOT_PHASE_UNIT_ATTACK);
				} else {
					// Wait until gameplayPhase is GAMEPLAY_WORK
					trQuestVarSet("botClick", 0);
				}
			}
			
			case BOT_PHASE_UNIT_ATTACK:
			{
				if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SELECT) {
					trQuestVarSet("botPhase", BOT_PHASE_CARD_CHOOSE);
				} else if(trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK){
					if(trQuestVarGet("botNoAttack") == 0){
						int maxTargetCost = -1;
						float dist = xsPow(trQuestVarGet("botActiveRange") * 6 + 1, 2);
						trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("botActiveUnit"), true));

						for(x=yGetDatabaseCount("allUnits"); >0) {
							yDatabaseNext("allUnits");
							if (mGetVarByQV("allUnits", "player") == 1) {
								if (zDistanceToVectorSquared("allUnits", "pos") < dist) {
									int currentTargetCost = mGetVarByQV("allUnits", "cost");
									if(currentTargetCost > maxTargetCost){
										maxTargetCost = currentTargetCost;
										trVectorSetUnitPos("botClickPos", "allUnits");
									}
								}
							}
						}
						if(maxTargetCost > -1){
							// Bot Click Right
							trQuestVarSet("botClick", RIGHT_CLICK);
							trQuestVarSet("botAttackTimer", trTime());
						} else {
							mSetVar(1*trQuestVarGet("botActiveIndex"), "action", ACTION_DONE);
							trQuestVarSet("botClick", LEFT_CLICK);
							trVectorQuestVarSet("botClickPos", xsVectorSet(110,0,110));
						}
					} 
					if(trQuestVarGet("botActiveFury") == 1){
						trQuestVarSet("botActiveFury", 0);
					} else {
						trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);	
					}
				} else {
					// Wait until gameplayPhase is GAMEPLAY_WORK
					trQuestVarSet("botClick", 0);
				}
			}	
		}
		xsEnableRule("Bot2");
		xsDisableRule("Bot1");
		
   }
}

rule Bot2
highFrequency
inactive
{
	if (trTimeMS() > trQuestVarGet("botTimeNext")){
		if(trQuestVarGet("botClick") < 0){
			trQuestVarSet("botThinking", trQuestVarGet("botThinking") + 1);
		} else {
			trQuestVarSet("botThinking", 0);
			trVectorQuestVarSet("p2clickPos", trVectorQuestVarGet("botClickPos"));
			trQuestVarSet("p2click", trQuestVarGet("botClick"));
		}
		if(trQuestVarGet("botThinking") > 10){
			trTechInvokeGodPower(2, "Nidhogg", vector(110,0,110), vector(110,0,110));
		} else {
			xsEnableRule("Bot1");
		}
		xsDisableRule("Bot2");
	}
}