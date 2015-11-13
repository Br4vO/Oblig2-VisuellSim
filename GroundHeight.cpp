#include "GroundHeight.h"
#include "HeightMap.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>

#include <math.h>


GroundHeight::GroundHeight()
{
    mMap = new HeightMap();

}

QVector3D GroundHeight::findGround(QVector3D &playerPos)
{
  float lastRegisteredDistance = 10.0f;
    for(int i = 0; i < (128*128); i++)
    {
        if(mMap->mMapData[i].position.distanceToPoint(playerPos) <= 10.0f)
        {
            float tempY = mMap->mMapData[i].position.distanceToPoint(playerPos);
            if (tempY < lastRegisteredDistance)
              {
                playerPos.setY(mMap->mMapData[i].position.y()-1);
                lastRegisteredDistance = tempY;
                //qDebug() << "playerposition = " << playerPos;
              }
        }
    }
    return playerPos;
}
