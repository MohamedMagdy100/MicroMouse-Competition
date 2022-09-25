void stepPid()
{
  pos_r = 0;
  pos_l = 0;
  int step = 0 ;
  int distance;
  if (FirstStep)
  {
    distance = DistanceCM(30);
    FirstStep = 0;
  }
  else
  {
    distance = DistanceCM(30);
  }

  while (pos_r != distance )
  {
    motor_l(step);
    motor_r(-step++);
    //    delay(10);
    //    stopModified();
    //      Serial.print("yaw out");
    //      Serial.println(P.angZ);
    Serial.print(pos_l); Serial.print("\t\t"); Serial.println(pos_r);

  }
  stopModified();
  pos_r = 0;
  pos_l = 0;
  STOP();
  pos_r = 0;
  pos_l = 0;
//  delay(1000);
  pos_r = 0;
  pos_l = 0;

}


/*************************************************************************/
/****************** Calibrate step in testing day  ***********************/
/*************************************************************************/
void testStep()
{
  pos_r = 0;
  pos_l = 0;
  int distance;
  if (FirstStep)
  {
    distance = DistanceCM(30);
    FirstStep = 0;
  }
  else
  {
    distance = DistanceCM(30);
  }

  while (pos_r != distance )
  {
    forward_step();
    //    delay(10);
    //    stopModified();
    //      Serial.print("yaw out");
    //      Serial.println(P.angZ);
    Serial.print(pos_l); Serial.print("\t\t"); Serial.println(pos_r);

  }
  stopModified();
  pos_r = 0;
  pos_l = 0;
  while (pos_l != 7)
  {
    analogWrite(ENL, spd);
    analogWrite(ENR, spd);

    digitalWrite(ML1, 1);
    digitalWrite(ML2, 0);

    digitalWrite(MR1, 0);
    digitalWrite(MR2, 0);
  }
  STOP();
  pos_r = 0;
  pos_l = 0;
  delay(1000);
  pos_r = 0;
  pos_l = 0;
}

/*************************************************************************/
/****************** Calibrate vlx in testing day  ************************/
/*************************************************************************/
void testMotionWithVlx()
{
  // NOT no wall

  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  // two walls beside robot
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Straight path or using pid
  {
    //    stepNextCell();
    testStep();
    delay(500);
  }
  // three walls around robot
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    right_180();
  }
  //No walls
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Right Turn or using pid
  {
    left_90();
    //    stepNextCell();
    testStep();
    delay(500);
  }
  //no wall left and no wall centre
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    //    stepNextCell();
    testStep();
    delay(500);
  }
  //no wall left and no wall centre
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    //    stepNextCell();
    testStep();
    delay(500);
  }
  //no wall left
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    //    stepNextCell();
    testStep();
    delay(500);
  }
  //no wall left and no wall right
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    //    stepNextCell();
    testStep();
    delay(500);
  }
  //no wall right
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    right_90();
    //    stepNextCell();
    testStep();
    delay(500);
  }

}

/*************************************************************************/
/****************** Reading vlx in testing day  **************************/
/*************************************************************************/
void testReadingVlx()
{
  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  Serial.print(leftVlx); Serial.print("\t\t"); Serial.print(centreVlx); Serial.print("\t\t"); Serial.println(rightVlx);
}

/*************************************************************************/
/********************* Testing Shortest Path  ****************************/
/*************************************************************************/
void testShortestPath()
{
  char path[] = "SLRSRLSSSSSLRSLSSLSRRSLSSSLLSSRSLSRSSSRR";

  for (int i = 0; i <= 40 ;)
  {
    if (path[i] == 'R')
    {
      right_90();
      delay(500);
      changeHeading('r');
      stepNextCell();
      delay(500);
      updateXY();
      i++;
      Serial.print('('); Serial.print(x); Serial.print(','); Serial.print(y); Serial.println(')');
    }
    if (path[i] == 'L')
    {
      left_90();
      delay(500);
      changeHeading('l');
      stepNextCell();
      delay(500);
      updateXY();
      i++;
      Serial.print('('); Serial.print(x); Serial.print(','); Serial.print(y); Serial.println(')');
    }
    if (path[i] == 'S')
    {
      stepNextCell();
      delay(500);
      updateXY();
      i++;
      Serial.print('('); Serial.print(x); Serial.print(','); Serial.print(y); Serial.println(')');
    }
    if (path[i] == 'B')
    {
      right_180();
      delay(500);
      changeHeading('b');
      stepNextCell();
      delay(500);
      updateXY();
      i++;
      Serial.print('('); Serial.print(x); Serial.print(','); Serial.print(y); Serial.println(')');
    }
  }

  STOP();
  delay(10000);
}


/*************************************************************************/
/****************** Testing Array Optimization  **************************/
/*************************************************************************/
void testAlgorithm()
{

  SHORTEST_PATH_left();
  Second_trail();
}

/*************************************************************************/
/************************* Testing Buttons  ******************************/
/*************************************************************************/
void testSwitches()
{
  Serial.print("DirectionSwitch: ");
  Serial.print(digitalRead(DirectionSwitch));

  Serial.print("\t\tStopMapping: ");
  Serial.println(digitalRead(StopMapping));
  delay(1000);
}

/*************************************************************************/
/************************** Testing Turns  *******************************/
/*************************************************************************/
void testTurn()
{
  //  pos_r = 0;
  //  pos_l = 0;
  //
  //  while(pos_r != -10)
  //  {
  //    analogWrite(ENL, spd);
  //    analogWrite(ENR, spd);
  //
  //    digitalWrite(ML1, 0);
  //    digitalWrite(ML2, 1);
  //
  //    digitalWrite(MR1, 0);
  //    digitalWrite(MR2, 1);
  //  }


  P.clearAng();
  pos_r = 0;
  pos_l = 0;
  int step = 0;
  MpuUpdate();
  float flag = P.angZ;
  float Yaw = P.angZ;
  //  Serial.print("flag=");
  //  Serial.println(flag);
  //  Serial.print("yaw out");
  //  Serial.println(Yaw);


  while (Yaw != -90)
  {
    MpuUpdate();
    Yaw = P.angZ;
    //    Serial.print("yaw in");
    //    Serial.println(Yaw);
    if (Yaw > flag - 85)
    {
      motor_l(-step);
      motor_r(step++);
    }
    else  if (Yaw < flag - 93)
    {
      motor_l(step);
      motor_r(-step++);
    }
    else
    {
      stopModified();
      if (Yaw <= -92 || Yaw >= -88) {
        //P.clearAng();
        pos_r = 0;
        pos_l = 0;
        break;
      }
    }
    MpuUpdate();
    Yaw = P.angZ;
  }
}
