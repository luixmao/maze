#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Open the file specified by filename, and read the 
 * maze into a dynamically allocated array.
 * 
 * Return the pointer to that array (don't delete it..
 * we'll do that in main() ).  Return NULL if
 * you are unable to open the file or can't read
 * the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  those values in with the number of rows and 
 *  columns read by from the file (first two value
 *  in the file)
 *
 *************************************************/
char* read_maze(char* filename, int* rows, int* cols )
{

//loads the file into ifile
ifstream ifile(filename); 

//return NULL if ifstream fails
if( ifile.fail() ){
  return NULL; 
  }

else{
  // stores rows and colum numbers of maze and find the number of elements
  ifile >> *rows;              
  ifile >> *cols;
  int size= *rows * *cols;

  //returns NULL if unable to read meaningful number or rows or columns
  if (size==0){
     ifile.close();
     return NULL;
    }

  // dinamically allocate the size of array depending on the number of rows and columns
  char* MazeData= new char[size+1]; //extra +1 for null


  // store data in MazeData 
  for (int i=0; i<size; i++){
    ifile >> MazeData[i]; 
  }

  ifile.close();
  return MazeData;
  }

}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/

void print_maze(char *maze, int rows, int cols)
{
// print character by character, and start a new line after it hits a wall
for(int i=0;i<rows*cols;i++){
  cout << maze[i];
  if ( (i+1)%(cols) == 0 ) {       //to start a new line once finished columns
    cout << endl;
    }
 }

}


/*************************************************
 * Write maze should open the file specified by 
 * filename and write the contents of the maze
 * array to the file with the dimensions on the first
 * line.
 *
 *************************************************/
void write_maze(char *filename, char *maze, int rows, int cols)
{
ofstream ofile(filename);
// outputs rows and columns in first line
ofile << rows <<" "<< cols <<endl;

// stores in ofile character by character. It start a new line after it hits a wall
for (int i=0;i<rows*cols;i++){
  ofile << maze[i];
  if ((i+1)%(cols)==0) {       //to start a new line once finished columns
     ofile << endl;     
     }    
 }


}
