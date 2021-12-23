
void ThrowError(string message = "Zeno you made bug again!"){
	trShowWinLose(message, "xpack\xtaunts\en\999 theme.mp3");
}

const int STATE_ALIVE = 0;
const int STATE_DEAD = 1;

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
Commanders
*/
const int COMMANDER_ROGERS = 0;
const int COMMANDER_VENLESH = 1;
const int COMMANDER_NANO = 2;
const int COMMANDER_NOTTUD = 3;
const int COMMANDER_SCRAGINS = 4;
const int COMMANDER_REACH = 5;
const int COMMANDER_ROXAS = 6;
const int COMMANDER_YEEBAAGOOON = 7;
const int COMMANDER_ANRAHEIR = 8;
const int COMMANDER_ZENOPHOBIA = 9;
const int COMMANDER_NICK = 10;
const int COMMANDER_GOD = 11;

/*
Spells
*/
const int SPELL_NONE = 0;
const int SPELL_COMMANDER = 1; // Since the "spell" variable is unused on normal minions, we use it here to mark a unit as the Commander

const int SPELL_TYPE_DEFENSIVE = 1;
const int SPELL_TYPE_OTHER = 2;
const int SPELL_TYPE_OFFENSIVE = 3;

// Story
const int SPELL_INTIMIDATE = 999;
const int SPELL_GROUND_STOMP = 998;
const int SPELL_PISTOL_SHOT = 997;
const int SPELL_BOOTS_TREASURE = 996;
const int SPELL_WEAPONS_TREASURE = 995;
const int SPELL_SHIELDS_TREASURE = 994;
const int SPELL_RELOAD = 993;
const int SPELL_POISON_CLOUD = 992;
const int SPELL_NATURE_ANGRY = 991;
const int SPELL_ELVEN_APOCALYPSE = 990;
const int SPELL_FROST_BREATH = 989;
const int SPELL_PYROBALL = 988;
const int SPELL_MIRROR_REFLECTION = 987;
const int SPELL_KRAKEN_HUG = 986;
const int SPELL_WATER_PRESSURE = 985;
const int SPELL_OXYGEN_TANK = 984;

const int SPELL_DOMINANCE = 802;
const int SPELL_TAVERN_BRAWL = 801;
const int SPELL_SPIDER_LAIR = 800;
// Heap

// Adventurer
const int SPELL_FIRST_AID = 2;
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
const int SPELL_SUMMON_ONE = 13;
const int SPELL_WOLF = 14;
const int SPELL_PING = 15;
const int SPELL_GUARDIAN_OF_SEA = 16;


// Arcane
const int SPELL_SPARK = 17;
const int SPELL_EXPLOSION = 18;
const int SPELL_RUNE_OF_FLAME = 19;
const int SPELL_RUNE_OF_ICE = 20;
const int SPELL_FIRE_AND_ICE = 21;
const int SPELL_DOUBLEBLAST = 22;
const int SPELL_ELECTROSURGE = 23;
const int SPELL_CLASS_TIME = 24;
const int SPELL_COPY_HOMEWORK = 25;
const int SPELL_METEOR = 26;
const int SPELL_MIRROR_IMAGE = 27;
const int SPELL_FINAL_EXAM = 28;
const int SPELL_APOCALYPSE = 29;
const int SPELL_SNIPE = 30;

const int SPELL_VALKYRIE_HEAL = 31;
const int SPELL_SHAPESHIFT = 32;

// Naga
const int SPELL_WATER_CANNON = 33;
const int SPELL_TIDAL_WAVE = 34;
const int SPELL_FLUSH = 35;
const int SPELL_DEEP_DIVE = 36;
const int SPELL_SEA_EMBRACE = 37;
const int SPELL_TELETIDE = 38;
const int SPELL_WRATH_OF_SEA = 39;
const int SPELL_RUNE_OF_WATER = 40;
const int SPELL_CLEANSING_WATERS = 41;
const int SPELL_DROWN = 42;

const int SPELL_LAMPADES_CONVERT = 43;
const int SPELL_MEDUSA_STUN = 44;

// Otherworld
const int SPELL_WORLD_SPLITTER = 45;
const int SPELL_SOUL_SIPHON = 46;
const int SPELL_BLOOD_PRICE = 47;
const int SPELL_DEATH_APPROACHES = 48;
const int SPELL_DOOM = 49;
const int SPELL_SHADOWSTEP = 50;
const int SPELL_FINAL_FRENZY = 51;
const int SPELL_CORPSE_PARTY = 52;
const int SPELL_UNDEATH = 53;
const int SPELL_RUNE_OF_DARKNESS = 54;
const int SPELL_ZENOS_PARADOX = 55;

const int SPELL_DEMON_EAT = 56;
const int SPELL_SCORPION_STING = 57;

// Clockwork
const int SPELL_CHOOSE_DIRECTION = 58;
const int SPELL_SCRAP_METAL = 59;
const int SPELL_MAGNETIZE = 60;
const int SPELL_ELECTRIC_GRID = 61;
const int SPELL_ZAP_GUN = 62;
const int SPELL_GEAR_FACTORY = 63;
const int SPELL_COMPRESS = 64;
const int SPELL_UPGRADE = 65;
const int SPELL_PROFITEERING = 66;
const int SPELL_WARNING_SHOT = 67;
const int SPELL_PORTABLE_SPELL_SHIELD = 68;
const int SPELL_REWIND = 69;
const int SPELL_TIME_POCKET = 70;
const int SPELL_BANHAMMER = 71;
const int SPELL_ASSEMBLY_LINE = 72;
const int SPELL_POWER_SUIT = 73;
const int SPELL_BORROWED_TIME = 74;
const int SPELL_FORTIFY = 75;
const int SPELL_SONG_OF_REST = 76;

// SPACE
const int SPELL_NICKS_PORTAL = 77;

/*
OnAttack events (bit positions)
*/
const int ATTACK_DRAW_CARD = 0;
const int ATTACK_STUN_TARGET = 1;
const int ATTACK_GET_WINDSONG = 2;
const int ATTACK_BLOCK_DEATH = 3;
const int ATTACK_SING = 4;
const int ATTACK_ANIMATE_ORACLE = 5;
const int ATTACK_DISCOUNT = 6;
const int ATTACK_GET_ARCANE = 7;
const int ATTACK_YEET = 8;
const int ATTACK_PUSH = 9;
const int ATTACK_RETURN = 10;
const int ATTACK_GET_MANAFLOW = 11;
const int ATTACK_GET_ZOMBIE = 12;
const int ATTACK_SUMMON_ZOMBIE = 13;
const int ATTACK_POISON = 14;
const int ATTACK_GET_MINION = 15;
const int ATTACK_GET_FENRIS = 16;
const int ATTACK_ANIMATE_TOWER = 17;
const int ATTACK_OVERKILL_HEALS = 18;
const int ATTACK_RALLY = 19;
const int ATTACK_ARCANE_MISSLE = 20;
const int ATTACK_SPELL_DAMAGE = 21;
const int ATTACK_DRAW_CARD_ENEMY_COST = 22;
const int ATTACK_SUMMON_TREE = 23;
const int ATTACK_TEAMWORK = 24;

const int ATTACK_EVENT_COUNT = 25;

/*
OnDeath events (bit positions)
*/
const int DEATH_DRAW_CARD = 1;
const int DEATH_OPPONENT_DRAW_CARD = 2;
const int DEATH_BOOM_SMALL = 3;
const int DEATH_EGG = 4;
const int DEATH_GET_ARCANE = 5;
const int DEATH_SUMMON_ZOMBIE = 6;
const int DEATH_SUMMON_SHADOW = 7;
const int DEATH_GET_ATTACK = 8;
const int DEATH_POISON_MIST = 9;
const int DEATH_DARKNESS_RETURNS = 10;
const int DEATH_SUMMON_RANDOM = 11;
const int DEATH_GET_SCRAP = 12;
const int DEATH_GET_TREASURE = 13;
const int DEATH_SUMMON_BEETLE = 14;
const int DEATH_DAMAGE_ENEMY = 15;
const int DEATH_REDUCE_COST = 16;

const int DEATH_EVENT_COUNT = 17;


/*
Keyword bit positions. Use these to index into keywords by bit position
*/
const int CHARGE = 0;
const int GUARD = 1;
const int AIRDROP = 2;
const int FURIOUS = 3;
const int LIGHTNING = 4;
const int REGENERATE = 5;
const int DEADLY = 6;
const int ETHEREAL = 7;
const int ARMORED = 8;
const int WARD = 9;
const int BEACON = 10;
const int AMBUSH = 11;
const int FLEETING = 12;
const int HEALER = 13;
const int DECAY = 14;
const int FLYING = 15;
const int OVERFLOW = 16;
const int MAGNETIC = 17;
const int CONDUCTOR = 18;
const int STEALTH = 19;
const int IMPORTANT = 20;

const int NUM_KEYWORDS = 21;


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
		case MAGNETIC: return("Magnetic");
		case CONDUCTOR: return("Conductor");
		case STEALTH: return("Stealth");
		case IMPORTANT: return("Important");
	}
	ThrowError("Invalid keyword id. Method: GetKeywordName");
	return ("");
}

