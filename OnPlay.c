void OnPlay(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	int type = 0;
	int card = 0;
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
	if (HasKeyword(REPEATABLE, 1*mGetVar(unit, "keywords"))) {
		card = generateCard(p, proto, 0, true);
		if (card > 0) {
			mSetVar(card, "keywords", ClearBit(mGetVar(card, "keywords"), REPEATABLE));
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
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "Growl!!!");
			}
		}
		case kbGetProtoUnitID("Lancer Hero"):
		{
			damageUnit(unit, 4);
			spyEffect("Phoenix From Egg");
			trSoundPlayFN("firegiantdie.wav","1",-1,"","");
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
			scaleUnit(unit);
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("archeryrange.wav","1",-1,"","");
			if(trQuestVarGet("chats_Immortal_0") == 0){
				trQuestVarSet("chats_Immortal_0", 1);
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "*intense staring*");
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
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "Preparing to clean.");
			}
		}
		case kbGetProtoUnitID("Monument 2"):
		{
			if(trQuestVarGet("chats_Monument2_0") == 0){
				trQuestVarSet("chats_Monument2_0", 1);
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "Preparing to help with outfit.");
			}
		}
		case kbGetProtoUnitID("Monument 3"):
		{
			if(trQuestVarGet("chats_Monument3_0") == 0){
				trQuestVarSet("chats_Monument3_0", 1);
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "Preparing to assist guest with luggage.");
			}
		}
		case kbGetProtoUnitID("Monument 4"):
		{
			if(trQuestVarGet("chats_Monument4_0") == 0){
				trQuestVarSet("chats_Monument4_0", 1);
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "Prepare Arcane buffet.");
			}
		}
		case kbGetProtoUnitID("Monument 5"):
		{
			if(trQuestVarGet("chats_Monument5_0") == 0){
				trQuestVarSet("chats_Monument5_0", 1);
				trCameraShake(3.0, 0.3);
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "RANDOM BULLSHIT GO!");
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
		case kbGetProtoUnitID("Manticore"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_COPY_ATTACK_EFFECT);
		}
		case kbGetProtoUnitID("Avenger"):
		{
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trMutateSelected(kbGetProtoUnitID("Avenger"));
			trUnitOverrideAnimation(39, 0, false, true, -1);
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
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
					if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						mSetVarByQV("allUnits", "health", 1 + mGetVarByQV("allUnits", "health"));
						mSetVarByQV("allUnits", "maxhealth", 1 + mGetVarByQV("allUnits", "maxhealth"));
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
			trUnitOverrideAnimation(39, 0, false, true, -1);
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if (mGetVarByQV("allUnits", "spell") == 0) {
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
			if (mGetVarByQV("p"+p+"commander", "action") < ACTION_SLEEPING) {
				mSetVarByQV("p"+p+"commander", "action", ACTION_READY);
			}
			trSoundPlayFN("militarycreate.wav","1",-1,"","");
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case kbGetProtoUnitID("Myrmidon"):
		{
			mSetVar(unit, "health", mGetVar(unit, "health") + trQuestVarGet("p"+p+"manaflow"));
			mSetVar(unit, "maxhealth", mGetVar(unit, "maxhealth") + trQuestVarGet("p"+p+"manaflow"));
		}
		case kbGetProtoUnitID("Behemoth"):
		{
			mSetVar(unit, "health", mGetVar(unit, "health") + trQuestVarGet("p"+p+"manaflow"));
			mSetVar(unit, "maxhealth", mGetVar(unit, "maxhealth") + trQuestVarGet("p"+p+"manaflow"));
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
			ySetPointer("p"+p+"deck", 1*trQuestVarGet("highestPointer"));
			yDatabaseNext("p"+p+"deck", false, true);
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
			/*
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_DEMON_EAT);
			*/
			trSoundPlayFN("wild.wav","1",-1,"","");
			drawCard(3 - p);
			mSetVar(unit, "attack", mGetVar(unit, "attack") + yGetDatabaseCount("p"+(3-p)+"hand"));
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
			if (yGetDatabaseCount("p"+p+"hand") > yGetDatabaseCount("p"+(3-p)+"hand")) {
				done = false;
				trQuestVarSet("spellCaster", unit);
				chooseSpell(SPELL_SCORPION_STING);
			}
		}
		case kbGetProtoUnitID("Pharaoh"):
		{
			done = false;
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_DUPLICATE_FRIEND);
		}
		case kbGetProtoUnitID("Anubite"):
		{
			trQuestVarSet("p"+(3-p)+"drawCards", 1 + trQuestVarGet("p"+(3-p)+"drawCards"));
		}
		case kbGetProtoUnitID("Hero Greek Bellerophon"):
		{
			deployAtTile(0, "Arkantos God Out", mGetVar(unit, "tile"));
			trSoundPlayFN("arkantosarrive.wav","1",-1,"","");
			healUnit(1*trQuestVarGet("p"+p+"commander"), 10);
			deployAtTile(0, "Regeneration SFX", mGetVarByQV("p"+p+"commander", "tile"));
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
		case kbGetProtoUnitID("Fire Siphon"):
		{
			trQuestVarSet("spellCaster", unit);
			mSetVar(unit, "laserDirx", -70710);
			mSetVar(unit, "laserDirz", -70710);
			trSetUnitOrientation(xsVectorSet(-0.707107,0,-0.707107), xsVectorSet(0,1,0), true);
			chooseSpell(SPELL_CHOOSE_DIRECTION);
		}
		case kbGetProtoUnitID("Female"):
		{
			drawCard(p);
		}
		case kbGetProtoUnitID("Flying Purple Hippo"):
		{
			/*
			trSoundPlayFN("gaiaattack.wav","1",-1,"","");
			trQuestVarSetFromRand("soundRandom", 1, 6, true);
			switch(1*trQuestVarGet("soundRandom"))
			{
				case 1:
				{
					trSoundPlayFN("hippogrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoreselect1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: ANJKLDNSMDKHALDMNBNA!!!");
				}
				case 2:
				{
					trSoundPlayFN("hippogrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoreselect2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: OIUHDSNBAGNKDAKDAKDA!!!");
				}
				case 3:
				{
					trSoundPlayFN("hyenagrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoremove1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: GDAGAKDGBAJKDGABJKDG!!!");
				}
				case 4:
				{
					trSoundPlayFN("hyenagrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoremove2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: IAHDUIADHANILDHADNDA!!!");
				}
				case 5:
				{
					trSoundPlayFN("walrusgrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoregrunt1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: UYADGAKDGAKDGGDASKJF!!!");
				}
				case 6:
				{
					trSoundPlayFN("walrusgrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoregrunt2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "<color=1,1,1>: TARIHDNADHADHDGNALAD!!!");
				}
			}
			*/
		}
		case kbGetProtoUnitID("Villager Atlantean Hero"):
		{
			done = false;
			chooseSpell(SPELL_BAD_FOOD);
		}
	case kbGetProtoUnitID("Transport Ship Norse"):
		{
			trQuestVarSet("p"+p+"manaTax", 2 + trQuestVarGet("p"+p+"manaTax"));
		}
		case kbGetProtoUnitID("Siege Ship Greek"):
		{
			trQuestVarSet("p"+p+"manaTax", 2 + trQuestVarGet("p"+p+"manaTax"));
		}
		case kbGetProtoUnitID("Fire Ship Atlantean"):
		{
			trQuestVarSet("p"+p+"manaTax", 3 + trQuestVarGet("p"+p+"manaTax"));
		}
		case kbGetProtoUnitID("Siege Ship Atlantean"):
		{
			trQuestVarSet("p"+p+"manaTax", 4 + trQuestVarGet("p"+p+"manaTax"));
		}
		case kbGetProtoUnitID("Hero Greek Argo"):
		{
			if(trQuestVarGet("chats_Argo_0") == 0){
				trFadeOutAllSounds(0.0);
				trQuestVarSet("chats_Argo_0", 1);
				trSoundPlayFN("dialog\en\ajax097.mp3","1",-1,"","");
				CharacterLog(p, "Hawk's Captain", "Do I always have to watch your back?");
				MusicHigh();
			}
			trQuestVarSet("p"+p+"manaTax", 5 + trQuestVarGet("p"+p+"manaTax"));
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("drop" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");

		}
		case kbGetProtoUnitID("Hero Greek Heracles"):
		{
			if(trQuestVarGet("chats_Heracles_0") == 0){
				trFadeOutAllSounds(0.0);
				trQuestVarSet("chats_Heracles_0", 1);
				trSoundPlayFN("xpack\xdialog\en\xfol535.mp3","1",-1,"","");
				CharacterLog(p, trStringQuestVarGet("card_" + proto + "_name"), "My brothers have arrived!");
				MusicHigh();
			}
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hero Ragnorok"):
		{
			mSetVar(unit, "health", mGetVar(unit, "health") + yGetDatabaseCount("p"+p+"hand"));
			mSetVar(unit, "maxhealth", mGetVar(unit, "maxhealth") + yGetDatabaseCount("p"+p+"hand"));
		}
		case kbGetProtoUnitID("Promethean Small"):
		{
			trQuestVarSet("spellCaster", unit);
			chooseSpell(SPELL_DUPLICATE_ME);
			done = false;
		}
	}
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+unit));
	if (HasKeyword(MAGNETIC, 1*mGetVar(unit, "keywords"))) {
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if ((trQuestVarGet("allUnits") == unit) || (mGetVarByQV("allUnits", "player") == 3 - p)) {
				continue;
			} else if (HasKeyword(MAGNETIC, 1*mGetVarByQV("allUnits", "keywords")) &&
				trDistanceToVectorSquared("allUnits", "pos") < 40) {
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

rule cheer_activate
highFrequency
inactive
{
	xsDisableSelf();
	OnPlay(1*trQuestVarGet("cheerTarget"));
}
