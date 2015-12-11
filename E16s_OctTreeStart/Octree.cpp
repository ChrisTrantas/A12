#include "Octree.hpp"
#include "MyBOManager.h"
#include "MyEntityManager.h"

#define HasSubdivided() (static_cast<bool>( _children[ 0 ] ))

// New octree
Octree::Octree()
    : _bounds( vector3(), vector3() )
    , _subdivision( 0 )
{
    Rebuild();
}

// New child octree
Octree::Octree( int subdivision, vector3 center, vector3 size )
    : _bounds( center - size * 0.5f, center + size * 0.5f )
    , _subdivision( subdivision )
{
}

// Destroy this octree
Octree::~Octree()
{
}

// Add an object to this octree
bool Octree::AddObject( MyBOClass* object )
{
    // Create the object list if it does not exist
    if ( !_objects )
    {
        _objects = std::make_shared<std::vector<MyBOClass*>>();
        if ( !_objects ) return false; // Return if there was an allocation error
    }

    // If we don't contain or intersect the object, don't worry about it
    if ( !_bounds.IsColliding( object ) )
    {
        return false;
    }

    // Make sure we can add the object to our children
    if ( _objects->size() < 3 && !HasSubdivided() )
    {
        _objects->push_back( object );
        return true;
    }
    else
    {
        // If we can't subdivide, then we'll just add it to ourself
        if ( !HasSubdivided() )
        {
            if ( !Subdivide() )
            {
                _objects->push_back( object );
                return true;
            }
        }

        // Try to add the object to our children
        for ( auto& child : _children )
        {
            if ( child->AddObject( object ) )
            {
                return true;
            }
        }
    }

    assert( "Execution shouldn't reach here :D" );
    return false;
}

// Clears this octree
void Octree::Clear()
{
    if ( _objects )
    {
        _objects->clear();
    }
    if ( HasSubdivided() )
    {
        for ( auto& child : _children )
        {
            if ( child ) child->Clear();
        }
    }
}

// Draws this octree
void Octree::Draw()
{
    const vector3 min = _bounds.GetMin();
    const vector3 max = _bounds.GetMax();
    const vector3 center = ( max + min ) * 0.5f;

    MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
    meshManager->AddCubeToQueue( glm::translate( center ) * glm::scale( max - min ), vector3( 1.0f ), ReEng::WIRE );

    if ( HasSubdivided() )
    {
        for ( auto& child : _children )
        {
            if ( child ) child->Draw();
        }
    }
}

// Get the number of items in this octree
size_t Octree::GetObjectCount()
{
    size_t count = 0;

    if ( _objects ) count += _objects->size();

    if ( HasSubdivided() )
    {
        for ( auto& child : _children )
        {
            size_t childCount = child->GetObjectCount();
            count += childCount;
        }
    }

    return count;
}

// Rebuild this octree
void Octree::Rebuild()
{
    Clear();

    vector3 min( FLT_MAX );
    vector3 max = -min;

    // Get the new min and max
    MyBOManager* boManager = MyBOManager::GetInstance();
    for ( size_t i = 0; i < boManager->GetObjectCount(); ++i )
    {
        MyBOClass* bo = boManager->GetBoundingObject( i );
        min = glm::min( min, bo->GetMinG() );
        max = glm::max( max, bo->GetMaxG() );
    }

    // Reset the bounds
    _bounds = MyBOClass( min, max );

    // Add all of the bounding objects
    for ( size_t i = 0; i < boManager->GetObjectCount(); ++i )
    {
        MyBOClass* bo = boManager->GetBoundingObject( i );
        AddObject( bo );
    }
}

// Subdivide this octree
bool Octree::Subdivide()
{
    if ( _subdivision == 3 )
    {
        return false;
    }

    // Get some helper variables
    const vector3 min = _bounds.GetMin();
    const vector3 max = _bounds.GetMax();
    const vector3 center = ( max + min ) * 0.5f;
    const vector3 size = max - min;
    const vector3 hSize = size * 0.5f;
    const vector3 qSize = size * 0.25f;

    // Get the centers of our children
    std::vector<vector3> centers =
    {
        vector3( center.x - qSize.x, center.y - qSize.y, center.z - qSize.z ),
        vector3( center.x - qSize.x, center.y - qSize.y, center.z + qSize.z ),
        vector3( center.x - qSize.x, center.y + qSize.y, center.z - qSize.z ),
        vector3( center.x - qSize.x, center.y + qSize.y, center.z + qSize.z ),
        vector3( center.x + qSize.x, center.y - qSize.y, center.z - qSize.z ),
        vector3( center.x + qSize.x, center.y - qSize.y, center.z + qSize.z ),
        vector3( center.x + qSize.x, center.y + qSize.y, center.z - qSize.z ),
        vector3( center.x + qSize.x, center.y + qSize.y, center.z + qSize.z )
    };

    // Create our children
    for ( size_t iChild = 0; iChild < 8; ++iChild )
    {
        // Create the child
        _children[ iChild ].reset( new Octree( _subdivision + 1, centers[ iChild ], hSize ) );
    
        // Go through our objects and check if we can move them to the current child
        for ( size_t iObj = 0; _objects && iObj < _objects->size(); ++iObj )
        {
            if ( _children[ iChild ]->AddObject( _objects->at( iObj ) ) )
            {
                _objects->erase( _objects->begin() + iObj );
                --iObj;
                break;
            }
        }
    }

    return true;
}