string GetKeywordDescription(int bitPosition=0){
	switch(bitPosition){
		case CHARGE: return ("Ready to act when summoned.");
		case GUARD: return ("If an adjacent ally is attacked, swap spaces with it before combat occurs.");
		case AIRDROP: return ("I don't have to be summoned next to Beacon.");
		case FURIOUS: return ("Two attacks each turn.");
		case LIGHTNING: return ("Attack will chain through connected enemies.");
		case REGENERATE: return ("Restores to full health at the start of your turn.");
		case DEADLY: return ("I kill any minion that I attack.");
		case ETHEREAL: return ("Can pass through units and impassable terrain.");
		case ARMORED: return ("I take 1 less damage from all sources.");
		case WARD: return ("I cannot be targeted by spells or play effects.");
		case BEACON: return ("Allies can be summoned next to me.");
		case AMBUSH: return ("When initiating combat, I attack first.");
		case FLEETING: return ("The card is discarded from hand at the end of the turn.");
		case HEALER: return("Can't attack or counter-attack. Instead, I can heal allies within range.");
		case DECAY: return("I take 1 damage at the end of your turn.");
		case FLYING: return("Pathfinder. Other units can move through. Can only be attacked by ranged enemies.");
		case OVERFLOW: return("Cost is reduced by your Manaflow.");
		case MAGNETIC: return("When played next to another Magnetic minion, you can combine them, adding attack, health, and keywords.");
		case CONDUCTOR: return("Allied Lightning effects can pass through me.");
		case STEALTH: return("I cannot be targeted until I take damage.");
		case IMPORTANT: return("If my Commander dies I become the new Commander.");
	}
	ThrowError("Invalid keyword id. Method: GetKeywordDescription");
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


int getCardClass(int index = 0) {
	return(1*xsFloor(index / 30));
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


/* 
Given the class and spell type, returns the statue animation
*/
int GetSpellAnimation(int class = 0, int type = 0){
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			switch(type)
			{
				case SPELL_TYPE_OFFENSIVE:
				{
					return (6);	// Loki
				}
				case SPELL_TYPE_DEFENSIVE:
				{
					return (8);	// Thor
				}
				case SPELL_TYPE_OTHER:
				{
					return (7);	// Odin
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(type)
			{
				case SPELL_TYPE_OFFENSIVE:
				{
					return (9);	// Kronos
				}
				case SPELL_TYPE_DEFENSIVE:
				{
					return (9); // Kronos
				}
				case SPELL_TYPE_OTHER:
				{
					return (11); // Oranos
				}
			}
		}
		case CLASS_NAGA:
		{
			switch(type)
			{
				case SPELL_TYPE_OFFENSIVE:
				{
					return (9); // Kronos
				}
				case SPELL_TYPE_DEFENSIVE:
				{
					return (9); // Kronos
				}
				case SPELL_TYPE_OTHER:
				{
					return (10); // Gaia
				}
			}
		}
		case CLASS_CLOCKWORK:
		{
			switch(type)
			{
				case SPELL_TYPE_OFFENSIVE:
				{
					return (2);	// Set
				}
				case SPELL_TYPE_DEFENSIVE:
				{
					return (0);	// Isis
				}
				case SPELL_TYPE_OTHER:
				{
					return (1);	// Ra
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(type)
			{
				case SPELL_TYPE_OFFENSIVE:
				{
					return (3);	// Hades
				}
				case SPELL_TYPE_DEFENSIVE:
				{
					return (4);	// Poseidon
				}
				case SPELL_TYPE_OTHER:
				{
					return (5);	// Zeus
				}
			}
		}
	}
	ThrowError("GetSpellAnimation");
}

string getCardClassIcon(int card = 0) {
	switch(getCardClass(card))
	{
		case CLASS_ADVENTURER:
		{
			return("icons\building specialist icons 64");
		}
		case CLASS_ARCANE:
		{
			return("icons\improvement focus icons 64");
		}
		case CLASS_NAGA:
		{
			return("icons\improvement poseidons secret icons 64");
		}
		case CLASS_CLOCKWORK:
		{
			return("icons\improvement engineers icon 64");
		}
		case CLASS_EVIL:
		{
			return("icons\god power ancestors icon 64");
		}
		case CLASS_SPACE:
		{
			return("icons\god power eclipse icon 64");
		}
	}
}

string colorizeStat(int name = 0, string s = "Attack", string d = "ATK") {
	int diff = mGetVar(name, s) - trQuestVarGet("card_"+1*mGetVar(name, "proto")+"_"+s);
	string val = "";
	
	if (diff > 0) {
		val = "<color=0,1,0>"+d+" "+1*mGetVar(name, s)+"</color>";
	} else if (diff < 0) {
		val = "<color=1,0,0>"+d+" "+1*mGetVar(name, s)+"</color>";
	} else {
		val = d+" "+1*mGetVar(name, s);
	}
	
	return(val);
}


/*
Given a card proto or spell
*/
void displayCardDetails(int proto = 0, int spell = 0) {
	string dialog = "";
	string message = "";
	int keywords = trQuestVarGet("card_"+proto+"_keywords");
	message = trStringQuestVarGet("card_"+proto+"_ability");
	int card = ProtoToCard(proto);
	if (spell > 1) {
		keywords = trQuestVarGet("spell_"+spell+"_keywords");
		message = trStringQuestVarGet("spell_"+spell+"_description");
		card = SpellToCard(proto);
	}
	
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
		trChatSend(0, "<color={Playercolor(1)}>==== (" + 1*trQuestVarGet("card_"+proto+"_cost") + ") " + trStringQuestVarGet("card_"+proto+"_name")+" ====</color>");
		trChatSend(0, "ATK " + 1*trQuestVarGet("card_"+proto+"_attack") + " | HP " + 1*trQuestVarGet("card_"+proto+"_health") + " | SPD " + 1*trQuestVarGet("card_"+proto+"_speed") + " | RNG " + 1*trQuestVarGet("card_"+proto+"_range"));
	} else {
		trChatSend(0, "<color={Playercolor(1)}>=== (" + 1*trQuestVarGet("spell_"+spell+"_cost") + ") " + trStringQuestVarGet("spell_"+spell+"_name")+" ===</color>");
	}
	
	if(message != ""){
		trChatSend(0, message);		
	}

	bool multiple = false;
	if (keywords>0) {
		trChatSend(0, "==== Keywords ====");
		int current = xsPow(2, NUM_KEYWORDS - 1);
		for(k=NUM_KEYWORDS - 1; >=0){
			if (keywords >= current) {
				if(multiple){
					dialog = dialog + ", ";
				}
				multiple = true;
				dialog = dialog + GetKeywordName(k);
				keywords = keywords - current;
				trChatSend(0, GetKeywordName(k) + ": " + GetKeywordDescription(k));
			}
			current = current / 2;
		}
	}

	trSoundPlayDialog("default", "1", -1, false, " : " + dialog, getCardClassIcon(card));
}

void updateMana() {
	for(p=1;<=2){
		trCounterAbort("mana"+p);
		string str = "<color={Playercolor("+p+")}>Manaflow: "+1*trQuestVarGet("p"+p+"manaflow");
		if(p == trQuestVarGet("activePlayer")){
			str = str + " | Mana: "+1*trQuestVarGet("p"+p+"mana") + "/" + 1*trQuestVarGet("maxMana");
		}
		trCounterAddTime("mana"+p, -1, -9999999, str,-1);
		trCounterAbort("handAndDeck"+p);
		trCounterAddTime("handAndDeck"+p, -1, -9999999, 
			"<color={Playercolor("+p+")}>Hand: "+1*yGetDatabaseCount("p"+p+"hand") + " | Deck: "+1*yGetDatabaseCount("p"+p+"deck"), -1);
	}
}

/*
Given a card name in a given db array, print information
of the selected unit.
*/
void displayCardKeywordsAndDescription(int name = 0) {
	ChatLogShow();
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

	int card = ProtoToCard(proto);
	int old = xsGetContextPlayer();
	int p = mGetVar(name, "player");
	int discount = 0;
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
		
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+name));
		trVectorQuestVarSet("center", kbGetBlockPosition("128"));

		trChatSend(0, "<color={Playercolor("+p+")}>==== (" + 1*mGetVar(name, "cost") + ") " + trStringQuestVarGet("card_"+proto+"_name")+" ====</color>");
		if (zDistanceBetweenVectorsSquared("pos", "center") > 2025) {
			discount = trQuestVarGet("p"+p+"minionDiscount");
			if (HasKeyword(OVERFLOW, 1*mGetVar(name, "keywords"))) {
				discount = discount + trQuestVarGet("p"+p+"manaflow");
			}
			if (discount > 0) {
				trChatSend(0, "<color=0,1,0>Discount " + discount);
				bonus = "Discount " + discount;
			}
			trChatSend(0, "ATK " + 1*trQuestVarGet("card_"+proto+"_attack") + " | HP " + 1*trQuestVarGet("card_"+proto+"_health") + " | SPD " + 1*trQuestVarGet("card_"+proto+"_speed") + " | RNG " + 1*trQuestVarGet("card_"+proto+"_range"));
		} else {
			xsSetContextPlayer(1*mGetVar(name, "player"));
			int diff = 1*mGetVar(name, "health") - kbUnitGetCurrentHitpoints(kbGetBlockID(""+name, true));
			if (diff > 0) {
				bonus = bonus + "HP +" + diff + " ";
			}

			diff = mGetVar(name, "attack") - trQuestVarGet("card_" + proto + "_Attack");
			if (diff > 0) {
				bonus = bonus + "ATK +" + diff + " ";
			} else if (diff < 0) {
				bonus = bonus + "ATK " + diff + " ";
			}

			diff = mGetVar(name, "speed") - trQuestVarGet("card_" + proto + "_Speed");
			if (diff > 0) {
				bonus = bonus + "SPD +" + diff;
			} else if (diff < 0) {
				bonus = bonus + "SPD " + diff;
			}
			trChatSend(0, colorizeStat(name, "Attack", "ATK") + " | " + colorizeStat(name, "Health", "HP") + " | " + colorizeStat(name, "Speed", "SPD") + " | " + colorizeStat(name, "Range", "RNG"));
		}
		
		if (mGetVar(name, "keywords") > 0) {
			trChatSend(0, dialog);
		}
		trChatSend(0, trStringQuestVarGet("card_"+proto+"_Ability"));
	} else {
		card = SpellToCard(1*mGetVar(name, "spell"));
		trChatSend(0, "<color={Playercolor("+p+")}>=== (" + 1*mGetVar(name, "cost") + ") " + trStringQuestVarGet("spell_"+1*mGetVar(name, "spell")+"_name")+" ===</color>");

		discount = trQuestVarGet("p"+p+"spellDiscount");
		if (HasKeyword(OVERFLOW, 1*mGetVar(name, "keywords"))) {
			discount = discount + trQuestVarGet("p"+p+"manaflow");
		}
		if ((discount == 0) == false) {
			bonus = "Discount " + discount;
			if (discount > 0) {
				trChatSend(0, "<color=0,1,0>Discount " + discount);
			} else if (discount < 0) {
				trChatSend(0, "<color=1,0,0>Discount " + discount);
			}
		}
		
		if (mGetVar(name, "keywords") > 0) {
			trChatSend(0, dialog);
		}
		trChatSend(0, trStringQuestVarGet("spell_"+1*mGetVar(name, "spell")+"_description"));
	}

	updateMana();
	trSoundPlayDialog("default", "1", -1, false, bonus + ": " + dialog, getCardClassIcon(card));

	xsSetContextPlayer(old);
}

