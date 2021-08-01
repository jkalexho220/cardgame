
void ThrowError(string message = "Zeno you made bug again!"){
	trShowWinLose(message, "xpack\xtaunts\en\999 theme.mp3");
}


/*
Spells
*/
const int SPELL_NONE = 0;
const int SPELL_COMMANDER = 1; // Since the "spell" variable is unused on normal minions, we use it here to mark a unit as the Commander

const int SPELL_SPARK = 2;
const int SPELL_FOOD = 3;
const int SPELL_SING = 4;


/*
OnAttack events (bit positions)
*/
const int ATTACK_DRAW_CARD = 0;
const int ATTACK_STUN_TARGET = 1;
const int ATTACK_GET_WINDSONG = 2;
const int ATTACK_BLOCK_DEATH = 3;

const int ATTACK_EVENT_COUNT = 4;

/*
OnPlay events (bit positions)
*/
const int PLAY_FOOD = 0;
const int PLAY_GET_TRAP = 1;
const int PLAY_GET_SPARK = 2;
const int PLAY_DOUBLEBLADE = 3;
const int PLAY_LEGENDARY = 4;

const int PLAY_EVENT_COUNT = 5;

/*
OnDeath events (bit positions)
*/
const int DEATH_DRAW_CARD = 0;
const int DEATH_OPPONENT_DRAW_CARD = 1;
const int DEATH_BOOM_SMALL = 2;
const int DEATH_BOOM_MEDIUM = 3;
const int DEATH_BOOM_BIG = 4;

const int DEATH_EVENT_COUNT = 5;

/*
Keyword bit positions. Use these to index into keywords by bit position
*/
const int CHARGE = 0;			// Action is ready when summoned
const int GUARD = 1;			// If an adjacent ally is attacked, swap spaces with it before combat occurs.
const int AIRDROP = 2;			// Doesn't have to be summoned next to the commander.
const int FURIOUS = 3;			// Two attacks each turn.
const int LIGHTNING = 4;		// Attack will chain through connected enemies.
const int REGENERATE = 5;		// Restores to full health at the start of your turn.
const int DEADLY = 6;
const int ETHEREAL = 7;			// Can pass through units and impassable terrain.
const int ARMORED = 8;			// Unit regenerates to full health after combat
const int WARD = 9;				// Unit is immune to spells
const int BEACON = 10;			// Allies can be summoned next to this unit.
const int AMBUSH = 11;			// When initiating combat, unit attacks first.
const int FLEETING = 12; 		// The card is discarded from hand at the end of the turn.

const int NUM_KEYWORDS = 13;


string GetKeywordName(int bitPosition=0){
	switch(bitPosition){
		case CHARGE: return ("Charge");
		case GUARD: return ("Guard");
		case AIRDROP: return ("Airdrop");
		case FURIOUS: return ("Furious");
		case LIGHTNING: return ("Lightning");
		case REGENERATE: return ("Regenerate");
		case DEADLY: return ("Deadly");
		case ETHEREAL: return ("Pathfinder");
		case ARMORED: return ("Armored");
		case WARD: return ("Ward");
		case BEACON: return ("Beacon");
		case AMBUSH: return ("Ambush");
		case FLEETING: return ("Fleeting");
	}
	ThrowError("Invalid keyword id. Method: GetKeywordName");
	return ("");
}

/* 
Given a bitPosition, return 2^bitPosition
*/
int Keyword(int bitPos = 0) {
	return(1*xsPow(2, bitPos));
}

/*
Example: HasKeyword(CHARGE, 123456) = false

Given a key and a keywords integer, returns true if the keywords integer has the keyword
*/
bool HasKeyword(int key = 0, int keywords = 0) {
	return(GetBit(keywords, key));
}

