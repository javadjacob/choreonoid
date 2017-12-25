/**
   \file
   \author Shin'ichiro Nakaoka
*/

#ifndef CNOID_UTIL_COLLISION_DETECTOR_H
#define CNOID_UTIL_COLLISION_DETECTOR_H

#include "Collision.h"
#include "Referenced.h"
#include "exportdecl.h"

namespace cnoid {

class SgNode;

struct CollisionPair {
    Referenced* objects[2];
    int geometryId[2]; ///< \deprecated
    CollisionArray collisions;
};

class CNOID_EXPORT CollisionDetector : public Referenced
{
public:
    static bool registerFactory(const std::string& name, std::function<CollisionDetector*()> factory);
    static int numFactories();
    static std::string factoryName(int factoryIndex);
    static int factoryIndex(const std::string& name);
    static CollisionDetector* create(int factoryIndex);
        
    virtual ~CollisionDetector();
    virtual const char* name() const = 0;

    /**
       \note The geometries and the non interfarence pairs of them
       are not copied to the clone object. That is same as the state
       after calling clearGeometries();
    */
    virtual CollisionDetector* clone() const = 0;
        
    virtual bool enableGeometryCache(bool on) = 0;
    virtual void clearGeometryCache(SgNode* geometry) = 0;
    virtual void clearAllGeometryCaches() = 0;

    virtual void clearGeometries() = 0;
    virtual int numGeometries() const = 0;

    /**
       \return Geometry ID
    */
    virtual int addGeometry(SgNode* geometry, Referenced* object);

    virtual void setGeometryStatic(int geometryId, bool isStatic = true) = 0;
    virtual void setNonInterfarenceGeometyrPair(int geometryId1, int geometryId2) = 0;
    
    virtual bool makeReady() = 0;
    
    virtual void updatePosition(int geometryId, const Position& position) = 0;
    virtual void updatePositions(
        std::function<void(Referenced* object, Position*& out_Position)> positionQuery);

    virtual void detectCollisions(std::function<void(const CollisionPair& collisionPair)> callback) = 0;

    // optional functions
    virtual bool isFindClosestPointsAvailable() const;
    virtual double findClosestPoints(int geometryId1, int geometryId2, Vector3& out_point1, Vector3& out_point2);

    /*
      \deprecated
      \note If this function is overriden, int addToometry(SgNode* geomety, Referenced* object) must not be overriden.
    */
    virtual int addGeometry(SgNode* geometry);
};

typedef ref_ptr<CollisionDetector> CollisionDetectorPtr;

}

#endif
