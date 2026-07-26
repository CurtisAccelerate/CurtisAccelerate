# Certified finite result

Let

\[
M_n=\min_{a_{ij}\in\{\pm1\}}\max_{x_i\in\{\pm1\}}
\left|\sum_{1\le i<j\le n}a_{ij}x_ix_j\right|.
\]

This package gives a reproducible computer-assisted proof that

\[
\boxed{M_{11}=17}.
\]

Equivalently, if

\[
\widehat C_{11}=C_{\mathrm{cut}}(K_{11})\cup
\bigl(\mathbf 1+C_{\mathrm{cut}}(K_{11})\bigr),
\]

then its binary Hamming covering radius is

\[
\boxed{\rho(\widehat C_{11})=19}.
\]

The 2009 Esmaeili--Zaghian conjecture predicts radius 20 at this parameter, so
this is a counterexample at the first parameter outside their verified range
\(7\le m\le10\).

This does **not** settle whether \(M_n/n^{3/2}\) has a limit.
