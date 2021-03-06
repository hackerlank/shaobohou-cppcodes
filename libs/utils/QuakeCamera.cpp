#include "QuakeCamera.h"

#include "Constants.h"

using MathConstants::PI;
using MathConstants::TWO_PI;
using MathConstants::HALF_PI;


QuakeCamera::QuakeCamera()
{
    this->lat = 0.0;
    this->lon = 0.0;
    modOrientation(0.0, 0.0, 0.0);
}

QuakeCamera::QuakeCamera(const Vector3D &pos, double lat, double lon, double runSpeed, double turnSpeed, double sensitivity)
        :BasicCamera(pos, runSpeed, turnSpeed, sensitivity)
{
    this->lat = lat;
    this->lon = lon;
    modOrientation(0.0, 0.0, 0.0);
}

QuakeCamera::~QuakeCamera()
{
}

void QuakeCamera::modOrientation(double rotateX, double rotateY, double rotateZ)
{
    double newLon = lon + rotateY;
    double newLat = lat + rotateX;

    if (newLon < 0.0)
        lon = newLon + TWO_PI;
    else if (newLon > TWO_PI)
        lon = newLon - TWO_PI;
    else
        lon = newLon;

    if ((newLat > -HALF_PI) && (newLat < HALF_PI))
        lat = newLat;

    //need to stack rotation this way to achieve desired Quake cam effect
    orientation = ~(Quaternion::makeFromEulerAngles(lat, 0.0, 0.0) * Quaternion::makeFromEulerAngles(0.0, lon, 0.0));
    this->trueOrientation = orientation * cameraOffset;
}

void QuakeCamera::modOrientation(double changeX, double changeY)
{
    modOrientation(changeY * sensitivity, changeX * sensitivity,  0.0);
}

void QuakeCamera::reset()
{
    lon = PI;
    lat = 0.0;
    position = Vector3D();
    modOrientation(0.0, 0.0, 0.0);
}
