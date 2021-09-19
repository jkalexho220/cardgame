const int BOT_PHASE_CARD_CHOOSE = 0;
const int BOT_PHASE_CARD_PLAY = 1;
const int BOT_PHASE_UNIT_CHOOSE = 2;
const int BOT_PHASE_UNIT_MOVE = 3;
const int BOT_PHASE_UNIT_ATTACK = 4;
const int BOT_PHASE_SPELL_PLAY = 5;

const int BOT_PERSONALITY_DEFAULT = 0;	// Default bot, moves and attacks
const int BOT_PERSONALITY_TRAINING = 1; // Training bot, passes turn

void InitBot(int personality = 0){
	trQuestVarSet("botPersonality", personality);
}

rule Bot_00_turn_start
highFrequency
inactive
{
	trQuestVarCopy("botManaOptions", "p2mana");
	trQuestVarSet("botMoveOptions", 10);
	xsEnableRule("Bot1");
	xsDisableRule("Bot_00_turn_start");
}

/*
botManaOptions: The bot prioritizes the most expensive card it can play that is still <= botManaOptions.
This is so that the bot can skip spells that it cannot play. This resets to p2mana if the state of the board changes.
botMoveOptions: The bot prioritizes the most expensive card to move that still costs less than botMoveOptions.
This QV resets to 10 when the state of the board changes.
*/

