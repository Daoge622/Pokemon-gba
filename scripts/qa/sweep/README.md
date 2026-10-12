# Headless runtime sweeps (Claude, 2026-10-08)

Only run when the user has explicitly authorized silent mGBA runs for the current task.
No GUI, input ROM/save never modified; all setup is RAM-only.

- `mkprobe2.py`: builds ~/qa-sweep/probe2 from ../gameplay-probe.c, adding debug-log output and the commands
  mark / ptrread / stackfill / stackscan.
- `rt.py`: harness. It runs setup through a small event-script bytecode written to gStringVar4
  (warpsilent + waitstate, setflag, setvar, additem, setmonmove, setwildbattle, dowildbattle),
  so it also works on LTO release builds.
- `sweep.py ROM SAVE OUT`: runs every Emerald map object / sign / coord script, presses A then B, and flags reset,
  crash screen or invalid jump. 4100 cases in about 10 minutes with 8 processes.
- `battle_sweep.py ROM SAVE OUT`: starts a battle against every trainer and roster opponent (900) and mashes A.
- `capture.py`, `user2.py`, `stack.py`: user-save replays (capture, walk to Steven, stack high-water mark).
  They expect ~/user-bug.sav.
Results 2026-10-08: see BUGFIX_MYBOY_2026-10-08.md.
