void OnPlay(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	int type = 0;
	bool done = true;
	trUnitSelectClear();
	trUnitSelect(""+unit);
	if (HasKeyword(WARD, 1*mGetVar(unit, "keywords"))) {
		spyEffect("UI Range Indicator Norse SFX");
	}
	if (HasKeyword(DECAY, 1*mGetVar(unit, "keywords"))) {
		spyEffect("Poison SFX");
	}
	if (HasKeyword(DEADLY, 1*mGetVar(unit, "keywords"))) {
		spyEffect("Chaos effect");
	}
	if (HasKeyword(STEALTH, 1*mGetVar(unit, "keywords"))) {
		trQuestVarSet("stealthSFX" + unit, spyEffect("Sky Passage"));
	}
	if(kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("p" + p + "commander"))) == kbGetProtoUnitID("Shaba Ka")){
		trQuestVarSetFromRand("temp", 1, 3, true);			
		if(trQuestVarGet("temp") == 1){
			generateCard(p, 0, SPELL_BOOTS_TREASURE);	
		} else if(trQuestVarGet("temp") == 2){
			generateCard(p, 0, SPELL_WEAPONS_TREASURE);	
		} else {
			generateCard(p, 0, SPELL_SHIELDS_TREASURE);	
		}
		if(trQuestVarGet("chats_Kemsyt_0") == 0){
			trQuestVarSet("chats_Kemsyt_0", 1);
			ChatLog(0, "<color={Playercolor("+p+")}>Mister Pirate</color>: I like treasure!");
			trSoundPlayFN("kemsytattack2.wav","1",-1,"","");
		}
	}
	switch(proto)
	{
		case kbGetProtoUnitID("Bear"):
		{
			trQuestVarSetFromRand("soundRandom", 1, 2, true);
			trSoundPlayFN("beargrunt" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			if(trQuestVarGet("chats_Bear_0") == 0){
				trQuestVarSet("chats_Bear_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: Growl!!!");
			}
		}
		case kbGetProtoUnitID("Bondi"):
		{
			trSoundPlayFN("militarycreate.wav","1",-1,"","");
			trQuestVarSet("p"+p+"manaTax", trQuestVarGet("p"+p+"manaTax") + 2);
		}
		case kbGetProtoUnitID("Pirate Ship"):
		{
			trSoundPlayFN("battlecry1.wav","1",-1,"","");
			trQuestVarSet("pirateShipTarget" + unit, -1);
		}
		case kbGetProtoUnitID("Hero Chinese Immortal"):
		{
			mSetVar(unit, "scale", 2);
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trSetSelectedScale(2, 2, 2);
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("archeryrange.wav","1",-1,"","");
			if(trQuestVarGet("chats_Immortal_0") == 0){
				trQuestVarSet("chats_Immortal_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: *intense staring*");
			}
		}
		case kbGetProtoUnitID("Audrey Water"):
		{
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("carnivoragrunt" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Griffon"):
		{
			trQuestVarSetFromRand("soundRandom", 1, 2, true);
			trSoundPlayFN("griffongrunt" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("wingflaplarge" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Apep"):
		{
			trQuestVarSetFromRand("soundRandom", 1, 2, true);
			trSoundPlayFN("crocodilegrunt" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Monument"):
		{
			if(trQuestVarGet("chats_Monument_0") == 0){
				trQuestVarSet("chats_Monument_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: Preparing to clean.");
			}
		}
		case kbGetProtoUnitID("Monument 2"):
		{
			if(trQuestVarGet("chats_Monument2_0") == 0){
				trQuestVarSet("chats_Monument2_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: Preparing to help with outfit.");
			}
		}
		case kbGetProtoUnitID("Monument 3"):
		{
			if(trQuestVarGet("chats_Monument3_0") == 0){
				trQuestVarSet("chats_Monument3_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: Preparing to assist guest with luggage.");
			}
		}
		case kbGetProtoUnitID("Monument 4"):
		{
			if(trQuestVarGet("chats_Monument4_0") == 0){
				trQuestVarSet("chats_Monument4_0", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: Preparing Arcane buffet.");
			}
		}
		case kbGetProtoUnitID("Monument 5"):
		{
			if(trQuestVarGet("chats_Monument5_0") == 0){
				trQuestVarSet("chats_Monument5_0", 1);
				trCameraShake(3.0, 0.3);
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: PREPARING EVERYTHING.");
			}
		}	
		case kbGetProtoUnitID("Slinger"):
		{
			generateCard(p, 0, SPELL_SPARK);
		}
		case kbGetProtoUnitID("Skraeling"):
		{
			trQuestVarSet("summonedUnit", unit);
			chooseSpell(SPELL_WOLF);
			done = false;
		}
		case kbGetProtoUnitID("Villager Atlantean"):
		{
			done = false;
			chooseSpell(SPELL_FOOD);
		}
		case kbGetProtoUnitID("Avenger"):
		{
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trMutateSelected(kbGetProtoUnitID("Avenger"));
			trUnitOverrideAnimation(39, 0, 0, 1, -1);
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit(1*trQuestVarGet("allUnits"), 1);
						deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("sphinxspecialattack.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hero Greek Hippolyta"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hetairoi"):
		{
			done = false;
			chooseSpell(SPELL_MAP);
		}
		case kbGetProtoUnitID("Peltast"):
		{
			done = false;
			chooseSpell(SPELL_PING);
		}
		case kbGetProtoUnitID("Huskarl"):
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (trQuestVarGet("allUnits") == unit) {
					continue;
				} else if ((mGetVarByQV("allUnits", "player") == p) && (mGetVarByQV("allUnits", "spell") == 0)) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						mSetVarByQV("allUnits", "health", 1 + mGetVarByQV("allUnits", "health"));
						trUnitSelectClear();
						trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
						spyEffect("Einheriar Boost SFX");
					}
				}
			}
			trSoundPlayFN("researchcomplete.wav","1",-1,"","");
			trSoundPlayFN("battlecry3.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Nemean Lion"):
		{
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trMutateSelected(kbGetProtoUnitID("Nemean Lion"));
			trUnitOverrideAnimation(39, 0, 0, 1, -1);
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if ((trQuestVarGet("p"+p+"manaflow") >= mGetVarByQV("allUnits", "cost")) &&
						(mGetVarByQV("allUnits", "spell") == 0)) {
						stunUnit(1*trQuestVarGet("allUnits"));
					}
				}
			}
		}
		case kbGetProtoUnitID("Valkyrie"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_VALKYRIE_HEAL);
		}
		case kbGetProtoUnitID("Centaur"):
		{
			trQuestVarSet("p"+p+"drawCards", 1 + trQuestVarGet("p"+p+"drawCards"));
		}
		case kbGetProtoUnitID("Sphinx"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_SHAPESHIFT);
		}
		case kbGetProtoUnitID("Hero Greek Chiron"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("sentinelbirth.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Heka Gigantes"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("ageadvance.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hero Greek Polyphemus"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("cinematics\15_in\gong.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hypaspist"):
		{
			trQuestVarSet("p"+p+"yeebBonus", 1 + trQuestVarGet("p"+p+"yeebBonus"));
			mSetVarByQV("p"+p+"commander", "attack", 1 + mGetVarByQV("p"+p+"commander", "attack"));
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case kbGetProtoUnitID("Hippikon"):
		{
			trQuestVarSet("p"+p+"yeebBonus", 2 + trQuestVarGet("p"+p+"yeebBonus"));
			mSetVarByQV("p"+p+"commander", "attack", 2 + mGetVarByQV("p"+p+"commander", "attack"));
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case kbGetProtoUnitID("Myrmidon"):
		{
			mSetVar(unit, "health", mGetVar(unit, "health") + trQuestVarGet("p"+p+"manaflow"));
		}
		case kbGetProtoUnitID("Behemoth"):
		{
			mSetVar(unit, "health", mGetVar(unit, "health") + trQuestVarGet("p"+p+"manaflow"));
			mSetVar(unit, "attack", mGetVar(unit, "attack") + trQuestVarGet("p"+p+"manaflow"));
			mSetVar(unit, "scale", 1 + 0.25 * trQuestVarGet("p"+p+"manaflow"));
			scaleUnit(unit);
		}
		case kbGetProtoUnitID("Hippocampus"):
		{
			trQuestVarSet("highestCost", 0);
			trQuestVarSet("currentCost", 0);
			trQuestVarSet("highestPointer", 0);
			for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
				type = yDatabaseNext("p"+p+"deck");
				if (yGetVar("p"+p+"deck", "spell") == 0) {
					trQuestVarCopy("currentCost", "card_"+type+"_cost");
					if (trQuestVarGet("currentCost") >= trQuestVarGet("highestCost")) {
						trQuestVarSet("highestPointer", yGetPointer("p"+p+"deck"));
						trQuestVarCopy("highestCost", "currentCost");
					}
				}
			}
			ySetPointer("p"+p+"deck", 1 + trQuestVarGet("highestPointer"));
			drawCard(p);
		}
		case kbGetProtoUnitID("Medusa"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_MEDUSA_STUN);
		}
		case kbGetProtoUnitID("Lampades"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_LAMPADES_CONVERT);
		}
		case kbGetProtoUnitID("Tartarian Gate spawn"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_DEMON_EAT);
		}
		case kbGetProtoUnitID("Axeman"):
		{
			trQuestVarSet("p"+p+"yeebBonus", 1 + trQuestVarGet("p"+p+"yeebBonus"));
			mSetVarByQV("p"+p+"commander", "attack", 1 + mGetVarByQV("p"+p+"commander", "attack"));
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case kbGetProtoUnitID("Guardian"):
		{
			trQuestVarSet("p"+(3-p)+"drawCards", 2 + trQuestVarGet("p"+(3-p)+"drawCards"));
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("cinematics\32_out\kronosbehinddorrshort.mp3","1",-1,"","");
		}
		case kbGetProtoUnitID("Hero Greek Achilles"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("xpack\xdialog\xkri075.mp3","1",-1,"", "");
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("p"+(3-p)+"commander"));
			spyEffect("Poison SFX");
			deployAtTile(0, "Kronny Birth SFX", 1*mGetVarByQV("p"+(3-p)+"commander", "tile"));
			mSetVarByQV("p"+(3-p)+"commander", "keywords", SetBit(1*mGetVarByQV("p"+(3-p)+"commander", "keywords"), DECAY));
			stunUnit(1*trQuestVarGet("p"+(3-p)+"commander"));
		}
		case kbGetProtoUnitID("Scorpion Man"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_SCORPION_STING);
		}
		case kbGetProtoUnitID("Anubite"):
		{
			deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("p"+p+"commander", "tile"));
			damageUnit(1*trQuestVarGet("p"+p+"commander"), 3);
		}
		case kbGetProtoUnitID("Hero Greek Ajax"):
		{
			trQuestVarSet("summonedUnit", unit);
			chooseSpell(SPELL_SUMMON_ONE);
			done = false;
		}
		case kbGetProtoUnitID("Tower Mirror"):
		{
			trSoundPlayFN("wonder.wav","1",-1,"","");
		}
	}
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+unit));
	if (HasKeyword(MAGNETIC, 1*mGetVar(unit, "keywords"))) {
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if ((trQuestVarGet("allUnits") == unit) || (mGetVarByQV("allUnits", "player") == 3 - p)) {
				continue;
			} else if (HasKeyword(MAGNETIC, 1*mGetVarByQV("allUnits", "keywords")) &&
				zDistanceToVectorSquared("allUnits", "pos") < 40) {
				done = false;
				trQuestVarSet("spellCaster", unit);
				chooseSpell(SPELL_MAGNETIZE);
				break;
			}
		}
	}
	if (done) {
		removeDeadUnits();
		xsEnableRule("gameplay_01_select");
		highlightReady(999999);
	}
}