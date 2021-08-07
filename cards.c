
void ThrowError(string message = "Zeno you made bug again!"){
	trShowWinLose(message, "xpack\xtaunts\en\999 theme.mp3");
}

/*
Classes
*/
const int CLASS_ADVENTURER = 0;
const int CLASS_ARCANE = 1;
const int CLASS_NAGA = 2;
const int CLASS_CLOCKWORK = 3;
const int CLASS_EVIL = 4;
const int CLASS_SPACE = 5;

/*
Spells
*/
const int SPELL_NONE = 0;
const int SPELL_COMMANDER = 1; // Since the "spell" variable is unused on normal minions, we use it here to mark a unit as the Commander

const int SPELL_SPARK = 2;
const int SPELL_FOOD = 3;
const int SPELL_SING = 4;
const int SPELL_MAP = 5;
const int SPELL_BACKSTAB = 6;
const int SPELL_DUEL = 7;
const int SPELL_PARTY_UP = 8;
const int SPELL_TEAMWORK = 9;
const int SPELL_DEFENDER = 10;
const int SPELL_VICTORY = 11;
const int SPELL_WHIRLWIND = 12;
const int SPELL_HEROIC = 13;
const int SPELL_WOLF = 14;
const int SPELL_PING = 15;
const int SPELL_FIRST_AID = 16;

const int SPELL_SNIPE = 17;
const int SPELL_EXPLOSION = 18;
const int SPELL_RUNE_OF_FLAME = 19;
const int SPELL_RUNE_OF_ICE = 20;
const int SPELL_FIRE_AND_ICE = 21;
const int SPELL_DOUBLEBLAST = 22;
const int SPELL_ELECTROSURGE = 23;
const int SPELL_CLASS_TIME = 24;


/*
OnAttack events (bit positions)
*/
const int ATTACK_DRAW_CARD = 0;
const int ATTACK_STUN_TARGET = 1;
const int ATTACK_GET_WINDSONG = 2;
const int ATTACK_BLOCK_DEATH = 3;
const int ATTACK_SING = 4;
const int ATTACK_ANIMATE_ORACLE = 5;

const int ATTACK_EVENT_COUNT = 6;


/*
OnDeath events (bit positions)
*/
const int DEATH_DRAW_CARD = 0;
const int DEATH_OPPONENT_DRAW_CARD = 1;
const int DEATH_BOOM_SMALL = 2;
const int DEATH_EGG = 3;
const int DEATH_SPELL_DAMAGE = 4;
const int DEATH_SPELL_DISCOUNT = 5;

const int DEATH_EVENT_COUNT = 6;

/*
Keyword bit positions. Use these to index into keywords by bit position
*/
const int CHARGE = 0;			// Action is ready when summoned
const int GUARD = 1;			// If an adjacent ally is attacked, swap spaces with it before combat occurs.
const int AIRDROP = 2;			// Doesn't have to be summoned next to the commander.
const int FURIOUS = 3;			// Two attacks each turn.
const int LIGHTNING = 4;		// Attack will chain through connected enemies.
const int REGENERATE = 5;		// Restores to full health at the start of your turn.
const int DEADLY = 6;			// I kill any minion that I damage.
const int ETHEREAL = 7;			// Can pass through units and impassable terrain.
const int ARMORED = 8;			// Unit regenerates to full health after combat
const int WARD = 9;				// Unit cannot be targeted by enemy spells
const int BEACON = 10;			// Allies can be summoned next to this unit.
const int AMBUSH = 11;			// When initiating combat, unit attacks first.
const int FLEETING = 12; 		// The card is discarded from hand at the end of the turn.
const int HEALER = 13;			// Can't attack or counter-attack. Instead, unit can heal allies within range.
const int DECAY = 14;			// Takes 1 damage at the end of your turn.
const int FLYING = 15;			// Can move through units and difficult terrain. Other units can move through it. Can only be attacked by enemies with Range >1
const int OVERFLOW = 16;		// Cost is reduced by your Manaflow.

