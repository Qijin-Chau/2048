// purpose: 4-row implementation of 2048
// by: Qijin Chau
// date: 3/13/19
// proj1c 2048
//

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

const string QUIT = "q";
const string UP = "w", DOWN = "s", LEFT = "a", RIGHT = "d";
const string EMPTY = "-", TWO = "2", FOUR = "4";
const int ROWS = 4, COLS = 4;

void play();
void start_grid(string grid[ROWS][COLS], int score);
void display_grid(string grid[ROWS][COLS], int score);
int random_index(int x);
int random_number();
void move_left(string grid[ROWS][COLS]);
void move_right(string grid[ROWS][COLS]);
void move_up(string grid[ROWS][COLS]);
void move_down(string grid[ROWS][COLS]);
void combine_left(string grid[ROWS][COLS]);
void combine_right(string grid[ROWS][COLS]);
void combine_up(string grid[ROWS][COLS]);
void combine_down(string grid[ROWS][COLS]);
int score_horizontal(string grid[ROWS][COLS], int score);
int score_vertical(string grid[ROWS][COLS], int score);
void shift_left(string grid[ROWS][COLS], int score);
void shift_right(string grid[ROWS][COLS], int score);
void shift_up(string grid[ROWS][COLS], int score);
void shift_down(string grid[ROWS][COLS], int score);
int check_max_tile(string grid[ROWS][COLS]);
void end_game_check(string grid[ROWS][COLS], int score);
int check_full(string grid[ROWS][COLS]);
int no_new_tile(string grid[ROWS][COLS]);
void spawn_tile(string grid[ROWS][COLS]);
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);

int main()
{
    play();
    return 0;
}

/* play
 * Incorporates all the functions to run a 4-row imitation of the game 2048
 * Displays the grid after each movement and an "end screen" once the
 * grid is full and no more moves can be made
 * Instructions: "a" to move left, "d" to move right,
                 "w" to move up, "s" to move down,  and "q" to quit
 */
void play()
{
    int flag = 0, score = 0;
    string direction;
    srand(time(NULL));

    cout << "Starting game!" << endl;    
    string grid[4][4] = {
                         {"-", "-", "-", "-"},
                         {"-", "-", "-", "-"},
                         {"-", "-", "-", "-"},
                         {"-", "-", "-", "-"}
                                             };
    start_grid(grid, score);

    while (flag == 0)
    {
        cin  >> direction;
	      if (direction == QUIT) {
		    cout << "Game over! Your score is " << score << "." << endl;
	          flag = 1;
            }
            
            if (direction != LEFT && direction != RIGHT && 
                direction != UP && direction != DOWN && direction != QUIT) {
	          cout << "Command not recognized. Please try again." << endl;
            } 
            
            if (direction == LEFT) {
		    move_left(grid);
		    score = score_horizontal(grid, score);
	          shift_left(grid, score);
	          flag = no_new_tile(grid);
            } else if (direction == RIGHT) {
		    move_right(grid);
		    score = score_horizontal(grid, score);
	          shift_right(grid, score);
	          flag = no_new_tile(grid);
	      } else if (direction == UP) {
		    move_up(grid);
		    score = score_vertical(grid, score);
	          shift_up(grid, score);
	          flag = no_new_tile(grid);
            } else if (direction == DOWN) {
		    move_down(grid);
		    score = score_vertical(grid, score);
	          shift_down(grid, score);
	          flag = no_new_tile(grid);
            }

    }
}

/* start_grid
 * Takes in a 2-D string array and an integer. 
 * Changes two random elements in the array into a "2".
 * Calls the display_grid function to output/display the grid.
 */
void start_grid(string grid[ROWS][COLS], int score)
{
    int i, j;

    i = random_index(4);
    j = random_index(4);
    grid[i][j] = TWO;
    
    do
    {
        i = random_index(4);
        j = random_index(4);
    } while (grid[i][j] != EMPTY);
    
    grid[i][j] = TWO;
    display_grid(grid, score);
}

