# UnHoarder changelog

## 1.2.8 - staged visibility update

- Share filter visibility with matching Controller QOL so hidden loot does not
  consume LB pickup slots. Use QOL rev.80-beta.7-visibility.2 for the latest
  unmodified-controller pickup handling as well.
- Retain the 1.2.7 label-only behavior: filtered labels can be hidden while
  native pickup remains available. UnHoarder no longer intercepts pickup actions.
- Preserve the controller labels, drop alerts and socket-rule fixes from 1.2.6.

Validation: 37 CTest tests, 51 Python source checks and 61 matching QOL tests
pass. Visible combined hide/pickup behavior, audible alert behavior and
exhaustive hosted-game combinations remain pending. No binary release has
been published for this branch. Original author credits and license are intact.

## 1.2.6 - staged fork update

- Apply filter names, colors and backgrounds to controller ground labels.
- Play filter alerts when items drop, even with labels hidden, with the normal
  drop sound retained when filter playback cannot be used.
- Make the 16 bundled filter alerts use the Items volume control. Requires the
  matching sound-table changes as well as the DLL.
- Restore socket-based show/hide rules with the reviewed Maps companion.

Includes the earlier 1.2.3-1.2.5 staged fixes. Existing filter rules and settings
are preserved. Original author: MindH1ve; this fork is maintained by Pyre-Flies.

Validation: 37 CTest tests, 49 Python source checks and matching QOL's 55 tests
passed. Controller labels were confirmed by the user; socket forwarding was
inspected read-only in game. Audible alert behavior and visible socket-rule
retesting remain pending. These changes have not been released as a binary here.
