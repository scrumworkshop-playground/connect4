#!/usr/bin/env python3
"""
Test script for Connect 4 AI

This script demonstrates various test cases for the Connect 4 AI.
"""

import subprocess
import sys

def test_ai(board_state, stone='O', description=""):
    """Test the AI with a given board state"""
    print(f"\n=== {description} ===")
    print("Board:")
    print(board_state)
    print(f"AI playing as: {stone}")
    
    try:
        result = subprocess.run(
            ['python3', 'connect4', stone],
            input=board_state,
            text=True,
            capture_output=True,
            timeout=5
        )
        
        if result.returncode == 0:
            move = result.stdout.strip()
            print(f"AI chose column: {move}")
        else:
            print(f"Error: {result.stderr}")
    except subprocess.TimeoutExpired:
        print("AI timed out")
    except Exception as e:
        print(f"Error running AI: {e}")

def main():
    # Test case 1: Example from README
    board1 = """- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - X - - -
- O X O X O X"""
    test_ai(board1, 'O', "Example from README")
    
    # Test case 2: Winning move for O
    board2 = """- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
O O O - X X X"""
    test_ai(board2, 'O', "Winning move for O")
    
    # Test case 3: Block opponent's win
    board3 = """- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
X X X - O O O"""
    test_ai(board3, 'O', "Block opponent's winning move")
    
    # Test case 4: Full board
    board4 = """X O X O X O X
O X O X O X O
X O X O X O X
O X O X O X O
X O X O X O X
O X O X O X O"""
    test_ai(board4, 'O', "Full board (should return -1)")
    
    # Test case 5: Empty board
    board5 = """- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -
- - - - - - -"""
    test_ai(board5, 'X', "Empty board (X starts)")

if __name__ == "__main__":
    main() 
