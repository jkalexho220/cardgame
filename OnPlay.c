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
	if (1*mGetVar(unit, "echo") <= 0 && (HasKeyword(REPEATABLE, 1*mGetVar(unit, "keywords")) || trCountUnitsInArea("128",p,"Hero Greek Heracles",45) > 0)) {
		generateCard(p, proto, 0, true);
		if(HasKeyword(FLEETING, 1*mGetVarByQV("next", "keywords"))){
			mSetVarByQV("next", "echo", 1);
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
			scaleUnit(unit);
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
			if (mGetVarByQV("p"+p+"commander", "action") < ACTION_SLEEPING) {
				mSetVarByQV("p"+p+"commander", "action", ACTION_READY);
			}
			trSoundPlayFN("militarycreate.wav","1",-1,"","");
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
			if (yGetDatabaseCount("p"+p+"hand") > yGetDatabaseCount("p"+(3-p)+"hand")) {
				done = false;
				trQuestVarSet("spellCaster", unit);
				chooseSpell(SPELL_SCORPION_STING);
			}
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
		case kbGetProtoUnitID("Fire Siphon"):
		{
			trQuestVarSet("spellCaster", unit);
			mSetVar(unit, "laserDirx", -70710);
			mSetVar(unit, "laserDirz", -70710);
			trSetUnitOrientation(xsVectorSet(-0.707107,0,-0.707107), xsVectorSet(0,1,0), true);
			chooseSpell(SPELL_CHOOSE_DIRECTION);
		}
		case kbGetProtoUnitID("Theris"):
		{
			drawCard(p);
		}
		case kbGetProtoUnitID("Female"):
		{
			mSetVarByQV("p"+p+"commander", "health", 2 + mGetVarByQV("p"+p+"commander", "health"));
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		case kbGetProtoUnitID("Flying Purple Hippo"):
		{
			trSoundPlayFN("gaiaattack.wav","1",-1,"","");
			trQuestVarSetFromRand("soundRandom", 1, 6, true);
			switch(1*trQuestVarGet("soundRandom"))
			{
				case 1:
				{
					trSoundPlayFN("hippogrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoreselect1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: ANJKLDNSMDKHALDMNBNA!!!");
				}
				case 2:
				{
					trSoundPlayFN("hippogrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoreselect2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: OIUHDSNBAGNKDAKDAKDA!!!");
				}
				case 3:
				{
					trSoundPlayFN("hyenagrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoremove1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: GDAGAKDGBAJKDGABJKDG!!!");
				}
				case 4:
				{
					trSoundPlayFN("hyenagrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoremove2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: IAHDUIADHANILDHADNDA!!!");
				}
				case 5:
				{
					trSoundPlayFN("walrusgrunt1.wav","1",-1,"","");
					trSoundPlayFN("manticoregrunt1.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: UYADGAKDGAKDGGDASKJF!!!");
				}
				case 6:
				{
					trSoundPlayFN("walrusgrunt2.wav","1",-1,"","");
					trSoundPlayFN("manticoregrunt2.wav","1",-1,"","");
					ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: TARIHDNADHADHDGNALAD!!!");
				}
			}
		}
		case kbGetProtoUnitID("Villager Atlantean Hero"):
		{
			done = false;
			chooseSpell(SPELL_FOOD);
		}
		case kbGetProtoUnitID("Trireme"):
		{
			damageUnit(unit, 4);
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("drop" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Fire Ship Atlantean"):
		{
			damageUnit(unit, 5);
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("drop" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Siege Ship Atlantean"):
		{
			damageUnit(unit, 8);
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("drop" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hero Greek Argo"):
		{
			if(trQuestVarGet("chats_Argo_0") == 0){
				trFadeOutAllSounds(0.0);
				trQuestVarSet("chats_Argo_0", 1);
				trSoundPlayFN("dialog\en\ajax097.mp3","1",-1,"","");
				ChatLog(0, "<color={Playercolor("+p+")}>Hawk's Captain</color>: Do I always have to watch your back?");
				MusicHigh();
			}
			damageUnit(unit, 10);
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
				ChatLog(0, "<color={Playercolor("+p+")}>" + trStringQuestVarGet("card_" + proto + "_name") + "</color>: My brothers have arrived!");
				MusicHigh();
			}
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Catapult"):
		{
			deployAtTile(0, "Meteor", 1*mGetVar(unit, "tile"));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if ((1*mGetVarByQV("allUnits", "spell") == 0) && (1*trQuestVarGet("allUnits") != unit)) {
					if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit(1*trQuestVarGet("allUnits"), 5);
						deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			trCameraShake(1.0, 0.1);
			trSoundPlayFN("tartariangateselect.wav","1",-1,"","");
			trSoundPlayFN("tartariangateselect.wav","1",-1,"","");
			trSoundPlayFN("gateramloud.wav","1",-1,"","");
			trSoundPlayFN("gateramloud.wav","1",-1,"","");
			trSoundPlayFN("chaos.wav","1",-1,"","");
			trSoundPlayFN("chaos.wav","1",-1,"","");
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