/*
Given a card name in a given db array, print information
of the selected unit.
*/
void displayCardKeywordsAndDescription(int name = 0) {
	string bonus = " ";
	string dialog = "";
	string message = "";
	int proto = mGetVar(name, "proto");
	int keywords = mGetVar(name, "keywords");
	bool multiple = false;
	if (mGetVar(name, "stunTime") > 0) {
		dialog = "Stunned";
		multiple = true;
	}
	if(keywords>0){
		int current = xsPow(2, NUM_KEYWORDS - 1);
		for(k=NUM_KEYWORDS - 1; >=0){
			if (keywords >= current) {
				if(multiple){
					dialog = dialog + ", ";
				}
				multiple = true;
				dialog = dialog + GetKeywordName(k);
				keywords = keywords - current;
			}
			current = current / 2;
		}
	}
	message = mGetString(name, "ability");

	int old = xsGetContextPlayer();
	if (mGetVar(name, "spell") <= SPELL_COMMANDER) {
		gadgetUnreal("DetailedHelpButton");
		if(HasKeyword(ARMORED, keywords)){
			gadgetUnreal("NormalArmorTextDisplay");			
		} else {
			gadgetUnreal("unitStatPanel-stat-normalArmor");
		}
		if(HasKeyword(WARD, keywords)){
			gadgetUnreal("PierceArmorTextDisplay");			
		} else {
			gadgetUnreal("unitStatPanel-stat-pierceArmor");
		}

		xsSetContextPlayer(1*mGetVar(name, "player"));
		int diff = 1*mGetVar(name, "health") - kbUnitGetCurrentHitpoints(kbGetBlockID(""+name, true));
		if (diff > 0) {
			bonus = bonus + "HP +" + diff;
		}

		diff = mGetVar(name, "attack") - trQuestVarGet("card_" + proto + "_Attack");
		if (diff > 0) {
			bonus = bonus + " ATK +" + diff;
		} else if (diff < 0) {
			bonus = bonus + " ATK " + diff;
		}

		diff = mGetVar(name, "speed") - trQuestVarGet("card_" + proto + "_Speed");
		if (diff > 0) {
			bonus = bonus + " SPD +" + diff;
		} else if (diff < 0) {
			bonus = bonus + " SPD " + diff;
		}
	}
	

	trSoundPlayDialog("default", "1", -1, false, bonus + ": " + dialog, "");
	trSetCounterDisplay(message);

	xsSetContextPlayer(old);
}

int CardInstantiate(int p = 0, int proto = 0, int spell = 0) {
	int next = trGetNextUnitScenarioNameNumber();
	trArmyDispatch("1,10","Dwarf",1,119,0,1,0,true);
	trUnitSelectClear();
	trUnitSelect(""+next, true);
	trUnitConvert(p);

	if (spell == 0 || spell == SPELL_COMMANDER) {
		trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
		mSetVar(next, "attack", trQuestVarGet("card_" + proto + "_Attack"));
		mSetVar(next, "health", trQuestVarGet("card_" + proto + "_Health"));
		mSetVar(next, "speed", trQuestVarGet("card_" + proto + "_Speed"));
		mSetVar(next, "range", trQuestVarGet("card_" + proto + "_Range"));
		mSetVar(next, "cost", trQuestVarGet("card_" + proto + "_Cost"));
		mSetVar(next, "keywords", trQuestVarGet("card_" + proto + "_Keywords"));
		mSetVar(next, "onPlay", trQuestVarGet("card_" + proto + "_OnPlay"));
		mSetVar(next, "onAttack", trQuestVarGet("card_" + proto + "_OnAttack"));
		mSetVar(next, "onDeath", trQuestVarGet("card_" + proto + "_OnDeath"));
		mSetString(next, "ability", trStringQuestVarGet("card_" + proto + "_Ability"));
	} else {
		trUnitChangeName("("+1*trQuestVarGet("spell_" + spell + "_Cost")+") "+trStringQuestVarGet("spell_" + spell + "_Name"));
		mSetVar(next, "cost", trQuestVarGet("spell_" + spell + "_Cost"));
		proto = kbGetProtoUnitID("Statue of Lightning");
	}
	
	mSetVar(next, "proto", proto);
	mSetVar(next, "player", p);
	mSetVar(next, "spell", spell);

	return(next);
}

void SpellSetup(string name = "", int cost = 0, int spell = 0) {
	trStringQuestVarSet("spell_"+spell+"_name", name);
	trQuestVarSet("spell_"+spell+"_cost", cost);
}

void CardEvents(string protoName = "", int onPlay = 0, int onAttack = 0, int onDeath = 0, string ability="") {
	int proto = kbGetProtoUnitID(protoName);
	trQuestVarSet("card_" + proto + "_OnPlay",onPlay);
	trQuestVarSet("card_" + proto + "_OnAttack",onAttack);
	trQuestVarSet("card_" + proto + "_OnDeath",onDeath);
	trStringQuestVarSet("card_" + proto + "_Ability",ability);
}

