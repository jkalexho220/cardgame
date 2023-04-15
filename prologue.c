void MusicHigh(){
	trQuestVarSetFromRand("random", 1, 4, true);
	if(trQuestVarGet("random") == 1){
		trSoundPlayFN("cinematics\8_in\music.mp3", "26", -1, "","");
	}
	if(trQuestVarGet("random") == 2){
		trSoundPlayFN("cinematics\9_out\music.mp3", "29", -1, "","");
	}
	if(trQuestVarGet("random") == 3){
		trSoundPlayFN("cinematics\23_out\music 2.mp3", "30", -1, "","");
	}
	if(trQuestVarGet("random") == 4){
		trSoundPlayFN("xpack\xcinematics\8_in\music.mp3", "56", -1, "","");
	}
}
void MusicMedium(){
	trQuestVarSetFromRand("random", 1, 4, true);
	if(trQuestVarGet("random") == 1){
		trSoundPlayFN("cinematics\05_out\music.mp3", "19", -1, "","");
	}
	if(trQuestVarGet("random") == 2){
		trSoundPlayFN("cinematics\31_out\music.mp3", "34", -1, "","");
	}
	if(trQuestVarGet("random") == 3){
		trSoundPlayFN("cinematics\22_in\music 2.mp3", "14", -1, "","");
	}
	if(trQuestVarGet("random") == 4){
		trSoundPlayFN("xpack\xcinematics\7_out\music.mp3", "19", -1, "","");
	}
}
void MusicLow(){
	trQuestVarSetFromRand("random", 1, 4, true);
	if(trQuestVarGet("random") == 1){
		trSoundPlayFN("cinematics\26_out\music.mp3", "37", -1, "","");
	}
	if(trQuestVarGet("random") == 2){
		trSoundPlayFN("cinematics\21_in\music.mp3", "51", -1, "","");
	}
	if(trQuestVarGet("random") == 3){
		trSoundPlayFN("cinematics\04_in\music 1.mp3", "13", -1, "","");
	}
	if(trQuestVarGet("random") == 4){
		trSoundPlayFN("cinematics\26_in\music.mp3", "26", -1, "","");
	}
}

