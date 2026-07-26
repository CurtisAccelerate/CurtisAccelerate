#!/usr/bin/env python3
"""Independent 0-1 MILP cross-check for the lower bound M_11 >= 17.

After switching, all signs incident to one distinguished vertex are +1. The
45 binary variables describe which edges among the other ten vertices are
negative. All 2^10 spin inequalities enforce |q(x)| <= 15.

Requires SciPy with scipy.optimize.milp (HiGHS backend).
"""

from __future__ import annotations

import itertools
import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp
from scipy.sparse import csr_matrix, vstack

V = 10
edges = [(i, j) for i in range(V) for j in range(i + 1, V)]
edge_index = {edge: k for k, edge in enumerate(edges)}

rows: list[np.ndarray] = []
lower: list[float] = []
upper: list[float] = []
for bits in itertools.product((-1, 1), repeat=V):
    x = np.asarray(bits, dtype=int)
    constant = int(x.sum())
    row = np.zeros(len(edges), dtype=int)
    for k, (i, j) in enumerate(edges):
        product = int(x[i] * x[j])
        constant += product
        row[k] = -2 * product
    rows.append(row)
    lower.append(-15 - constant)
    upper.append(15 - constant)

degree_rows: list[np.ndarray] = []
for i in range(V):
    row = np.zeros(len(edges), dtype=int)
    for k, (a, b) in enumerate(edges):
        if a == i or b == i:
            row[k] = 1
    degree_rows.append(row)

base_matrix = csr_matrix(np.asarray(rows, dtype=float))
base_lower = np.asarray(lower, dtype=float)
base_upper = np.asarray(upper, dtype=float)

all_infeasible = True
for max_degree in range(9, 4, -1):
    extra_rows: list[np.ndarray] = []
    extra_lower: list[float] = []
    extra_upper: list[float] = []

    for j in range(1, V):
        row = np.zeros(len(edges), dtype=int)
        row[edge_index[(0, j)]] = 1
        value = 1 if j <= max_degree else 0
        extra_rows.append(row)
        extra_lower.append(value)
        extra_upper.append(value)

    for i in range(1, V):
        extra_rows.append(degree_rows[i])
        extra_lower.append(-np.inf)
        extra_upper.append(max_degree)

    if max_degree == 5:
        for i in range(V):
            extra_rows.append(degree_rows[i])
            extra_lower.append(4)
            extra_upper.append(np.inf)

    matrix = vstack(
        [base_matrix, csr_matrix(np.asarray(extra_rows, dtype=float))],
        format="csr",
    )
    lo = np.concatenate([base_lower, np.asarray(extra_lower, dtype=float)])
    hi = np.concatenate([base_upper, np.asarray(extra_upper, dtype=float)])

    print(f"\nCASE maximum degree {max_degree}; constraints={matrix.shape}")
    result = milp(
        c=np.zeros(len(edges)),
        integrality=np.ones(len(edges)),
        bounds=Bounds(np.zeros(len(edges)), np.ones(len(edges))),
        constraints=LinearConstraint(matrix, lo, hi),
        options={
            "disp": True,
            "presolve": True,
            "time_limit": 300.0,
            "mip_rel_gap": 0.0,
        },
    )
    print(f"status={result.status}: {result.message}")

    case_infeasible = result.status == 2 and result.x is None
    all_infeasible = all_infeasible and case_infeasible
    if not case_infeasible:
        raise RuntimeError(
            f"case max_degree={max_degree} was not certified infeasible"
        )

assert all_infeasible
print("\nMILP cross-check: PASS (all five symmetry cases proven infeasible)")
