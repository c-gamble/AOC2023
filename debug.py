grid = [list(line.strip()) for line in open('/Users/coopergamble/code/comps/aoc/2023/Day 14/test.txt', 'r')]
ROWS = len(grid)
COLS = len(grid[0])

def tilt(grid):
    new_grid = []
    for row in grid:
        new_row = []
        for i in range(COLS):
            if row[i] == '#':
                new_row.append('#')
            else:
                new_row.append(".")
        new_grid.append(new_row)
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "O":
                row_up = r
                while row_up >= 0 and new_grid[row_up][c] == ".":
                    row_up -= 1
                new_grid[row_up+1][c] = "O"
    return new_grid

def computeWeight(grid):
    total = 0
    for i, row in enumerate(reversed(grid), 1):
        total += i * row.count("O")
    return total

def rotateGrid(grid):
    grid = [list(row) for row in zip(*grid)]
    return [row[::-1] for row in grid]

def stringify(grid):
    return "".join(["".join(row) for row in grid])


def cycle(grid):
    for _ in range(4):
        grid = tilt(grid)
        grid = rotateGrid(grid)
    return grid


def findCycle(grid):
    GRIDS = dict()

    i = 1
    while True:
        grid = cycle(grid)
        hash = stringify(grid)

        if hash in GRIDS:
            cycle_length = i - GRIDS[hash]
            return (grid, i, cycle_length)
        else:
            GRIDS[hash] = i
            i += 1

def finishCycles(grid, spin_idx, cycle_length):
    spins_remaining = 1_000_000_000 - spin_idx
    full_cycles = spins_remaining // cycle_length
    spins_remaining -= full_cycles * cycle_length

    while spins_remaining:
        grid = cycle(grid)
        spins_remaining -= 1
    
    return grid

print("\n".join(["".join(row) for row in grid]))
grid = rotateGrid(grid)
print()
print("\n".join(["".join(row) for row in grid]))

grid, spin_idx, cycle_length = findCycle(grid)
print(spin_idx, cycle_length)
grid = finishCycles(grid, spin_idx, cycle_length)


print(computeWeight(grid))