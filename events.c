const int EVENT_LASER_END = 0;
const int EVENT_PRESS_SPACE = 1;

rule event_assignment
highFrequency
active
{
	trEventSetHandler(EVENT_LASER_END, "laserEnd");
	trEventSetHandler(EVENT_PRESS_SPACE, "pressSpace");
	xsDisableRule("event_assignment");
}