void CardSetup(string protoName="", int cost=1, string name="", int attack=1, int health=1, int speed=1, int range=0, int keywords=0, bool commander = false){
	int proto = kbGetProtoUnitID(protoName);
	if(proto<0){
		ThrowError("That's not a unit. Method: CardSetup");
	}
	if (commander == false) {
		trQuestVarSet("cardProtos_" + 1*trQuestVarGet("cardProtosIndex"), proto);
		trQuestVarSet("cardProtosIndex", trQuestVarGet("cardProtosIndex") + 1);
	}
	trStringQuestVarSet("card_" + proto + "_Name",name);
	trQuestVarSet("card_" + proto + "_Cost",cost);
	trQuestVarSet("card_" + proto + "_Attack",attack);
	trQuestVarSet("card_" + proto + "_Health",health);
	trQuestVarSet("card_" + proto + "_Speed",speed);
	trQuestVarSet("card_" + proto + "_Range",range);
	trQuestVarSet("card_" + proto + "_Keywords",keywords);
	if (HasKeyword(ETHEREAL, keywords)) {
		trModifyProtounit(protoName, 1, 55, 4);
		trModifyProtounit(protoName, 2, 55, 4);
	}
	
	for(p=1;<cNumberPlayers){
		trModifyProtounit(protoName, p, 16, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 16, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 16, 0); // Cost Gold
		trModifyProtounit(protoName, p, 17, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 17, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 17, 0); // Cost Wood
		trModifyProtounit(protoName, p, 18, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 18, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 18, 0); // Cost Food
		trModifyProtounit(protoName, p, 19, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 19, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 19, cost); // Cost Favor
		if(range==1){
			trModifyProtounit(protoName, p, 27, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 27, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 27, attack); // Hand Attack Hack
			trModifyProtounit(protoName, p, 28, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 28, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 28, 0); // Hand Attack Pierce
			trModifyProtounit(protoName, p, 29, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 29, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 29, 0); // Hand Attack Crush
		} else {
			trModifyProtounit(protoName, p, 30, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 30, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 30, 0); // Ranged Attack Hack
			trModifyProtounit(protoName, p, 31, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 31, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 31, attack); // Ranged Attack Pierce
			trModifyProtounit(protoName, p, 32, 9999999999999999999.0);
			trModifyProtounit(protoName, p, 32, -9999999999999999999.0);
			trModifyProtounit(protoName, p, 32, 0); // Ranged Attack Crush
		}
		trModifyProtounit(protoName, p, 0, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 0, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 0, health); // Hitpoints

		trModifyProtounit(protoName, p, 11, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 11, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 11, range); // Range

		trModifyProtounit(protoName, p, 1, 10); // Just give everything +10 speed

		// 0 LOS
		trModifyProtounit(protoName, p, 2, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 2, -9999999999999999999.0);
	}
}

