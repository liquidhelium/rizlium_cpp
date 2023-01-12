#ifndef KEYPOINTSUTIL_H
#define KEYPOINTSUTIL_H
#include "bisect.h"
#include "easing.h"
#include "rizTypes.h"
#include <vector>
using namespace rizTypes;
int findKeypoint_floorPos(std::vector<KeyPoint> keyPoints, float time)
{
    return bisectByKey<KeyPoint>(keyPoints, time, [](KeyPoint x) {return x.floorPosition; })-1;
}

int findKeypoint_time(std::vector<KeyPoint> keyPoints, float time)
{
    return bisectByKey<KeyPoint>(keyPoints, time, [](KeyPoint x) {return x.time; })-1;
}
// time: rizTime
float getValue(const std::vector<KeyPoint> &keyPoints,float time)
{
    if (keyPoints.size() < 1)
    {
        qWarning() << "empty keypoints";
        return 0;
    }
    if (time <= keyPoints[0].time)
        return keyPoints[0].value;
    if (time >= keyPoints[keyPoints.size()-1].time)
        return keyPoints[keyPoints.size()-1].value;
    int index = findKeypoint_time(keyPoints, time);
    return lerpWithEase(
        easing[keyPoints[index].easeType],
        keyPoints[index].value,
        keyPoints[index + 1].value,
        inverseLerp(keyPoints[index].time, keyPoints[index + 1].time, time)
    );
}

float getIntegration(const std::vector<KeyPoint> &keyPoints, float time)
{
    if (keyPoints.size() < 1)
    {
        qWarning() << "getIntegration: empty keypoints";
        return 0;

    }
    if (time <= keyPoints[0].time)
        return keyPoints[0].floorPosition;
    if (time >= keyPoints[keyPoints.size()-1].time)
        return keyPoints[keyPoints.size()-1].floorPosition;
    int index = findKeypoint_time(keyPoints, time);
    return keyPoints[index].floorPosition + keyPoints[index].value * (time - keyPoints[index].time);
}
#endif