const int NUM_KEYWORDS = 17;


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
		case HEALER: return("Healer");
		case DECAY: return("Decay");
		case FLYING: return("Flying");
		case OVERFLOW: return("Overflow");
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
Given a card proto or spell
*/
void displayCardDetails(int proto = 0, int spell = 0) {
	string dialog = "";
	string message = "";
	int keywords = trQuestVarGet("card_"+proto+"_keywords");
	if (spell > 1) {
		keywords = trQuestVarGet("spell_"+spell+"_keywords");
		trMessageSetText(trStringQuestVarGet("spell_"+spell+"_description"), -1);
	}
	bool multiple = false;
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
	message = trStringQuestVarGet("card_"+proto+"_ability");

	if (spell <= SPELL_COMMANDER) {
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
	}

	trSoundPlayDialog("default", "1", -1, false, " : " + dialog, "");
	trSetCounterDisplay(message);

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
	int next = zBankNext("p"+p+"unitBank");
	trUnitSelectClear();
	trUnitSelect(""+next, false);

	if (spell == 0 || spell == SPELL_COMMANDER) {
		trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
		mSetVar(next, "attack", trQuestVarGet("card_" + proto + "_Attack"));
		mSetVar(next, "health", trQuestVarGet("card_" + proto + "_Health"));
		mSetVar(next, "speed", trQuestVarGet("card_" + proto + "_Speed"));
		mSetVar(next, "range", trQuestVarGet("card_" + proto + "_Range"));
		mSetVar(next, "cost", trQuestVarGet("card_" + proto + "_Cost"));
		mSetVar(next, "keywords", trQuestVarGet("card_" + proto + "_Keywords"));
		mSetVar(next, "onAttack", trQuestVarGet("card_" + proto + "_OnAttack"));
		mSetVar(next, "onDeath", trQuestVarGet("card_" + proto + "_OnDeath"));
		mSetString(next, "ability", trStringQuestVarGet("card_" + proto + "_Ability"));
	} else {
		trUnitChangeName("("+1*trQuestVarGet("spell_" + spell + "_Cost")+") "+trStringQuestVarGet("spell_" + spell + "_Name"));
		mSetVar(next, "cost", trQuestVarGet("spell_" + spell + "_Cost"));
		mSetVar(next, "keywords", trQuestVarGet("spell_"+spell+"_keywords"));
		proto = kbGetProtoUnitID("Statue of Lightning");
	}
	
	mSetVar(next, "proto", proto);
	mSetVar(next, "player", p);
	mSetVar(next, "spell", spell);

	trMutateSelected(proto);

	return(next);
}

void SpellSetup(string name = "", int cost = 0, int spell = 0, string desc = "", int keywords = 0) {
	trStringQuestVarSet("spell_"+spell+"_name", name);
	trQuestVarSet("spell_"+spell+"_cost", cost);
	trStringQuestVarSet("spell_"+spell+"_description", desc);


	trQuestVarSet("cardToSpell"+1*trQuestVarGet("cardIndex"), spell);
	trQuestVarSet("spellToCard"+spell, trQuestVarGet("cardIndex"));
	trQuestVarSet("cardToProto"+1*trQuestVarGet("cardIndex"), kbGetProtoUnitID("Statue of Lightning"));
	trQuestVarSet("cardIndex", 1 + trQuestVarGet("cardIndex"));

	trQuestVarSet("spell_"+spell+"_keywords", keywords);

}

void CardEvents(string protoName = "", int onAttack = 0, int onDeath = 0, string ability="") {
	int proto = kbGetProtoUnitID(protoName);
	trQuestVarSet("card_" + proto + "_OnAttack",onAttack);
	trQuestVarSet("card_" + proto + "_OnDeath",onDeath);
	trStringQuestVarSet("card_" + proto + "_Ability",ability);
}

