#!/bin/bash

# -1 error
#  0 valid turn and not win or draw
#  1 win
#  2 draw
#
#  $1 = playerX and turns first
#  $2 = playerO

VALIDATOR=./connect4_engine

if [ $# -lt 2 ]; then
	echo "Not enough params"
	echo "$0 playerX playerO <gui-file-location>"
	exit 255
fi

PLAYERX=$1
PLAYERO=$2

tfirst=0
tsecond=1

GUI_BOARD_FILE="$3"

test -x $VALIDATOR || {
	echo "$VALIDATOR is not executable."
	exit 255
}
test -x $PLAYERX || {
	echo "$PLAYERX is not executable."
	exit 255
}
test -x $PLAYERO || {
	echo "$PLAYERO is not executable."
	exit 255
}

while true; do
	TURN=`$PLAYERX < t$tfirst`
	echo "$PLAYERX made turn in column $TURN"

	$VALIDATOR $TURN 'X' < t$tfirst > t$tsecond
	ret=$?
	if [ $ret = 1 ]; then
		test -z "$GUI_BOARD_FILE" || cp t$tsecond $GUI_BOARD_FILE
		echo "$PLAYERX has won"
		cat t$tsecond
		exit 1;
	elif [ $ret = 2 ]; then
		test -z "$GUI_BOARD_FILE" || cp t$tsecond $GUI_BOARD_FILE
		echo "DRAW!"
		exit 2;
	elif [ $ret != 0 ]; then
		echo "$PLAYERX made invalid turn";
		exit 255;
	fi
	echo "Player X $PLAYERX has played column: $TURN"
	echo "Result:"
	cat t$tsecond

	if [ -n "$GUI_BOARD_FILE" ]; then
		cp t$tsecond $GUI_BOARD_FILE

		echo "Press ENTER to continue"
		read
	fi

	TURN=`$PLAYERO < t$tsecond`
	echo "$PLAYERO made turn in column $TURN"

	tfirst=$((tfirst+2))

	# 1 2
	$VALIDATOR $TURN 'O' < t$tsecond > t$tfirst
	ret=$?

	if [ $ret = 1 ]; then
		test -z "$GUI_BOARD_FILE" || cp t$tfirst $GUI_BOARD_FILE
		echo "$PLAYERO has won!"
		cat t$tfirst
		exit 1;
	elif [ $ret = 2 ]; then
		test -z "$GUI_BOARD_FILE" || cp t$tfirst $GUI_BOARD_FILE
		echo "DRAW!"
		exit 2;
	elif [ $ret != 0 ]; then
		echo "$PLAYERO made invalid turn";
		exit 255;
	fi
	echo "Player O $PLAYERO has played column: $TURN"
	echo "Result:"
	cat t$tfirst

	if [ -n "$GUI_BOARD_FILE" ]; then
		cp t$tfirst $GUI_BOARD_FILE

		echo "Press ENTER to continue"
		read
	fi

	tsecond=$((tfirst+1))
done
