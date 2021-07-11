const int BOT_PHASE_CARD_CHOOSE = 0;
const int BOT_PHASE_CARD_PLAY = 1;
const int BOT_PHASE_UNIT_CHOOSE = 2;
const int BOT_PHASE_UNIT_MOVE = 3;
const int BOT_PHASE_UNIT_ATTACK = 4;


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
	if ((trTime()-cActivationTime) >= 0){	
		trQuestVarSet("botClick", -1);
		
		if(trQuestVarGet("botNoMove") == 1 && trQuestVarGet("botNoAttack") == 1){
			// End Turn
			trQuestVarSet("botPhase", -1);
			trQuestVarSet("botThinking", 47);
		}
		
		switch(1*trQuestVarGet("botPhase"))
		{
			case BOT_PHASE_CARD_CHOOSE:
			{
				trQuestVarSet("botActiveKeywords", 0);
				int maxCardCost = -1;
				for(x=yGetDatabaseCount("p2hand"); >0) {
					yDatabaseNext("p2hand");
					if (yGetVar("p2hand", "cost") <= trQuestVarGet("p2mana") && yGetVar("p2hand", "spell") == 0) {
						// Bot plays cast in desc order of their cost
						int currentCardCost = yGetVar("p2hand", "cost");
						// Bot loves Airdrop
						if(HasKeyword(AIRDROP, 1*yGetVar("p2hand", "keywords"))){
							currentCardCost = currentCardCost + 9000;
						}
						if(currentCardCost > maxCardCost){
							maxCardCost = currentCardCost;
							trQuestVarSet("botActiveKeywords", 1*yGetVar("p2hand", "keywords"));
							trVectorSetUnitPos("botClickPos", "p2hand");
						}	
					}
				}
				if(maxCardCost > -1){
					// Bot Click Left	
					trQuestVarSet("botClick", LEFT_CLICK);
					trQuestVarSet("botPhase", BOT_PHASE_CARD_PLAY);
				} else {
					trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);
				}			
			}
			
			case BOT_PHASE_CARD_PLAY:
			{
				yClearDatabase("summonLocations");
				if (HasKeyword(AIRDROP, 1*trQuestVarGet("botActiveKeywords"))) {
					for(x=zGetBankCount("tiles"); >0) {
						zBankNext("tiles");
						if (zGetVar("tiles", "occupied") == TILE_EMPTY) {
							yAddToDatabase("summonLocations", "tiles");
						}
					}
				} else {
					for(x=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits");
						if (yGetVar("allUnits", "player") == 2 && HasKeyword(BEACON, 1*yGetVar("allUnits", "keywords"))) {
							findAvailableTiles(yGetVar("allUnits", "tile"), 1, "summonLocations");
						}
					}
				}
				// Bot tries to play a unit but there are no tiles where to summon it, skip playing cards
				if(yGetDatabaseCount("summonLocations") == 0){
					trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);
					// Bot Click Right 
					trQuestVarSet("botClick", RIGHT_CLICK);
				} else {
					trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("summonLocations"), true);
				}
				
				for (x=yGetDatabaseCount("summonLocations"); >0) {
					yDatabaseNext("summonLocations");
					// Bot summons a unit
					if(trQuestVarGet("botRandom") == x){
						trVectorSetUnitPos("botClickPos", "summonLocations");
						// Bot Click Left
						trQuestVarSet("botClick", LEFT_CLICK);
						trQuestVarSet("botPhase", BOT_PHASE_CARD_CHOOSE);
					}
				}
			}
			
			case BOT_PHASE_UNIT_CHOOSE:
			{
				trQuestVarSet("botActiveUnit", 0);
				trQuestVarSet("botActiveIndex", -1);
				trQuestVarSet("botActiveKeywords", 0);
				trQuestVarSet("botActiveSpeed", 0);
				trQuestVarSet("botActiveRange", 0);
				trQuestVarSet("botActiveFury", 0);
				int maxUnitCost = -1;
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (yGetVar("allUnits", "action") == ACTION_READY && yGetVar("allUnits", "player") == 2) {
						int currentUnitCost = yGetVar("allUnits", "cost");
						if(currentUnitCost > maxUnitCost){
							maxUnitCost = currentUnitCost;
							trQuestVarSet("botActiveUnit", trQuestVarGet("allUnits"));
							trQuestVarSet("botActiveIndex", yGetPointer("allUnits"));
							trQuestVarSet("botActiveKeywords", 1*yGetVar("allUnits", "keywords"));
							trQuestVarSet("botActiveSpeed", 1*yGetVar("allUnits", "speed"));
							trQuestVarSet("botActiveRange", 1*yGetVar("allUnits", "range"));
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
			}
			
			case BOT_PHASE_UNIT_MOVE:
			{
				if(trQuestVarGet("botNoMove")==0){
					yClearDatabase("botReachable");
					trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("botActiveUnit"), true));
					findAvailableTiles(findNearestTile("pos"), trQuestVarGet("botActiveSpeed"), "botReachable", HasKeyword(ETHEREAL, 1*trQuestVarGet("botActiveKeywords")));
					if(yGetDatabaseCount("botReachable") == 0){
						// Nowhere to move
						ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("botActiveIndex"), ACTION_DONE);
					} else {
						trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("botReachable"), true);
					}
				
					for(x=yGetDatabaseCount("botReachable"); >0) {
						yDatabaseNext("botReachable");
						// Bot moves
						if(trQuestVarGet("botRandom") == x){
							trVectorSetUnitPos("botClickPos", "botReachable");
							trVectorSetUnitPos("botMovePos", "botReachable");							
							// Bot Click Right
							trQuestVarSet("botClick", RIGHT_CLICK);
						}
					}
				}
				trQuestVarSet("botPhase", BOT_PHASE_UNIT_ATTACK);
			}
			
			case BOT_PHASE_UNIT_ATTACK:
			{
				if(zDistanceToVectorSquared("botActiveUnit", "botMovePos") < 1 && (trTime() - trQuestVarGet("botAttackTimer")) > 3){
					if(trQuestVarGet("botNoAttack") == 0){
						int maxTargetCost = -1;
						float dist = xsPow(trQuestVarGet("botActiveRange") * 6 + 1, 2);
						trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("botActiveUnit"), true));

						for(x=yGetDatabaseCount("allUnits"); >0) {
							yDatabaseNext("allUnits");
							if (yGetVar("allUnits", "player") == 1) {
								if (zDistanceToVectorSquared("allUnits", "pos") < dist) {
									int currentTargetCost = yGetVar("allUnits", "cost");
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
							ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("botActiveIndex"), ACTION_DONE);
						}
					} 
					if(trQuestVarGet("botActiveFury") == 1){
						trQuestVarSet("botActiveFury", 0);
					} else {
						trQuestVarSet("botPhase", BOT_PHASE_UNIT_CHOOSE);	
					}
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
	if ((trTime()-cActivationTime) > 0){
		if(trQuestVarGet("botClick") < 0){
			trQuestVarSet("botThinking", trQuestVarGet("botThinking") + 1);
		} else {
			trQuestVarSet("botThinking", 0);
			trVectorQuestVarSet("p2clickPos", trVectorQuestVarGet("botClickPos"));
			trQuestVarSet("p2click", trQuestVarGet("botClick"));
		}
		if(trQuestVarGet("botThinking") > 10){
			trTechInvokeGodPower(2, "Rain", vector(0,0,0), vector(0,0,0));
		} else {
			xsEnableRule("Bot1");
		}
		xsDisableRule("Bot2");
	}
}