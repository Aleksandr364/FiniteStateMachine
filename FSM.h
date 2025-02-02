#pragma once

#include <vector>
#include <iostream>


struct TestStruct
{
  int x = 0;
  bool y = 0;
  std::vector<int> testV;
};

enum class States
{
  Init,
  Run,
  Show,
  error
};

enum class Signals
{
  Start,
  Stop,
  Timeout
};

//class FSM;
//using FuncType = void (FSM::*)(void); // Тип - указатель на функцию-метод класса FSM (пока пустую).
//             ... void  FSM::X (void)

using FuncType = void (*)(TestStruct&); // Тип - указатель на глобальную функцию (пока пустую).

void Run(TestStruct&);
void Show(TestStruct&);

struct Transition
{
  States state = States::Init;
  FuncType func = nullptr;
};


// Матрица переходов.
//        Start   Stop   Timeout
// Init   Run     error  error
// Run    error   Show   Show
// Show   Run     error  error

class FSM
{
protected:

  std::vector<std::vector<Transition>> TransitionMatrix =
  {
    { {States::Run, Run}, {States::error, nullptr}, {States::error, nullptr} },
    { {States::error, nullptr}, {States::Show, Show}, {States::Show, Show} },
    { {States::Run, Run}, {States::error, nullptr}, {States::error, nullptr} }
  };

  States CurrentState = States::Init;

public:

  void Reset() { CurrentState = States::Init; }

  void Step(Signals signal, TestStruct& s)
  {
    if (CurrentState == States::error)
    {
      std::cout << "\nStates::error!\n";
      return;
    }

    int y = (int)CurrentState;
    int x = (int)signal;
    
    if (y < 0 || y > 2 || x < 0 || x > 2)
    {
      std::cout << "\nWrong x or y!\n";
      return;
    }

    Transition transition = TransitionMatrix[y][x];

    CurrentState = transition.state;
    if (transition.func)
      (*transition.func)(s);
  }

};