# Connect 4 Engine (Validator)

This program validates and applies a move in a Connect 4 game. It checks the validity of the board and the move, applies the move, and determines if the move results in a win, draw, or a valid continuation.

## Compilation

```
gcc -o connect4_engine connect4_engine.c
```

## Usage

```
./connect4_engine <COLUMN> <STONE>
```
- `<COLUMN>`: The column number (1-7) where the player wants to place their stone.
- `<STONE>`: The stone character, either `X` or `O`, representing the player making the move.

The program reads the current board state from standard input.

## Input Format
- The board is a 6-row by 7-column grid.
- Each cell is represented by a single character:
  - `-` (dash): empty cell
  - `X`: cell occupied by player X
  - `O`: cell occupied by player O
- Each row is printed on a separate line.
- Cells in a row are separated by a single space.

**Example Input:**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X
```

## Output
- If the board or move is invalid, prints `INVALID`.
- If the move is valid and not a win or draw, prints the new board state.
- If the move is a winning move, prints the new board state.
- If the move results in a draw (board is full), prints `DRAW` and the new board state.

## Return Codes
- `-1`: Invalid input board or move.
- `0`: Valid board and move, not a win or draw.
- `1`: The move was a winning move.
- `2`: The move resulted in a draw (board is full).

## Example

**Input (stdin):**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X
```

**Command:**
```
./connect4_engine 1 O < input-board-in-file
```

**Output (stdout):**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
O O X O X O X
```

**Return code:**
```
0
``` 
