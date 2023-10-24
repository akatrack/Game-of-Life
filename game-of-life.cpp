#include <iostream>
const int ROWS(40), COLUMNS(20), BIRTH(3), OVERCROWDING(4), LONELINESS(1);

void init_config(char life_world[][ROWS]);
//Sets the initial configuration of the array life_world.
void generation(char life_world[][ROWS]);
//Precondition: The array life_world is filled with the initial configuration.
//Postcondition: Cells are modified and marked with births and deaths
//in accordance with the rules of the Game of Life.
void set_config(char life_world[][ROWS], int& column);
//Precondition: Cells have already been marked for birth or death
//in accordance with the rules of Life.
//Postcondition: cells marked for birth are configured to the live state,
//and cells marked for death are configured to the dead state.
void display(const char life_world[][ROWS]);
//Precondition: The appropriate configuration of the array life_world
//has been determined for the generation to be displayed.
//Postcondition: The life_world array is displayed as-is on screen.
void prompt(char& nxt_gen);
//Prompts the user whether to produce the next generation
//of Life, or to quit the program.
void chk_nbrs(char life_world[][ROWS], int& column);
//Counter the number of neighbors of cells in L[i][k],
//for 0 < k < ROWS and 0 < i < COLUMNS.
//Marks cells to be birthed or killed of loneliness or overcrowding.
void chk_nbr_h(char life_world[][ROWS], int& column);
//Counts the number of neighbors of cells in L[i][k],
//for 0 < k < COLUMNS.
//Marks cells to be birthed or killed of loneliness or overcrowding.
void chk_nbr_v(char life_world[][ROWS], int& column);
//Counts the number of neighbors of cells in L[i][k],
//for 0 < k < ROWS.
//Marks cells to be birthed or killed of loneliness or overcrowding.
void chk_crnrs(char life_world[][ROWS], int& column);
//Checks the states of the four corner cells and marks them
//for birth or death in accordance with the rules of Life.

int main() {
    char world[COLUMNS][ROWS], next;
    init_config(world);
    std::cout << "Welcome to the Game of LIFE!" << std::endl;
    std::cout << "An initial configuration is given below:" << std::endl;
    display(world);
    
    prompt(next);
    while ( next == '\n' ) {
        generation(world);
        display(world);
        prompt(next);
    }
}


void display(const char life_world[][ROWS]) {
    for ( int i = 0; i < COLUMNS; i++ ) {
        for ( int j = 0; j < ROWS; j++ ) {
            std::cout.put(life_world[i][j]);
            if ( j == ROWS - 1 ) {
                std::cout.put('\n');
            }
        }
    }
}

void init_config(char life_world[][ROWS]) {
    char live('X'), dead(' ');
    for ( int j = 0; j < COLUMNS; j++ ) {
        for ( int k = 0; k < ROWS; k++ ) {
            life_world[j][k] = dead;
        }
    }

    for ( int i = 10; i < 15; i++ ) {
        life_world[10][i] = live;
        life_world[10][i+6] = live;
        life_world[10][i+12] = live;
    }
}

void generation(char life_world[][ROWS]) {
    for ( int j = 0; j < COLUMNS; j++ ) {
        chk_nbrs(life_world, j);
    }
    for ( int k = 0; k < COLUMNS; k++ ) {
        set_config(life_world, k);
    }
}

void set_config(char life_world[][ROWS], int& column) {
    char live('X'), dying('d'), dead(' '), birth('b');
    
    for ( int i = 0; i < ROWS - 1; i++ ) {
        if ( life_world[column][i] == dying ) { life_world[column][i] = dead; }
        else if ( life_world[column][i] == birth ) { life_world[column][i] = live; }
    }
}

void prompt(char& nxt_gen) {
    std::cout << "\nEnter `return` to see the next generation of LIFE, or q to quit: ";
    std::cin.get(nxt_gen);
    while ( nxt_gen != '\n' && tolower(nxt_gen) != 'q' ) {
        std::cout << "Invalid response: please enter either a new line character of q to quit: ";
        std::cin.get(nxt_gen);
    }
}

