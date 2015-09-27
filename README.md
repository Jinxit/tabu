# Tabu search

Based on the papers by F. Glover:
* http://www.iro.umontreal.ca/~dift6751/paper_glover_ts_1.pdf
* http://www.iro.umontreal.ca/~dift6751/paper_glover_ts_2.pdf

This version will attempt to maximize the given `fitness` function.
It will select a starting point using the `random` function, and
find neighbours using `neighbours`.

A simple example is given in [main.cpp](../blob/main.cpp)