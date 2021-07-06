
void ThrowError(string message = "Zeno you made bug again!"){
	trShowWinLose(message, "xpack\xtaunts\en\999 theme.mp3");
}


/*
Spells
*/
const int SPELL_NONE = 0;
const int SPELL_COMMANDER = 1; // Since the "spell" variable is unused on normal minions, we use it here to mark a unit as the Commander

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
const int AMBUSH = 11;		// When initiating combat, unit attacks first.

const int NUM_KEYWORDS = 12;


string GetKeywordName(int bitPosition=0){
	switch(bitPosition){
		case CHARGE: return ("Charge");
		case GUARD: return ("Guard");
		case AIRDROP: return ("Airdrop");
		case FURIOUS: return ("Furious");
		case LIGHTNING: return ("Lightning");
		case REGENERATE: return ("Regenerate");
		case DEADLY: return ("Deadly");
		case ETHEREAL: return ("Ethereal");
		case ARMORED: return ("Armored");
		case WARD: return ("Ward");
		case BEACON: return ("Beacon");
		case AMBUSH: return ("Ambush");
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
	string dialog = "";
	string message = "";
	int keywords = yGetVarByIndex(db, "keywords", index);
	if(keywords>0){
		bool multiple = false;
		for(k=0;<NUM_KEYWORDS){
			if(GetBit(keywords, k)){
				if(multiple){
					dialog = dialog + ", ";
				}
				multiple = true;
				dialog = dialog + GetKeywordName(k);
			}
		}
	}
	message = yGetStringByIndex(db, "ability", index);

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

	trSoundPlayDialog("default", "1", -1, false, " : " + dialog, "");
	trSetCounterDisplay(message);
}


void CardSetup(string protoName="", int cost=1, string name="", int attack=1, int health=1, int speed=1, int range=0, int keywords=0, string ability=""){
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

		trStringQuestVarSet("card_" + proto + "_Ability",ability);
	}
}


void CardInstantiate(string protoName="", string vectorName=""){
	int proto = kbGetProtoUnitID(protoName);
	if(proto<0){
		ThrowError("That's not a unit. Method: CardInstantiate");
	}
	int index = trQuestVarGet("cardUnitsIndex");
	trQuestVarSet("cardUnits_" + index, trGetNextUnitScenarioNameNumber());
	trStringQuestVarSet("cardUnits_" + index + "_Name",trStringQuestVarGet("card_" + proto + "_Name"));
	trQuestVarSet("cardUnits_" + index + "_Cost",trQuestVarGet("card_" + proto + "_Cost"));
	trQuestVarSet("cardUnits_" + index + "_Attack",trQuestVarGet("card_" + proto + "_Attack"));
	trQuestVarSet("cardUnits_" + index + "_Health",trQuestVarGet("card_" + proto + "_Health"));
	trQuestVarSet("cardUnits_" + index + "_Speed",trQuestVarGet("card_" + proto + "_Speed"));
	trQuestVarSet("cardUnits_" + index + "_Range",trQuestVarGet("card_" + proto + "_Range"));
	trQuestVarSet("cardUnits_" + index + "_Keywords",trQuestVarGet("card_" + proto + "_Keywords"));
	trStringQuestVarSet("cardUnits_" + index + "_Ability",trStringQuestVarGet("card_" + proto + "_Ability"));
	trQuestVarSet("cardUnitsIndex", index + 1);
	
	DeploySober(protoName,vectorName);
	trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
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
	}

	//Pick a card. Any card.
	/*
	        Proto                  Cost    Name       Attack|Health|Speed|Range     Keywords|Ability
	*/
	CardSetup("Hero Greek Jason",		0, "phdorogres4", 		2, 20, 2, 1, Keyword(BEACON) + Keyword(ETHEREAL));
	CardSetup("Swordsman", 				1, "New Recruit", 		1, 3, 2, 1);
	CardSetup("Maceman", 				2, "School Guard",		2, 3, 2, 1, Keyword(GUARD));
	CardSetup("Skraeling", 				1, "Wolfpelt", 			1, 2, 2, 1, Keyword(CHARGE));
	CardSetup("Slinger", 				1, "Apprentice", 		1, 1, 2, 2);
	CardSetup("Toxotes", 				2, "Sharpshooter",	 	2, 2, 2, 2);
	CardSetup("Hero Greek Theseus", 	3, "Party Leader", 		4, 4, 2, 1);
	CardSetup("Raiding Cavalry",		3, "Reckless Rider", 	3, 1, 3, 1, Keyword(AMBUSH));
	CardSetup("Trident Soldier",		4, "Shieldbearer", 		2, 7, 1, 1, Keyword(GUARD));
	CardSetup("Jarl", 					4, "Wanderer", 			1, 3, 3, 1, Keyword(DEADLY));
	CardSetup("Behemoth", 				5, "Behemoth", 			2, 4, 1, 1, Keyword(ARMORED));
	CardSetup("Avenger", 				6, "Doubleblade", 		5, 5, 2, 1, Keyword(AIRDROP));
	CardSetup("Archer Atlantean Hero", 	7, "Ace", 				4, 2, 2, 2, Keyword(FURIOUS) + Keyword(AMBUSH) + Keyword(CHARGE));

	
	
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
