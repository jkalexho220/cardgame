const int EVENT_LASER_END = 0;

rule event_assignment
highFrequency
active
{
	trEventSetHandler(EVENT_LASER_END, "laserEnd");
	xsDisableRule("event_assignment");
}
