# The Antipodal Cut Code of \(K_{11}\) Has Covering Radius 19

## A counterexample to the Esmaeili–Zaghian conjecture

**Curtis White — research lead and prompt engineer**  
**GPT-5.6 Pro (OpenAI) — AI mathematical collaborator**

This repository contains a reproducible computer-assisted proof of the exact finite result

\[
M_{11}=17,
\]

where

\[
M_n=\min_{a_{ij}\in\{\pm1\}}
\max_{x_i\in\{\pm1\}}
\left|\sum_{1\le i<j\le n}a_{ij}x_ix_j\right|.
\]

Equivalently, the antipodal cut code

\[
\widehat C_{11}=C_{\mathrm{cut}}(K_{11})\cup
\bigl(\mathbf 1+C_{\mathrm{cut}}(K_{11})\bigr)
\]

has binary Hamming covering radius

\[
\rho(\widehat C_{11})=19.
\]

Esmaeili and Zaghian's 2009 conjecture predicts radius 20 at this parameter. The result here therefore gives a counterexample at \(m=11\), the first parameter beyond the authors' reported verification range \(7\le m\le10\).

> **Scope:** This is an exact finite theorem. It does **not** settle whether \(M_n/n^{3/2}\) converges as \(n\to\infty\), the question asked by Paata Ivanisvili on MathOverflow.

## Verification

The proof package provides three independent layers:

1. An explicit \(11\times11\) sign-matrix witness, exhaustively checked over all spin configurations modulo global symmetry, proves \(M_{11}\le17\).
2. A deterministic, symmetry-reduced C++ enumeration proves that no signing can achieve threshold 15, hence \(M_{11}\ge17\) by parity.
3. An independent 0–1 MILP formulation using SciPy/HiGHS cross-checks the lower bound.

All primary witness and enumeration calculations use exact integer arithmetic.

Start with [the reproducibility README](reproducibility/README.md), then run:

```bash
cd reproducibility
chmod +x run_all.sh
./run_all.sh
```

The original lower-bound enumeration recorded:

```text
TOTAL nodes=50778686 complete=936720 pass4=936720 passall=0
```

## Repository contents

- [`reproducibility/CLAIM.md`](reproducibility/CLAIM.md): concise theorem statement
- [`reproducibility/README.md`](reproducibility/README.md): proof reduction and reproduction instructions
- [`reproducibility/m11_witness.json`](reproducibility/m11_witness.json): explicit upper-bound witness
- [`reproducibility/verify_witness.py`](reproducibility/verify_witness.py): exhaustive witness checker
- [`reproducibility/lower_bound_enumerator.cpp`](reproducibility/lower_bound_enumerator.cpp): exact lower-bound enumerator
- [`reproducibility/milp_crosscheck.py`](reproducibility/milp_crosscheck.py): independent MILP cross-check
- [`reproducibility/logs/`](reproducibility/logs): bundled output logs
- [`reproducibility/SHA256SUMS`](reproducibility/SHA256SUMS): integrity manifest
- [`reproducibility/SOURCES.md`](reproducibility/SOURCES.md): provenance and literature links

## Citation

Please cite this work as:

> **Curtis White, with GPT-5.6 Pro.** “The Antipodal Cut Code of \(K_{11}\) Has Covering Radius 19: A Counterexample to the Esmaeili–Zaghian Conjecture.” GitHub research artifact, 2026.

A machine-readable citation is provided in [`CITATION.cff`](CITATION.cff).

## Contribution statement

Curtis White selected and directed the research problem, designed the prompting and agent workflow, drove the literature and provenance investigation, prioritized uncertainty resolution, and commissioned the final verification package. GPT-5.6 Pro performed AI-assisted literature synthesis, mathematical reformulation, proof search, computational construction, exact verification design, and preparation of the reproducibility artifacts. The result should be treated as computer-assisted mathematics and independently reviewed before journal publication.

## Prior work and motivating question

- Paata Ivanisvili, “Min-max of a quadratic form of plus-minus ones,” MathOverflow, 2022.
- M. Esmaeili and A. Zaghian, “On covering radius of a family of codes \(C_m\cup(1+C_m)\) with maximum distance between \(C_m\) and \(1+C_m\),” *Utilitas Mathematica* 78 (2009), 151–158.

Full links and the notation concordance appear in [`reproducibility/SOURCES.md`](reproducibility/SOURCES.md).

## License

Code is released under the MIT License. Documentation, proof exposition, data, and computational artifacts are released under CC BY 4.0. See [`LICENSE.md`](LICENSE.md).
