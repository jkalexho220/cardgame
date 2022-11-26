const int EVENT_LASER_END = 0;
const int EVENT_PRESS_SPACE = 1;
const int EVENT_START_MISSION = 2;
const int EVENT_DESELECT = 3;

rule event_assignment
highFrequency
active
{
	trEventSetHandler(EVENT_LASER_END, "laserEnd");
	trEventSetHandler(EVENT_PRESS_SPACE, "pressSpace");
	trEventSetHandler(EVENT_START_MISSION, "CollectionStartMission");
	trEventSetHandler(EVENT_DESELECT, "deselectAll");
	xsDisableRule("event_assignment");
}
