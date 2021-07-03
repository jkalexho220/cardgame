
// Gonna hardcode the name of the hand vector for now
void addCardToHand(int p = 0, int proto = 0) {
	trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("p"+p+"handx"),0,trQuestVarGet("p"+p+"handz"),0,true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true);
	trMutateSelected(proto);
	trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");

	yAddToDatabase("p"+p+"hand", "next");
	yAddUpdateString("p"+p+"hand", "name", trStringQuestVarGet("card_" + proto + "_Name"));
	yAddUpdateVar("p"+p+"hand", "cost", trQuestVarGet("card_" + proto + "_Cost"));
	yAddUpdateVar("p"+p+"hand", "attack", trQuestVarGet("card_" + proto + "_Attack"));
	yAddUpdateVar("p"+p+"hand", "health", trQuestVarGet("card_" + proto + "_Health"));
	yAddUpdateVar("p"+p+"hand", "speed", trQuestVarGet("card_" + proto + "_Speed"));
	yAddUpdateVar("p"+p+"hand", "range", trQuestVarGet("card_" + proto + "_Range"));
	yAddUpdateVar("p"+p+"hand", "keywords", trQuestVarGet("card_" + proto + "_Keywords"));
	yAddUpdateString("p"+p+"hand", "ability", trStringQuestVarGet("card_" + proto + "_Ability"));
}