void CardSetup(string protoName="", int cost=1, string name="", int attack=1, int health=1, int speed=1, int range=0, int keywords=0, bool uncollectable = false){
	int proto = kbGetProtoUnitID(protoName);
	if(proto<0){
		ThrowError("That's not a unit. Method: CardSetup");
	}

	if (uncollectable == false) {
		trQuestVarSet("cardToProto"+1*trQuestVarGet("cardIndex"), proto);
		trQuestVarSet("protoToCard"+proto, trQuestVarGet("cardIndex"));
		trQuestVarSet("cardIndex", 1 + trQuestVarGet("cardIndex"));
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
		/* 
		need this for heroize deck importing 
		trForbidProtounit(p, "Swordsman Hero"); 
		*/
		trForbidProtounit(p, "Trident Soldier Hero");
		trForbidProtounit(p, "Villager Atlantean Hero");
		trForbidProtounit(p, "Settlement Level 1");
		trForbidProtounit(p, "Guild");
		trForbidProtounit(p, "Manor");
		trForbidProtounit(p, "Dock");
		trForbidProtounit(p, "Wall Connector");
		trForbidProtounit(p, "Temple");
	}

	/*
	Don't use unit 0 because a lot of things are default 0
	*/
	zBankInit("p1unitBank", 1, 63);
	zBankInit("p2unitBank", 64, 64);
	zBankInit("allUnitsBank", 1, 128);

	//Pick a card. Any card.
	/*
	Unit stats and keywords
	        Proto                  Cost    Name       Attack|Health|Speed|Range    Keywords
	*/
	CardSetup("Statue of Lightning",	0, "Spell",				0, 1, 0, 0, 0, true);
	/*
	ADVENTURER
	*/
	// Created cards
	CardSetup("Hero Greek Jason",		0, "phdorogers4", 		2, 20, 2, 1, Keyword(BEACON) + Keyword(ETHEREAL), true);
	
	// 0 - 4
	CardSetup("Swordsman", 				1, "New Recruit", 		1, 3, 2, 1, Keyword(ETHEREAL));
	CardSetup("Wolf",					1, "Loyal Wolf",		1, 1, 2, 1, Keyword(GUARD));
	CardSetup("Khopesh", 				2, "Thief", 			1, 2, 2, 1); // Attack: Draw 1 card.
	CardSetup("Skraeling", 				3, "Bear Hunter", 		3, 1, 2, 1); // Play: Summon a 1|1 Loyal Wolf with Guard.
	CardSetup("Toxotes", 				2, "Sharpshooter",	 	2, 2, 2, 2);
	// 5 - 9
	CardSetup("Villager Atlantean",		2, "Traveling Chef",	1, 2, 2, 1); // Play: Grant an allied minion +1|+1
	CardSetup("Peltast", 				3, "Forest Ranger", 	2, 1, 2, 2); // Play: Deal 1 damage.
	CardSetup("Physician",				3, "Bard", 				0, 3, 2, 1, Keyword(HEALER));
	CardSetup("Hero Greek Ajax", 		3, "Party Leader", 		3, 4, 2, 1, Keyword(ETHEREAL));
	CardSetup("Raiding Cavalry",		3, "Reckless Rider", 	3, 2, 3, 1, Keyword(AMBUSH));
	// 10 - 14 (LEGENDARY at 19)
	CardSetup("Trident Soldier",		4, "Shieldbearer", 		2, 6, 1, 1, Keyword(GUARD));
	CardSetup("Jarl", 					4, "Wanderer", 			1, 4, 3, 1, Keyword(DEADLY));
	CardSetup("Huskarl",			 	5, "Seasoned Veteran", 	2, 3, 2, 1); // Play: Grant adjacent allied minions +1|+1
	CardSetup("Hero Greek Theseus", 	4, "Silent Paladin", 	4, 6, 2, 1); // Minions I kill don't trigger their Death effect.
	CardSetup("Archer Atlantean Hero", 	7, "Ace", 				3, 1, 2, 2, Keyword(FURIOUS) + Keyword(AMBUSH) + Keyword(CHARGE));
	// 15 - 19
	CardSetup("Mountain Giant",	 		5, "Big Friendly Giant",6, 7, 1, 1);
	CardSetup("Avenger", 				6, "Doubleblade", 		5, 5, 2, 1, Keyword(AIRDROP));
	SpellSetup("Windsong", 				2, SPELL_SING, 			"(2)Windsong: Select an ally that has already acted. Grant it another action.");
	SpellSetup("Explorer's Map", 		2, SPELL_MAP, 			"(2)Explorer's Map: Grant an allied minion +1 Speed and Pathfinder");
	SpellSetup("Backstab", 				1, SPELL_BACKSTAB, 		"(1)Backstab: Deal 2 damage to an enemy next to another enemy.");
	// 20 - 24
	SpellSetup("Duel", 					2, SPELL_DUEL, 			"(2)Duel: An allied minion and an enemy minion attack each other, regardless of distance.");
	SpellSetup("Party Up!", 			3, SPELL_PARTY_UP, 		"(3)Party Up!: Draw 3 cards that cost 1 mana.");
	SpellSetup("Teamwork", 				5, SPELL_TEAMWORK, 		"(5)Teamwork: Choose an enemy minion. All allies within range attack it.");
	SpellSetup("Defender's Glory", 		3, SPELL_DEFENDER, 		"(3)Defender's Glory: Grant an allied minion +2 health and Guard.");
	SpellSetup("Song of Victory", 		3, SPELL_VICTORY, 		"(3)Song of Victory: Grant all allied minions +1 attack and Ambush this turn.");
	// 25 - 29 (LEGENDARY at 29)
	SpellSetup("Whirlwind", 			7, SPELL_WHIRLWIND, 	"(7)Whirlwind: A minion attacks all adjacent enemies.");
	SpellSetup("Heroic Tales", 			4, SPELL_HEROIC, 		"(4)Heroic Tales: Grant an allied minion +1 attack and Furious.");
	CardSetup("Scout",					3, "Speedy Cartographer",2, 3, 3, 1); // Play: Add an Explorer's Map to your hand.
	SpellSetup("First-Aid", 			1, SPELL_FIRST_AID, 	"(1)First-Aid: Teleport an allied minion next to your Commander and restore 2 health to it.");
	CardSetup("Nemean Lion",			8, "Guild Master",		6, 6, 2, 1); // Play: Stun all enemy minions that cost {Manaflow} or less.
	/*
	ARCANE
	*/
	// Created cards
	CardSetup("Fire Giant",				5, "Blaze Elemental",	4, 6, 2, 2, Keyword(FURIOUS));
	CardSetup("Frost Giant",			5, "Frost Elemental",	3, 6, 2, 1); // stuns its targets.
	CardSetup("Phoenix Egg",			5, "Reviving Egg",		0, 3, 0, 0); // At the start of your turn, destroy me and summon a Fading Lightwing on my tile.
	
	// 30-34
	CardSetup("Slinger", 				2, "Apprentice", 		1, 1, 2, 2);
	CardSetup("Maceman", 				2, "School Guard",		2, 3, 2, 1, Keyword(GUARD));
	CardSetup("Swordsman Hero",			3, "Spellsword",		1, 4, 2, 1); // After you cast a spell, grant me +1 attack.
	CardSetup("Javelin Cavalry Hero",	3, "Magic Messenger",	1, 1, 3, 2, Keyword(BEACON) + Keyword(WARD));
	CardSetup("Priest",					4, "Tower Researcher",	2, 2, 2, 2, Keyword(HEALER)); // Your spells cost 1 less.
	// 35-39
	CardSetup("Oracle Scout",			3, "Magic Teacher",		0, 2, 1, 0); // Your spells deal +1 damage.
	SpellSetup("Spark", 				1, SPELL_SPARK, 		"(1)Spark: Deal 1 damage.");
	SpellSetup("Class Time",			3, SPELL_CLASS_TIME,	"(3)Class Time: Draw a spell and a minion.");
	SpellSetup("Spellsnipe",			3, SPELL_SNIPE,			"(3)Spellsnipe: An ally attacks an enemy within range. Add their range to the damage dealt.");
	SpellSetup("Arcane Explosion",		3, SPELL_EXPLOSION,		"(3)Arcane Explosion: Deal 1 damage to enemies within 1 space of the target location.");
	// 40-44 (LEGENDARY at 44)
	SpellSetup("Rune of Flame",			5, SPELL_RUNE_OF_FLAME,	"(5)Rune of Flame: Deal 6 damage to your Commander to summon a 4|6 Blaze Elemental with Furious.");
	SpellSetup("Rune of Ice",			5, SPELL_RUNE_OF_ICE,	"(5)Rune of Ice: Stun your Commander to summon a 3|6 Frost Elemental that stuns its target.");
	SpellSetup("Doubleblast",			2, SPELL_DOUBLEBLAST,	"(2)Doubleblast: Deal 1 damage to two enemies.");
	SpellSetup("Electrosurge",			5, SPELL_ELECTROSURGE,	"(5)Electrosurge: Deal 2 damage with Lightning.");
	SpellSetup("Fire and Ice",			15, SPELL_FIRE_AND_ICE,	"(15)Fire and Ice: Summon a Blaze Elemental and a Frost Elemental. Cost is reduced by your Manaflow.", Keyword(OVERFLOW));
	// 45-49
	CardSetup("Phoenix From Egg",		5, "Fading Lightwing",	4, 3, 2, 1, Keyword(FLYING) + Keyword(DECAY));
	// 50-54

	// 55-59 (LEGENDARY at 59)

	/*
	Unit OnPlay, OnAttack, OnDeath, and description
		Proto | OnAttack | OnDeath | Description
	*/
	CardEvents("Hero Greek Jason", Keyword(ATTACK_GET_WINDSONG), 0, "Attack: Add a Windsong to your hand. Discard it when turn ends.");
	CardEvents("Khopesh", Keyword(ATTACK_DRAW_CARD), 0, "Attack: Draw a card.");
	CardEvents("Skraeling", 0, 0, "Play: Summon a 1|1 Loyal Wolf with Guard.");
	CardEvents("Avenger", 0, 0, "Play: Deal 1 damage to all adjacent enemies.");
	CardEvents("Villager Atlantean", 0, 0, "Play: Grant an allied minion +1 attack and health.");
	CardEvents("Hero Greek Theseus", Keyword(ATTACK_BLOCK_DEATH), 0, "Minions I kill don't trigger their Death effect.");
	CardEvents("Physician", Keyword(ATTACK_SING), 0, "When I heal an ally that has acted, grant them another action.");
	CardEvents("Scout", 0, 0, "Play: Add an Explorer's Map to your hand.");
	CardEvents("Peltast", 0, 0, "Play: Deal 1 damage.");
	CardEvents("Huskarl", 0, 0, "Play: Grant adjacent allied minions +1 attack and health.");
	CardEvents("Nemean Lion", 0, 0, "Play: Stun all enemy minions that cost {Manaflow} or less.");

	CardEvents("Swordsman Hero", 0, 0, "After you cast a spell, grant me +1 attack.");
	CardEvents("Slinger", 0, 0, "Play: Add a Spark to your hand.");
	CardEvents("Priest", 0, Keyword(DEATH_SPELL_DISCOUNT), "Your spells cost 1 less.");
	CardEvents("Oracle Scout", 0, Keyword(DEATH_SPELL_DAMAGE), "Your spells deal +1 damage.");
	CardEvents("Frost Giant", Keyword(ATTACK_STUN_TARGET), 0, "Attack: Stun my target.");
	CardEvents("Phoenix Egg", 0, 0, "At the start of your turn, destroy me to summon a Fading Lightwing.");
	CardEvents("Phoenix From Egg", 0, Keyword(DEATH_EGG), "Death: Summon a Reviving Egg on my tile.");
	/*
	Spells
				Name 	Cost 	Spell
	*/
	
	
	
	xsDisableRule("initializeCards");
}

