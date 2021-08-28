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
	switch(proto)
	{
		case kbGetProtoUnitID("Slinger"):
		{
			addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_SPARK);
			updateHandPlayable(p);
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
			addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_MAP);
			updateHandPlayable(p);
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
		case kbGetProtoUnitID("Scout"):
		{
			trQuestVarSet("p"+(3-p)+"drawCards", 2 + trQuestVarGet("p"+(3-p)+"drawCards"));
		}
	}
	if (done) {
		removeDeadUnits();
		xsEnableRule("gameplay_01_select");
		highlightReady(999999);
	}
}