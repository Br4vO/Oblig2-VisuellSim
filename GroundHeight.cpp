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
    float lastRegisteredDistance = 100.0f;
    float newDistance;
    float tempX = playerPos.x();
    float tempZ = playerPos.z();

    for(int i = 0; i < 128*128; i++)
    {
        tempX = playerPos.x() - mMap->mMapData[i].position.x();
        tempZ = playerPos.z() - mMap->mMapData[i].position.z();

        if(tempX < 0)
        {
            tempX *= -1;
        }
        if(tempZ < 0)
        {
            tempZ *= -1;
        }

        newDistance = tempX + tempZ;

        if(newDistance < lastRegisteredDistance)
        {
            //qDebug() << "newDistance er " << newDistance;
            lastRegisteredDistance = newDistance;
            playerPos.setY(mMap->mMapData[i].position.y()-1);
            //qDebug() << "Player pos " << playerPos;
        }

        //qDebug() << "newDistance er " << newDistance;

    }

//    for(int i = 0; i < (128*128); i++)
//    {
//        if(mMap->mMapData[i].position.distanceToPoint(playerPos) <= 10.0f)
//        {
//            float tempY = mMap->mMapData[i].position.distanceToPoint(playerPos);
//            if (tempY < lastRegisteredDistance)
//            {
//                playerPos.setY(mMap->mMapData[i].position.y()-1);
//                lastRegisteredDistance = tempY;
//            }
//        }
//    }
    return playerPos;
}

int GroundHeight::findVertex(QVector3D &playerPos)
{
    int tempI = 0;
    float lastRegisteredDistance = 10.0f;
    for(int i = 0; i < (128*128); i++)
    {
        if(mMap->mMapData[i].position.distanceToPoint(playerPos) <= 10.0f)
        {
            float tempY = mMap->mMapData[i].position.distanceToPoint(playerPos);

            if (tempY < lastRegisteredDistance)
            {
                tempI = i;
                lastRegisteredDistance = tempY;
            }
        }
    }

    return tempI;
}