//check all neighboring cells
void chk_nbrs(char life_world[][ROWS], int& column) {
    char live('X'), dying('d');
    int neighbors(0);
    
    chk_crnrs(life_world, column);
    if ( column == 0 || column == COLUMNS - 1 ) {
        chk_nbr_h(life_world, column);
        chk_nbr_v(life_world, column);
    }
    
    if ( (column > 0) && (column < COLUMNS - 1) ) {
        for (int i = 1; i < ROWS - 1; i++) {
            if ( life_world[column][i - 1] == live || life_world[column][i - 1] == dying ) { neighbors++; }
            if ( life_world[column][i + 1] == live || life_world[column][i + 1] == dying ) { neighbors++; }
            if ( life_world[column - 1][i] == live || life_world[column - 1][i] == dying ) { neighbors++; }
            if ( life_world[column + 1][i] == live || life_world[column + 1][i] == dying ) { neighbors++; }
            if ( life_world[column - 1][i - 1] == live || life_world[column - 1][i - 1] == dying ) { neighbors++; }
            if ( life_world[column - 1][i + 1] == live || life_world[column - 1][i + 1] == dying ) { neighbors++; }
            if ( life_world[column + 1][i - 1] == live || life_world[column + 1][i - 1] == dying ) { neighbors++; }
            if ( life_world[column + 1][i + 1] == live || life_world[column + 1][i + 1] == dying ) { neighbors++; }
            //check cell state and change if necessary
            if ( life_world[column][i] == live ) {
                if ( (neighbors >= OVERCROWDING) || (neighbors <= LONELINESS) ) {
                    life_world[column][i] = dying;
                }
            } else {
                if ( neighbors == BIRTH ) { life_world[column][i] = 'b'; }
            }
            neighbors = 0;
        }
    }
}

//check the four corners of life_world
void chk_crnrs(char life_world[][ROWS], int& column) {
    char live('X'), dying('d');
    int neighbors(0);
    
    if ( column == 0 ) {
        //check life_world[0][0]:
        if ( life_world[column][1] == live ) { neighbors++; }
        if ( life_world[column + 1][0] == live ) { neighbors++; }
        if ( life_world[column + 1][1] == live ) { neighbors++; }
        //check cell state and change if necessary
        if ( life_world[column][0] == live ) {
            if ( neighbors <= LONELINESS ) { life_world[column][0] = dying; }
        } else {
            if ( neighbors == BIRTH ) { life_world[column][0] = 'b'; }
        }
        neighbors = 0;
        //check life_world[0][ROWS - 1]:
        if ( life_world[column][ROWS - 2] == live ) { neighbors++; }
        if ( life_world[column + 1][ROWS - 1] == live ) { neighbors++; }
        if ( life_world[column + 1][ROWS - 2] == live ) { neighbors++; }
        //check cell state and change if necessary
        if ( life_world[column][ROWS - 1] == live ) {
            if ( neighbors <= LONELINESS ) { life_world[column][ROWS - 1] = dying; }
        } else {
            if ( neighbors == BIRTH ) { life_world[column][ROWS - 1] = 'b'; }
        }
        neighbors = 0;
    } else if ( column == COLUMNS - 1 ) {
        //check life_world[COLUMNS - 1][0]:
        if ( life_world[column][1] == live || life_world[column][1] == dying ) { neighbors++; }
        if ( life_world[column - 1][0] == live || life_world[column - 1][0] == dying ) { neighbors++; }
        if ( life_world[column - 1][1] == live || life_world[column - 1][1] == dying ) { neighbors++; }
        //check cell state and change if necessary
        if ( life_world[column][0] == live ) {
            if ( neighbors <= LONELINESS ) { life_world[column][0] = dying; }
        } else {
            if ( neighbors == BIRTH ) { life_world[column][0] = 'b'; }
        }
        neighbors = 0;
        //check life_world[COLUMNS - 1][ROWS - 1]:
        if ( life_world[column][ROWS - 2] == live || life_world[column][ROWS - 2] == dying ) { neighbors++; }
        if ( life_world[column - 1][ROWS - 1] == live || life_world[column - 1][ROWS - 1] == dying ) { neighbors++; }
        if ( life_world[column - 1][ROWS - 2] == live || life_world[column - 1][ROWS - 2] == dying ) { neighbors++; }
        //check cell state and change if necessary
        if ( life_world[column][ROWS - 1] == live ) {
            if ( neighbors <= LONELINESS ) { life_world[column][ROWS - 1] = dying; }
        } else {
            if ( neighbors == BIRTH ) { life_world[column][ROWS - 1] = 'b'; }
        }
    }
}

