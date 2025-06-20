# Python Connect 4 AI

This is a Python implementation of a Connect 4 AI that follows the protocol specified in the [main repository](https://github.com/scrumworkshop-playground/connect4).

## Features

- **Smart Strategy**: The AI uses heuristics to make intelligent moves:
  - Prioritizes winning moves
  - Blocks opponent's winning moves
  - Prefers center columns for better positioning
  - Counts potential threats and opportunities
- **Protocol Compliant**: Follows the exact input/output format specified
- **Error Handling**: Gracefully handles invalid inputs and edge cases

## Usage

### Basic Usage

```bash
python3 connect4.py [STONE]
```

- `STONE`: Either `X` or `O` (optional, defaults to `O`)
- The program reads the board state from STDIN
- Outputs a single column number (1-7) or -1 if no valid moves

### Input Format

The board must be provided as 6 rows × 7 columns via STDIN:
- `-` represents an empty cell
- `X` represents a cell occupied by player X  
- `O` represents a cell occupied by player O
- Each row on a separate line
- Cells separated by single spaces

### Example

**Input:**
```
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X
```

**Command:**
```bash
echo "- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X" | python3 connect4.py O
```

**Output:**
```
4
```

## AI Strategy

The AI evaluates moves using the following criteria:

1. **Winning Moves** (Priority: Highest): If the AI can win in one move, it will play that move
2. **Blocking Moves** (Priority: High): If the opponent can win in their next move, the AI will block it
3. **Center Preference** (Priority: Medium): Prefers playing in center columns for better positioning
4. **Threat Creation** (Priority: Medium): Favors moves that create multiple winning opportunities

## Testing

Run the test suite to verify functionality:

```bash
python3 test_connect4.py
```

This will test various scenarios including:
- Example from the main README
- Winning moves
- Blocking opponent wins
- Full board handling
- Empty board scenarios

## Files

- `connect4.py`: Main AI implementation
- `test_connect4.py`: Test suite with various scenarios
- `PYTHON_README.md`: This documentation

## Requirements

- Python 3.6 or higher
- No external dependencies (uses only standard library)

## License

This implementation follows the same terms as the original repository. 
