#include <babylon/mesh/base_sub_mesh.h>

#include <babylon/materials/material_defines.h>

namespace BABYLON {

BaseSubMesh::BaseSubMesh()
    : _materialDefines{nullptr}
    , _materialEffect{nullptr}
    , effect{this, &BaseSubMesh::get_effect}
{
}

BaseSubMesh::~BaseSubMesh()
{
}

EffectPtr& BaseSubMesh::get_effect()
{
  return _materialEffect;
}

void BaseSubMesh::setEffect(const EffectPtr& iEffect)
{
  if (_materialEffect == iEffect) {
    if (!iEffect) {
      _materialDefines = nullptr;
    }
    return;
  }
  _materialDefines = nullptr;
  _materialEffect  = iEffect;
}

void BaseSubMesh::setEffect(const EffectPtr& iEffect,
                            const MaterialDefines& defines)
{
  if (_materialEffect == iEffect) {
    if (!iEffect) {
      _materialDefines = nullptr;
    }
    return;
  }
  _materialDefines = std::make_unique<MaterialDefines>(defines);
  _materialEffect  = iEffect;
}

} // end of namespace BABYLON
