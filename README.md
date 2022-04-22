# La FFT et arithmétique rapide

Ce projet consiste à implémenter en C et à comparer différents algorithmes de multiplication et d'inversion de matrice. Pour des raisons de simplicité, l'implémentation se fera uniquement avec des matrices carrées de taille 2^n. Finalement, toute opération arithmétique se fera dans le coprs fini ℤ/pℤ avec p un nombre premier ne dépassant pas les 30 bits. Il est vivement recommandé de choisir un nombre premier p assez élevé afin d'obtenir (avec grande probabilité) des matrices inversibles. En effet, le programme part du principe que les matrices sont inversibles (néanmoins, il est possible de vérifier si c'est vraiment le cas).

## Les algorithmes implémentés

- Décomposition LU (méthode Doolittle)

- Résolution de système linéaire avec la décomposition LU

- Inversion de matrice avec la décomposition LU

- Inversion de matrice avec l'algorithme de Strassen

- Produit matriciel avec l'algorithme de Strassen

## Lancement

Pour créer l'exécutable, il suffit d'utiliser la commande `make` et l'exécutable `project.out` sera
généré. Pour lancer l'application, il suffit de lancer l'exécutable.

**ATTENTION** : un compilateur supportant C99 est nécessaire (de préférence GCC car certains flags d'optimisations sont activés).

## Options

Voici les options disponibles à l'utilisateur lors de l'exécution :

```bash
--prime p : compute in the prime finite field ℤ/pℤ. [default 65537])
--size n : size of the square matrix (have to be a power of 2). [default 4])
--demo d : execute a demo using all the functions : 0 (false). [default true, i.e, != 0]);
--test t : measure the execution time and export the result into a CSV format : 0 (false). [default 0, i.e, == 0]
--limit l : to set the maximum size of matrices during the benchmark test such as n = 2^l (have to be greater than 0). [default 10]
```

Un exemple de commande :

```bash
./project.out --size 4 --demo 1 --test 1 --limit 5
```

## Benchmark

Lors des benchmarks, les résultats sont exportés au format CSV dans le dossier `benchmark`. Pour obtenir les plots des résultats, il suffit d'exécuter le script `plot.py` pour obtenir les images dans le dossier `img`.

**ATTENTION** : le package matplotlib est nécessaire.

## Sources

### Inversion modulaire

<https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm>

### Décomposition LU

<https://en.wikipedia.org/wiki/LU_decomposition>
<https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/doolittle.pdf>
<https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/INT-APP/CURVE-linear-system.html>

### Strassen

<https://specfun.inria.fr/bostan/mpri/DenseLinAlg.pdf>

## Auteurs

- Hamza RAIS
- Tahar AMAIRI