rule Bot1
highFrequency
inactive
{
	if(trQuestVarGet("botPersonality") == BOT_PERSONALITY_TRAINING){
		trTechInvokeGodPower(2, "Nidhogg", vector(110,0,110), vector(110,0,110));
		xsDisableRule("Bot1");
		trQuestVarSet("gameplayPhase", -1);
	}
	
	trQuestVarSet("botTimeNext", trTimeMS() + 300);
	trQuestVarSet("botClick", -1);
	
	switch(1*trQuestVarGet("gameplayPhase"))
	{
		case GAMEPLAY_SELECT:
		{
			/*
			Bot has two options:
			1. Select a card in hand
			2. Select a ready unit
			*/
			trQuestVarSet("botChooseHand", 0);
			trQuestVarSet("botChooseUnit", 0);
			if (trQuestVarGet("botManaOptions") > 0) {
				trQuestVarSetFromRand("botChooseHand", 1, 3, true);
			}
			if (trQuestVarGet("botMoveOptions") >= 0) {
				trQuestVarSetFromRand("botChooseUnit", 1, 3, true);
			}
			// If no more options left
			if (trQuestVarGet("botChooseHand") + trQuestVarGet("botChooseUnit") == 0) {
				trTechInvokeGodPower(2, "Nidhogg", vector(110,0,110), vector(110,0,110));
				xsDisableRule("Bot1");
			// If choose hand
			} else if (trQuestVarGet("botChooseHand") > trQuestVarGet("botChooseUnit")) {
				trQuestVarSet("botSpell", -1);
				trQuestVarSet("botProto", -1);
				int maxCardCost = -1;
				int spell = 0;
				int proto = 0;
				for(x=yGetDatabaseCount("p2hand"); >0) {
					yDatabaseNext("p2hand");
					if ((mGetVarByQV("p2hand", "cost") <= trQuestVarGet("p2mana")) &&
						mGetVarByQV("p2hand", "cost") <= trQuestVarGet("botManaOptions")) {
						// Bot plays cast in desc order of their cost
						int currentCardCost = mGetVarByQV("p2hand", "cost");
						// Bot loves Airdrop
						if(HasKeyword(AIRDROP, 1*mGetVarByQV("p2hand", "keywords"))){
							currentCardCost = currentCardCost + 9000;
						}
						if(currentCardCost > maxCardCost){
							maxCardCost = currentCardCost;
							trVectorSetUnitPos("botClickPos", "p2hand");
							spell = 1*mGetVarByQV("p2hand", "spell");
							proto = 1*mGetVarByQV("p2hand", "proto");
						}	
					}
				}
				if(maxCardCost > -1){
					// Bot Click Left	
					trQuestVarSet("botClick", LEFT_CLICK);
					if (spell > 0) {
						trQuestVarSet("botSpell", spell);		
					}
					trQuestVarSet("botProto", proto);
				} else {
					trQuestVarSet("botManaOptions", 0);
				}
			// bot select unit
			} else {
				trQuestVarSet("botActiveUnit", 0);
				int maxUnitCost = -1;
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "action") == ACTION_READY && mGetVarByQV("allUnits", "player") == 2) {
						int currentUnitCost = mGetVarByQV("allUnits", "cost");
						if ((currentUnitCost > maxUnitCost) &&
							currentUnitCost <= trQuestVarGet("botMoveOptions")){
							maxUnitCost = currentUnitCost;
							trQuestVarSet("botActiveUnit", trQuestVarGet("allUnits"));				
							trVectorSetUnitPos("botClickPos", "allUnits");
							trVectorSetUnitPos("botMovePos", "allUnits");
						}	
					}
				}
				if(maxUnitCost > -1){
					// Bot Click Left
					trQuestVarSet("botClick", LEFT_CLICK);
				} else {
					trQuestVarSet("botMoveOptions", -1);
				}
			}
		}

		case GAMEPLAY_SPELL_UNIT:
		{
			if(1*trQuestVarGet("spell_" + 1*trQuestVarGet("botSpell") + "_type") == SPELL_TYPE_OFFENSIVE){
				yDatabasePointerDefault("castTargets");
				for(x=yGetDatabaseCount("castTargets"); >0) {
					yDatabaseNext("castTargets", true);
					if(trUnitIsOwnedBy(2)){
						yRemoveFromDatabase("castTargets");
					}
				}
				
				if(1*trQuestVarGet("botSpell") == SPELL_INTIMIDATE){
					yDatabasePointerDefault("castTargets");
					for(x=yGetDatabaseCount("castTargets"); >0) {
						yDatabaseNext("castTargets");
						if(mGetVarByQV("castTargets", "stunTime") > 0){
							yRemoveFromDatabase("castTargets");
						}
					}
				} else if(1*trQuestVarGet("botSpell") == SPELL_PISTOL_SHOT){
					yDatabasePointerDefault("castTargets");
					for(x=yGetDatabaseCount("castTargets"); >0) {
						yDatabaseNext("castTargets");
						if(mGetVarByQV("castTargets", "attack") + mGetVarByQV("castTargets", "health") + mGetVarByQV("castTargets", "cost") < 9){
							yRemoveFromDatabase("castTargets");
						}
					}
				} else if(1*trQuestVarGet("botSpell") == SPELL_ELECTROSURGE){
					yDatabasePointerDefault("castTargets");
					for(x=yGetDatabaseCount("castTargets"); >0) {
						yDatabaseNext("castTargets");
						if(trCountUnitsInArea(""+1*trQuestVarGet("castTargets"),1,"Unit",9) < 2){
							yRemoveFromDatabase("castTargets");
						}
					}
				}
				
			} else if(1*trQuestVarGet("spell_" + 1*trQuestVarGet("botSpell") + "_type") == SPELL_TYPE_DEFENSIVE){
				yDatabasePointerDefault("castTargets");
				for(x=yGetDatabaseCount("castTargets"); >0) {
					yDatabaseNext("castTargets", true);
					if(trUnitIsOwnedBy(2) == false){
						yRemoveFromDatabase("castTargets");
					}
				}
			}

			if (yGetDatabaseCount("castTargets") > 0) {
				trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("castTargets"), true);
				for(x=trQuestVarGet("botRandom"); >0) {
					yDatabaseNext("castTargets");
				}
				trVectorSetUnitPos("botClickPos", "castTargets");
				trQuestVarSet("botClick", LEFT_CLICK);
				trQuestVarSet("botThinking", 0);
			} else {
				trQuestVarSet("botClick", RIGHT_CLICK);
				trQuestVarSet("botManaOptions", trQuestVarGet("botManaOptions") - 1);
				trQuestVarSet("botTimeNext", trTimeMS());
			}
		}

		case GAMEPLAY_SPELL_TILE:
		{
			if (1*trQuestVarGet("spell_" + 1*trQuestVarGet("botSpell") + "_type") == SPELL_TYPE_OFFENSIVE) {
				yDatabasePointerDefault("castTiles");
				for(x=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if(mGetVar(1*zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("castTiles")), "player") != 1){
						yRemoveFromDatabase("castTiles");
					}
				}
				
				if(1*trQuestVarGet("botSpell") == SPELL_EXPLOSION){
					yDatabasePointerDefault("castTiles");
					for(x=yGetDatabaseCount("castTiles"); >0) {
						yDatabaseNext("castTiles");
						if(trCountUnitsInArea(""+1*zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("castTiles")),1,"Unit",9) < 2){
							yRemoveFromDatabase("castTiles");
						}
					}
				}
				
			} else if (1*trQuestVarGet("spell_" + 1*trQuestVarGet("botSpell") + "_type") == SPELL_TYPE_DEFENSIVE) {
				yDatabasePointerDefault("castTiles");
				for(x=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if(mGetVar(1*zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("castTiles")), "player") < 2){
						yRemoveFromDatabase("castTiles");
					}
				}
			}

			if(1*trQuestVarGet("botSpell") == SPELL_GROUND_STOMP){
				if(trCountUnitsInArea(""+1*trQuestVarGet("p2commander"),1,"Unit",9) < 1){
					yClearDatabase("castTiles");
				}
			} else if((1*trQuestVarGet("botSpell") == SPELL_FINAL_EXAM) || (1*trQuestVarGet("botSpell") == SPELL_CLASS_TIME) || (1*trQuestVarGet("botSpell") == SPELL_PARTY_UP)){
				if(yGetDatabaseCount("p2hand") > 7){
					yClearDatabase("castTiles");
				}
			} else if((1*trQuestVarGet("botSpell") == SPELL_APOCALYPSE) || (1*trQuestVarGet("botSpell") == SPELL_ELVEN_APOCALYPSE)){
				if(yGetDatabaseCount("p2hand") > 2){
					yClearDatabase("castTiles");
				}
			} else if(1*trQuestVarGet("botSpell") == SPELL_VICTORY){
				if(trCountUnitsInArea("128",2,"Unit",45) < 3){
					yClearDatabase("castTiles");
				}
			}

			if (yGetDatabaseCount("castTiles") > 0) {
				trQuestVarSetFromRand("botRandom", 1, yGetDatabaseCount("castTiles"), true);
				for(x=trQuestVarGet("botRandom"); >0) {
					yDatabaseNext("castTiles");
				}
				trVectorSetUnitPos("botClickPos", "castTiles");
				trQuestVarSet("botClick", LEFT_CLICK);
				trQuestVarSet("botThinking", 0);
			} else {
				trQuestVarSet("botClick", RIGHT_CLICK);
				trQuestVarSet("botManaOptions", trQuestVarGet("botManaOptions") - 1);
				trQuestVarSet("botTimeNext", trTimeMS());
			}
		}
		
		case GAMEPLAY_SUMMONING:
		{
			if((trQuestVarGet("botProto") == kbGetProtoUnitID("Griffon")) || (trQuestVarGet("botProto") == kbGetProtoUnitID("Avenger"))){
				yDatabasePointerDefault("summonLocations");
				for(x=yGetDatabaseCount("summonLocations"); >0) {
					yDatabaseNext("summonLocations");
					if(trCountUnitsInArea(""+1*trQuestVarGet("summonLocations"),1,"Unit",9) < 1){
						yRemoveFromDatabase("summonLocations");
					}
				}
			}		
			// Bot tries to play a unit but there are no tiles where to summon it, skip playing cards
			if(yGetDatabaseCount("summonLocations") == 0){
				trQuestVarSet("botManaOptions", trQuestVarGet("botManaOptions") - 1);
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
			// Reset move options to 10 because there may be new options now
			trQuestVarSet("botMoveOptions", 10);
		}
		
		
		case GAMEPLAY_WORK:
		{
			yClearDatabase("botOptions");
			int bestTile = 0;
			int bestTileScore = -1000;
			int currentScore = 0;
			trVectorSetUnitPos("commanderpos", "p1commander");
			for(x=yGetDatabaseCount("reachable"); >0) {
				yDatabaseNext("reachable");
				/*
				the score of a tile is the attack of the active unit * the number of targets it can reach on the tile
				also prioritize tiles closer to enemy commander
				*/
				currentScore = 2*mGetVarByQV("botActiveUnit", "attack") * trCountUnitsInArea(""+1*trQuestVarGet("reachable"),1,"Unit",1.0+6.0*mGetVarByQV("botActiveUnit", "range"));
				currentScore = currentScore - zDistanceToVector("reachable", "commanderpos") / 9;
				if (currentScore >= bestTileScore) {
					/*
					prioritize tiles that can be attacked by the fewest number of enemies
					this loops through so much lmao
					*/
					trVectorSetUnitPos("pos", "reachable");
					for(y=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits");
						if (yGetVar("allUnits", "player") == 1) {
							if (zDistanceToVector("allUnits", "pos") < 1.0 + 6.0*mGetVarByQV("allUnits", "range")) {
								currentScore = currentScore - mGetVarByQV("allUnits", "attack");
							}
						}
					}

					/*
					If it's still the best tile, update
					*/
					if (currentScore >= bestTileScore) {
						bestTileScore = currentScore;
						bestTile = trQuestVarGet("reachable");
					}
				}
			}

			int bestTarget = 0;
			int bestTargetScore = -1000;
			currentScore = 0;
			trVectorSetUnitPos("pos", "botActiveUnit");
			for (x=yGetDatabaseCount("targets"); >0) {
				yDatabaseNext("targets");	
				if((trQuestVarGet("botActiveUnit") == trQuestVarGet("p2commander")) && (mGetVarByQV("targets", "attack") >= mGetVarByQV("botActiveUnit", "health"))){
					continue;
				}
				if((HasKeyword(DEADLY, 1*mGetVarByQV("botActiveUnit", "keywords"))) && (1*mGetVarByQV("targets", "spell") == 0)){
					currentScore = mGetVarByQV("targets", "health");
				} else {
					currentScore = mGetVarByQV("botActiveUnit", "attack") - mGetVarByQV("targets", "health");
					if(HasKeyword(ARMORED, 1*mGetVarByQV("targets", "keywords"))){
						currentScore = currentScore - 1;
					}
				}				
				// If the target dies, then currentScore = 2 * (target's attack + cost)
				if (currentScore >= 0) {
					currentScore = 2*(mGetVarByQV("targets", "attack") + mGetVarByQV("targets", "cost"));
				}
				// If the target can counterattack, we subtract its attack from currentScore
				if (zDistanceToVector("targets", "pos") <= 1 + 6 * mGetVarByQV("targets", "range")) {			
					if((HasKeyword(DEADLY, 1*mGetVarByQV("targets", "keywords"))) && (1*mGetVarByQV("botActiveUnit", "spell") == 0)){
						currentScore = currentScore - mGetVarByQV("botActiveUnit", "health");
					} else {
						if(1*mGetVarByQV("targets", "stunTime") == 0){
							currentScore = currentScore - mGetVarByQV("targets", "attack");
							if(HasKeyword(ARMORED, 1*mGetVarByQV("botActiveUnit", "keywords"))){
								currentScore = currentScore + 1;
							}							
						}
					}
				}
				if (currentScore > bestTargetScore) {
					bestTargetScore = currentScore;
					bestTarget = trQuestVarGet("targets");
				}
			}

			trQuestVarSet("botClick", RIGHT_CLICK);
			if (bestTargetScore > bestTileScore) {
				trVectorQuestVarSet("botClickPos", kbGetBlockPosition(""+bestTarget,true));
				trQuestVarSet("botMoveOptions", 10);
				trQuestVarCopy("botManaOptions", "p2mana");
			} else if (bestTileScore > -1000) {
				trVectorQuestVarSet("botClickPos", kbGetBlockPosition(""+bestTile));
				trQuestVarSet("botMoveOptions", 10);
				trQuestVarCopy("botManaOptions", "p2mana");
			} else {
				trVectorQuestVarSet("botClickPos", xsVectorSet(111,0,111));
				trQuestVarSet("botClick", LEFT_CLICK);
				trQuestVarSet("botMoveOptions", trQuestVarGet("botMoveOptions") - 1);
				trQuestVarSet("botTimeNext", trTimeMS());
			}
		}	
	}
	if (trQuestVarGet("botClick") >= 0) {
		xsEnableRule("Bot2");
		xsDisableRule("Bot1");
	}
}

rule Bot2
highFrequency
inactive
{
	if (trTimeMS() > trQuestVarGet("botTimeNext")){
		trVectorQuestVarSet("p2clickPos", trVectorQuestVarGet("botClickPos"));
		trQuestVarSet("p2click", trQuestVarGet("botClick"));
		
		xsEnableRule("Bot1");
		
		xsDisableRule("Bot2");
	}
}