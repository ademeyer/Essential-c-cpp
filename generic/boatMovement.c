#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * water = true
 * land = false
 * game_matrix[row][col] → 1D equivalent: game_matrix_1D[row * cols + col] 
 */

bool helper(bool *game_matrix, int rows, int cols, int from_row,
                   int from_column, int to_row, int to_column, bool* visited)
{
        // base condition:
        // If out-of-balance
	int index = from_row * from_column + from_column;
        if(from_row == rows || from_column == cols 
                        || from_row < 0 || from_column < 0	
                        || !game_matrix[index] || visited[index]) 
		return false;
        
	// If we get lucky
        if(from_row == to_row && from_column == to_column) return true;
	
	// Mark that we have visited this
	visited[index] = true;

	// Recursively, we find ways in four directions
	const int dirs[][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	for(int i = 0; i < 4; ++i)
	{
		int nr = from_row + dirs[i][0];
		int nc = from_column + dirs[i][1];
		if(helper(game_matrix, rows, cols, nr, nc, to_row, to_column, visited))
			return true;
	}
	return false;
}

bool can_travel_to(bool *game_matrix, int rows, int cols, int from_row,
                   int from_column, int to_row, int to_column)
{ 
	bool* visited = malloc(sizeof(bool) * rows * cols);
	bool result = helper(game_matrix, rows, cols, from_row, from_column,
			to_row, to_column, visited);
	free(visited);
	return result;
}

#ifndef RunTests
int main()
{
    bool game_matrix[6][6] = {
        {false, true,  true,  false, false, false},
        {true,  true,  true,  false, false, false},
        {true,  true,  true,  true,  true,  true},
        {false, true,  true,  false, true,  true},
        {false, true,  true,  true,  false, true},
	{false, false, false, false, false, false},
    };
    printf("%d\n", can_travel_to((bool*) game_matrix, 6, 6, 3, 2, 2, 2)); // true, Valid move
    printf("%d\n", can_travel_to((bool*) game_matrix, 6, 6, 3, 2, 3, 4)); // false, Can't travel through land
    printf("%d\n", can_travel_to((bool*) game_matrix, 6, 6, 3, 2, 6, 2)); // false, Out of bounds
}
#endif

