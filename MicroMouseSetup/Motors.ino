/********************************************************************************/
/******************************* Move Straight  *********************************/
/********************************************************************************/
void forward(void)
{
  digitalWrite(MR1, 1);
  digitalWrite(MR2, 0);
  analogWrite(ENR, spd);

  digitalWrite(ML1, 1);
  digitalWrite(ML2, 0);
  analogWrite(ENL, spd);
}



void forward_step()
{
  if (startMove == 0)
  {
//  pos_l = 5;
  digitalWrite(MR1, 1);
  digitalWrite(MR2, 0);
  analogWrite(ENR, spd);

  digitalWrite(ML1, 1);
  digitalWrite(ML2, 0);
  analogWrite(ENL, spd);
  
  startMove = 1;  
  }
  if (pos_l > pos_r)
  {
    analogWrite(ENL, spd);
    analogWrite(ENR, spd);

    digitalWrite(ML1, 0);
    digitalWrite(ML2, 0);

    digitalWrite(MR1, 1);
    digitalWrite(MR2, 0);
  }
  else if ( pos_l < pos_r)
  {
    analogWrite(ENL, spd);
    analogWrite(ENR, spd);

    digitalWrite(ML1, 1);
    digitalWrite(ML2, 0);

    digitalWrite(MR1, 0);
    digitalWrite(MR2, 0);
  }
  else
  {
    analogWrite(ENL, spd);
    analogWrite(ENR, spd);

    digitalWrite(ML1, 1);
    digitalWrite(ML2, 0);

    digitalWrite(MR1, 1);
    digitalWrite(MR2, 0);
  }
}

/********************************************************************************/
/********************************* Turn Left  ***********************************/
/********************************************************************************/
void left(void)
{
  digitalWrite(MR1, 1);
  digitalWrite(MR2, 0);
  analogWrite(ENR, spd);

  digitalWrite(ML1, 0);
  digitalWrite(ML2, 1);
  analogWrite(ENL, spd);
}

/*********************************************************************************/
/********************************* Turn Right  ***********************************/
/*********************************************************************************/
void right(void)
{
  digitalWrite(MR1, 0);
  digitalWrite(MR2, 1);

  digitalWrite(ML1, 1);
  digitalWrite(ML2, 0);

  analogWrite(ENR, spd);
  analogWrite(ENL, spd);
}

/**********************************************************************************/
/********************************* Stop Motors  ***********************************/
/**********************************************************************************/
void STOP(void)
{
  digitalWrite(MR1, 0);
  digitalWrite(MR2, 0);


  digitalWrite(ML1, 0);
  digitalWrite(ML2, 0);

  //  for (int i = spd ; i <= 0 ; i--)
  //  {
  analogWrite(ENR, 0);
  analogWrite(ENL, 0);
  //  }
}

/*************************************************************************/
/****************** Step to center of the cell  **************************/
/*************************************************************************/
void stepNextCell()
{
  digitalWrite(MR1, 1);
  digitalWrite(MR2, 1);


  digitalWrite(ML1, 0);
  digitalWrite(ML2, 1);

  analogWrite(ENR, 0);
  analogWrite(ENL, 0);

  delay(100);
  pos_r = 0;
  pos_l = 0;
  int distance;
  if (FirstStep)
  {
    distance = DistanceCM(31);
    FirstStep = 0;
  }
  else
  {
    distance = DistanceCM(32);
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
  int i=16;
  while (i!=0)
  {
  stopModified();
  i--;  
  }
  
  startMove = 0;
  pos_r = 0;
  pos_l = 0;
  //  while (pos_l != 3)        //7 in first test
  //  {
  //    analogWrite(ENL, spd);
  //    analogWrite(ENR, spd);
  //
  //    digitalWrite(ML1, 1);
  //    digitalWrite(ML2, 0);
  //
  //    digitalWrite(MR1, 0);
  //    digitalWrite(MR2, 0);
  //  }
  STOP();
  pos_r = 0;
  pos_l = 0;

  digitalWrite(MR1, 1);
  digitalWrite(MR2, 1);


  digitalWrite(ML1, 0);
  digitalWrite(ML2, 1);

  analogWrite(ENR, 0);
  analogWrite(ENL, 0);

  delay(100);

  digitalWrite(MR1, 0);
  digitalWrite(MR2, 0);


  digitalWrite(ML1, 0);
  digitalWrite(ML2, 0);

  analogWrite(ENR, 0);
  analogWrite(ENL, 0);
}


/*************************************************************************/
/********************* Rigth with Angle 90  ******************************/
/*************************************************************************/
void right_90()
{
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


  while (Yaw != 90 ) {
    MpuUpdate();
    Yaw = P.angZ;
    //    Serial.print("yaw in");
    //    Serial.println(Yaw);

    if (Yaw < flag + 85)
    {
      motor_l(step++);
      motor_r(-step);
    }
    else  if (Yaw > flag + 93)
    {
      motor_l(-step);
      motor_r(step++);
    }
    else
    {
      stopModified();
      if (Yaw <= 92 || Yaw >= 88)
      {
        stopModified();
        P.clearAng();
        pos_r = 0;
        pos_l = 0;
        break;
      }
    }
    MpuUpdate();
    Yaw = P.angZ;

  }
}
/*************************************************************************/
/********************* Left with Angle 90  ******************************/
/*************************************************************************/
void left_90()
{
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
/*************************************************************************/
/********************* Rigth with Angle 180  *****************************/
/*************************************************************************/
void right_180()
{
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


  while (Yaw != 180 ) {
    MpuUpdate();
    Yaw = P.angZ;
    //    Serial.print("yaw in");
    //    Serial.println(Yaw);

    if (Yaw < flag + 175)
    {
      motor_l(step++);
      motor_r(-step);
    }
    else  if (Yaw > flag + 183)
    {
      motor_l(-step);
      motor_r(step++);
    }
    else
    {
      stopModified();
      if (Yaw <= 182 || Yaw >= 173)
      {
        stopModified();
        P.clearAng();
        pos_r = 0;
        pos_l = 0;
        break;
      }
    }
    MpuUpdate();
    Yaw = P.angZ;

  }
}

/******************************************************************************************/
/*********************************** Modify using PID  ************************************/
/******************************************************************************************/
void stopModified()
{
  int stop_atR = pos_r;
  int stop_atL = pos_l;
  while (pos_r > stop_atR && pos_l > stop_atL)
  {
    if (pos_r > stop_atR)
    {
      motor_r(stop_atR);
    }
    if (pos_l > stop_atL)
    {
      motor_l(stop_atL);
    }
  }
  digitalWrite(ML1, 0);
  digitalWrite(ML2, 0);

  digitalWrite(MR1, 0);
  digitalWrite(MR2, 0);
}
