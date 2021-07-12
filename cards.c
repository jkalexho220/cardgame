
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

const int ATTACK_EVENT_COUNT = 3;

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
Given a card index in a given db array, print information
of the selected unit.
*/
void displayCardKeywordsAndDescription(string db = "", int index = 0) {
	string bonus = " ";
	string dialog = "";
	string message = "";
	int proto = yGetVarByIndex(db, "proto", index);
	int keywords = yGetVarByIndex(db, "keywords", index);
	bool multiple = false;
	if (yGetVarByIndex(db, "stunTime", index) > 0) {
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
	message = yGetStringByIndex(db, "ability", index);

	int old = xsGetContextPlayer();
	if (yGetVarByIndex(db, "spell", index) <= SPELL_COMMANDER) {
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

		xsSetContextPlayer(1*yGetVarByIndex(db, "player", index));
		int diff = 1*yGetVarByIndex(db, "health", index) - kbUnitGetCurrentHitpoints(kbGetBlockID(""+1*yGetUnitAtIndex(db, index), true));
		if (diff > 0) {
			bonus = bonus + "HP +" + diff;
		}

		diff = yGetVarByIndex(db, "attack", index) - trQuestVarGet("card_" + proto + "_Attack");
		if (diff > 0) {
			bonus = bonus + " ATK + " + diff;
		} else if (diff < 0) {
			bonus = bonus + " ATK " + diff;
		}

		diff = yGetVarByIndex(db, "speed", index) - trQuestVarGet("card_" + proto + "_Speed");
		if (diff > 0) {
			bonus = bonus + " SPD + " + diff;
		} else if (diff < 0) {
			bonus = bonus + " SPD " + diff;
		}
	}
	

	trSoundPlayDialog("default", "1", -1, false, bonus + ": " + dialog, "");
	trSetCounterDisplay(message);

	xsSetContextPlayer(old);
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

void CardSetup(string protoName="", int cost=1, string name="", int attack=1, int health=1, int speed=1, int range=0, int keywords=0){
	int proto = kbGetProtoUnitID(protoName);
	if(proto<0){
		ThrowError("That's not a unit. Method: CardSetup");
	}	
	trQuestVarSet("cardProtos_" + 1*trQuestVarGet("cardProtosIndex"), proto);
	trQuestVarSet("cardProtosIndex", trQuestVarGet("cardProtosIndex") + 1);
	trStringQuestVarSet("card_" + proto + "_Name",name);
	trQuestVarSet("card_" + proto + "_Cost",cost);
	trQuestVarSet("card_" + proto + "_Attack",attack);
	trQuestVarSet("card_" + proto + "_Health",health);
	trQuestVarSet("card_" + proto + "_Speed",speed);
	trQuestVarSet("card_" + proto + "_Range",range);
	trQuestVarSet("card_" + proto + "_Keywords",keywords);
	
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


void CardLoad(bool firstBit = false, bool secondBit = false, int index = 0){
	int copies = 0;
	if(firstBit){
		if(secondBit){
			copies = 3;
		} else {
			copies = 1;
		}
	} else {
		if(secondBit){
			copies = 2;
		}
	}
	if(copies>0){
		trChatSend(0, "Player has " + copies + " copies of " + trStringQuestVarGet("card_" + 1*trQuestVarGet("cardProtos_"+index) + "_Name"));
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
	CardSetup("Statue of Lightning",	0, "Spell",				0, 1, 0, 0);
	CardSetup("Hero Greek Jason",		0, "phdorogers4", 		2, 20, 2, 1, Keyword(BEACON) + Keyword(ETHEREAL));
	
	CardSetup("Swordsman", 				1, "New Recruit", 		1, 3, 2, 1, Keyword(ETHEREAL));
	CardSetup("Petrobolos",				1, "Bear Trap",			1, 1, 0, 1, Keyword(AIRDROP) + Keyword(GUARD));
	CardSetup("Khopesh", 				2, "Thief", 			1, 2, 2, 1);
	CardSetup("Maceman", 				2, "School Guard",		2, 3, 2, 1, Keyword(GUARD));
	CardSetup("Skraeling", 				2, "Trapper", 			1, 2, 2, 1);
	CardSetup("Slinger", 				2, "Apprentice", 		1, 1, 2, 2);
	CardSetup("Toxotes", 				2, "Sharpshooter",	 	2, 2, 2, 2);
	CardSetup("Villager Atlantean",		2, "Traveling Chef",	1, 3, 2, 1);
	CardSetup("Hero Greek Theseus", 	3, "Party Leader", 		3, 4, 2, 1, Keyword(ETHEREAL));
	CardSetup("Raiding Cavalry",		3, "Reckless Rider", 	3, 2, 3, 1, Keyword(AMBUSH));
	CardSetup("Trident Soldier",		4, "Shieldbearer", 		2, 7, 1, 1, Keyword(GUARD));
	CardSetup("Jarl", 					4, "Wanderer", 			1, 3, 3, 1, Keyword(DEADLY));
	CardSetup("Behemoth", 				5, "Behemoth", 			2, 4, 1, 1, Keyword(ARMORED));
	CardSetup("Avenger", 				6, "Doubleblade", 		5, 5, 2, 1, Keyword(AIRDROP));
	CardSetup("Archer Atlantean Hero", 	7, "Ace", 				4, 2, 2, 2, Keyword(FURIOUS) + Keyword(AMBUSH) + Keyword(CHARGE));

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
	/*
	Spells
				Name 	Cost 	Spell
	*/
	SpellSetup("Spark", 1, SPELL_SPARK);
	SpellSetup("Windsong", 2, SPELL_SING);




	//Loading player collection
	int cardIndex = 0;
	for(i=0;<16){
		int n = trGetScenarioUserData(i);
		CardLoad((n<0), (zModulo(2,n)==1), cardIndex);
		n=n/2;
		cardIndex = cardIndex + 1;
		int j=1;
		while(j<29){
			bool firstBit = (zModulo(2,n)==1);
			n=n/2;
			bool secondBit = (zModulo(2,n)==1);
			n=n/2;
			CardLoad(firstBit, secondBit, cardIndex);
			cardIndex = cardIndex + 1;
			j=j+2;
		}
	}
	
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
