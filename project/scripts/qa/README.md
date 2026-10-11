# Explicitly authorized runtime regressions

Normal builds never execute ROMs. AGENTS.md prohibits unattended emulator / ROM tests by default. Run this driver only after the user explicitly authorizes ROM execution for the current task; historical authorization is not a standing permission.

The C harness uses the installed mGBA core (libmgba-dev, cc), without any GUI. The driver requires arm-none-eabi-nm, Python3, the matching ROM/ELF, and the **synthetic pre-fix Dewford fixture**. It is not a generic acceptance script for arbitrary personal saves. All setup changes remain in emulator RAM; inputs are hashed and never overwritten. A separate output directory receives screenshots, command files, logs and results.json. It is intentionally absent from build.sh.

Example, only after explicit authorization:

```sh
python3 scripts/qa/check-gameplay.py --allow-rom-execution \
  --rom pokeemerald.gba --elf pokeemerald.elf \
  --save /home/pokemon/qa-bugfix-2026-10-07/old-save-fixture/fixture-dewford.sav \
  --output /home/pokemon/qa-bugfix-2026-10-07/suite-normal
```

For release use pokeemerald-release.gba / .elf and suite-release. For task-start backup use the matching original ROM/ELF, an unused output directory, and --expect-old-capture-bug. The original failure evidence is already preserved in suite-baseline; do not overwrite it.

Coverage / limits: capture registration ownership after ordinary Pokédex close, free/full party with egg and ExpShare, known species, both KO outcomes, and normal-build Rusturf rescue coordinates/state. Release LTO removes some native fixture setup helpers, so its Rusturf case is explicitly SKIP. Initial party and battle conditions are controlled fixtures, not proof of a naturally played full story. No output implies the entire PART is TESTED.

Results and save guidance: ../../BUGFIX_PLAYABILITY_2026-10-07.md. Windows evidence copies live at D:/Pokemon gba/artifacts/bugfix-2026-10-07/runtime/. No personal save was supplied or modified.
