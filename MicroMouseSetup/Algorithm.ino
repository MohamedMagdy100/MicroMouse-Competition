void changeHeading(char moving)
{
  if (robotHeading == FORWARD_HEADING)
  {
    switch (moving)
    {
      case 'r': robotHeading = RIGHT_HEADING; break;
      case 'l': robotHeading = LEFT_HEADING; break;
      case 'b': robotHeading = BACK_HEADING; break;
    }
  }

  else if (robotHeading == RIGHT_HEADING)
  {
    switch (moving)
    {
      case 'r': robotHeading = BACK_HEADING; break;
      case 'l': robotHeading = FORWARD_HEADING; break;
      case 'b': robotHeading = LEFT_HEADING; break;
    }
  }

  else if (robotHeading == BACK_HEADING)
  {
    switch (moving)
    {
      case 'r': robotHeading = LEFT_HEADING; break;
      case 'l': robotHeading = RIGHT_HEADING; break;
      case 'b': robotHeading = FORWARD_HEADING; break;
    }
  }

  else if (robotHeading == LEFT_HEADING)
  {
    switch (moving)
    {
      case 'r': robotHeading = FORWARD_HEADING; break;
      case 'l': robotHeading = BACK_HEADING; break;
      case 'b': robotHeading = RIGHT_HEADING; break;
    }
  }
}

void updateXY()
{
  switch (robotHeading)
  {
    case FORWARD_HEADING: y++; break;
    case BACK_HEADING:    y--; break;
    case RIGHT_HEADING:   x++; break;
    case LEFT_HEADING:    x--; break;
  }
}


/*******************************************************************************************/
/******************** Function to save direction of robot in array  ************************/
/*******************************************************************************************/
void Creating_array ()
{
  //NOT ---> NO WALLS

  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))       //Straight path
  {
    stepNextCell();
    delay(500);
    updateXY();
  }

  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //Left turn
  {
    left_90();
    changeHeading('l');
    stepNextCell();
    delay(500);
    updateXY();
  }

  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //Right turn
  {
    right_90();
    changeHeading('r');
    stepNextCell();
    delay(500);
    updateXY();
  }

  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //T Intersection
  {
    if (digitalRead(DirectionSwitch) == MOST_LEFT) // 1 for most left
    {
      left_90();      // As Left is possible
      changeHeading('l');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'L';
    }
    else        //0 for most right
    {
      right_90();
      changeHeading('r');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'R';
    }
    pathSize++;
  }

  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))       //Left T Intersection
  {
    if (digitalRead(DirectionSwitch) == MOST_LEFT)       //most left
    {
      left_90();                // As Left is possible
      changeHeading('l');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'L';
    }
    else //most right
    {
      stepNextCell();
      delay(500);               //As Straight path is possible
      updateXY();
      directions[pathSize] = 'S';

    }
    pathSize++;
  }

  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))       //Right T Tntersection
  {
    if (digitalRead(DirectionSwitch) == MOST_LEFT)     //most left
    {
      stepNextCell();         //As Straight path is possible
      delay(500);
      updateXY();
      directions[pathSize] = 'S';
    }
    else                      //most right
    {
      right_90();
      changeHeading('r');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'R';
    }
    pathSize++;
  }

  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //Dead End
  {
    right_180();              //As no other direction is possible
    changeHeading('b');
    stepNextCell();
    delay(500);
    updateXY();
    directions[pathSize] = 'B';
    pathSize++;
  }

  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))       //4 Lane intersection
  {
    if (digitalRead(DirectionSwitch) == MOST_LEFT)     //most left
    {
      left_90();              // As Left is possible
      changeHeading('l');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'L';
    }
    else                      //most right
    {
      right_90();
      changeHeading('r');
      stepNextCell();
      delay(500);
      updateXY();
      directions[pathSize] = 'R';
    }
    pathSize++;
  }
}

/***********************************************************************************************************/
/*********************** Minimzing the array used in the shortest path functions ***************************/
/***********************************************************************************************************/
void minimize_array( int x, int y)
{
  directions[x] = directions[y];
  for (int i = y; i <= pathSize - 2 ; i++)
  {
    directions[i] = directions[i + 2];
  }
  pathSize = pathSize - 2;
}

/*********************************************************************************************************/
/*********************** Optimizing the array to the shortest path (Most Left) ***************************/
/*********************************************************************************************************/
void SHORTEST_PATH_left()
{
  /*
    LBL = S
    LBR = B
    LBS = R
    RBL = B
    SBL = R
    SBS = B */
  directions[pathSize] = '\0';
  pathSize++;
  char ACTION;
  
  for (int i = 0; i <= pathSize - 2; i++)
  {
    ACTION = directions[i];

    if (ACTION == 'B')
    {
      if (directions[i - 1] == 'L' && directions[i + 1] == 'R')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'L' && directions[i + 1] == 'S')
      {
        directions[i] = 'R';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'R' && directions[i + 1] == 'L')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'S' && directions[i + 1] == 'L')
      {
        directions[i] = 'R';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'S' && directions[i + 1] == 'S')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'L' && directions[i + 1] == 'L')
      {
        directions[i] = 'S';
        minimize_array( i - 1, i);
      }
      i = -1;
    }
  }
}

/**********************************************************************************************************/
/*********************** Optimizing the array to the shortest path (Most Right) ***************************/
/**********************************************************************************************************/
void SHORTEST_PATH_right()
{
  /*
    RBR = S
    RBL = B
    RBS = L
    LBR = B
    SBR = L
    SBS = B
  */
  directions[pathSize] = '\0';
  pathSize++;
  char ACTION;

  for (int i = 0; i <= pathSize - 2; i++)
  {
    ACTION = directions[i];

    if (ACTION == 'B')
    {
      if (directions[i - 1] == 'L' && directions[i + 1] == 'R')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'R' && directions[i + 1] == 'S')
      {
        directions[i] = 'L';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'R' && directions[i + 1] == 'L')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'S' && directions[i + 1] == 'R')
      {
        directions[i] = 'L';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'S' && directions[i + 1] == 'S')
      {
        directions[i] = 'B';
        minimize_array( i - 1, i);
      }

      if (directions[i - 1] == 'R' && directions[i + 1] == 'R')
      {
        directions[i] = 'S';
        minimize_array( i - 1, i);
      }

      i = -1;
    }

  }
}

/*********************************************************************************************************/
/************************************** Run the shortest path ********************************************/
/*********************************************************************************************************/
void Second_trail()
{
  directions[pathSize]='\0';
  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  for (int i = 0; i <= pathSize ;)
  {
    seeVlx(&leftVlx, &centreVlx, &rightVlx);
    if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
        && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))       //Straight path
    {
      stepNextCell();
      delay(500);
    }

    if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
        && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //Left turn
    {
      left_90();
      stepNextCell();
      delay(500);
    }

    if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
        && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))        //Right Turn
    {
      right_90();
      stepNextCell();
      delay(500);
    }

    if ((!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
         && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE)) ||

        ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
         && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE)) ||

        (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
         && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE)) ||

        (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
         && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))&& (i<pathSize))
    {
      if (directions[i] == 'R')
      {
        right_90();
        stepNextCell();
        delay(500);
        i++;
      }
      if (directions[i] == 'L')
      {
        left_90();
        stepNextCell();
        delay(500);
        i++;
      }
      if (directions[i] == 'S')
      {
        stepNextCell();
        delay(500);
        i++;
      }
    }
    else
    {
       STOP();
    }
  }
 
}
