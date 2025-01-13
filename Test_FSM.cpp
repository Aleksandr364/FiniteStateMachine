#include "Test_FSM.h"
#include "FSM.h"

void TestFSM()
{
  FSM testData;

  testData.Step(Signals::Start);
  testData.Step(Signals::Timeout);
  testData.Step(Signals::Start);
}