#pragma once

enum EVENT
{
  Open,
  Close,
  Stop,
  Resume
};

enum WATER_LEVEL
{
  low,
  belowValve2,
  aboveValve2,
  aboveValve3,
  high
};

enum SLUICE_STATE
{
  WaterLevelLow,
  WaterLevelHigh,
  HighToLow,
  LowToHigh
};

enum DOOR_TYPE
{
  Normal,
  OneSecond,
  Damaged
};

enum DOOR_STATE
{
  doorLocked,
  doorClosed,
  doorOpen,
  doorClosing,
  doorOpening,
  doorStopping,
  motorDamage
};

enum SIDE
{
  LEFT,
  RIGHT
};

enum VALVE_STATE
{
  Opened,
  Closed
};

enum POS
{
  bottom,
  middle,
  top
};