rule CinPrologue00
highFrequency
inactive
{
	if (trTime() > trQuestVarGet("cinTime")) {
		switch(1*trQuestVarGet("cinStep"))
		{
		case 0:
			{
				trLetterBox(true);
				trQuestVarSet("cinTime", trTime() + 6);
				trOverlayText("The story began on an ordinary day...", 5.0);
			}
		case 1:
			{
				trLetterBox(false);
				CinematicPlay("HeavenGames\intro_", 1, 8, "cinematics\26_out\music.mp3");
				MusicLow();
				trQuestVarSet("cinTime", trTime());
				trQuestVarSet("idsStart", trGetNextUnitScenarioNameNumber());
			}
		case 2:
			{
				trQuestVarSet("cinTime", trTime() + 6);
				ambientColor(0,0,0);
				sunColor(0,0,0);
				trLetterBox(true);
				trSoundPlayFN("cinematics\35_out\music.mp3");
				trCameraCut(vector(15.341919,89.480629,24.112017), vector(0.000398,-1.000000,-0.000003),
					vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
				trVectorQuestVarSet("V", xsVectorSet(23.99, 0.00, 34.41));
				for(x=0;<20){
					trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V"),trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")-1));
					DeploySober("Curse SFX", "V");
				}
				for(x=0;<12){
					trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V")-0.75,trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")+0.75));
					DeploySober("Curse SFX", "V");
				}
				for(x=0;<12){
					trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V")-0.75,trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")-0.75));
					DeploySober("Curse SFX", "V");
				}
				trSoundPlayFN("lightningstrike1.wav", "2", -1, "","");
				trUIFadeToColor(255,255,255,500,0,false);
				trOverlayText("Zenophobia presents...", 4.0, -1, -1, -1);
				trSoundPlayFN("godpower.wav", "6", -1, "","");
			}
		case 3:
			{
				trQuestVarSet("cinTime", trTime() + 3);
				trSoundPlayFN("lightningstrike4.wav", "5", -1, "","");
				trSoundPlayFN("vortexstart.wav", "3", -1, "","");
				trCameraCut(vector(16.595451,124.640816,14.744846), vector(0.000398,-1.000000,-0.000003),
					vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
				trOverlayText("...in collaboration with Nickonhawk...", 4.0, 450, 600, 1000);
				trVectorQuestVarSet("V", xsVectorSet(7.98, 0.00, 2.24));
				string n = "Curse SFX";
				string g = "Increase Prosperity Small";
				for(z=0;<26){
					for(x=0;<24){
						string p = "";
					if(z==0 && x>14 && x<17){p=n;}
					if(z==1 && (x>3 && x<6 || x>11 && x<19)){ if(x>16){p=g;}else{p=n;} }
					if(z==2 && x<19){ if(x>14){p=g;}else{p=n;} }
					if(z==3 && x<19){ if(x>11 && x<18){p=g;}else{p=n;} }
					if(z==4){ if(x>10 && x<17){p=g;}else{p=n;} }
					if(z==5){ if(x>8 && x<17){p=g;}else{p=n;} }
					if(z==6){ if(x>8 && x<17){p=g;}else{p=n;} }
					if(z==7 && x<22){ if(x>8&&x<18){p=g;}else{p=n;} }
					if(z==8 && x<19 && x!=12){ if(x>12){p=g;}else{p=n;} }
					if(z==9 && x<19 && x!=12 && x!=13){ if(x>16){p=g;}else{p=n;} }
					if(z==10 && x>0 && x<18){p=n;}
					if(z==11 && x>0 && x<15){p=n;}
					if(z==12 && x>0 && x<11){p=n;}
					if(z==13 && x<11){p=n;}
					if(z==14 && x<11){p=n;}
					if(z==15 && x<11){p=n;}
					if(z==16 && x<11){p=n;}
					if(z==17 && x<13){p=n;}
					if(z==18 && x<15){p=n;}
					if(z==19 && x<17){p=n;}
					if(z==20 && x>0 && x<18){p=n;}
					if(z==21 && x>2 && x<19){p=n;}
					if(z==22 && x>4 && x<19){p=n;}
					if(z==23 && x>14 && x<19){p=n;}
					if(z==24 && x>14 && x<18){p=n;}
					if(z==25 && x>14 && x<17){p=n;}
						if(p!=""){
							trArmyDispatch("1,10",p,1,trVectorQuestVarGetX("V")+x,0,trVectorQuestVarGetZ("V")+z,0,true);
						}
					}
				}
			}
		case 4:
			{
				trUIFadeToColor(0,0,0, 1000, 0, true);
				trQuestVarSet("cinTime", trTime() + 3);
			}
		case 5:
			{
				trOverlayText("~ H E A V E N   G A M E S ~", 4.7, 516, 200, 1000);
				trSoundPlayFN("xsentinelbirth.wav", "3", -1, "","");
				trQuestVarSet("cinTime", trTime() + 3);
			}
		case 6:
			{
				trFadeOutAllSounds(3.0);
				trQuestVarSet("cinTime", trTime() + 3);
			}
		default:
			{
				// cleanup
				int next = trGetNextUnitScenarioNameNumber();
				for(i=trQuestVarGet("idsStart");<next){
					trUnitSelectClear();
					trUnitSelect(""+i, true);
					trUnitDestroy();
				}
				xsDisableSelf();
				trLetterBox(false);
				xsEnableRule("MissionBegin");
				trSetLighting("default", 0);
				trQuestVarSet("missionSelection", -1);
				trQuestVarSet("missionClass", -1);
			}
		}
		trQuestVarSet("cinStep", 1 + trQuestVarGet("cinStep"));
	}
}
/*
rule CinPrologue01
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " :He finished work and was heading home feeling good.", "");
		trRenderSky(true, "SkyBlue");
		xsDisableRule("CinPrologue01");
		xsEnableRule("CinPrologue02");
	}
}

rule CinPrologue02
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " :However fate was about to intervene...", "");
		trCameraCut(vector(115.395638,-62.376621,13.212063), vector(-0.913248,0.407394,0.002918),
			vector(0.407396,0.913250,-0.001302), vector(0.003194,0.000000,0.999995));
		trSoundPlayFN("lightthunder.wav", "14", -1, "","");
		xsDisableRule("CinPrologue02");
		xsEnableRule("CinPrologue03");
	}
}

rule CinPrologue03
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trFadeOutAllSounds(0.0);
		trUIFadeToColor(255,255,255,500,0,false);
		trSoundPlayFN("lightningstrike2.wav", "2", -1, "","");
		trRenderSky(true, "SkyStormy");
		trSoundPlayFN("lightningbirth.wav", "4", -1, "","");
		trSoundPlayFN("cinematics\35_out\music.mp3");
		xsDisableRule("CinPrologue03");
		xsEnableRule("CinPrologue04");
	}
}

rule CinPrologue04
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trCameraCut(vector(15.341919,89.480629,24.112017), vector(0.000398,-1.000000,-0.000003),
			vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
		trVectorQuestVarSet("V", xsVectorSet(23.99, 0.00, 34.41));
		for(x=0;<20){
			trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V"),trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")-1));
			DeploySober("Curse SFX", "V");
		}
		for(x=0;<12){
			trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V")-0.75,trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")+0.75));
			DeploySober("Curse SFX", "V");
		}
		for(x=0;<12){
			trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V")-0.75,trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")-0.75));
			DeploySober("Curse SFX", "V");
		}
		trSoundPlayFN("lightningstrike1.wav", "2", -1, "","");
		trUIFadeToColor(255,255,255,500,0,false);
		trOverlayText("Zenophobia presents...", 4.0, -1, -1, -1);
		trSoundPlayFN("godpower.wav", "6", -1, "","");
		xsDisableRule("CinPrologue04");
		xsEnableRule("CinPrologue05");
	}
}

rule CinPrologue05
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " :Spooked by the sudden storm, Rogers picked up the pace!", "");
		trCameraCut(vector(34.321800,34.885281,60.436821), vector(0.004775,-0.665678,0.746224),
			vector(0.004259,0.746244,0.665658), vector(0.999979,0.000000,-0.006399));
		trUnitSelectClear();trUnitSelect(""+1*trQuestVarGet("idsStart"));
		trUnitMoveToPoint(58.63, 0.00, 101.83, -1, false);
		trUIFadeToColor(255,255,255,500,0,false);
		trSoundPlayFN("lightningstrike5.wav", "4", -1, "","");
		xsDisableRule("CinPrologue05");
		xsEnableRule("CinPrologue06");
	}
}

rule CinPrologue06
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " :Inevitably, he stumbled and fell.", "");
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("idsStart"));
		trDamageUnitPercent(100);
		trUnitSetAnimation("default",false,-1);
		xsDisableRule("CinPrologue06");
		xsEnableRule("CinPrologue07");
	}
}

rule CinPrologue07
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 4){
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trUIFadeToColor(255,255,255,500,0,false);
		trSoundPlayFN("lightningstrike4.wav", "5", -1, "","");
		trSoundPlayFN("vortexstart.wav", "3", -1, "","");
		trCameraCut(vector(16.595451,124.640816,14.744846), vector(0.000398,-1.000000,-0.000003),
			vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
		trOverlayText("...in collaboration with Nickonhawk...", 4.0, 450, 600, 1000);
		trVectorQuestVarSet("V", xsVectorSet(7.98, 0.00, 2.24));
		string n = "Curse SFX";
		string g = "Increase Prosperity Small";
		for(z=0;<26){
			for(x=0;<24){
				string p = "";
			if(z==0 && x>14 && x<17){p=n;}
			if(z==1 && (x>3 && x<6 || x>11 && x<19)){ if(x>16){p=g;}else{p=n;} }
			if(z==2 && x<19){ if(x>14){p=g;}else{p=n;} }
			if(z==3 && x<19){ if(x>11 && x<18){p=g;}else{p=n;} }
			if(z==4){ if(x>10 && x<17){p=g;}else{p=n;} }
			if(z==5){ if(x>8 && x<17){p=g;}else{p=n;} }
			if(z==6){ if(x>8 && x<17){p=g;}else{p=n;} }
			if(z==7 && x<22){ if(x>8&&x<18){p=g;}else{p=n;} }
			if(z==8 && x<19 && x!=12){ if(x>12){p=g;}else{p=n;} }
			if(z==9 && x<19 && x!=12 && x!=13){ if(x>16){p=g;}else{p=n;} }
			if(z==10 && x>0 && x<18){p=n;}
			if(z==11 && x>0 && x<15){p=n;}
			if(z==12 && x>0 && x<11){p=n;}
			if(z==13 && x<11){p=n;}
			if(z==14 && x<11){p=n;}
			if(z==15 && x<11){p=n;}
			if(z==16 && x<11){p=n;}
			if(z==17 && x<13){p=n;}
			if(z==18 && x<15){p=n;}
			if(z==19 && x<17){p=n;}
			if(z==20 && x>0 && x<18){p=n;}
			if(z==21 && x>2 && x<19){p=n;}
			if(z==22 && x>4 && x<19){p=n;}
			if(z==23 && x>14 && x<19){p=n;}
			if(z==24 && x>14 && x<18){p=n;}
			if(z==25 && x>14 && x<17){p=n;}
				if(p!=""){
					trArmyDispatch("1,10",p,1,trVectorQuestVarGetX("V")+x,0,trVectorQuestVarGetZ("V")+z,0,true);
				}
			}}
			xsDisableRule("CinPrologue07");
			xsEnableRule("CinPrologue08");
		}
	}
	
	rule CinPrologue08
	highFrequency
	inactive
	{
		if ((trTime()-cActivationTime) >= 4){
			trSoundPlayDialog("default", "1", -1, false, " : ", "");
			trUIFadeToColor(255,255,255,500,0,true);
			trFadeOutAllSounds(3.0);
			trSoundPlayFN("lightningstrike5.wav", "4", -1, "","");
			trVectorQuestVarSet("V", xsVectorSet(74.62, 0.00, 119.92));
			trVectorQuestVarSet("U", trVectorQuestVarGet("V"));
			trVectorQuestVarSet("U", xsVectorSet(trVectorQuestVarGetX("U"),trVectorQuestVarGetY("U"),trVectorQuestVarGetZ("U") - 28));
			for(x=0;<18){
				trVectorQuestVarSet("V",xsVectorSet(trVectorQuestVarGetX("V")+8,trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V")));
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("V"),trVectorQuestVarGetY("V"),trVectorQuestVarGetZ("V"),270,true);
				trVectorQuestVarSet("U",xsVectorSet(trVectorQuestVarGetX("U")+8,trVectorQuestVarGetY("U"),trVectorQuestVarGetZ("U")));
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("U"),trVectorQuestVarGetY("U"),trVectorQuestVarGetZ("U"),90,true);
			}
			unitTransform("Dwarf","Palace");
			xsDisableRule("CinPrologue08");
			xsEnableRule("CinPrologue09");
		}
	}
	
	rule CinPrologue09
	highFrequency
	inactive
	{
		if ((trTime()-cActivationTime) >= 2){
			trSoundPlayDialog("default", "1", -1, false, " : When Rogers woke up, he found himself in a different place.", "");
			trUIFadeToColor(255,255,255,2000,0,false);
			trSoundPlayFN("visionswoosh.wav", "4", -1, "","");
			trSoundPlayFN("skypassageout.wav", "1", -1, "","");
			trCameraCut(vector(54.713875,7.545822,105.967346), vector(0.930725,-0.365716,-0.001491),
				vector(0.365710,0.930729,-0.000586), vector(-0.001603,0.000000,-0.999999));
			xsDisableRule("CinPrologue09");
			xsEnableRule("CinPrologue10");
		}
	}
	
	rule CinPrologue10
	highFrequency
	inactive
	{
		if ((trTime()-cActivationTime) >= 4){
			trSoundPlayDialog("default", "1", -1, false, " : ", "");
			unitTransform("Mist Olympus","Cinematic Block");
			trUnitSelectClear();trUnitSelect(""+1*trQuestVarGet("otherRogers"));
			trUnitMoveToPoint(75, 0.00, 104.7, -1, false);
			trCamTrackLoad("Prologue");
			trCamTrackPlay(-1, -1);
			xsDisableRule("CinPrologue10");
			xsEnableRule("CinPrologue11");
		}
	}
	
	rule CinPrologue11
	highFrequency
	inactive
	{
		if ((trTime()-cActivationTime) >= 4){
			trOverlayTextColour(255, 255, 0);
			trOverlayText("~ H E A V E N   G A M E S ~", 4.7, 516, 200, 1000);
			trSoundPlayFN("xsentinelbirth.wav", "3", -1, "","");
			trSoundPlayFN("cinematics\32_in\music.mp3", "15", -1, "","");
			trModifyProtounit("Hero Greek Jason", 1, 1, 9999999999999999999.0);
			trModifyProtounit("Hero Greek Jason", 1, 1, -9999999999999999999.0);
			trModifyProtounit("Hero Greek Jason", 1, 1, 10);
			xsDisableRule("CinPrologue11");
			xsEnableRule("CinPrologue12");
			trUIFadeToColor(0,0,0,1000,6000,true);
		}
	}

	rule CinPrologue12
	highFrequency
	inactive
	{
		if ((trTime()-cActivationTime) >= 7){
			xsDisableRule("CinPrologue12");
			trQuestVarSet("missionSelection", -1);
			trQuestVarSet("missionClass", -1);
			trQuestVarSet("newCommanderType", kbGetProtoUnitID("Hero Greek Jason"));
			xsEnableRule("CinPrologue14");
			xsEnableRule("NewCommander0");
			trCameraCut(vector(-58.161659,112.294716,-58.161659),vector(0.500000,-0.707107,0.500000),vector(0.500000,0.707107,0.500000),vector(0.707107,0.000000,-0.707107));
			trLetterBox(false);
			trShowImageDialog("icons\god power meteor icon", "Great Evil approaches! You must bring together the scattered Forumers!");
			trSoundPlayFN("xnew_objective.wav","1",-1,"","");		
			trDelayedRuleActivation("ClassUnlockMessage_0");
		}
	}

	rule CinPrologue14
	highFrequency
	inactive
	{
		if (trQuestVarGet("newCommanderType") == 0){
			xsDisableRule("CinPrologue14");
			xsEnableRule("MissionBegin");
		}
	}
*/

