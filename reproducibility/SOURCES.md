# Source provenance

## MathOverflow problem

Paata Ivanisvili, “Min-max of a quadratic form of plus-minus ones,” posted January 16, 2022:

- https://mathoverflow.net/questions/413935/min-max-of-a-quadratic-form-of-plus-minus-ones

The post asks whether \(M_n/n^{3/2}\) converges and explicitly says that numerical computations or isolated upper/lower bounds are not the desired answer unless they materially indicate nonexistence.

## Exact coding-theory predecessor

M. Esmaeili and A. Zaghian, “On covering radius of a family of codes \(C_m\cup(1+C_m)\) with maximum distance between \(C_m\) and \(1+C_m\),” *Utilitas Mathematica* 78 (2009), 151–158.

Official volume record:

- https://combinatorialpress.com/um/vol78/

Accessible abstract:

- https://www.researchgate.net/publication/266941646_On_covering_radius_of_a_family_of_codes_C_m_1C_m_with_maximum_distance_between_C_m_and_1C_m

The abstract defines \(C_m\) using all nonzero binary length-\(m\), weight-two columns and studies \(C_m^\perp\cup(\mathbf1+C_m^\perp)\). It conjectures

\[
\rho\!\left(C_m^\perp\cup(\mathbf1+C_m^\perp)\right)=\rho(C_{m-1}^\perp),\qquad m\ge7,
\]

and reports verification for \(7\le m\le10\).

## Why the code is exactly the MathOverflow object

Index the weight-two columns by the edges \(\{i,j\}\) of \(K_m\). Row \(i\) of the parity-check matrix is the incidence vector of the star at vertex \(i\). Therefore the row span, namely \(C_m^\perp\), is the binary cut/cocycle code of \(K_m\). Adjoining the all-one coset adds the complements of all cuts. This is precisely the operation induced by the absolute value in the quadratic minimax problem.

## Novelty search status

Title, author, exact-conjecture, and parameter-value searches did not locate an indexed erratum, correction, or prior report of the parameter-11 failure. That is a negative search result, not proof of novelty.
