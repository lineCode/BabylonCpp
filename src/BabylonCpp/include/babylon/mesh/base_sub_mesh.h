#ifndef BABYLON_MESH_BASE_SUB_MESH_H
#define BABYLON_MESH_BASE_SUB_MESH_H

#include <memory>

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>

namespace BABYLON {

class Effect;
struct MaterialDefines;
using EffectPtr = std::shared_ptr<Effect>;

/**
 * @brief Base class for submeshes.
 */
class BABYLON_SHARED_EXPORT BaseSubMesh {

public:
  BaseSubMesh();
  ~BaseSubMesh();

  /**
   * @brief Sets associated effect (effect used to render this submesh).
   * @param effect defines the effect to associate with
   * @param defines defines the set of defines used to compile this effect
   */
  void setEffect(const EffectPtr& effect);
  void setEffect(const EffectPtr& effect, const MaterialDefines& defines);

protected:
  /**
   * @brief Gets the associated effect.
   */
  EffectPtr& get_effect();

public:
  /**
   * Hidden
   */
  std::unique_ptr<MaterialDefines> _materialDefines;

  /**
   * Hidden
   */
  EffectPtr _materialEffect;

  /**
   * Gets associated effect
   */
  ReadOnlyProperty<BaseSubMesh, EffectPtr> effect;

}; // end of class BaseSubMesh

} // end of namespace BABYLON

#endif // end of BABYLON_MESH_BASE_SUB_MESH_H
