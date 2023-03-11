const int EVENT_LASER_END = 0;
const int EVENT_PRESS_SPACE = 1;
const int EVENT_START_MISSION = 2;
const int EVENT_DESELECT = 3;

const int EVENT_CHOOSE_SAVE = 4;
const int EVENT_NEXT_SAVE = 5;

const int EVENT_CHOOSE_LOAD = 6;
const int EVENT_NEXT_LOAD = 7;

const int EVENT_CHOOSE_DELETE = 8;
const int EVENT_NEXT_DELETE = 9;

const int EVENT_CHOOSE_LOAD_DELETE = 10;

const int EVENT_MUSIC = 11;

const int EVENT_CHOOSE_CLASS = 12;
const int EVENT_NEXT_CLASS = 13;

rule event_assignment
highFrequency
active
{
	trEventSetHandler(EVENT_LASER_END, "laserEnd");
	trEventSetHandler(EVENT_PRESS_SPACE, "pressSpace");
	trEventSetHandler(EVENT_START_MISSION, "CollectionStartMission");
	trEventSetHandler(EVENT_DESELECT, "deselectAll");

	trEventSetHandler(EVENT_CHOOSE_SAVE, "saveToFile");
	trEventSetHandler(EVENT_NEXT_SAVE, "nextFile");

	trEventSetHandler(EVENT_CHOOSE_LOAD, "loadFromFile");
	trEventSetHandler(EVENT_NEXT_LOAD, "nextFile");

	trEventSetHandler(EVENT_CHOOSE_DELETE, "deleteFile");
	trEventSetHandler(EVENT_NEXT_DELETE, "nextFile");

	trEventSetHandler(EVENT_CHOOSE_LOAD_DELETE, "loadOrDeleteFile");

	xsDisableSelf();
}
