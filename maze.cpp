#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototype for maze_search
int maze_search(char *, int, int);

int main(int argc, char *argv[])
{

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
    }

  int rows,cols,result;

  char*  mymaze = read_maze(argv[1], &rows, &cols);


  // For checkpoint 1, just leave maze_search() unedited
  //  and the program should read in the maze, print it
  //  and write it back to the output file
  result= maze_search(mymaze, rows,cols);
  
  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  delete [] mymaze;
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char *maze, int rows, int cols)
{

int size = rows*cols;
int* bfsq = new int[size];     

// array with exploration data  
int* tracking= new int[size];  

// initialize start and finish cell index, if these values don't change from the initial, then error will be displayed
int start = -10;                
int finish= -10;                 

// inicialize tracking into "-1" (unknown) except at "start"
for(int i=0; i<size; i++){
  if(maze[i]=='S'){
     tracking[i]=-2;
     start=i;
   }
   else if(maze[i]=='F'){
     finish=i;
     tracking[i]=-1;
   }
   else{
   tracking[i]=-1; 
   }
}

//return error (-1) if there isn't 'S' or 'F' 
if (start==-10 || finish==-10) {
  delete [] bfsq; 
  delete [] tracking;
  return -1;
}

//initialize bfsq
int head=0, tail=0;   
bfsq[head]=start;
tail++;

// over_index is the index of last cell before the "finish" cell, if this value doesn't change from the initial, there is no path possible
int over_index= -100;  


// use while loop to run the search until "bfsq" runs out of indexes to look
while(head != tail){

// cc = current cell index
int cc = bfsq[head]; 

// find if the current cell is in any size of the maze
bool top = false, bott= false, right = false, left =false;
if(cc<cols){
   top = true;
}
if (cc > size -cols -1){
   bott = true;
}
if ( !( (cc+1)%cols) ){
   right = true;
}
if ( ! (cc%cols)    ){
   left = true;
}

//  unless they are walls, find north, east, south and west cells

// if the current cell is not on the top, then find the cell above it 
if (!top){
  // "north" is index of the north cell
  int north= cc - cols; 

  // exit loop if "finish" is found
  if ( maze[north]=='F'  ){
  over_index=cc;
  break;
  }

  // when the north cell is not a wall, "start", or discovered already, then assign the current cell index in the tracking memory array. Also, put the north cell index into the line of bfsq.
  if ( maze[north]!='#' && maze[north]!='S' && tracking[north]==-1  ){
  tracking[north]= cc;
  bfsq[tail]=north;
  tail++;
  }
}

// similiar as finding north cell above:

if (!left){
  int west= cc -1; // "west" is index of the west cell
  if ( maze[west]=='F'  ){
  over_index=cc;
  break;
  }
  if ( maze[west]!='#' && maze[west]!='S' && tracking[west]==-1  ){
  tracking[west]= cc;
  bfsq[tail]=west;
  tail++;
  }
}


if (!bott){
  int south= cc +cols ; // "south" is index of the south cell
  if ( maze[south]=='F'  ){
  over_index=cc;
  break;
  }
  if ( maze[south]!='#' && maze[south]!='S' && tracking[south]==-1  ){
  tracking[south]= cc;
  bfsq[tail]=south;
  tail++;
  }
}


if (!right){
  int east= cc +1; // "east" is index of the east cell
  if ( maze[east]=='F'  ){
  over_index=cc;
  break;
  }
  if ( maze[east]!='#' && maze[east]!='S' && tracking[east]==-1   ){
  tracking[east]= cc;
  bfsq[tail]=east;
  tail++;
  }
}
head++;
}

// if there was no path found, over_index would have not changed from its initial value and hence there is no path possible
if (over_index==-100) {

  delete [] bfsq; 
  delete [] tracking;
  return 0;
}

// if there is path found then mark the path
else{
  int predecessor= over_index;

// mark the path by refering to the tracking memory array that has stored the indexes of the preceding cell.
  while (predecessor != start){ 
    maze[predecessor]= '*';
    predecessor= tracking[predecessor];
    }
  delete [] bfsq; 
  delete [] tracking;
  return 1;
}

}
