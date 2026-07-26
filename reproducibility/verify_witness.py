#!/usr/bin/env python3
"""Exact verifier for the explicit n=11 upper-bound witness.

No third-party packages are required. The global spin symmetry lets us fix
x_1=+1 and enumerate the remaining 2^10 spin vectors.
"""

from __future__ import annotations

import itertools
import json
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
DATA = json.loads((HERE / "m11_witness.json").read_text(encoding="utf-8"))
S: list[list[int]] = DATA["matrix"]
n = DATA["n"]

assert n == 11
assert len(S) == n and all(len(row) == n for row in S)
assert all(S[i][i] == 0 for i in range(n))
assert all(S[i][j] == S[j][i] for i in range(n) for j in range(n))
assert all(S[i][j] in (-1, 1) for i in range(n) for j in range(i + 1, n))


def q(x: tuple[int, ...]) -> int:
    return sum(S[i][j] * x[i] * x[j] for i in range(n) for j in range(i + 1, n))


values: list[int] = []
extremizers: list[tuple[int, ...]] = []
for tail in itertools.product((-1, 1), repeat=n - 1):
    x = (1, *tail)
    value = q(x)
    values.append(value)
    if abs(value) == 17:
        extremizers.append(x)

counts = Counter(values)
expected_counts = {
    -15: 29,
    -11: 95,
    -7: 142,
    -3: 206,
    1: 209,
    5: 163,
    9: 92,
    13: 64,
    17: 24,
}

assert min(values) == -15
assert max(values) == 17
assert max(map(abs, values)) == 17
assert dict(sorted(counts.items())) == expected_counts
assert len(values) == 2 ** (n - 1)
assert len(extremizers) == 24

print("witness verification: PASS")
print(f"n={n}; spin vectors checked={len(values)} (x_1 fixed to +1)")
print(f"minimum={min(values)}; maximum={max(values)}; max_abs={max(map(abs, values))}")
print("value distribution:")
for value in sorted(counts):
    print(f"  {value:>3}: {counts[value]}")
print(f"absolute extremizers with x_1=+1: {len(extremizers)}")
