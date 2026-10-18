from pathlib import Path
s=Path(__file__).resolve().parents[1].joinpath('src/plugin.cpp').read_text()
assert s.count('InstallNativePickupGuard(')==1 # definition only; never installed
assert 'LOOT_HIDE_PRESENTATION_ONLY pickup-dispatch-hook=none targeted-label=native' in s
a=s.index('// A hidden-hover label'); b=s.index('if (!rule->hasBackground',a)
assert 'if (!rule->show) return false;' in s[a:b]
assert 'SuppressHiddenHover(' not in s[a:b]
assert 'ConcealBulkVisuals(' in s
print('label-only hide: native pickup dispatch untouched, targeted labels forwarded')