rule CinPrologue_end
inactive
highFrequency
{
	switch(1*trQuestVarGet("cinStep"))
	{
	case 0:
		{
			trShowImageDialog("HeavenGames\class0unlock0", "New class unlocked!");
			trSoundPlayFN("ageadvance.wav");
		}
	case 1:
		{
			trShowImageDialog("HeavenGames\class0unlock1", "New Commander unlocked!");
			trSoundPlayFN("ui\thunder1.wav");
			trSoundPlayFN("herocreation.wav");
		}
	case 2:
		{
			trShowImageDialog("HeavenGames\class1unlock0", "New class unlocked!");
			trSoundPlayFN("ageadvance.wav");
		}
	case 3:
		{
			trShowImageDialog("HeavenGames\class1unlock1", "New Commander unlocked!");
			trSoundPlayFN("ui\thunder1.wav");
			trSoundPlayFN("herocreation.wav");
		}
	default:
		{
			trQuestVarSet("newCommanderType", 0);
		}
	}
	trQuestVarSet("cinStep", 1 + trQuestVarGet("cinStep"));
	xsDisableSelf();
	trDelayedRuleActivation("CinPrologue_end2");
}

rule CinPrologue_end2
inactive
highFrequency
{
	if (trIsGadgetVisible("ShowImageBox") == false) {
		if (trQuestVarGet("newCommanderType") > 0) {
			trDelayedRuleActivation("CinPrologue_end");
		}
		xsDisableSelf();
	}
}


rule ClassUnlockMessage_0
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\building specialist icons 64", "Class Unlocked: Adventurer");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}

rule ClassUnlockMessage_1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement focus icons 64", "Class Unlocked: Arcane");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}

rule ClassUnlockMessage_2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement poseidons secret icons 64", "Class Unlocked: Naga");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}

rule ClassUnlockMessage_3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement engineers icon 64", "Class Unlocked: Clockwork");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}

rule ClassUnlockMessage_4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\god power ancestors icon 64", "Class Unlocked: Otherworld");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}

rule ClassUnlockMessage_5
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\god power eclipse icon 64", "Class Unlocked: Space");
		trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
	}
}
