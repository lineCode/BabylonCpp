#ifndef BABYLON_MESH_MESH_LOD_LEVEL_H
#define BABYLON_MESH_MESH_LOD_LEVEL_H

#include <babylon/babylon_api.h>

namespace BABYLON {

class Mesh;

/**
 * @brief Class used to represent a specific level of detail of a mesh.
 * @see http://doc.babylonjs.com/how_to/how_to_use_lod
 */
class BABYLON_SHARED_EXPORT MeshLODLevel {

public:
  /**
   * @brief Creates a new LOD level.
   * @param distance defines the distance where this level should star being
   * displayed
   * @param mesh defines the mesh to use to render this level
   */
  MeshLODLevel(float distance, Mesh* mesh);
  MeshLODLevel(const MeshLODLevel& other);
  MeshLODLevel(MeshLODLevel&& other);
  MeshLODLevel& operator=(const MeshLODLevel& other);
  MeshLODLevel& operator=(MeshLODLevel&& other);
  ~MeshLODLevel();

  bool operator==(const MeshLODLevel& other) const;
  bool operator!=(const MeshLODLevel& other) const;

public:
  /**
   * Defines the distance where this level should star being displayed
   */
  float distance;

  /**
   * Defines the mesh to use to render this level
   */
  Mesh* mesh;

}; // end of class MeshLODLevel

} // end of namespace BABYLON

#endif // end of BABYLON_MESH_MESH_LOD_LEVEL_H
