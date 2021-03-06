/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2007      Scott Lembcke
Copyright (c) 2010      Lam Pham

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SUPPORT_CGPOINTEXTENSION_H__
#define __SUPPORT_CGPOINTEXTENSION_H__

/**
 @file
 Point extensions based on Chipmunk's cpVect file.
 These extensions work both with Point and cpVect.
 
 The "ccp" prefix means: "CoCos2d Point"
 
 Examples:
  - ccpAdd( Point(1,1), Point(2,2) ); // preferred cocos2d way
  - ccpAdd( Point(1,1), Point(2,2) ); // also ok but more verbose
  
  - cpvadd( cpv(1,1), cpv(2,2) ); // way of the chipmunk
  - ccpAdd( cpv(1,1), cpv(2,2) ); // mixing chipmunk and cocos2d (avoid)
  - cpvadd( Point(1,1), Point(2,2) ); // mixing chipmunk and CG (avoid)
 */

#include "cocoa/CCGeometry.h"
#include <math.h>

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

/** Helper macro that creates a Point
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE inline Point ccp(float x, float y)
{
    return Point(x, y);
}

/** Returns opposite of point.
 @return Point
 @since v0.7.2
 @deprecated please use Point::-, for example: -v1
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpNeg(const Point& v)
{
    return -v;
}

/** Calculates sum of two points.
 @return Point
 @since v0.7.2
 @deprecated please use Point::+, for example: v1 + v2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpAdd(const Point& v1, const Point& v2)
{
    return v1 + v2;
}

/** Calculates difference of two points.
 @return Point
 @since v0.7.2
 @deprecated please use Point::-, for example: v1 - v2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpSub(const Point& v1, const Point& v2)
{
    return v1 - v2;
}

/** Returns point multiplied by given factor.
 @return Point
 @since v0.7.2
 @deprecated please use Point::*, for example: v1 * v2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpMult(const Point& v, const float s)
{
    return v * s;
}

/** Calculates midpoint between two points.
 @return Point
 @since v0.7.2
 @deprecated please use it like (v1 + v2) / 2.0f
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpMidpoint(const Point& v1, const Point& v2)
{
    return v1.getMidpoint(v2);
}

/** Calculates dot product of two points.
 @return float
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE float
ccpDot(const Point& v1, const Point& v2)
{
    return v1.dot(v2);
}

/** Calculates cross product of two points.
 @return float
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE float
ccpCross(const Point& v1, const Point& v2)
{
    return v1.cross(v2);
}

/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
 @return Point
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpPerp(const Point& v)
{
    return v.getPerp();
}

/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
 @return Point
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpRPerp(const Point& v)
{
    return v.getRPerp();
}

/** Calculates the projection of v1 over v2.
 @return Point
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpProject(const Point& v1, const Point& v2)
{
    return v1.project(v2);
}

/** Rotates two points.
 @return Point
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpRotate(const Point& v1, const Point& v2)
{
    return v1.rotate(v2);
}

/** Unrotates two points.
 @return Point
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE Point
ccpUnrotate(const Point& v1, const Point& v2)
{
    return v1.unrotate(v2);
}

/** Calculates the square length of a Point (not calling sqrt() )
 @return float
 @since v0.7.2
 */
static inline CC_DEPRECATED_ATTRIBUTE float
ccpLengthSQ(const Point& v)
{
    return v.getLengthSq();
}


/** Calculates the square distance between two points (not calling sqrt() )
 @return float
 @since v1.1
*/
static inline CC_DEPRECATED_ATTRIBUTE float
ccpDistanceSQ(const Point p1, const Point p2)
{
    return (p1 - p2).getLengthSq();
}


/** Calculates distance between point an origin
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE float CC_DLL ccpLength(const Point& v);

/** Calculates the distance between two points
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE float CC_DLL ccpDistance(const Point& v1, const Point& v2);

/** Returns point multiplied to a length of 1.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpNormalize(const Point& v);

/** Converts radians to a normalized vector.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpForAngle(const float a);

/** Converts a vector to radians.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE float CC_DLL ccpToAngle(const Point& v);


/** Clamp a point between from and to.
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpClamp(const Point& p, const Point& from, const Point& to);

/** Quickly convert Size to a Point
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpFromSize(const Size& s);

/** Run a math operation function on each point component
 * absf, fllorf, ceilf, roundf
 * any function that has the signature: float func(float);
 * For example: let's try to take the floor of x,y
 * ccpCompOp(p,floorf);
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpCompOp(const Point& p, float (*opFunc)(float));

/** Linear Interpolation between two points a and b
 @returns
    alpha == 0 ? a
    alpha == 1 ? b
    otherwise a value between a..b
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpLerp(const Point& a, const Point& b, float alpha);


/** @returns if points have fuzzy equality which means equal with some degree of variance.
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE bool CC_DLL ccpFuzzyEqual(const Point& a, const Point& b, float variance);


/** Multiplies a and b components, a.x*b.x, a.y*b.y
 @returns a component-wise multiplication
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpCompMult(const Point& a, const Point& b);

/** @returns the signed angle in radians between two vector directions
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE float CC_DLL ccpAngleSigned(const Point& a, const Point& b);

/** @returns the angle in radians between two vector directions
 @since v0.99.1
*/
CC_DEPRECATED_ATTRIBUTE float CC_DLL ccpAngle(const Point& a, const Point& b);

/** Rotates a point counter clockwise by the angle around a pivot
 @param v is the point to rotate
 @param pivot is the pivot, naturally
 @param angle is the angle of rotation cw in radians
 @returns the rotated point
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpRotateByAngle(const Point& v, const Point& pivot, float angle);

/** A general line-line intersection test
 @param p1 
    is the startpoint for the first line P1 = (p1 - p2)
 @param p2 
    is the endpoint for the first line P1 = (p1 - p2)
 @param p3 
    is the startpoint for the second line P2 = (p3 - p4)
 @param p4 
    is the endpoint for the second line P2 = (p3 - p4)
 @param s 
    is the range for a hitpoint in P1 (pa = p1 + s*(p2 - p1))
 @param t
    is the range for a hitpoint in P3 (pa = p2 + t*(p4 - p3))
 @return bool 
    indicating successful intersection of a line
    note that to truly test intersection for segments we have to make 
    sure that s & t lie within [0..1] and for rays, make sure s & t > 0
    the hit point is        p3 + t * (p4 - p3);
    the hit point also is    p1 + s * (p2 - p1);
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE bool CC_DLL ccpLineIntersect(const Point& p1, const Point& p2, 
                      const Point& p3, const Point& p4,
                      float *s, float *t);

/*
ccpSegmentIntersect returns YES if Segment A-B intersects with segment C-D
@since v1.0.0
*/
CC_DEPRECATED_ATTRIBUTE bool CC_DLL ccpSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D);

/*
ccpIntersectPoint returns the intersection point of line A-B, C-D
@since v1.0.0
*/
CC_DEPRECATED_ATTRIBUTE Point CC_DLL ccpIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D);

// end of data_structures group
/// @}

NS_CC_END

#endif // __SUPPORT_CGPOINTEXTENSION_H__

