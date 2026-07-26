# Reproducibility package: the exact value \(M_{11}=17\)

## Result

For

\[
M_n:=\min_{a_{ij}\in\{\pm1\}}
\max_{x\in\{\pm1\}^n}
\left|\sum_{i<j}a_{ij}x_ix_j\right|,
\]

this package certifies

\[
\boxed{M_{11}=17}.
\]

The upper bound is an explicit sign matrix checked against all spin vectors. The lower bound is an exhaustive, symmetry-reduced enumeration in integer arithmetic showing that no sign matrix can have maximum absolute value at most 15. Since the sum contains 55 odd terms, every value is odd, so excluding 15 proves the lower bound 17.

## Run the proof

Requirements:

- Python 3
- a C++20 compiler (`g++` by default)

```bash
chmod +x run_all.sh
./run_all.sh
```

The expected final counter line is:

```text
TOTAL nodes=50778686 complete=936720 pass4=936720 passall=0
```

## Exact upper-bound witness

`m11_witness.json` contains a symmetric zero-diagonal \(11\times11\) sign matrix. `verify_witness.py` fixes the first spin to +1 using global spin symmetry, checks all \(2^{10}=1024\) remaining spin vectors, and obtains minimum \(-15\), maximum \(17\), and maximum absolute value \(17\). Thus \(M_{11}\le17\).

## Exact lower-bound reduction

Assume for contradiction that a signing has maximum absolute value at most 15. Switch vertices so all signs incident to one distinguished vertex are positive. Let \(H\) be the graph of negative edges on the remaining ten vertices, with \(m=e(H)\). For each subset \(S\), the number of negative terms after switching is

\[
k_H(S)=m+|S|(11-|S|)-2c_H(S).
\]

The threshold-15 assumption is exactly

\[
20\le k_H(S)\le35
\]

for every subset \(S\). Complement symmetry reduces the edge count to \(m\in\{20,21,22\}\). Singleton constraints reduce the possible sorted degree sequences to 42 total. Four-vertex constraints provide exact pruning. `lower_bound_enumerator.cpp` then generates every graph in the reduced search space and checks all 1024 subset constraints. No graph passes.

## Coding-theory consequence

Let

\[
\widehat C_n=C_{\rm cut}(K_n)\cup(\mathbf1+C_{\rm cut}(K_n)).
\]

Then

\[
M_n=\binom n2-2\rho(\widehat C_n).
\]

For \(n=11\), the certified value gives \(\rho(\widehat C_{11})=19\). The Esmaeili–Zaghian conjecture predicts 20, so it fails at \(m=11\), the first parameter beyond the authors' stated verification range.

## Scope and proof status

This package does not prove or disprove existence of the asymptotic limit \(M_n/n^{3/2}\).

- Upper bound: transparent exhaustive verification of one explicit witness
- Lower bound: deterministic exhaustive enumeration using exact integer logic
- Optional cross-check: independent 0–1 MILP formulation
- Not included: a formally checkable DRAT/VeriPB proof certificate

## Attribution

Research direction and prompt engineering: **Curtis White**.  
AI mathematical collaborator: **GPT-5.6 Pro (OpenAI)**.

Preferred citation:

> Curtis White, with GPT-5.6 Pro, “The Antipodal Cut Code of \(K_{11}\) Has Covering Radius 19: A Counterexample to the Esmaeili–Zaghian Conjecture,” GitHub research artifact, 2026.
