#include <babylon/materials/pbr/pbr_metallic_roughness_material.h>

#include <nlohmann/json.hpp>

#include <babylon/babylon_stl_util.h>

namespace BABYLON {

PBRMetallicRoughnessMaterial::PBRMetallicRoughnessMaterial(
  const std::string& iName, Scene* scene)
    : PBRBaseSimpleMaterial{iName, scene}
    , baseColor{this, &PBRMetallicRoughnessMaterial::get_baseColor,
                &PBRMetallicRoughnessMaterial::set_baseColor}
    , baseTexture{this, &PBRMetallicRoughnessMaterial::get_baseTexture,
                  &PBRMetallicRoughnessMaterial::set_baseTexture}
    , metallic{this, &PBRMetallicRoughnessMaterial::get_metallic,
               &PBRMetallicRoughnessMaterial::set_metallic}
    , roughness{this, &PBRMetallicRoughnessMaterial::get_roughness,
                &PBRMetallicRoughnessMaterial::set_roughness}
    , metallicRoughnessTexture{
        this, &PBRMetallicRoughnessMaterial::get_metallicRoughnessTexture,
        &PBRMetallicRoughnessMaterial::set_metallicRoughnessTexture}
{
  _useRoughnessFromMetallicTextureAlpha = false;
  _useRoughnessFromMetallicTextureGreen = true;
  _useMetallnessFromMetallicTextureBlue = true;

  metallic  = 1.f;
  roughness = 1.f;
}

PBRMetallicRoughnessMaterial::~PBRMetallicRoughnessMaterial()
{
}

const std::string PBRMetallicRoughnessMaterial::getClassName() const
{
  return "PBRMetallicRoughnessMaterial";
}

Color3& PBRMetallicRoughnessMaterial::get_baseColor()
{
  return _albedoColor;
}

void PBRMetallicRoughnessMaterial::set_baseColor(const Color3& value)
{
  if (_albedoColor == value) {
    return;
  }

  _albedoColor = value;
  _markAllSubMeshesAsTexturesDirty();
}

BaseTexturePtr& PBRMetallicRoughnessMaterial::get_baseTexture()
{
  return _albedoTexture;
}

void PBRMetallicRoughnessMaterial::set_baseTexture(const BaseTexturePtr& value)
{
  if (_albedoTexture == value) {
    return;
  }

  _albedoTexture = value;
  _markAllSubMeshesAsTexturesDirty();
}

float PBRMetallicRoughnessMaterial::get_metallic() const
{
  return _metallic.value_or(1.f);
}

void PBRMetallicRoughnessMaterial::set_metallic(float value)
{
  if (_metallic.has_value()) {
    if (stl_util::almost_equal(_metallic.value(), value)) {
      return;
    }
  }

  _metallic = value;
  _markAllSubMeshesAsTexturesDirty();
}

float PBRMetallicRoughnessMaterial::get_roughness() const
{
  return _roughness.value_or(1.f);
}

void PBRMetallicRoughnessMaterial::set_roughness(float value)
{
  if (_roughness.has_value()) {
    if (stl_util::almost_equal(_roughness.value(), value)) {
      return;
    }
  }

  _roughness = value;
  _markAllSubMeshesAsTexturesDirty();
}

BaseTexturePtr& PBRMetallicRoughnessMaterial::get_metallicRoughnessTexture()
{
  return _metallicTexture;
}

void PBRMetallicRoughnessMaterial::set_metallicRoughnessTexture(
  const BaseTexturePtr& value)
{
  if (_metallicTexture == value) {
    return;
  }

  _metallicTexture = value;
  _markAllSubMeshesAsTexturesDirty();
}

std::vector<BaseTexturePtr>
PBRMetallicRoughnessMaterial::getActiveTextures() const
{
  auto activeTextures = PBRBaseSimpleMaterial::getActiveTextures();

  if (baseTexture()) {
    activeTextures.emplace_back(baseTexture);
  }

  if (metallicRoughnessTexture()) {
    activeTextures.emplace_back(metallicRoughnessTexture);
  }

  return activeTextures;
}

bool PBRMetallicRoughnessMaterial::hasTexture(
  const BaseTexturePtr& texture) const
{
  if (PBRBaseSimpleMaterial::hasTexture(texture)) {
    return true;
  }

  if (baseTexture() == texture) {
    return true;
  }

  if (metallicRoughnessTexture() == texture) {
    return true;
  }

  return false;
}

MaterialPtr PBRMetallicRoughnessMaterial::clone(const std::string& /*name*/,
                                                bool /*cloneChildren*/) const
{
  return nullptr;
}

json PBRMetallicRoughnessMaterial::serialize() const
{
  return nullptr;
}

PBRMetallicRoughnessMaterial*
PBRMetallicRoughnessMaterial::Parse(const json& /*source*/, Scene* /*scene*/,
                                    const std::string& /*rootUrl*/)
{
  return nullptr;
}

} // end of namespace BABYLON