int getCardClass(int index = 0) {
	return(1*xsFloor(index / 30));
}
/*
we don't need this function. Just call dataSave() in dataLoad.c;
*/
void saveDeck() {
	
}

int CardToProto(int card = 0) {
	return(1*trQuestVarGet("CardToProto"+card));
}

int CardToSpell(int card = 0) {
	return(1*trQuestVarGet("CardToSpell"+card));
}

int ProtoToCard(int proto = 0) {
	return(1*trQuestVarGet("ProtoToCard"+proto));
}

int SpellToCard(int spell = 0) {
	return(1*trQuestVarGet("SpellToCard"+spell));
}

int getCardCountCollection(int index = 0) {
	return(1*trQuestVarGet("card_"+index+"_count") - trQuestVarGet("card_"+index+"_countInDeck"));
}

int getCardCountDeck(int index = 0) {
	return(1*trQuestVarGet("card_"+index+"_countInDeck"));
}

void setCardCountCollection(int index = 0, int count = 0) {
	trQuestVarSet("card_"+index+"_count", count);
}

void setCardCountDeck(int index = 0, int count = 0) {
	trQuestVarSet("card_"+index+"_countInDeck", count);
}

void setDeckCommander(int commander = 0) {
	trQuestVarSet("commander", commander);
}

int getDeckCommander() {
	return(1*trQuestVarGet("commander"));
}

void setClassProgress(int class = 0, int progress = 0) {
	trQuestVarSet("class"+class+"progress", progress);
}

int getClassProgress(int class = 0) {
	return(1*trQuestVarGet("class"+class+"progress"));
}

