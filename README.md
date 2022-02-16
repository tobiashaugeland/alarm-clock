# alarm-clock
Alarm clock

## Test Cases
### Test case 1
type "s", type current date and time + 60 sec, "l". Then the programs expected result is the time set. We are testing that the program can set an alarm, and when the alarm is ongoing, it should be visible in the list. 
### Test case 2
type "s", a date and timebefore current time. Expected result should be Invalid time, and typing "l" should give no alarms. We are testing that the program handles incorrect entries. 
### Test case 3
type "s", current date and time + 60 sec, type "l" and the alarm should be visible, let the program run for 60 sec. The expected result should be "Alarm!" and a sound should play. Afterwards type "l" and no alarm should be active. We are testing that an alarm will be listed when active but removed when finished and that it is killed automatically.
### Test case 4
create 4 different valid alarms, type "l" to show them, then type "c" and kill alarm 3. Then type "l", and alaram 1, 2 and 4 should be listed, but not 3. We are testing that you can kill one of the alarms and that the rest will continue running.
