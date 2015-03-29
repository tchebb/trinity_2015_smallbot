/* statemachine.h
 * Header file for state machine.
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum State {
  STARTPUSHED,
  INITIALIZATION,
  WALLFOLLOW,
  INROOM,
  FOUNDFIRE,
  RETURNHOME,
  PUTOUTFIRE,
  ALIGNFIRE,
  HOMEREACHED
};

class StateMachine {
  public:
  StateMachine();

  void tick();

  private:
  State STATE;
};

#endif