//check the uppermost and lowermost rows of life_world
void chk_nbr_h(char life_world[][ROWS], int& column) {
    char live('X'), dying('d');
    int neighbors(0);
    
    for (int i = 1; i < ROWS - 1; i++) {
        if ( life_world[column][i - 1] == live || life_world[column][i - 1] == dying ) {
            neighbors++;
        }
        if ( life_world[column][i + 1] == live || life_world[column][i + 1] == dying ) {
            neighbors++;
        }
        
        //check the cells beneath those in the uppermost row
        if ( column == 0 ) {
            if ( life_world[column + 1][i - 1] == live || life_world[column + 1][i - 1] == dying ) { neighbors++; }
            if ( life_world[column + 1][i] == live || life_world[column + 1][i] == dying ) { neighbors++; }
            if ( life_world[column + 1][i + 1] == live || life_world[column + 1][i + 1] == dying ) { neighbors++; }
            
            //check cell status and change if necessary
            if ( life_world[column][i] == live ) {
                if ( (neighbors >= OVERCROWDING) || (neighbors <= LONELINESS) ) {
                    life_world[column][i] = dying;
                }
            } else {
                if ( neighbors == BIRTH ) { life_world[column][i] = 'b'; }
            }
        } else if ( column == COLUMNS - 1 ) {
            //checking cells above those in the lowermost row
            if ( life_world[column - 1][i - 1] == live || life_world[column - 1][i - 1] == dying ) { neighbors++; }
            if ( life_world[column - 1][i] == live || life_world[column - 1][i] == dying ) { neighbors++; }
            if ( life_world[column - 1][i + 1] == live || life_world[column - 1][i + 1] == dying ) { neighbors++; }
            
            //check cell status and change if necessary
            if ( life_world[column][i] == live ) {
                if ( (neighbors >= OVERCROWDING) || (neighbors <= LONELINESS) ) {
                    life_world[column][i] = dying;
                } else {
                    if ( neighbors == BIRTH ) { life_world[column][i] = 'b'; }
                }
            }
        }
        neighbors = 0;
    }
}

//check the leftmost and rightmost columns of life_world
void chk_nbr_v(char life_world[][ROWS], int& column) {
    char live('X'), dying('d');
    int neighbors(0);
    
    for (int i = 1; i < COLUMNS - 1; i++) {
        if ( life_world[i - 1][0] == live || life_world[i - 1][0] == dying ) {
            neighbors++;
        }
        if ( life_world[i + 1][0] == live || life_world[column][i + 1] == dying ) {
            neighbors++;
        }
        if ( life_world[i - 1][ROWS - 1] == live || life_world[i - 1][ROWS - 1] == dying ) {
            neighbors++;
        }
        if ( life_world[i + 1][ROWS - 1] == live || life_world[i + 1][ROWS - 1] == dying ) {
            neighbors++;
        }
        
        //check the cells to the right of those in the leftmost column
        if ( column == 0 ) {
            if ( life_world[i - 1][column + 1] == live || life_world[i - 1][column + 1] == dying ) { neighbors++; }
            if ( life_world[i][column + 1] == live || life_world[i][column + 1] == dying ) { neighbors++; }
            if ( life_world[i + 1][column + 1] == live || life_world[i + 1][column + 1] == dying ) { neighbors++; }
            
            //check cell status and change if necessary
            if ( life_world[i][column] == live ) {
                if ( (neighbors >= OVERCROWDING) || (neighbors <= LONELINESS) ) {
                    life_world[i][column] = dying;
                }
            } else {
                if ( neighbors == BIRTH ) { life_world[i][column] = 'b'; }
            }
        } else {
            //checking cells to the left of those in the rightmost column
            if ( life_world[i - 1][ROWS - 2] == live || life_world[i - 1][ROWS - 2] == dying ) { neighbors++; }
            if ( life_world[i][ROWS - 2] == live || life_world[i][ROWS - 2] == dying ) { neighbors++; }
            if ( life_world[i + 1][ROWS - 2] == live || life_world[i + 1][ROWS - 2] == dying ) { neighbors++; }
            
            //check cell status and change if necessary
            if ( life_world[i][ROWS - 1] == live ) {
                if ( (neighbors >= OVERCROWDING) || (neighbors <= LONELINESS) ) {
                    life_world[i][ROWS - 1] = dying;
                } else {
                    if ( neighbors == BIRTH ) { life_world[i][ROWS - 1] = 'b'; }
                }
            }
        }
        neighbors = 0;
    }
}
