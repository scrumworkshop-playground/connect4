 # Connect 4

This is a simple terminal-based Connect 4 game for two players (X and O) on a 6 rows and 7 columns board.

## How to Run

```
./connect4 <STONE>
```
- `<STONE>` is either `X` or `O` and specifies which stone the AI will play for this turn.
- If `<STONE>` is omitted, the AI defaults to `O`.

## Protocol for Exchanging Turns

### Board Representation
- The board is a 6-row by 7-column grid.
- Each cell is represented by a single character:
  - `-` (dash): empty cell
  - `X`: cell occupied by player X
  - `O`: cell occupied by player O
- Each row is printed on a separate line.
- Cells in a row are separated by a single space.
- No extra characters (such as `|` or prompts) are present in the input.

**Example Board:**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X
```

### Turn Exchange

#### 1. Input
- The program receives the current board state as described above, via standard input (stdin).
- The board must always have 6 rows and 7 columns, formatted as above.

#### 2. Command Line Argument
- The program is invoked as:
  `./connect4 <STONE>`
- `<STONE>` is either `X` or `O` and specifies which stone the AI will play for this turn.
- If `<STONE>` is omitted, the AI defaults to `O`.

#### 3. AIs Move
- The program parses the board and determines the AI's move using its strategy.
- The AI always plays a single move for the specified stone.

#### 4. Output
- The program outputs a single integer to standard output (stdout):
  - The column number (1-7, inclusive) where the AI will play its stone.
  - If there are no valid moves, the program outputs `-1`.
- No other output is produced.

### Example Turn Exchange

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
./connect4 O
```

**Output (stdout):**
```
1
```
*(Assuming the AI chose to play in the first column)*

**New Board State:**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
O O X O X O X
```

## How to Play
- Players take turns entering the column number (1-7) to drop their piece.
- The first player is X, the second is O.
- The game ends when a player connects four in a row (horizontally, vertically, or diagonally) or the board is full (draw). 
