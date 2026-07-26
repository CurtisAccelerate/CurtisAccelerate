#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOGS="$ROOT/logs"
mkdir -p "$LOGS"

printf '\n[1/3] Verifying the explicit witness...\n'
python3 "$ROOT/verify_witness.py" | tee "$LOGS/witness_verification.log"

printf '\n[2/3] Compiling the exact lower-bound enumerator...\n'
CXX="${CXX:-g++}"
"$CXX" -O3 -std=c++20 -Wall -Wextra -Wpedantic \
    "$ROOT/lower_bound_enumerator.cpp" -o "$ROOT/lower_bound_enumerator"

printf '\n[3/3] Running the exact lower-bound enumeration...\n'
if command -v /usr/bin/time >/dev/null 2>&1; then
  /usr/bin/time -f 'wall=%e sec maxrss=%M KB' \
      "$ROOT/lower_bound_enumerator" \
      > >(tee "$LOGS/lower_bound_stdout.log") \
      2> >(tee "$LOGS/lower_bound_stderr.log" >&2)
else
  "$ROOT/lower_bound_enumerator" \
      > >(tee "$LOGS/lower_bound_stdout.log") \
      2> >(tee "$LOGS/lower_bound_stderr.log" >&2)
fi

grep -q 'TOTAL nodes=50778686 complete=936720 pass4=936720 passall=0' \
    "$LOGS/lower_bound_stdout.log"

printf '\nAll mandatory checks passed.\n'
printf 'Optional independent MILP cross-check: python3 "%s"\n' "$ROOT/milp_crosscheck.py"
