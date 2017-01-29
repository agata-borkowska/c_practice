#include <stdio.h>
#include <stdlib.h>

FILE *input_file;

// Function to check if a given choice of a value conflicts with what's already on the board
int check_conflict(int cell, int value, int* board) {
	int x = cell % 9; // column
	int y = cell / 9; // row
	int i, j;
	int result = 1;

	// check row conflicts
	for (i = 0; i < 9; i++) {
		if (board[cell-x+i] == value) {
			result = 0;
			break;
		}
	}

	// check column conflicts
	for (i = 0; i < 9; i++) {
		if (board[x + 9*i] == value) {
			result = 0;
			break;
		}
	}

	// check small squares
	// work out which small square we're in
	int x2 = (x / 3) * 3;
	int y2 = (y / 3) * 3;
	// iterate over the cells in that square
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (board[x2 + i + (y2 + j) * 9] == value) {
				result = 0;
				break;
			}
		}
	}
	return result;
}

// printing board function
void print_board(int* board) {
	int i, j;
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			printf("%d", board[j + 9*i]);
		}
		printf("\n");
	}
	printf("\n");
}

// perform dfs
int dfs(int cell, int val, int* board) {
	int i = cell;
	if (i == 81) {
		printf("last cell\n");
		return 1; // we reached the last cell
	} else {
		int j;
		if (!board[i] && !check_conflict(i, val, board)) {
			// check that current cell isn't empty and we canput 
			// val in it. If not...
			return 0;
		} else {
			int board_val = board[i];
			if (!board[i]) {
				board[i] = val;
			}
			for (j = 1; j < 10; j++) {
				if (dfs(i+1, j, board)) {
					return 1;
				}
			}
			board[i] = board_val;
			return 0;
		}
	}	
	return 0;
}

int main(int argc, char *argv[]) {
	input_file = fopen(argv[1], "r");
	
	// check that we were given a file
	if (input_file == NULL) {
		printf("invalid file\n");
		return 1;
	}  
	
	int i = 0;
	int j;
	char buff[256];

	// read file and record what's on the board
	int *board = (int*) malloc(sizeof(int) * 81);
	  
	while(fgets(buff, sizeof(buff), input_file) && i < 9) {
		for (j = 0; j < 9; j++) {
			int x = buff[j] - '0';
			if (0 <= x && x < 10) {
				board[j + 9*i] = x;
			} else {
				board[j + 9*i] = 0;
			}
	 	}
		i++;
	}
	
	print_board(board);

	// perform dfs
	for (i = 1; i<10;i++) {
		if(dfs(0,i,board)) {
			print_board(board);
			break;
		}
	}
	//printf("%d\n", check_conflict(3,78, board));
	//printf("%d\n", check_conflict(7,78, board));	
	void free(void *board);
	return 0;

}
