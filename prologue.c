
void DeploySober(string p="", string v=""){
	int next = trGetNextUnitScenarioNameNumber();
	trArmyDispatch("1,10",p,1,trVectorQuestVarGetX(v), trVectorQuestVarGetY(v), trVectorQuestVarGetZ(v),0,true);
	trUnitSelectClear();trUnitSelect(""+next, true);
	trUnitTeleport(trVectorQuestVarGetX(v),trVectorQuestVarGetY(v),trVectorQuestVarGetZ(v));
}
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
	trChangeTerrainHeight(0, 0, 60, 60, 0, false);
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black
	trPaintTerrain(30, 30, 60, 60, 0, 9, false); //GaiaCreepASnow
    trPaintTerrain(0, 30, 30, 60, 0, 5, false); //CliffGreekB
    trLetterBox(true);
    trSoundPlayDialog("default", "1", -1, false, " :It was a fine day for Rogers.", "");
    trUIFadeToColor(0,0,0,1000,1000,false);
	trCameraCut(vector(-21.635717,32.595444,96.573792), vector(0.707104,-0.707109,-0.001133), vector(0.707104,0.707109,-0.001133), vector(-0.001603,0.000000,-0.999999));
    trSetFogAndBlackmap(false, false);
    trQuestVarSet("idsStart", trGetNextUnitScenarioNameNumber());
    trArmyDispatch("1,10", "Hero Greek Jason", 1, -0.19, 0.00, 97.42, 0, true);
	unitTransform("Hero Birth","Cinematic Block");
    trArmySelect("1,10");
    trUnitMoveToPoint(24.06, 0.00, 97.19, -1, false);
    trQuestVarSet("otherRogers", trGetNextUnitScenarioNameNumber());
    trArmyDispatch("1,10", "Hero Greek Jason", 1, 73.67, 0.00, 105.90, 270, true);
    trArmyDispatch("1,10", "Columns Broken", 1, 71.27, -0.00, 109.91, 47, true);
    trArmyDispatch("1,10", "Columns Broken", 1, 77.61, 0.00, 102.63, 333, true);
    trArmyDispatch("1,10", "Columns Broken", 1, 72.03, 0.00, 101.51, 111, true);
    trArmyDispatch("1,10", "Skeleton", 1, 78.01, 0.00, 109.91, 222, true);
    trArmyDispatch("1,10", "Mist Olympus", 1, 70.03, 0.00, 101.93, 222, true);
    trArmyDispatch("1,10", "Mist Olympus", 1, 74.71, 0.00, 109.70, 222, true);
    trArmyDispatch("1,10", "Mist Olympus", 1, 77.57, 0.00, 103.82, 222, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 11.34, 0.00, 104.54, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 15.13, 0.00, 82.10, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 7.41, 0.00, 86.42, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 7.99, 0.00, 93.50, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 9.34, 0.00, 108.28, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 17.80, 0.00, 103.35, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 25.46, -0.00, 107.95, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 32.37, 0.00, 113.47, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 45.28, 0.00, 108.99, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 48.73, 0.00, 90.59, 0, true);
    trArmyDispatch("1,10", "Berry Bush", 1, 30.57, 0.00, 92.07, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 34.31, 0.00, 95.09, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 43.62, 0.00, 94.96, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 29.75, 0.00, 107.86, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 43.11, 0.00, 107.56, 0, true);
    trArmyDispatch("1,10", "Rock Limestone Big", 1, 18.63, 0.00, 91.59, 0, true);
    trArmyDispatch("1,10", "Rain", 1, 32.11, 0.00, 91.33, 0, true);
    trArmyDispatch("1,10", "Rain", 1, 42.46, 0.00, 95.41, 0, true);
    trArmyDispatch("1,10", "Gate", 1, 119.84, 0.00, 100.72, 270, true);
    trArmySelect("1,10");
    trSetSelectedScale(2.5, 1.5, 2.5);
    trTechSetStatus(1, 413, 4);
    MusicLow();
    xsDisableRule("CinPrologue00");
	xsEnableRule("CinPrologue01");
}

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
      trCameraCut(vector(115.395638,-62.376621,13.212063), vector(-0.913248,0.407394,0.002918), vector(0.407396,0.913250,-0.001302), vector(0.003194,0.000000,0.999995));
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
	  MusicHigh();
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
      trCameraCut(vector(15.341919,89.480629,24.112017), vector(0.000398,-1.000000,-0.000003), vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
      trVectorQuestVarSet("V", xsVectorSet(23.99, 0.00, 34.41));
	  for(x=0;<20){
		  trVectorQuestVarSet("V", xsVectorSet(trVectorQuestVarGetX("V") - 0,trVectorQuestVarGetY("V") - 0,trVectorQuestVarGetZ("V") - 1));
		  DeploySober("Curse SFX", "V");
	  }
	  for(x=0;<12){
		  trVectorQuestVarSet("V", xsVectorSet(trVectorQuestVarGetX("V") - 0.75,trVectorQuestVarGetY("V") - 0,trVectorQuestVarGetZ("V") - -0.75));
		  DeploySober("Curse SFX", "V");
	  }
	  for(x=0;<12){
		  trVectorQuestVarSet("V", xsVectorSet(trVectorQuestVarGetX("V") - 0.75,trVectorQuestVarGetY("V") - 0,trVectorQuestVarGetZ("V") - 0.75));
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
      trCameraCut(vector(34.321800,34.885281,60.436821), vector(0.004775,-0.665678,0.746224), vector(0.004259,0.746244,0.665658), vector(0.999979,0.000000,-0.006399));
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
      trUnitSelect(""+1*trQuestVarGet("idsStart")+"");
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
      trCameraCut(vector(16.595451,124.640816,14.744846), vector(0.000398,-1.000000,-0.000003), vector(0.999984,0.000398,-0.005602), vector(-0.005602,0.000000,-0.999984));
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
      trVectorQuestVarSet("U", xsVectorSet(trVectorQuestVarGetX("U") - 0,trVectorQuestVarGetY("U") - 0,trVectorQuestVarGetZ("U") - 28));
	  for(x=0;<18){
		  trVectorQuestVarSet("V", xsVectorSet(trVectorQuestVarGetX("V") + 8,trVectorQuestVarGetY("V") + 0,trVectorQuestVarGetZ("V") + 0));
		  trArmyDispatch("1,10", "Dwarf", 1, trVectorQuestVarGetX("V"), trVectorQuestVarGetY("V"), trVectorQuestVarGetZ("V"), 270, true);
		  trVectorQuestVarSet("U", xsVectorSet(trVectorQuestVarGetX("U") + 8,trVectorQuestVarGetY("U") + 0,trVectorQuestVarGetZ("U") + 0));
		  trArmyDispatch("1,10", "Dwarf", 1, trVectorQuestVarGetX("U"), trVectorQuestVarGetY("U"), trVectorQuestVarGetZ("U"), 90, true);
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
	  trCameraCut(vector(54.713875,7.545822,105.967346), vector(0.930725,-0.365716,-0.001491), vector(0.365710,0.930729,-0.000586), vector(-0.001603,0.000000,-0.999999));
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
	  trOverlayText("G A M E S   O F   H E A V E N", 4.7, 500, 200, 1000);
      trSoundPlayFN("xsentinelbirth.wav", "3", -1, "","");
      trSoundPlayFN("cinematics\32_in\music.mp3", "15", -1, "","");
      xsDisableRule("CinPrologue11");
	  xsEnableRule("CinPrologue12");
   }
}

rule CinPrologue12
highFrequency
inactive
{
   if ((trTime()-cActivationTime) >= 7){
      trPaintTerrain(0, 0, 100, 100, 5, 4, false); //Black
	  int next = trGetNextUnitScenarioNameNumber();
	  for(i=trQuestVarGet("idsStart");<next){
		  trUnitSelectClear();trUnitSelect(""+i);
		  trUnitDestroy();
	  }
      trLetterBox(false);
      xsDisableRule("CinPrologue12");
   }
}
