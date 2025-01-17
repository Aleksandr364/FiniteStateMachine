#include "Test_FSM.h"
#include "FSM.h"

void TestFSM()
{
  FSM testData;
  TestStruct s;

  testData.Step(Signals::Start, s);
  testData.Step(Signals::Timeout, s);
  testData.Step(Signals::Start, s);
}