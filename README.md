# pwrsign
Send power state transition signal using Windows undocumented Native API.<br>
Support Windows 2000 to newer Windows 11.<br>

# How does it work?
The program will call NTAPI function `NtInitiatePowerAction` with `POWER_ACTION` and `SYSTEM_POWER_STATE` parameters passed by user.<br>

# How to use it?
```
pwrsign.exe param1 param2 param3

param1:
- pwrinfo - get power state informations
- slp* - sleep
- hib* - hibernate
- shut* - shutdown
- shutres* - shutdown then reset/restart
- shutoff* - shutdown then off

param2:
- slp1st* - sleep s1 state
- slp2st* - sleep s2 state
- slp3st* - sleep s3 state
- hibst* - hibernate s4 state
- shutst* - shutdown s5 state

param3 (optional):
- sync - function wait until done
- async - function return immediatelly
* symbol indicate both paramters (param1 and param2) must be passed!

example:
pwrsign.exe slp slp1st sync
```

# Demo

W7 (shutres)

https://github.com/user-attachments/assets/2d119a35-3787-4f69-ac21-6f54cfad264c

W2000 (hib)

https://github.com/user-attachments/assets/e4570607-502c-41f7-87a0-fdfd21787fc9

# Remarks
- pwrsign only SEND power state transition instead FORCE it!, so it depends how your system will handle it.
- `shut` `shutres` `shutoff` will trigger ungraceful shutdown/restart, meaning it will not flush any caches to disk and unsaved data may lost, USE WITH YOUR OWN RISK!
- `PowerActionWarmEject` and `PowerActionDisplayOff` options are omitted because it does not show any sign of working, but if you want included, compile it yourself.





