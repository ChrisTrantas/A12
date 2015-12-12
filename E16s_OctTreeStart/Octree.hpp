#pragma once

#include "MyBOClass.h"
#include "MyEntityClass.h"
#include <array>
#include <memory>
#include <vector>
#include <unordered_map>

// Defines an octree
class Octree
{
    static std::unordered_map<MyBOClass*, Octree*> ObjectOctreeCache;

    const int _subdivision;
    MyBOClass _bounds;
    std::array<std::shared_ptr<Octree>, 8> _children;
    std::shared_ptr<std::vector<MyBOClass*>> _objects; // Because we won't always have objects

    Octree( const Octree& ) = delete;
    Octree& operator=( const Octree& ) = delete;
    Octree( Octree&& ) = delete;
    Octree& operator=( Octree&& ) = delete;

    // Used to create child octrees
    Octree( int subdivision, vector3 center, vector3 size );

    // Subdivides this octree
    bool Subdivide();

public:
    // Creates a new octree
    Octree();

    // Destroys this octree
    ~Octree();

    // Adds an object to this octree
    bool AddObject( MyBOClass* object );

    // Clears this octree
    void Clear();

    // Draws this octree
    void Draw();

    // Gets the number of objects accounted for
	size_t GetObjectCount() const;

    // Checks to see if the given object is colliding with anything else
    bool IsColliding( MyBOClass* object ) const;

    // Rebuild the octree based on all entities
    void Rebuild();
};