/* display_grid
 * Takes in a 2-D string array and an integer.
 * Outputs the current score also 
 * uses the print_padded_string function to
 * print out the string array with the proper paddings.
 */
void display_grid(string grid[ROWS][COLS], int score)
{
    cout << "Current score: " << score << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<4; j++) {
            print_padded_string(grid[i][j]);
        }
        cout << "" << endl;
    }
}   

/* random_index
 * Takes in an integer. 
 * Returns a random integer from 0 to one less
 * of the integer value of the parameter (x).
 */
int random_index(int x)
{
    int index = rand() % x + 0;
    return index;
}

/* random_number
 * Takes no parameters. 
 * Returns a random integer from 1 to 10.
 */
int random_number()
{
    int number = rand() % 10 + 1;
    return number;
}

/* move_left
 * Takes in a 2-D string array. 
 * Shifts all the elements that are not empty
 * to their left most index of their row in the array.
 */ 
void move_left(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (grid[i][j] == "-") {
                for (int k=j+1; k<4; k++) {
	              if (grid[i][k] != EMPTY) {
	              grid[i][j] = grid[i][k];
	              grid[i][k] = EMPTY;
	              k = 4;
	              }
	          }
            }
	  }   
    }
}

/* move_right
 * Takes in a 2-D string array. 
 * Shifts all the elements that are not empty
 * to their right most index of their row in the array.
 */
void move_right(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=3; j>-1; j--) {
	      if (grid[i][j] == EMPTY) {
	          for (int k=j-1; k>-1; k--) {
	              if (grid[i][k] != EMPTY) {
	              grid[i][j] = grid[i][k];
	              grid[i][k] = EMPTY;
	              k = -1;
	              }
	          }
	      }
        }
    }
}

/* move_up
 * Takes in a 2-D string array.
 * Shifts all the elements that are not empty
 * to their up most index of their column in the array.
 */
void move_up(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (grid[j][i] == EMPTY) {
	          for (int k=j+1; k<4; k++) {
	              if (grid[k][i] != EMPTY) {
	                  grid[j][i] = grid[k][i];
	                  grid[k][i] = EMPTY;
	                  k = 4;
			  }
		    }
		}
	  }
    }
}

/* move_down
 * Takes in a 2-D string array.
 * Shifts all the elements that are not empty
 * to their bottom most index of their column in the array.
 */
void move_down(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=3; j>-1; j--) {
            if (grid[j][i] == EMPTY) {
	          for (int k=j-1; k>-1; k--) {
	              if (grid[k][i] != EMPTY) {
	                  grid[j][i] = grid[k][i];
	                  grid[k][i] = EMPTY;
	                  k = -1;
		        }
		    }  
	      }
	  }
    }
}

/* combine_left
 * Takes in a 2-D string array.
 * Checks for equivalent adjacent elements in all the rows of the 
 * 2-D array. Uses the string2int and int2string functions to essentially
 * "add up" adjacent strings that are equaivalent. combine_left places 
 * the sum in the left index of the two equivalent strings while the
 * right index becomes empty.
 */
void combine_left(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (grid[i][j] != EMPTY && grid[i][j] == grid[i][j+1]) {
	          int index_int = string2int(grid[i][j]);
	          index_int = 2 * index_int; 
	          string index_string = int2string(index_int);
                grid[i][j] = index_string;
                grid[i][j+1] = EMPTY;
	      }
	  }
    }
}

/* combine_right
 * Takes in a 2-D string array.
 * Checks for equivalent adjacent elements in all the rows of the 
 * 2-D array. Uses the string2int and int2string functions to essentially
 * "add up" adjacent strings that are equaivalent. combine_right places 
 * the sum in the right index of the two equivalent strings while the
 * left index becomes empty.
 */
void combine_right(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=3; j>0; j--) {
            if (grid[i][j] != EMPTY && grid[i][j] == grid[i][j-1]) {
	          int index_int = string2int(grid[i][j]);
	          index_int = 2 * index_int;
	          string index_string = int2string(index_int);
	          grid[i][j] = index_string;
	          grid[i][j-1] = EMPTY;
	      }
	  }
    }
}
        
