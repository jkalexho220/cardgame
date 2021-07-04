
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
const int CHARGE = 0;
const int GUARD = 1;
const int AIRDROP = 2;
const int FURIOUS = 3;
const int LIGHTNING = 4;
const int REGENERATE = 5;
const int DEADLY = 6;
const int ETHEREAL = 7;
const int ARMOR = 8;
const int WARD = 9;



string GetKeywordName(int bitPosition=0){
	switch(bitPosition){
		case CHARGE: return ("Charge"); 		// Has action when summoned.
		case GUARD: return ("Guard"); 		// If an adjacent ally is attacked, swap spaces with it before combat occurs.
		case AIRDROP: return ("Airdrop"); 	// Doesn’t have to be summoned next to commander.
		case FURIOUS: return ("Furious"); 	// Two attacks each turn.
		case LIGHTNING: return ("Lightning"); 	// Also attacks the enemies connected to the target.
		case REGENERATE: return ("Regenerate"); 	// Restores to full health at the start of your turn.
		case DEADLY: return ("Deadly"); 		// Destroy minions damaged by this.
		case ETHEREAL: return ("Ethereal"); 	// Can pass through units and impassable terrain.
		case ARMOR: return ("Armor"); 		// Takes half physical damage, rounded down.
		case WARD: return ("Ward"); 		// Takes half magical damage, rounded down.
	}
	ThrowError("Invalid keyword id. Method: GetKeywordName");
	return ("");
}

// Given a bitPosition, return 2^bitPosition
int KW(int bit = 0) {
	return(xsPow(2, bit));
}

/*
Example: HasKeyword(CHARGE, 123456) = false

Given a key and a keywords integer, returns true if the keywords integer has the keyword
*/
int HasKeyword(int key = 0, int keywords = 0) {
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
		for(k=0;<10){
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
	if(HasArmor(keywords)){
		gadgetUnreal("NormalArmorTextDisplay");			
	} else {
		gadgetUnreal("unitStatPanel-stat-normalArmor");
	}
	if(HasWard(keywords)){
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
		if(range==0){
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
		trModifyProtounit(protoName, p, 1, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 1, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 1, speed); // Speed
		trModifyProtounit(protoName, p, 11, 9999999999999999999.0);
		trModifyProtounit(protoName, p, 11, -9999999999999999999.0);
		trModifyProtounit(protoName, p, 11, range); // Range

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
	CardSetup("Militia", 				1, "Farmer", 			1, 3, 1, 0);
	CardSetup("Maceman", 				1, "Squire", 			1, 2, 1, 0, KW(GUARD));
	CardSetup("Skraeling", 				1, "Wolfpelt", 			1, 2, 1, 0, KW(CHARGE));
	CardSetup("Slinger", 				1, "Gypsy", 			1, 1, 1, 1);
	CardSetup("Toxotes", 				2, "Townguard Archer", 	2, 2, 1, 1);
	CardSetup("Spearman", 				2, "Roadside Bandit", 	3, 2, 1, 0);
	CardSetup("Anubite", 				2, "Dark Dog", 			2, 1, 2, 0, KW(CHARGE));
	CardSetup("Raiding Cavalry",		3, "Wild Horseman", 	2, 1, 3, 0);
	CardSetup("Wadjet", 				3, "Noble Cobra", 		2, 3, 1, 2, KW(REGENERATE));
	CardSetup("Ballista", 				4, "Giant Crossbow", 	3, 2, 1, 3);
	CardSetup("Trident Soldier",		4, "Throne Shield", 	2, 6, 1, 0, KW(GUARD));
	CardSetup("Avenger", 				5, "Avian Warrior", 	3, 5, 1, 0, KW(AIRDROP) + KW(FURIOUS));
	CardSetup("Battle Boar", 			5, "Golden Hog", 		4, 4, 2, 0, KW(CHARGE) + KW(GUARD));
	CardSetup("Hero Greek Odysseus",	9, "Nickonhawk", 		4, 7, 1, 2, KW(GUARD) + KW(ETEHREAL) + KW(REGENERATE), "Listening to anime music and eating trash.");
	CardSetup("Hoplite", 				9, "Zenophobia", 		7, 4, 1, 0, KW(CHARGE) + KW(ARMOR) + KW(DEADLY), "Currently hard at work on Star Fighter Ace 3.");
	CardSetup("Pharaoh of Osiris", 		9, "Yeebaagooon", 		9, 9, 9, 0, KW(AIRDROP) + KW(WARD) + KW(LIGHTNING), "Seraph addicted to dota and tea.");
	
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
