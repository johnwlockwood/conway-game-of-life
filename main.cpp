#include <iostream>
#include <time.h>

const int GRID_SIZE = 25;
const int DEAD = 0;
const int LIVE = 1;
const int PATTERN_SIZE = 3;
const float TICK_INTERVAL =0.1f;

bool shouldTick(float sinceTick)
{
    if (sinceTick >TICK_INTERVAL) {
        return true;
    }
    return false;

}

void makeDeadGrid(int grid[GRID_SIZE][GRID_SIZE])
{
    int i = 0;
    int j;
    while (i < GRID_SIZE) {
        j=0;
        while (j < GRID_SIZE) {
            grid[i][j] = DEAD;
            j++;
        }
        i++;
    }
    return;
}

int neighborCount(int i_coord, int j_coord, int grid[GRID_SIZE][GRID_SIZE])
{
    int tli = i_coord-1;
    int tlj = j_coord-1;
    
    int count = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            int curi = (tli+i)%GRID_SIZE;
            int curj = (tlj+j)%GRID_SIZE;
            if (curi < 0) {
                curi =GRID_SIZE-1;
            }
            if (curj < 0) {
                curj =GRID_SIZE-1;
            }
            //std::cout << curi << "  " << curj << std::endl;
            if (!(curi == i_coord && curj == j_coord)) {
                if (grid[curi][curj] == LIVE) {
                    count++;
                }
            }
        }

    }
    return count;
}

int wrapCoord(int coord)
{
    int wrappedCoord = coord%GRID_SIZE;

    if (wrappedCoord < 0) {
        wrappedCoord =GRID_SIZE-1;
    }
    return wrappedCoord;
}

void insertPatternInGridAtCoords(int pattern[3][3], int grid[GRID_SIZE][GRID_SIZE], int i_coord, int j_coord)
{
    for (int i=0; i<PATTERN_SIZE; i++) {
        for (int j=0; j<PATTERN_SIZE; j++) {
            grid[wrapCoord(i+i_coord)][wrapCoord(j+j_coord)] = pattern[i][j];
        }
    }
}

void copyGrid(int grid[GRID_SIZE][GRID_SIZE],  int gridCopy[GRID_SIZE][GRID_SIZE])
{
    for ( int i = 0; i < GRID_SIZE; i++ )               
    {                                           
        // loop through columns of current row   
        for ( int j = 0; j < GRID_SIZE; j++ ) 
        {
            gridCopy[i][j] = grid [i][j];
        }
    } 
}

void stepGrid( int grid[GRID_SIZE][GRID_SIZE],  int lastGrid[GRID_SIZE][GRID_SIZE])
{
    //makeDeadGrid(lastGrid);
    copyGrid(grid,lastGrid);
    // loop through array's rows                
    for ( int i = 0; i < GRID_SIZE; i++ )               
    {                                           
        // loop through columns of current row   
        for ( int j = 0; j < GRID_SIZE; j++ ) 
        {
            int count = neighborCount(i, j, lastGrid);
            
            if (count > 0 && (count < 2 || count > 3)) {
                grid[i][j] = DEAD;
            } else if ((lastGrid[i][j]==LIVE) && (count == 2 || count == 3)) {
                grid[i][j] = LIVE;
            } else if (count == 3) {
                grid[i][j] = LIVE;
            } else {
                grid[i][j] = DEAD;
            }
        }

    } // end outer for   
    
    grid = lastGrid;
}

// output array with two rows and three columns
void printArrayF( const int a[][ 3 ] )          
{                                              
    // loop through array's rows                
    for ( int i = 0; i < 3; i++ )               
    {                                           
        // loop through columns of current row   
        for ( int j = 0; j < 3; j++ )            
            std::cout << a[ i ][ j ] << ' ';           
        
        std::cout << std::endl; // start new line of output
    } // end outer for                          
} // end function printArray

// output array with two rows and three columns
void printLifeGrid( int a[][GRID_SIZE])          
{                                              
    // loop through array's rows                
    for ( int i = 0; i < GRID_SIZE; i++ )               
    {                                           
        // loop through columns of current row   
        for ( int j = 0; j < GRID_SIZE; j++ ) 
        {
            if (a[ i ][ j ]==LIVE) {
                std::cout << "X  ";
            } else {
                std::cout << "   ";
            }
        }

        
        std::cout << std::endl; // start new line of output
    } // end outer for                          
} // end function printArray


int main (int argc, char * const argv[]) {
    clock_t lastTime;
    clock_t frameTime;
    clock_t totalTime;
    
    

    
    
    
//    const int patternSize = 3;
    
//    int liveRow[patternSize] = {LIVE,LIVE,LIVE};
//    int dllRow[patternSize] = {DEAD,LIVE,LIVE};
//    int lldRow[patternSize] = {LIVE,LIVE,DEAD};
//    int deadRow[patternSize] = {DEAD,DEAD,DEAD};
//    int ldlRow[patternSize] = {LIVE,DEAD,LIVE};
//    int dldRow[patternSize] = {DEAD,LIVE,DEAD};
    
    int BLINKER[3][3] = {
        {DEAD,DEAD,DEAD},
        {LIVE,LIVE,LIVE},
        {DEAD,DEAD,DEAD}
    };
    
    
//    int BOAT[3][3] = {*lldRow,
//       *ldlRow,
//       *dldRow };
    
    int UEXPAND[3][3] = {
        {LIVE,DEAD,LIVE},
        {LIVE,DEAD,LIVE},
        {LIVE,LIVE,LIVE}
                };
    int GLIDER[3][3] = {
        {LIVE,DEAD,DEAD},
        {DEAD,LIVE,LIVE},
        {LIVE,LIVE,DEAD}
    };
    

    lastTime = clock ();
    std::cout << "Hello, World!\n" <<  lastTime << std::endl;
    
    //printArrayF(BOAT);
    int grid[GRID_SIZE][GRID_SIZE];
    int lastGrid[GRID_SIZE][GRID_SIZE];
    
    makeDeadGrid(lastGrid);
    makeDeadGrid(grid);
    
    int count = neighborCount(0,0,grid);
    std::cout << "neighbor count is: " << count << std::endl;
    
    insertPatternInGridAtCoords(BLINKER,grid,4,10);
    insertPatternInGridAtCoords(GLIDER,grid,10,10);
    insertPatternInGridAtCoords(UEXPAND,grid,5,16);
    insertPatternInGridAtCoords(UEXPAND,grid,24,24);
    
    printLifeGrid(grid);
    
    float sinceTick = 0.0f;
    bool gameRunning = true;
    totalTime = lastTime;
    int totalTicks = 0;
    float deltaTime = 0;
    
    while (gameRunning) {
        // Get the time when the frame started.
        frameTime = clock();
        
        // The elapsed seconds per frame will almost always be less than 1.0.
        float elapsedSeconds = float(frameTime - lastTime) / CLOCKS_PER_SEC;
        if (shouldTick(sinceTick)) {
            deltaTime =  sinceTick;
            sinceTick = 0.0f;
            totalTicks +=1;
            stepGrid(grid, lastGrid);
            printLifeGrid(grid);
            std::cout << "game  " << deltaTime << " " << elapsedSeconds << std::endl;
        }
        sinceTick += elapsedSeconds;
        
        if (totalTicks > 300) {
            gameRunning=false;
        }
                
        totalTime += frameTime;
        // Update the last time counter so that we can use it next frame.
        lastTime = frameTime;
    }
    
    
    return 0;
}
