#ifndef BABYLON_MESH_PRIMITIVE_GEOMETRIES_GROUND_GEOMETRY_H
#define BABYLON_MESH_PRIMITIVE_GEOMETRIES_GROUND_GEOMETRY_H

#include <babylon/babylon_api.h>
#include <babylon/mesh/mesh.h>
#include <babylon/mesh/primitivegeometries/_primitive_geometry.h>

namespace BABYLON {

class GroundGeometry;
using GroundGeometryPtr = std::shared_ptr<GroundGeometry>;

/**
 * @brief Creates a new ground geometry.
 * @see http://doc.babylonjs.com/how_to/set_shapes#ground
 */
class BABYLON_SHARED_EXPORT GroundGeometry : public _PrimitiveGeometry {

public:
  template <typename... Ts>
  static GroundGeometryPtr New(Ts&&... args)
  {
    auto mesh = std::shared_ptr<GroundGeometry>(
      new GroundGeometry(std::forward<Ts>(args)...));
    mesh->addToScene(mesh);

    return mesh;
  }
  ~GroundGeometry() override;

  /**
   * @brief Hidden
   * @return
   */
  std::unique_ptr<VertexData> _regenerateVertexData() override;

  GeometryPtr copy(const std::string& id) override;
  json serialize() const override;

  // Statics
  static GroundGeometryPtr Parse(const json& parsedGround, Scene* scene);

protected:
  /**
   * @brief Creates a new ground geometry.
   * @param id defines the unique ID of the geometry
   * @param scene defines the hosting scene
   * @param width defines the width of the ground
   * @param height defines the height of the ground
   * @param subdivisions defines the subdivisions to apply to the ground
   * @param canBeRegenerated defines if the geometry supports being regenerated
   * with new parameters (false by default)
   * @param mesh defines the hosting mesh (can be null)
   */
  GroundGeometry(const std::string& id, Scene* scene, unsigned int width,
                 unsigned int height, unsigned int subdivisions,
                 bool canBeRegenerated, Mesh* mesh = nullptr);

public:
  /**
   * Defines the width of the ground
   */
  unsigned int width;

  /**
   * Defines the height of the ground
   */
  unsigned int height;

  /**
   * Defines the subdivisions to apply to the ground
   */
  unsigned int subdivisions;

}; // end of class GroundGeometry

} // end of namespace BABYLON

#endif // end of BABYLON_MESH_PRIMITIVE_GEOMETRIES_GROUND_GEOMETRY_H
