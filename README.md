# Game of Life
_A rudimentary implementation of Conway's Game of Life with a specific initial configuration._

LIFE is an organism that lives in a discrete, two-dimensional world. This world is an array with each cell capable of holding one LIFE cell. Generations mark the passage of time. Each generation brings births and deaths to the LIFE community.

The births and deaths follow the set of rules that follow:
1. We define each cell to have eight __neighbor__ cells. The neighbors of a cell are the cell directly above, below, to the right, to the left, diagonally above to the right and left, and diagonally below to the right and left.
2. If an occupied cell has 0 or 1 neighbors, it dies of __loneliness.__ If an occupied cell has more than 3 neighbors, it dies of __overcrowding.__
3. If an empty cell has exactly three occupied neighbor cells, there is a __birth__ of a new cell to replace the empty cell.
4. Births and deaths are instantaneous, and occur at the changes of generation. A newborn cell cannot resurrect a cell that is dying, nor will a cell's death prevent the death of another, say, by reducing the population.

## Notes:
Some configurations grow from relatively small starting configurations, while others move across the region. A simple initial configuration is used here.

_Problem description taken from Walter Savitch's "Problem Solving in C++."_
