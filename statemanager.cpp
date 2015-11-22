#include "statemanager.h"
#include "mainwidget.h"
#include <QDebug>

stateManager::stateManager()
{
  pause = true;
}

void stateManager::startProgram()
{

}

void stateManager::pauseProgram()
{
  if (pause == false)
    {
      pause = true;
    }
  else
    {
      pause = false;
    }
}