int CardInstantiate(int p = 0, int proto = 0, int spell = 0) {
	int next = 0;
	for(x=64; >0) {
		next = zBankNext("p"+p+"unitBank");
		if (mGetVar(next, "played") == 0) {
			break;
		}
	}
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
		mSetVar(next, "scale", 1);
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
	mSetVar(next, "played", 1);
	mSetVar(next, "state", STATE_ALIVE);

	trMutateSelected(proto);
	trUnitConvert(p);

	return(next);
}

void SpellSetup(string name = "", int cost = 0, int spell = 0, string desc = "", int type = 0, int keywords = 0, bool uncollectable = false) {
	trStringQuestVarSet("spell_"+spell+"_name", name);
	trQuestVarSet("spell_"+spell+"_cost", cost);
	trStringQuestVarSet("spell_"+spell+"_description", desc);
	trQuestVarSet("spell_"+spell+"_type", type);
	trQuestVarSet("spell_"+spell+"_animation", GetSpellAnimation((1*trQuestVarGet("cardIndex"))/30, type));

	// This is so that the uncollectable card is assigned to the right class
	trQuestVarSet("spellToCard"+spell, trQuestVarGet("cardIndex"));
	if (uncollectable == false) {
		trQuestVarSet("cardToSpell"+1*trQuestVarGet("cardIndex"), spell);
		trQuestVarSet("cardToProto"+1*trQuestVarGet("cardIndex"), kbGetProtoUnitID("Statue of Lightning"));
		trQuestVarSet("cardIndex", 1 + trQuestVarGet("cardIndex"));
	}

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

	// this is so that the uncollectable card is assigned to the right class
	trQuestVarSet("protoToCard"+proto, trQuestVarGet("cardIndex"));
	if (uncollectable == false) {
		trQuestVarSet("cardToProto"+1*trQuestVarGet("cardIndex"), proto);
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
	} else {
		trModifyProtounit(protoName, 1, 55, 1);
		trModifyProtounit(protoName, 2, 55, 1);
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

		trModifyProtounit(protoName, p, 1, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 1, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 1, 10); // Speed

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
		trForbidProtounit(p, "Siege Tower");
		trForbidProtounit(p, "Manor");
		trForbidProtounit(p, "Dock");
		trForbidProtounit(p, "Wall Connector");
		trForbidProtounit(p, "Temple");
		trForbidProtounit(p, "Ulfsark");
		trModifyProtounit("Minion", p, 8, -99); // minion lifespan
	}

	/*
	Don't use unit 0 because a lot of things are default 0
	*/
	zBankInit("p1unitBank", 1, 63);
	zBankInit("p2unitBank", 64, 64);
	zBankInit("allUnitsBank", 1, 127);

	CardSetup("Automaton",		0, "Training Dummy", 		0, 10, 0, 0, 0, true);
	CardEvents("Automaton", 0, 0, 		"Hit me hard daddy!");
	
	CardSetup("General Melagius",		0, "General Store", 			2, 20, 2, 1, Keyword(BEACON), true);
	CardEvents("General Melagius", Keyword(ATTACK_RALLY), 0,	"Attack: If it's my turn, give allied minions +1 Attack.");
	CardSetup("Shaba Ka",				0, "Mister Pirate", 			2, 20, 2, 1, Keyword(BEACON), true);
	CardEvents("Shaba Ka", 0, 0,	"At the start of your turn, the player with the most units gets a random treasure.");
	CardSetup("Qilin",					0, "Forest Protector",		2, 40, 2, 1, Keyword(BEACON), true);
	CardEvents("Qilin", Keyword(ATTACK_DRAW_CARD_ENEMY_COST), 0, 	"Attack: Draw a card. Reduce its cost by the number of enemies.");
	CardSetup("Audrey",					0, "Vora",					2, 20, 0, 1, Keyword(BEACON) + Keyword(DEADLY), true);
	CardEvents("Audrey", 0, 0,	"I gain Regenerate on Turn 5.");
	
	CardSetup("Pharaoh Secondary",		0, "Fire Mage", 			2, 20, 2, 2, Keyword(BEACON), true);
	CardEvents("Pharaoh Secondary", Keyword(ATTACK_SPELL_DAMAGE), 0, 	"After I counterattack, I gain +1 Spell Damage.");
	CardSetup("King Folstag",			0, "Frost Mage", 			3, 30, 2, 1, Keyword(BEACON) + Keyword(ARMORED), true);
	CardEvents("King Folstag", Keyword(ATTACK_STUN_TARGET), 0, 	"Attack: Stun my target.");
	CardSetup("Hero Boar",				0, "Polymorphed Mage", 		1, 30, 2, 1, Keyword(BEACON), true);
	CardEvents("Hero Boar", Keyword(ATTACK_YEET), 0,						"After I counterattack, return my target to your opponent's hand.");
	CardSetup("Setna",					0, "Archmage", 				2, 20, 2, 2, Keyword(BEACON), true);
	CardEvents("Setna", Keyword(ATTACK_ARCANE_MISSLE), 0, 	"Attack: Deal 1 Damage to a random enemy.");
	CardSetup("Circe",					0, "Archmage's Mom", 		2, 40, 2, 2, Keyword(BEACON) + Keyword(LIGHTNING), true);
	CardEvents("Circe", Keyword(ATTACK_ARCANE_MISSLE), 0, 	"Attack: Deal 1 Damage to a random enemy.");

	SpellSetup("Intimidating Presence", 1, SPELL_INTIMIDATE, 		"Stun an enemy adjacent to your Commander.", SPELL_TYPE_OFFENSIVE, 0, true);
	SpellSetup("Ground Stomp", 			2, SPELL_GROUND_STOMP, 		"Deal 1 Damage to units adjacent to your Commander.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Boots Treasure", 		2, SPELL_BOOTS_TREASURE, 	"Give your minions Pathfinder.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Weapons Treasure", 		4, SPELL_WEAPONS_TREASURE, 	"Give your minions +2 Attack.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Shields Treasure", 		6, SPELL_SHIELDS_TREASURE, 	"Give your minions +3 Health.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Pistol Shot", 			1, SPELL_PISTOL_SHOT, 		"Kill a minion. Put Reload on top of your deck.", SPELL_TYPE_OFFENSIVE, 0, true);
	SpellSetup("Reload", 				5, SPELL_RELOAD, 			"Draw a card.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Mirror Reflection",		3, SPELL_MIRROR_REFLECTION,	"Duplicate a minion on the symmetrical opposite tile.", SPELL_TYPE_DEFENSIVE, 0, true);
	SpellSetup("Blazeball", 			4, SPELL_PYROBALL, 			"Deal 6 Damage. Can only target Commanders if you have bonus Spell Damage.", SPELL_TYPE_OFFENSIVE, 0, true);
	SpellSetup("Frost Breath", 			3, SPELL_FROST_BREATH, 		"Stun all enemy minions. Deal 3 Damage to those already Stunned.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Poison Cloud", 			5, SPELL_POISON_CLOUD, 		"Give all enemy minions Decay. Deal 5 Damage to those that already have Decay.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Nature Has Had Enough", 10, SPELL_NATURE_ANGRY, 	"Heal allies and give enemies Decay.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Descend From Treetops",	10, SPELL_ELVEN_APOCALYPSE,	"Fill your hand with random elves. They are Fleeting and cost 0.", SPELL_TYPE_OTHER, 0, true);

	SpellSetup("Kraken Gives You A Hug",8, SPELL_KRAKEN_HUG,	"Opponent draws 8 cards for each unit they control.", SPELL_TYPE_OTHER, 0, true);
	//SpellSetup("High Pressure",			2, SPELL_WATER_PRESSURE,"Set a minion's Attack and Health to 1.", SPELL_TYPE_OFFENSIVE, 0, true);
	SpellSetup("Nickonhawk's Portal", 3, SPELL_NICKS_PORTAL, "Summon a random minion on a random tile.", SPELL_TYPE_OTHER, 0, true);	
	SpellSetup("Oxygen Tank",			5, SPELL_OXYGEN_TANK,	"Shuffle this in your deck.", SPELL_TYPE_OTHER, 0, true);
	
	CardSetup("Bondi",					1, "Mercenary",				5, 4, 2, 1, 0, true);
	CardEvents("Bondi", 0, 0,								"Play: Pay 2 Mana next turn.");
	CardSetup("Golem",					6, "Arcane Golem",			7, 9, 2, 1, 0, true);
	CardEvents("Golem", 0, 0, 								"Ignore odd damage.");
	CardSetup("Hero Chinese Immortal",	7, "Elven Champion",		5, 9, 2, 1, Keyword(GUARD) + Keyword(WARD), true);
	CardEvents("Hero Chinese Immortal", 0, 0, 				"I have +1 Range during opponent's turn.");
	CardSetup("Griffon",				4, "Soaring Griffy",		3, 6, 2, 1, Keyword(AIRDROP) + Keyword(CHARGE), true);
	CardSetup("Apep",					4, "Lurking Crocky",		4, 3, 2, 1, Keyword(AMBUSH) + Keyword(STEALTH), true);
	CardSetup("Bear",					6, "Hungry Bear",			7, 7, 2, 1, 0, true);
	CardEvents("Bear", Keyword(ATTACK_OVERKILL_HEALS), 0, 	"Whenever I kill an enemy I gain +2 Health.");
	CardSetup("Pirate Ship",			10, "Stuck Pirate Ship",			0, 40, 0, 0, 0, true);
	CardEvents("Pirate Ship", 0, 0, 						"Turn Start: Secretly choose an enemy tile, next turn deal 8 Damage there.");
	
	CardSetup("Audrey Water",			2, "Vora Sapling",			2, 5, 0, 1, Keyword(AIRDROP) + Keyword(DEADLY), true);
	CardSetup("Monument",				2, "Floating Housekeeper",	0, 5, 5, 0, 0, true);
	CardEvents("Monument", 0, 0, 		"Turn Start: Deal 1 Damage to damaged minions.");
	CardSetup("Monument 2",				4, "Floating Butler",		0, 10, 5, 0, 0, true);
	CardEvents("Monument 2", 0, 0, 		"Turn Start: Restore 5 health to my Commander.");
	CardSetup("Monument 3",				6, "Floating Steward",		0, 15, 5, 0, 0, true);
	CardEvents("Monument 3", 0, 0, 		"Turn Start: Opponent discards a random card.");
	CardSetup("Monument 4",				8, "Floating Twins",		0, 20, 5, 0, 0, true);
	CardEvents("Monument 4", 0, 0, 		"Turn Start: Summon a random Arcane minion and play a random Arcane spell.");
	CardSetup("Monument 5",				10, "Floating Majordomo",	0, 25, 5, 0, 0, true);
	CardEvents("Monument 5", 0, 0, 		"I have the effects of Floating Housekeeper, Butler, Steward and Twins.");

	SpellSetup("Chaos",					4, SPELL_TAVERN_BRAWL,		"Every unit attacks another one at random, regardless of distance.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Dominance",				3, SPELL_DOMINANCE,			"Your Commander gains +1 attack and then attacks an enemy.", SPELL_TYPE_OTHER, 0, true);
	SpellSetup("Infestation",			2, SPELL_SPIDER_LAIR,		"Add 3 Festering Eggs to your hand. They cost 0 and have Airdrop.", SPELL_TYPE_OTHER, 0, true);

	CardSetup("Tartarian Gate",			4, "Mouth of Chaos",		0, 8, 0, 0, Keyword(BEACON), true); 
	CardEvents("Tartarian Gate", 0, 0,	"At the start of your turn, draw a card and set its cost to 0.");

	CardSetup("Invisible Target",		0, "Destination",			0, 999, 0, 0, Keyword(WARD) + Keyword(REGENERATE) + Keyword(STEALTH), true);
	CardSetup("Cinematic Block",		0, "Indestructable",		0, 999, 0, 0, Keyword(WARD) + Keyword(REGENERATE) + Keyword(STEALTH), true);

	CardSetup("Theris",					2, "Infernal Jester",		3, 2, 2, 1, 0, true); 
	CardEvents("Theris", 0, Keyword(DEATH_REDUCE_COST), "Play: Draw a card. Death: Reduce the cost of cards in your hand by 1.");

	CardSetup("Bireme",					4, "Cloud Sail",			2, 6, 2, 2, Keyword(BEACON) + Keyword(ETHEREAL), true);
	CardEvents("Bireme", 0, 0, "Turn Start: Gain 1 mana.");

	CardSetup("Javelin Cavalry",		3, "Profit Hunter",			3, 2, 3, 2, Keyword(CHARGE), true);
	CardEvents("Javelin Cavalry", Keyword(ATTACK_SING), 0, "Attack: Give your Commander another action if he has already acted.");

	CardSetup("Chieroballista",			4, "Gatling Gun",			3, 4, 2, 2, Keyword(FURIOUS), true);
	CardSetup("Crossbowman",			2, "Security Sniper",		1, 3, 2, 3, Keyword(AIRDROP) + Keyword(LIGHTNING), true);

	CardSetup("Female",					2, "Princess Arsch",		1, 2, 2, 1, Keyword(WARD), true);
	CardEvents("Female", 0, Keyword(DEATH_DAMAGE_ENEMY), "Play: Give your Commander +2 health. Death: Deal 2 damage to the enemy Commander.");

	CardSetup("Eitri",					3, "Mad Scientist",			2, 1, 2, 1, Keyword(BEACON), true);
	CardEvents("Eitri", 0, 0, "Turn Start: Fill your hand with Scrap Metal.");

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
	CardSetup("Hero Greek Jason",		0, "phdorogers4", 		2, 20, 2, 1, Keyword(BEACON), true);
	CardSetup("Lancer Hero",			0, "Venlesh", 			2, 20, 3, 1, Keyword(BEACON) + Keyword(ETHEREAL), true);
	
	// 0 - 4
	CardSetup("Swordsman", 				1, "New Recruit", 		1, 3, 2, 1, Keyword(ETHEREAL));
	CardSetup("Khopesh", 				2, "Thief", 			1, 2, 2, 1); // Attack: Draw 1 card.
	CardSetup("Skraeling", 				3, "Bear Hunter", 		3, 1, 2, 1); // Play: Summon a 1|1 Loyal Wolf with Guard.
	CardSetup("Toxotes", 				2, "Sharpshooter",	 	2, 2, 2, 2);
	SpellSetup("Guardian of the Woods",	2, SPELL_GUARDIAN_OF_SEA,	"Grant your Commander Armored and Guard until the start of your next turn.", SPELL_TYPE_OTHER);
	// 5 - 9
	CardSetup("Peltast", 				3, "Forest Ranger", 	2, 1, 2, 2, Keyword(ETHEREAL)); // Play: Deal 1 damage.
	CardSetup("Mountain Giant",	 		5, "Big Friendly Giant",6, 7, 1, 1);
	CardSetup("Physician",				3, "Bard", 				0, 3, 2, 1, Keyword(HEALER));
	CardSetup("Hero Greek Ajax", 		4, "Party Leader", 		3, 3, 2, 1); // Play: Summon a random 1-cost minion from your deck.
	CardSetup("Raiding Cavalry",		3, "Reckless Rider", 	3, 2, 3, 1, Keyword(AMBUSH));
	// 10 - 14 (LEGENDARY at 14)
	CardSetup("Trident Soldier",		4, "Shieldbearer", 		2, 6, 1, 1, Keyword(GUARD));
	CardSetup("Jarl", 					4, "Wanderer", 			1, 3, 3, 1, Keyword(DEADLY) + Keyword(ARMORED));
	CardSetup("Huskarl",			 	5, "Seasoned Veteran", 	2, 3, 2, 1); // Play: Grant adjacent allied minions +1|+1
	CardSetup("Hero Greek Theseus", 	4, "Elven Moonblade", 	4, 6, 2, 1); // Minions I kill don't trigger their Death effect.
	CardSetup("Hero Greek Hippolyta", 	7, "Queen of Elves",	3, 5, 2, 2, Keyword(FURIOUS) + Keyword(CHARGE));
	// 15 - 19
	CardSetup("Wolf",					1, "Loyal Wolf",		1, 1, 2, 1, Keyword(GUARD));
	CardSetup("Avenger", 				6, "Doubleblade", 		5, 5, 2, 1, Keyword(AIRDROP));
	SpellSetup("Windsong", 				2, SPELL_SING, 			"Select an ally that has already acted. Grant it another action.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Villager Atlantean",		2, "Traveling Chef",	1, 2, 2, 1); // Play: Grant an allied minion +1|+1
	SpellSetup("Backstab", 				1, SPELL_BACKSTAB, 		"Deal 2 damage to an enemy next to another enemy.", SPELL_TYPE_OFFENSIVE);
	// 20 - 24
	SpellSetup("Duel", 					2, SPELL_DUEL, 			"An allied minion and an enemy minion attack each other, regardless of distance.", SPELL_TYPE_OTHER);
	SpellSetup("Party Up!", 			3, SPELL_PARTY_UP, 		"Draw 3 cards that cost 1 Mana.", SPELL_TYPE_OTHER);
	SpellSetup("Cheers", 				1, SPELL_TEAMWORK, 		"Give an allied minion +1 attack and activate its Play effect.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Defender's Glory", 		3, SPELL_DEFENDER, 		"Grant an allied minion +2 health and Guard.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Song of Victory", 		3, SPELL_VICTORY, 		"Grant all allied minions +1 attack and Ambush this turn.", SPELL_TYPE_OTHER);
	// 25 - 29 (LEGENDARY at 29)
	SpellSetup("Whirlwind", 			6, SPELL_WHIRLWIND, 	"A minion attacks all adjacent enemies.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Ornlu",					4, "Pack Hunter",		4, 3, 3, 1, Keyword(ETHEREAL)); // Attack: Create a Pack Hunter.
	CardSetup("Hetairoi",				3, "Elven Guide",		2, 3, 3, 1); // Play: Create an Explorer's Map.
	SpellSetup("First-Aid", 			1, SPELL_FIRST_AID, 	"Teleport an allied minion next to your Commander and restore 2 health to it.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Nemean Lion",			8, "Guild Master",		6, 6, 2, 1); // Play: Stun all enemy minions that cost {Manaflow} or less.
	/*
	ARCANE
	*/
	// Created cards
	CardSetup("Oracle Hero",			0, "Nanodude", 			1, 20, 2, 2, Keyword(BEACON), true);
	CardSetup("Minotaur",				0, "nottud", 			2, 20, 2, 1, Keyword(BEACON), true);
	CardSetup("Fire Giant",				5, "Blaze Elemental",	4, 6, 2, 2, Keyword(FURIOUS), true);
	CardSetup("Frost Giant",			5, "Frost Elemental",	3, 6, 2, 1, 0, true); // stuns its targets.
	CardSetup("Phoenix Egg",			5, "Reviving Egg",		0, 3, 0, 0, 0, true); // At the start of your turn, destroy me and summon a Fading Lightwing on my tile.
	
	// 30-34
	CardSetup("Slinger", 				2, "Apprentice", 		1, 1, 2, 2);
	CardSetup("Maceman", 				2, "School Guard",		2, 3, 2, 1, Keyword(GUARD));
	SpellSetup("Arcane Explosion",		3, SPELL_EXPLOSION,		"Deal 1 damage to enemies within 1 space of the target location.", SPELL_TYPE_OFFENSIVE);
	CardSetup("Javelin Cavalry Hero",	3, "Magic Messenger",	1, 1, 3, 2, Keyword(BEACON) + Keyword(WARD));
	SpellSetup("Doubleblast",			4, SPELL_DOUBLEBLAST,	"Deal 1 damage to two enemies. Draw a card.", SPELL_TYPE_OFFENSIVE);
	// 35-39
	SpellSetup("Spark", 				1, SPELL_SPARK, 		"Deal 1 damage.",SPELL_TYPE_OFFENSIVE);
	SpellSetup("Class Time",			3, SPELL_CLASS_TIME,	"Draw a spell and a minion.", SPELL_TYPE_OTHER);
	SpellSetup("Spellsnipe",			3, SPELL_SNIPE,			"An ally attacks an enemy within range. Add their range to the damage dealt.", SPELL_TYPE_OTHER);
	CardSetup("Oracle Scout",			3, "Tower Researcher",	0, 2, 1, 0); // Your spells deal +1 damage.
	CardSetup("Priest",					4, "Magic Teacher",		1, 3, 2, 2, Keyword(HEALER)); // Your spells cost 1 less.
	// 40-44 (LEGENDARY at 44)
	CardSetup("Swordsman Hero",			3, "Spellsword",		1, 3, 2, 1); // After you cast a spell, grant me +1 attack.
	SpellSetup("Rune of Flame",			5, SPELL_RUNE_OF_FLAME,	"Deal 6 damage to your Commander to summon a 4|6 Blaze Elemental with Furious.", SPELL_TYPE_OTHER);
	SpellSetup("Rune of Ice",			5, SPELL_RUNE_OF_ICE,	"Stun your Commander to summon a 3|6 Frost Elemental that stuns its target.", SPELL_TYPE_OTHER);
	SpellSetup("Electrosurge",			6, SPELL_ELECTROSURGE,	"Deal 2 damage with Lightning.", SPELL_TYPE_OFFENSIVE, Keyword(LIGHTNING));
	CardSetup("Hero Greek Bellerophon",	10, "Royal Executioner",6, 4, 3, 1, Keyword(AIRDROP) + Keyword(AMBUSH) + Keyword(WARD));
	// 45-49
	SpellSetup("Fire and Ice",			15, SPELL_FIRE_AND_ICE,	"Summon a Blaze Elemental and a Frost Elemental.", SPELL_TYPE_OTHER, Keyword(OVERFLOW));
	CardSetup("Phoenix From Egg",		5, "Fading Lightwing",	4, 3, 2, 1, Keyword(FLYING) + Keyword(DECAY));
	CardSetup("Prisoner",				2, "Magic Test Subject",2, 2, 2, 1); // Death: Create a random Arcane spell.
	CardSetup("Chimera",				7, "Escaped Amalgam",	3, 7, 2, 1, Keyword(WARD)); // Attack: Create a random Arcane spell.
	CardSetup("Petsuchos", 				6, "Bejeweled Sunlisk",	0, 4, 1, 3); // I have 3 range. Each time you cast a spell, grant me +2 attack.
	// 50-54
	SpellSetup("Book of Reflections",	5, SPELL_COPY_HOMEWORK, "Create three random cards from your opponent's classes.", SPELL_TYPE_OTHER);
	SpellSetup("Meteor",				4, SPELL_METEOR, 		"Mark a tile. At the start of your next turn, deal 6 damage to it and 2 to adjacent tiles.", SPELL_TYPE_OFFENSIVE);
	CardSetup("Trident Soldier Hero",	5, "Throne Shield",		2, 7, 1, 1); // Your Commander has Guard. When they take damage, I take it instead.
	CardSetup("Valkyrie",				3, "Battle Maiden",		3, 3, 3, 1); // Play: Restore 3 health to an ally.
	CardSetup("Centaur",				3, "Book Courier",		2, 3, 3, 2); // Play: Draw a card. Death: Your opponent draws a card.
	// 55-59 (LEGENDARY at 59)
	SpellSetup("Final Exam",			2, SPELL_FINAL_EXAM,	"Both players draw two cards.", SPELL_TYPE_OTHER);
	CardSetup("Sphinx",					6, "Professor of Shapeshifting",		3, 3, 2, 1); // Play: Transform a minion into a copy of another one.
	SpellSetup("Apocalypse",			10, SPELL_APOCALYPSE,	"Fill your hand with Meteors. They are Fleeting and cost 0.", SPELL_TYPE_OTHER);
	SpellSetup("Mirror Image",			2, SPELL_MIRROR_IMAGE,	"Add a copy of a minion to your hand and deck. If your Commander is nottud, add another copy to your deck.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Hero Greek Chiron",		6, "The Librarian",		3, 6, 3, 2); // At the start of your turn, both players draw a card.

	/*
	NAGA
	*/
	// Created cards
	CardSetup("Royal Guard Hero",		0, "Out Reach", 		2, 20, 2, 1, Keyword(BEACON), true); // Your Mana spent on spells will still count as Manaflow next turn.
	CardSetup("Archer Atlantean Hero",	0, "scragins", 			1, 20, 2, 3, Keyword(BEACON), true);
	CardSetup("Servant",				6, "Tide Elemental",	2, 6, 2, 1, Keyword(ETHEREAL), true); // Attack: Push my target away from me.

	// 60-64
	CardSetup("Hypaspist",				1, "Undercity Soldier",		1, 2, 2, 1); // Play: Grant your Commander +1 attack this turn.
	CardSetup("Myrmidon",				2, "Undercity Elite",		3, 1, 2, 1); // Play: I gain {Manaflow} health this turn.
	SpellSetup("Sea's Embrace",			1, SPELL_SEA_EMBRACE,		"Restore 3 health to an allied minion and your Commander.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Hippocampus",			3, "Fish Bait",				0, 2, 2, 0, Keyword(BEACON)); // Play: Draw your most expensive minion.
	CardSetup("Wadjet",					3, "Venom Pet",				1, 1, 1, 2, Keyword(DEADLY));
	// 65-69
	CardSetup("Medusa",					4, "Naga Archer",			2, 3, 2, 2); // Play: Stun an enemy minion.
	CardSetup("Cyclops",				5, "Undercity Protector",	3, 5, 1, 1, Keyword(GUARD) + Keyword(OVERFLOW));
	CardSetup("Lampades",				6, "Naga Sea Witch",		2, 2, 2, 2); // Play: Convert an enemy that costs {Manaflow} or less.
	CardSetup("Behemoth",				5, "Mana Muncher",			1, 1, 1, 1); // Play: I gain {Manaflow} attack and health.
	CardSetup("Nereid",					4, "Naga Sea Hunter",		4, 1, 2, 1, Keyword(CHARGE) + Keyword(AMBUSH));
	// 70-74 (LEGENDARY at 74)
	SpellSetup("Rune of Water",			5, SPELL_RUNE_OF_WATER,		"Restore 6 health to the enemy Commander to summon a 2|6 Tide Elemental that pushes its targets.", SPELL_TYPE_OTHER);
	CardSetup("Hydra",					6, "Depth Strider",			4, 6, 1, 1, Keyword(REGENERATE) + Keyword(OVERFLOW));
	SpellSetup("Water Cannon",			5, SPELL_WATER_CANNON,		"Push an enemy in any direction.", SPELL_TYPE_OFFENSIVE);
	CardSetup("Sea Turtle",				6, "Ancient Watcher",		4, 5, 1, 1, Keyword(GUARD) + Keyword(ARMORED));
	CardSetup("Heka Gigantes",			10, "King of the Depths",	6, 7, 2, 1, Keyword(BEACON)); // All your minions have Overflow.
	// 75-79
	CardSetup("Hippikon",				4, "Undercity Captain",		2, 3, 3, 1); // Play: Give your Commander another action if they have already acted.
	CardSetup("Kraken",					5, "Kraken",				1, 5, 2, 1, Keyword(REGENERATE)); // Attack: Return my target to its owner's hand.
	CardSetup("Jormund Elver",			2, "Mana Spitter",			1, 3, 2, 2); // Attack: Gain 1 {Manaflow} this turn.
	SpellSetup("Tidal Wave",			4, SPELL_TIDAL_WAVE,		"Stun all minions that have {Manaflow} or less health.", SPELL_TYPE_OTHER);
	SpellSetup("Flush",					2, SPELL_FLUSH,				"Push all adjacent minions away from your Commander.", SPELL_TYPE_OTHER);
	// 80-84
	SpellSetup("Deep Dive",				2, SPELL_DEEP_DIVE,			"Draw {Manaflow / 2} cards.", SPELL_TYPE_OTHER);
	CardSetup("Archer Atlantean",		4, "Undercity Sniper",		1, 3, 2, 3); // Whenever your Commander attacks an enemy, I attack it too.
	SpellSetup("Teletide",				1, SPELL_TELETIDE,			"Teleport an allied minion to any available tile.", SPELL_TYPE_OTHER);
	CardSetup("Man O War",				6, "Lightning Jellyfish",	3, 4, 2, 2, Keyword(LIGHTNING));
	SpellSetup("Wrath of the Sea",		12, SPELL_WRATH_OF_SEA,		"Double your Commander's attack this turn.", SPELL_TYPE_OTHER, Keyword(OVERFLOW));
	// 85-89 (LEGENDARY at 89)
	CardSetup("Leviathan",				9, "Ship Eater",			8, 8, 2, 1, Keyword(GUARD));
	SpellSetup("Cleansing Waters",		1, SPELL_CLEANSING_WATERS,	"Choose a tile. Give it and adjacent tiles Ward.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Drown",					7, SPELL_DROWN,		 		"Shuffle a minion into your deck.", SPELL_TYPE_OFFENSIVE);
	CardSetup("Scylla",					7, "Hungry Serpent",		4, 8, 2, 1, Keyword(FURIOUS));
	CardSetup("Hero Greek Polyphemus",	6, "Undercity Champion",	4, 5, 1, 1); // Your Commander has Furious.
	/*
	CLOCKWORK
	*/
	// Created cards
	CardSetup("Arkantos God",			0, "Roxas", 				2, 1, 2, 1, Keyword(BEACON), true);
	CardSetup("Pharaoh of Osiris",		0, "Yeebaagooon", 			0, 20, 2, 2, Keyword(BEACON) + Keyword(LIGHTNING), true);
	SpellSetup("Scrap Metal",			0, SPELL_SCRAP_METAL,		"Gain 1 mana this turn.", SPELL_TYPE_OTHER, 0, true);
	CardSetup("Outpost",				0, "Lightning Rod",			0, 3, 0, 0, Keyword(CONDUCTOR) + Keyword(AIRDROP), true);
	CardSetup("Guild",					4, "Gear Factory",			0, 6, 0, 0, 0, true); // At the end of your turn, deal 2 damage to me and add a Gearwalker to your hand.
	CardSetup("Wall Connector",			0, "Iron Wall",				0, 3, 0, 0, Keyword(AIRDROP) + Keyword(FLEETING), true);

	// 90-94
	SpellSetup("Repair",		 		3, SPELL_SONG_OF_REST,		"Restore 6 health to your Commander. Draw a card.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Fortify",		 		3, SPELL_FORTIFY,			"Fill your hand with Iron Walls.", SPELL_TYPE_OTHER);
	CardSetup("Dwarf",					1, "Iron Scavenger",		1, 1, 2, 1); // Death: Add a Scrap Metal to your hand.
	CardSetup("Portable Ram",			2, "Circuit Squad",			1, 3, 2, 1, Keyword(ARMORED) + Keyword(CONDUCTOR)); 
	CardSetup("Petrobolos",				3, "Scrap Launcher",		1, 2, 1, 3); // Attack: Stun my target.
	// 95-99
	CardSetup("Maceman Hero",			3, "Shock Trooper",			2, 4, 2, 1, Keyword(LIGHTNING));
	CardSetup("Automaton SPC",			2, "Gearwalker",			2, 2, 2, 1, Keyword(MAGNETIC));
	CardSetup("Onager",					4, "Anything Launcher",		0, 3, 1, 3, Keyword(CHARGE)); // Attack: My adjacent allies attack with me.
	CardSetup("Throwing Axeman",		4, "Engineer",				2, 3, 2, 2, Keyword(BEACON)); // Your minions cost 1 less.
	CardSetup("Ballista",				4, "Mechanized Bow",		3, 1, 1, 3, Keyword(MAGNETIC));
	// 100-104 (LEGENDARY at 104)
	CardSetup("Helepolis",				5, "Troop Transport",		2, 5, 1, 1); // Death: Summon a random minion from your deck on my tile.
	CardSetup("Colossus",				8, "Steam Giant",			6, 8, 1, 1, Keyword(MAGNETIC) + Keyword(GUARD));
	CardSetup("Battle Boar",			5, "Bulldozer",				4, 4, 2, 1, Keyword(MAGNETIC) + Keyword(CHARGE));
	CardSetup("Ape of Set",				2, "Robot Monkey",			1, 1, 2, 1, Keyword(MAGNETIC)); // Death: I attack all adjacent units.
	CardSetup("Tower Mirror",			10, "Thunder Cannon",		8, 8, 0, 3, Keyword(LIGHTNING));
	// 105-109
	SpellSetup("Electric Grid",			2, SPELL_ELECTRIC_GRID,		"Add two Lightning Rods to your hand.", SPELL_TYPE_OTHER);
	SpellSetup("Zap Gun",				3, SPELL_ZAP_GUN,			"Give an allied minion Lightning.", SPELL_TYPE_DEFENSIVE);
	CardSetup("Fire Siphon",			3, "Directional Cannon",	2, 5, 0, 0); // Play: Choose a direction. Turn Start: I fire a laser and attack everything in a line.
	SpellSetup("Compress",				3, SPELL_COMPRESS,			"Combine a minion with all of its adjacent allied minions, adding up attack, health, and keywords.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Upgrade",				4, SPELL_UPGRADE,			"Give an allied minion +2|+2 and Magnetic.", SPELL_TYPE_DEFENSIVE);
	// 110-114
	SpellSetup("Profiteering",			2, SPELL_PROFITEERING,		"Give a minion 'Attack: Draw a card.' This effect does not stack", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Warning Shot",			2, SPELL_WARNING_SHOT,		"Deal 1 damage. Draw a card.", SPELL_TYPE_OFFENSIVE);
	SpellSetup("Portable Spell Shield",	2, SPELL_PORTABLE_SPELL_SHIELD,			"Give an allied minion Armored and Ward.", SPELL_TYPE_OTHER);
	SpellSetup("Rewind",				4, SPELL_REWIND,			"Return an enemy minion to your opponent's hand.", SPELL_TYPE_OTHER);
	SpellSetup("Time Pocket",			6, SPELL_TIME_POCKET,		"Stun all units within 1 space of the target tile.", SPELL_TYPE_OFFENSIVE);
	// 115-119 (LEGENDARY at 119)
	SpellSetup("TEH BANHAMMER",			7, SPELL_BANHAMMER,			"Destroy an enemy minion. If your Commander is Yeebaagooon, also destroy all enemy copies of it.", SPELL_TYPE_OTHER);
	SpellSetup("Assembly Line",			3, SPELL_ASSEMBLY_LINE,		"Shuffle a copy of your hand into your deck. Draw a card.", SPELL_TYPE_OTHER);
	SpellSetup("Gear Factory",			4, SPELL_GEAR_FACTORY,		"Summon a Gear Factory at the target location. It creates a Gearwalker each turn.", SPELL_TYPE_OTHER);
	SpellSetup("Borrowed Time",			20, SPELL_BORROWED_TIME,	"Gain an extra turn.", SPELL_TYPE_OTHER, Keyword(OVERFLOW));
	SpellSetup("The Power Suit",		5, SPELL_POWER_SUIT,		"Give your Commander Magnetic.", SPELL_TYPE_OTHER);

	/*
	OTHERWORLD
	*/
	// Created cards
	CardSetup("Hoplite",				0, "Zenophobia", 		2, 20, 2, 1, Keyword(BEACON), true);
	CardSetup("Hero Greek Perseus",		0, "Anraheir", 			2, 20, 2, 1, Keyword(BEACON), true);
	CardSetup("Minion",					0, "Zombie",			1, 1, 1, 1, Keyword(CHARGE), true);
	CardSetup("Shade of Hades",			4, "Shadow Elemental",	4, 3, 2, 1, Keyword(AMBUSH), true);
	CardSetup("Scarab",					5, "Man-Eating Beetle",	5, 5, 1, 1, Keyword(ETHEREAL), true);
	CardSetup("Walking Woods Marsh",	3, "Zombie Tree",		2, 4, 2, 1, 0, true);
	
	// 120-124
	CardSetup("Spearman",				1, "Cultist",				1, 1, 2, 1); // Death: Summon a Zombie on my tile.
	CardSetup("Shade",					2, "Vengeful Spirit",		1, 2, 2, 1, Keyword(GUARD) + Keyword(DEADLY));
	CardSetup("Axeman",					2, "Executioner",			3, 1, 2, 1); // Play and Death: Give your Commander +1 attack this turn.
	SpellSetup("Soul Siphon",			2, SPELL_SOUL_SIPHON,		"Kill an allied minion to draw 2 cards.", SPELL_TYPE_OTHER);
	CardSetup("Satyr",					3, "Bone Collector",		1, 4, 2, 2); // Attack: Create a Zombie.
	// 125-129
	CardSetup("Prodromos",				3, "Pillager",				3, 1, 3, 1); // Death: Draw a card.
	CardSetup("Tartarian Gate spawn",	3, "Demon",					2, 2, 2, 1, Keyword(CHARGE)); // Play: Kill an allied minion and grant me its attack and health.
	CardSetup("Mummy",					5, "Rot Lord",				3, 5, 2, 2); // Whenever I kill an enemy, summon a Zombie on their tile.
	CardSetup("Royal Guard",			4, "Frenzied Worshipper",	2, 2, 2, 1); // Death: Summon a Shadow Elemental on my tile.
	CardSetup("Einheriar",				4, "Dark Reaper",			2, 3, 1, 1); // Each time an ally dies, I gain +1 attack and health.
	// 130-134 (LEGENDARY at 134)
	CardSetup("Dryad",					3, "Plaguewalker",			2, 5, 2, 1); // Death: Give Decay to all adjacent minions.
	CardSetup("Theocrat",				3, "Mad Acolyte",			1, 4, 2, 2, Keyword(DECAY)); // At the start of your turn, draw a card and give it Fleeting.
	CardSetup("Argus",					5, "Mindflayer",			3, 4, 1, 1); // At the end of your turn, deal 1 damage to all units with Decay.
	CardSetup("Pharaoh",				5, "Dark Summoner",			2, 3, 2, 2, Keyword(AIRDROP) + Keyword(BEACON) + Keyword(HEALER));
	CardSetup("Guardian",				4, "The Darkness",			7, 7, 2, 1); // Play: Your opponent draws 2 cards. Death: Shuffle a copy of me into your deeck.
	// 135-139
	CardSetup("Spider Egg",				3, "Festering Egg",			0, 3, 0, 0, Keyword(DECAY)); // Death: Summon a 5|5 Man-Eating Beetle with Pathfinder.
	SpellSetup("World Splitter",		6, SPELL_WORLD_SPLITTER,	"A minion attacks everything in a line. If your Commander is Zenophobia, this can be cast on him.", SPELL_TYPE_OFFENSIVE);
	CardSetup("Anubite",				1, "Demonling",				3, 2, 2, 1, Keyword(CHARGE));
	SpellSetup("Blood Price",			1, SPELL_BLOOD_PRICE,		"Deal 2 damage to an allied minion and an enemy.", SPELL_TYPE_OTHER);
	SpellSetup("Death Approaches",		4, SPELL_DEATH_APPROACHES,	"Summon a 4|3 Shadow Elemental with Ambush on a tile next to the enemy Commander.", SPELL_TYPE_OTHER);
	// 140-144
	SpellSetup("Doom",					3, SPELL_DOOM,				"Deal 2 damage to a unit. If it has Decay, add a Doom to your hand.", SPELL_TYPE_OFFENSIVE);
	SpellSetup("Shadowstep",			1, SPELL_SHADOWSTEP,		"Your Commander swaps spaces with an allied minion.", SPELL_TYPE_OTHER);
	SpellSetup("Final Frenzy",			3, SPELL_FINAL_FRENZY,		"Give a minion Deadly and Decay.", SPELL_TYPE_DEFENSIVE);
	SpellSetup("Corpse Party",			3, SPELL_CORPSE_PARTY,		"Summon three Zombies.", SPELL_TYPE_OTHER);
	SpellSetup("Undeath",				4, SPELL_UNDEATH,			"Give all allied minions, 'Death: Summon a Zombie on my tile.'", SPELL_TYPE_OTHER);
	// 145-149 (LEGENDARY at 149)
	CardSetup("Bogsveigir",				2, "Death Messenger",		1, 2, 2, 2); // Attack: If my target is a minion, give it Decay.
	SpellSetup("Rune of Darkness",		5, SPELL_RUNE_OF_DARKNESS,	"Kill an allied minion to summon two 4|3 Shadow Elementals with Ambush.", SPELL_TYPE_OTHER);
	SpellSetup("Zeno's Paradox",		3, SPELL_ZENOS_PARADOX,		"An allied minion and an enemy minion swap spaces.", SPELL_TYPE_OTHER);
	CardSetup("Manticore",				4, "Face Stealer",			1, 4, 2, 2, Keyword(FURIOUS)); // Attack: If my target is a minion, give it Decay.
	CardSetup("Hero Greek Achilles",	8, "Nightrider",			5, 5, 3, 1); // Play: Stun the enemy Commander and give them Decay.
	/*
	SPACE
	*/
	// Created cards
	//CardSetup("Hero Greek Odysseus",	0, "Nickonhawk, Battle-Mode",	2, 20, 2, 2, Keyword(BEACON), true);
	//CardSetup("Caravan Atlantean",		0, "Nickonhawk, God-Mode", 		0, 20, 3, 0, Keyword(BEACON), true);
	
	//SpellSetup("Nickonhawk's Portal", 3, SPELL_NICKS_PORTAL, "Summon a random minion on a random tile.", SPELL_TYPE_OTHER, 0, true);	
	/*
	trStringQuestVarSet("spell_"+SPELL_NICKS_PORTAL+"_name", "Nickonhawk's Portal");
	trQuestVarSet("spell_"+SPELL_NICKS_PORTAL+"_cost", 3);
	trStringQuestVarSet("spell_"+SPELL_NICKS_PORTAL+"_description", "Summon a random minion on a random tile.");
	trQuestVarSet("spell_"+SPELL_NICKS_PORTAL+"_type", SPELL_TYPE_OTHER);
	trQuestVarSet("spell_"+SPELL_NICKS_PORTAL+"_animation", GetSpellAnimation((1*trQuestVarGet("cardIndex"))/30, SPELL_TYPE_OTHER));
	trQuestVarSet("spellToCard"+SPELL_NICKS_PORTAL, trQuestVarGet("cardIndex"));
	*/
	/* 150-154
	// 155-159
	// 160-164 (LEGENDARY at 164)
	// 165-169
	// 170-174
	// 175-179 (LEGENDARY at 179) */
	/*
	Unit OnPlay, OnAttack, OnDeath, and description
		Proto | OnAttack | OnDeath | Description
	*/
	CardEvents("Hero Greek Jason", Keyword(ATTACK_GET_WINDSONG), 0, 	"Attack: Create a Fleeting Windsong.");
	
	CardEvents("Khopesh", Keyword(ATTACK_DRAW_CARD), 0, 				"Attack: Draw a card.");
	CardEvents("Skraeling", 0, 0, 										"Play: Summon a 1|1 Loyal Wolf with Guard.");
	CardEvents("Avenger", 0, 0, 										"Play: Deal 1 damage to all adjacent enemies.");
	CardEvents("Villager Atlantean", 0, 0, 								"Play: Grant an allied minion +1 attack and health.");
	CardEvents("Hero Greek Ajax", 0, 0, 								"Play: Summon a random 1-cost minion from your deck.");
	CardEvents("Hero Greek Theseus", Keyword(ATTACK_BLOCK_DEATH), 0,	"Minions I kill don't trigger their Death effect.");
	CardEvents("Physician", Keyword(ATTACK_SING), 0, 					"When I heal an ally that has acted, grant them another action.");
	CardEvents("Hetairoi", 0, 0, 										"Play: Give an allied minion +1 speed and Pathfinder.");
	CardEvents("Peltast", 0, 0, 										"Play: Deal 1 damage.");
	CardEvents("Huskarl", 0, 0, 										"Play: Grant adjacent allied minions +1 attack and health.");
	CardEvents("Nemean Lion", 0, 0, 									"Play: Stun all enemy minions that cost {Manaflow} or less.");
	CardEvents("Ornlu", Keyword(ATTACK_GET_FENRIS), 0,					"Attack: Create a Pack Hunter.");

	CardEvents("Oracle Hero", Keyword(ATTACK_DISCOUNT), 0, 				"Attack: Reduce the cost of spells in your hand by 1.");
	CardEvents("Minotaur", Keyword(ATTACK_YEET), 0,						"After I counterattack, return my target to your opponent's hand.");
	
	CardEvents("Swordsman Hero", 0, 0, 									"After you cast a spell, grant me +1 attack.");
	CardEvents("Slinger", 0, 0, 										"Play: Create a Spark.");
	CardEvents("Priest", 0, 0,							 				"Your spells cost 1 less.");
	CardEvents("Oracle Scout", 0, 0,						 			"Your spells deal +1 damage.");
	CardEvents("Frost Giant", Keyword(ATTACK_STUN_TARGET), 0, 			"Attack: Stun my target.");
	CardEvents("Phoenix Egg",0, 0, 										"At the start of your turn, destroy me to summon a Fading Lightwing");
	CardEvents("Phoenix From Egg", 0, Keyword(DEATH_EGG), 				"Death: Summon a Reviving Egg on my tile.");
	CardEvents("Prisoner", 0, Keyword(DEATH_GET_ARCANE),				"Death: Create a random Arcane spell.");
	CardEvents("Chimera", Keyword(ATTACK_GET_ARCANE), 0,				"Attack: Create a random Arcane spell.");
	CardEvents("Petsuchos", 0, 0,										"After you cast a spell, grant me +2 attack.");
	CardEvents("Trident Soldier Hero",0,0,								"Your Commander has Guard. When they take damage, I take it instead");
	CardEvents("Valkyrie", 0, 0,										"Play: Restore 3 health to an ally.");
	CardEvents("Centaur", 0, Keyword(DEATH_OPPONENT_DRAW_CARD),			"Play: Draw a card. Death: Your opponent draws a card.");
	CardEvents("Hero Greek Chiron", 0, 0,								"At the start of your turn, both players draw a card.");
	CardEvents("Sphinx", 0, 0,											"Play: Transform a minion into a copy of another one.");
	
	CardEvents("Royal Guard Hero", 0, 0, 								"Your Mana spent on spells will still count as Manaflow next turn.");
	// CardEvents("Archer Atlantean Hero", 0, 0, 							"I have 3 range.");
	
	CardEvents("Hypaspist", 0, 0,										"Play: Grant your Commander +1 attack this turn.");
	CardEvents("Myrmidon", 0, 0,										"Play: I gain {Manaflow} health.");
	CardEvents("Archer Atlantean", 0, 0,								"Whenever your Commander attacks an enemy, I attack it too.");
	CardEvents("Hippocampus", 0, 0,										"Play: Draw the most expensive minion from your deck.");
	CardEvents("Medusa", 0, 0,											"Play: Stun an enemy minion.");
	CardEvents("Lampades", 0, 0,										"Play: Convert an enemy minion that costs {Manaflow} or less.");
	CardEvents("Behemoth", 0, 0,										"Play: I gain {Manaflow} attack and health.");
	CardEvents("Servant", Keyword(ATTACK_PUSH), 0,						"Attack: Push my target away from me.");
	CardEvents("Heka Gigantes", 0, 0,									"All your minions have Overflow.");
	CardEvents("Hippikon", 0, 0,										"Play: Give your Commander another action if they have already acted.");
	CardEvents("Kraken", Keyword(ATTACK_RETURN), 0,						"Attack: Return my target to its owner's hand.");
	CardEvents("Jormund Elver", Keyword(ATTACK_GET_MANAFLOW), 0,		"Attack: Gain 1 Manaflow this turn.");
	CardEvents("Hero Greek Polyphemus", 0, 0, 							"Your Commander has Furious.");
	
	CardEvents("Pharaoh of Osiris", 0, 0, 								"After you cast a spell, grant me +1 Attack until the end of the turn.");
	CardEvents("Arkantos God", 0, 0,									"I have +1 health for each card in your deck.");

	CardEvents("Dwarf", 0, Keyword(DEATH_GET_SCRAP),					"Death: Add a Scrap Metal to your hand.");
	CardEvents("Petrobolos", Keyword(ATTACK_STUN_TARGET), 0, 			"Attack: Stun my target.");
	CardEvents("Throwing Axeman", 0, 0,									"Your minions cost 1 less.");
	CardEvents("Helepolis", 0, Keyword(DEATH_SUMMON_RANDOM),			"Death: Summon a random minion from your deck on my tile.");
	CardEvents("Ape of Set", 0, Keyword(DEATH_BOOM_SMALL),				"Death: I attack all adjacent units.");
	CardEvents("Guild", 0, 0,											"At the end of your turn, deal 2 damage to me and add a Gearwalker to your hand.");
	CardEvents("Fire Siphon", 0, 0,										"Play: Choose a direction. Turn Start: I fire a laser and attack everything in a line.");
	CardEvents("Tower Mirror", Keyword(ATTACK_ANIMATE_TOWER), 0,		"");
	CardEvents("Onager", Keyword(ATTACK_TEAMWORK), 0,					"Attack: My adjacent allies attack with me. This effect does not stack.");

	CardEvents("Hoplite", Keyword(ATTACK_GET_MINION), 0,				"I can attack allies. Whenever I kill a minion, add a copy of it to your hand.");
	CardEvents("Hero Greek Perseus", 0, 0, 								"Whenever an ally dies, gain 1 Mana this turn.");
	CardEvents("Spearman", 0, Keyword(DEATH_SUMMON_ZOMBIE),				"Death: Summon a Zombie on my tile.");
	CardEvents("Axeman", 0, Keyword(DEATH_GET_ATTACK),					"Play and Death: Give your Commander +1 attack this turn.");
	CardEvents("Anubite", 0, 0,											"Play: Deal 3 damage to your Commander.");
	CardEvents("Satyr", Keyword(ATTACK_GET_ZOMBIE), 0, 					"Attack: Create a Zombie.");
	CardEvents("Prodromos", 0, Keyword(DEATH_DRAW_CARD),				"Death: Draw a card.");
	CardEvents("Tartarian Gate spawn", 0, 0,							"Play: Kill an ally and grant me its attack and health.");
	CardEvents("Mummy", Keyword(ATTACK_SUMMON_ZOMBIE), 0, 				"Attack: If my target dies, summon a Zombie on their tile.");
	CardEvents("Royal Guard", 0, Keyword(DEATH_SUMMON_SHADOW),			"Death: Summon a 4|3 Shadow Elemental with Ambush on my tile.");
	CardEvents("Einheriar", 0, 0,	 									"Each time an ally dies, I gain +1 attack and health.");
	CardEvents("Dryad", 0, Keyword(DEATH_POISON_MIST),					"Death: Give Decay to all adjacent minions.");
	CardEvents("Theocrat", 0, 0,										"At the start of your turn, draw a card and give it Fleeting.");
	CardEvents("Argus", 0, 0,											"At the end of your turn, deal 1 damage to all units with Decay.");
	CardEvents("Guardian", 0, Keyword(DEATH_DARKNESS_RETURNS),			"Play: Your opponent draws 2 cards. Death: Shuffle a copy of me into your deck.");
	CardEvents("Hero Greek Achilles", 0, 0, 							"Play: Stun the enemy Commander and give them Decay.");
	CardEvents("Spider Egg", 0, Keyword(DEATH_SUMMON_BEETLE),			"Death: Summon a 5|5 Man-Eating Beetle with Pathfinder.");
	CardEvents("Bogsveigir", Keyword(ATTACK_POISON), 0,					"Attack: If my target is a minion, give it Decay.");
	CardEvents("Manticore", Keyword(ATTACK_POISON), 0,					"Attack: If my target is a minion, give it Decay.");
	CardEvents("Walking Woods Marsh", Keyword(ATTACK_SUMMON_TREE), 0,	"Attack: If my target dies, summon a Zombie Tree on their tile.");

	//CardEvents("Hero Greek Odysseus", 0, 0, 							"Loading ability...");
	//CardEvents("Caravan Atlantean", 0, 0, 								"Loading ability...");	
	
	xsDisableRule("initializeCards");
}