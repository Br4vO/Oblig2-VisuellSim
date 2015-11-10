#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "mainwidget.h"

/** Statemanager which only has a pause function now.
   */
class stateManager
{
public:
  /** Initializer
     */
  stateManager();
  /** Does nothing
     */
  void startProgram();
  /** Changes to paused or not paused
     */
  void pauseProgram();
  /// bool to check if program is paused
  bool pause = false;
};

#endif // STATEMANAGER_H