/* combine_up
 * Takes in a 2-D string array.
 * Checks for equivalent adjacent elements in all the columns of the 
 * 2-D array. Uses the string2int and int2string functions to essentially
 * "add up" adjacent strings that are equaivalent. combine_up places 
 * the sum in the top index of the two equivalent strings while the
 * lower index becomes empty.
 */
void combine_up(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (grid[j][i] != EMPTY && grid[j][i] == grid[j+1][i]) {
	          int index_int = string2int(grid[j][i]);
	          index_int = 2 * index_int;
	          string index_string = int2string(index_int);
	          grid[j][i] = index_string;
	          grid[j+1][i] = EMPTY;
	      }
	  }
    }
}

/* combine_down
 * Takes in a 2-D string array.
 * Checks for equivalent adjacent elements in all the columns of the 
 * 2-D array. Uses the string2int and int2string functions to essentially
 * "add up" adjacent strings that are equaivalent. combine_down places 
 * the sum in the bottom index of the two equivalent strings while the
 * upper index becomes empty.
 */
void combine_down(string grid[ROWS][COLS])
{
    for (int i=0; i<4; i++) {
        for (int j=3; j>0; j--) {
            if (grid[j][i] != EMPTY && grid[j][i] == grid[j-1][i]) {
	          int index_int = string2int(grid[j][i]);
	          index_int = 2 * index_int;
	          string index_string = int2string(index_int);
	          grid[j][i] = index_string;
	          grid[j-1][i] = EMPTY;
	      }
	  }
    }
}

/* score_horizontal
 * Takes in a 2-D string array and an integer.
 * Checks for equivalent horizontally adjacent elements in all the rows 
 * of the 2-D array. Uses the string2int function to convert one of the 
 * equivalent strings into a integer. The integer is then doubled
 * and added onto the integer parameter called score. 
 * score is then returned as an integer.
 */
int score_horizontal(string grid[ROWS][COLS], int score)
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (grid[i][j] != EMPTY && grid[i][j] == grid[i][j+1]) {
	        int index_int = string2int(grid[i][j]);
	        index_int = 2 * index_int;
                score = score + index_int;
	    }
	}
    }
    return score;
}
 
/* score_vertical
 * Takes in a 2-D string array and an integer.
 * Checks for equivalent vertically adjacent elements in all the columns 
 * of the 2-D array. Uses the string2int function to convert one of the 
 * equivalent strings into a integer. The integer is then doubled
 * and added onto the integer parameter called score. 
 * score is then returned as an integer.
 */
int score_vertical(string grid[ROWS][COLS], int score)
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (grid[j][i] != EMPTY && grid[j][i] == grid[j+1][i]) {
	          int index_int = string2int(grid[j][i]);
	          index_int = 2 * index_int;
                score = score + index_int;
	      }
	  }
    }
    return score;
}

/* shift_left
 * Takes in a 2-D string array and an integer. 
 * Calls a bunch of functions that essentially accounts 
 * for a total leftward directional shift of the board.
 */ 
void shift_left(string grid[ROWS][COLS], int score)
{
    combine_left(grid);
    move_left(grid);
    spawn_tile(grid);
    display_grid(grid, score);
    end_game_check(grid, score);
}

/* shift_left
 * Takes in a 2-D string array and an integer. 
 * Calls a bunch of functions that essentially accounts 
 * for a total rightward directional shift of the board.
 */
void shift_right(string grid[ROWS][COLS], int score)
{
    combine_right(grid);
    move_right(grid);
    spawn_tile(grid);
    display_grid(grid, score);
    end_game_check(grid, score);
}

/* shift_up
 * Takes in a 2-D string array and an integer.
 * Calls a bunch of functions that essentially accounts
 * for a total upward directional shift of the board.
 */
void shift_up(string grid[ROWS][COLS], int score)
{
    combine_up(grid);
    move_up(grid);
    spawn_tile(grid);
    display_grid(grid, score);
    end_game_check(grid, score);
}