rule initializeCards
highFrequency
active
runImmediately
{
	for(p=1;<cNumberPlayers){
		trForbidProtounit(p, "Archer Atlantean Hero");
		trForbidProtounit(p, "Javelin Cavalry Hero");
		trForbidProtounit(p, "Lancer Hero");
		trForbidProtounit(p, "Maceman Hero");
		trForbidProtounit(p, "Oracle Hero");
		trForbidProtounit(p, "Royal Guard Hero");
		trForbidProtounit(p, "Swordsman Hero");
		trForbidProtounit(p, "Trident Soldier Hero");
		trForbidProtounit(p, "Villager Atlantean Hero");
		trForbidProtounit(p, "Settlement Level 1");
		trForbidProtounit(p, "Guild");
		trForbidProtounit(p, "Manor");
		trForbidProtounit(p, "Dock");
		trForbidProtounit(p, "Wall Connector");
		trForbidProtounit(p, "Temple");
	}

	//Pick a card. Any card.
	/*
	Unit stats and keywords
	        Proto                  Cost    Name       Attack|Health|Speed|Range    Keywords
	*/
	CardSetup("Statue of Lightning",	0, "Spell",				0, 1, 0, 0, 0, true);
	CardSetup("Hero Greek Jason",		0, "phdorogers4", 		2, 20, 2, 1, Keyword(BEACON) + Keyword(ETHEREAL), true);
	
	CardSetup("Swordsman", 				1, "New Recruit", 		1, 3, 2, 1, Keyword(ETHEREAL));
	CardSetup("Petrobolos",				1, "Bear Trap",			1, 1, 0, 1, Keyword(AIRDROP) + Keyword(GUARD));
	CardSetup("Khopesh", 				2, "Thief", 			1, 2, 2, 1);
	CardSetup("Maceman", 				2, "School Guard",		2, 3, 2, 1, Keyword(GUARD));
	CardSetup("Skraeling", 				2, "Trapper", 			1, 2, 2, 1);
	CardSetup("Slinger", 				2, "Apprentice", 		1, 1, 2, 2);
	CardSetup("Toxotes", 				2, "Sharpshooter",	 	2, 2, 2, 2);
	CardSetup("Villager Atlantean",		2, "Traveling Chef",	1, 3, 2, 1);
	CardSetup("Hero Greek Ajax", 		3, "Party Leader", 		3, 4, 2, 1, Keyword(ETHEREAL));
	CardSetup("Raiding Cavalry",		3, "Reckless Rider", 	3, 2, 3, 1, Keyword(AMBUSH));
	CardSetup("Trident Soldier",		4, "Shieldbearer", 		2, 7, 1, 1, Keyword(GUARD));
	CardSetup("Jarl", 					4, "Wanderer", 			1, 3, 3, 1, Keyword(DEADLY));
	CardSetup("Behemoth", 				5, "Behemoth", 			2, 4, 1, 1, Keyword(ARMORED));
	CardSetup("Avenger", 				6, "Doubleblade", 		5, 5, 2, 1, Keyword(AIRDROP));
	CardSetup("Archer Atlantean Hero", 	7, "Ace", 				4, 2, 2, 2, Keyword(FURIOUS) + Keyword(AMBUSH) + Keyword(CHARGE));
	
	CardSetup("Scout",					1, "Sameday Courier", 	2, 1, 4, 1); // Death: Opponent draws a card.
	CardSetup("Prodromos",				3, "Loot'n Horse", 		2, 2, 3, 1); // Death: Draw a card.
	CardSetup("Promethean Small",		2, "Boom Goblin", 		1, 2, 1, 1); // Death: Deal 2 Damage in 1 Range.
	CardSetup("Promethean",				4, "Boom Goblin Champ", 2, 4, 1, 1); // Death: Deal 4 Damage in 1 Range and 2 Damage in 2 Range.
	CardSetup("Hero Greek Chiron",		8, "Donut", 			3, 6, 3, 2); // Death: 6 Dmg 1 Rng, 4 Dmg 2 Rng, 2 Dmg 3 Rng and make tile Impassable.
	CardSetup("Hero Greek Theseus", 	4, "Silent Paladin", 	4, 6, 2, 1); // Minions I kill don't trigger their Death effect.
	
	/*
	Unit OnPlay, OnAttack, OnDeath, and description
		Proto | OnPlay | OnAttack | OnDeath | Description
	*/
	CardEvents("Hero Greek Jason", 0, Keyword(ATTACK_GET_WINDSONG), 0, "Attack: Add a Windsong to your hand. Discard it when turn ends.");
	CardEvents("Khopesh", 0, Keyword(ATTACK_DRAW_CARD), 0, "Attack: Draw a card.");
	CardEvents("Skraeling", Keyword(PLAY_GET_TRAP), 0, 0, "Play: Add a Bear Trap to your hand.");
	CardEvents("Slinger", Keyword(PLAY_GET_SPARK), 0, 0, "Play: Add a Spark to your hand.");
	CardEvents("Avenger", Keyword(PLAY_DOUBLEBLADE), 0, 0, "Play: Deal 1 damage to all adjacent enemies.");
	CardEvents("Villager Atlantean", Keyword(PLAY_FOOD), 0, 0, "Play: Grant an allied minion +1 attack and health.");
	CardEvents("Petrobolos", 0, Keyword(ATTACK_STUN_TARGET), 0, "Attack: Stun my target.");
	CardEvents("Archer Atlantean Hero", Keyword(PLAY_LEGENDARY), 0, 0);
	CardEvents("Scout", 0, 0, Keyword(DEATH_OPPONENT_DRAW_CARD), "Death: Opponent draws a card.");
	CardEvents("Prodromos", 0, 0, Keyword(DEATH_DRAW_CARD), "Death: Draw a card.");
	CardEvents("Promethean Small", 0, 0, Keyword(DEATH_BOOM_SMALL), "Death: Deal 2 Damage in 1 Range.");
	CardEvents("Promethean", 0, 0, Keyword(DEATH_BOOM_MEDIUM), "Death: Deal 4 Damage in 1 Range and 2 Damage in 2 Range.");
	CardEvents("Hero Greek Chiron", 0, 0, Keyword(DEATH_BOOM_BIG), "Death: 6 Dmg 1 Rng, 4 Dmg 2 Rng, 2 Dmg 3 Rng and make tile Impassable.");
	CardEvents("Hero Greek Theseus", 0, Keyword(ATTACK_BLOCK_DEATH), 0, "Minions I kill don't trigger their Death effect.");
	/*
	Spells
				Name 	Cost 	Spell
	*/
	SpellSetup("Spark", 1, SPELL_SPARK);
	SpellSetup("Windsong", 2, SPELL_SING);
	
	/*
	//Deploy one of each card to playtest.
	int cardsCount = trQuestVarGet("cardProtosIndex");
	for(i=0;<cardsCount){
		trQuestVarSetFromRand("random", 128, 296, true);
		trVectorQuestVarSet("temp", kbGetBlockPosition(""+1*trQuestVarGet("random")));
		CardInstantiate(kbGetProtoUnitName(trQuestVarGet("cardProtos_"+i)),"temp");
	}
	*/
	
	xsDisableRule("initializeCards");
}
