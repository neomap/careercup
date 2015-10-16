import java.util.Scanner;

class Main
{
  
  public static void main ( String[] args )
  {
    Scanner keyboard = new Scanner( System.in );
    
    //Read the higher position and compute the size of the board
    int rows, columns;

    columns = Integer.parseInt( keyboard.next() ) + 1;
    rows = Integer.parseInt( keyboard.next() ) + 1;
    ////////////////////////////////////////////////////////////

    //Create the board
    Board board = new Board( rows , columns );
    
    int x, y; //X and Y coordinates for the position of the robot
    char o; //Orientation of the robot

    //While we have robots
    while ( keyboard.hasNext() )
    {
      //Read the initial position of the robot
      x = Integer.parseInt( keyboard.next() );
      y = Integer.parseInt( keyboard.next() );
      o = keyboard.next().charAt(0);
      /////////////////////////////////

      //Create the robot
      Explorer robot = new Explorer( x, y, o );

      //Read all the instructions
      String instructions = new String();
      instructions = keyboard.next();
      ///////////////////////////

      //Process the instructions one by one
      char instruction;

      for ( int i = 0; i < instructions.length(); ++i )
      {
        instruction = instructions.charAt(i);

        processInstruction( robot, board, instruction );

        if ( !board.isInTheBoard( robot.getY(), robot.getX() ) )
          break;
      }
      /////////////////////////////////////

      if ( board.isInTheBoard( robot.getY(), robot.getX() ) )
        robot.showInTheBoard();
    }//end of while loop

  }//end of main method

  static void processInstruction( Explorer robot, Board board, char instruction )
  {
    if ( instruction == 'R' )
      robot.turnRight();
    else if ( instruction == 'L' )
      robot.turnLeft();
    else
      robot.forward( board );
  }//end of processInstruction method
  
}//end of MutantFlatworldExplorers class

class Explorer
{
  
  int x, y; //X and Y coordinates for the position of the robot
  char orientation; //Orientation of the robot

  Explorer( int x, int y, char o )
  {
    this.x = x;
    this.y = y;
    orientation = o;
  }//end of constructor

  int getX()
  {
    return x;
  }//end of getX method

  int getY()
  {
    return y;
  }//end of getY method

  void showInTheBoard()
  {
    System.out.println( x + " " + y + " " + orientation );
  }//end of showInTheBoard method
  
  void showOutOfTheBoard()
  {
    System.out.println( x + " " + y + " " + orientation + " LOST");
  }//end of showOutOfTheBoard method

  void turnRight()
  {
    switch ( orientation )
    {
      case 'N':
        orientation = 'E'; break;
      case 'E':
        orientation = 'S'; break;
      case 'S':
        orientation = 'W'; break;
      case 'W':
        orientation = 'N'; break;
      default:
        break;
    }
  }//end of turnRight method

  void turnLeft()
  {
    switch ( orientation )
    {
      case 'N':
        orientation = 'W'; break;
      case 'E':
        orientation = 'N'; break;
      case 'S':
        orientation = 'E'; break;
      case 'W':
        orientation = 'S'; break;
      default:
        break;
    }
  }//end of turnLeft method

  void forward(Board board)
  {
    //Compute the target position
    int target_x = x; //needed to avoid the initialisation error when compiling
    int target_y = y; //needed to avoid the initialisation error when compiling

    switch ( orientation )
    {
      case 'N':
        target_x = x; target_y = y + 1; break;
      case 'E':
        target_x = x + 1; target_y = y; break;
      case 'S':
        target_x = x; target_y = y - 1; break;
      case 'W':
        target_x = x - 1; target_y = y; break;
      default:
        break;
    }
    /////////////////////////////
    
    if ( board.isInTheBoard(target_y, target_x) )
    {
      x = target_x;
      y = target_y;
    }
    else
    {
      if ( board.hasScent(y, x) )
        ; //do nothing
      else
      {
        board.putScent(y, x);

        showOutOfTheBoard();
        
        x = target_x;
        y = target_y;
      }
    }
  }//end of forward method
  
}//end of class Explorer

class Board
{

  boolean m[][]; //the board
  int num_rows;
  int num_columns;

  Board( int rows, int columns )
  {
    m = new boolean[rows][columns];
    num_rows = rows;
    num_columns = columns;

    for ( int row = 0; row < num_rows; ++row )
      for ( int column = 0; column < num_columns; ++column )
        m[row][column] = false;
  }//end of constructor

  boolean isInTheBoard(int row, int column)
  {
    if ( row < 0 || row >= num_rows )
      return false;
    
    if ( column < 0 || column >= num_columns )
      return false;
    
    return true;
  }//end of isInTheBoard method

  boolean hasScent(int row, int column)
  {
    return m[row][column];
  }//end of hasScent method

  void putScent(int row, int column)
  {
    m[row][column] = true;
  }//end of putScent method
  
}//end of class Board