/* shift_down
 * Takes in a 2-D string array and an integer.
 * Calls a bunch of functions that essentially accounts
 * for a total downward directional shift of the board.
 */
void shift_down(string grid[ROWS][COLS], int score)
{
    combine_down(grid);
    move_down(grid);
    spawn_tile(grid);
    display_grid(grid, score);
    end_game_check(grid, score);
}

/* check_max_tile
 * Takes in a 2-D string array.
 * Returns the maximum integer value of all the strings in the array.
 */
int check_max_tile(string grid[ROWS][COLS])
{
    int max_tile = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
	      int tile_num = string2int(grid[i][j]);
	          if (tile_num > max_tile) {
	              max_tile = tile_num;
		    }
	  }
    }
    return max_tile;
}

/* end_game_check
 * Takes in a 2-D string array and an integer. 
 * Calls the no_new_tile function and sets flag equal to the returned 
 * value. If the flag returned equals 1 and the max tile is less than 2048
 * then game over and the score will be displayed. Else a congrats will
 * be displayed along with the value of the maximum tile.
 */  
void end_game_check(string grid[ROWS][COLS], int score)
{
    int flag = no_new_tile(grid);
    if (flag == 1) {
        int max_tile = check_max_tile(grid);
        
  	  if  (max_tile < 2048) {
	      cout << "Game over! Your score is " << score << "." << endl;
	  } else {
	      cout << "Game over! Congrats you reached 2048!" << endl;   
            cout << "Your score is " << score << "." << endl;
            cout << "Your maximum tile is " << max_tile << "." << endl;
	  }
    }

}

/* check_full
 * Takes in a 2-D string array. 
 * Goes through each element in the array.
 * If any element is empty then the integer 0 is returned, 
 * else the integer 1 is returned.
 */
int check_full(string grid[ROWS][COLS])
{
    int flag = 1;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (grid[i][j] == EMPTY) {
	          flag = 0;
		}
	  }
    }
    return flag;
}

/* no_new_tile
 * Takes in a 2-D string array. 
 * Returns the integer 1 if the grid is full and no adjacent 
 * tiles are equivalent either horizontally nor vertically. 
 * Returns the integer 0 if the grid is not full or if there is
 * at least one pair of adjacent tiles that are equivalent.
 */ 
int no_new_tile(string grid[ROWS][COLS])
{
    int i, j;
    int flag = check_full(grid);
    
    if (flag == 1) {
        for (i=0; i<4; i++) {
	      for (j=0; j<3; j++) { 
                if (grid[i][j] == grid[i][j+1]) {
	              flag = 0;
                    i = 4;
		    }
	      }
	  }
    }
    
    if (flag == 1) {
        for (i=0; i<3; i++) {
	      for (j=0; j<4; j++) {
	          if (grid[i][j] == grid[i+1][j]) {
	              flag = 0;
	              i = 3;
		    }
	      }
	  }
    }
    return flag;
}

/* spawn_tile
 * Takes in a 2-D string array. 
 * Spawns one index on the board by changing one empty index 
 * into a "2" with a 90% chance or a "4" with a 10% chance.
 */
void spawn_tile(string grid[ROWS][COLS])
{
    int i, j, k, full; 
    full = check_full(grid);
    if (full == 0) {
        do
        {
	      k = random_number();
            i = random_index(4);
            j = random_index(4);
        } while (grid[i][j] != EMPTY);
        
            if (k < 10) {
                grid[i][j] = TWO;
            } 
            else {
	          grid[i][j] = FOUR;
            }
    }
}

/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical.
 */
int string2int(string s)
{
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
    throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* int2string
 * Converts an int to string.
 * Returns the string form of the given int.
 */
string int2string(int num)
{
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}

/* print_padded_string
 * Print a string (persumably an int in the form of a string) with
 * right paddings of up to 5 spaces.
 */
void print_padded_string(string s)
{
    printf("%-6s", s.c_str());
}
