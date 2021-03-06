#ifndef BABYLON_SAMPLES_MATERIALS_PBR_METALLIC_ROUGHNESS_TEXTURE_MATERIAL_SCENE_H
#define BABYLON_SAMPLES_MATERIALS_PBR_METALLIC_ROUGHNESS_TEXTURE_MATERIAL_SCENE_H

#include <babylon/interfaces/irenderable_scene.h>

namespace BABYLON {
namespace Samples {

/**
 * @brief PBR Metallic Roughness Texture Material Scene. Example demonstrating
 * how to create physically based rendering metallic roughness materials.
 * @see https://www.babylonjs-playground.com/#2FDQT5#13
 * @see https://doc.babylonjs.com/how_to/physically_based_rendering
 */
struct PBRMetallicRoughnessTextureMaterialScene : public IRenderableScene {

  PBRMetallicRoughnessTextureMaterialScene(ICanvas* iCanvas);
  ~PBRMetallicRoughnessTextureMaterialScene() override;

  const char* getName() override;
  void initializeScene(ICanvas* canvas, Scene* scene) override;

}; // end of struct PBRMetallicRoughnessTextureMaterialScene

} // end of namespace Samples
} // end of namespace BABYLON

#endif // end of
       // BABYLON_SAMPLES_MATERIALS_PBR_METALLIC_ROUGHNESS_TEXTURE_MATERIAL_SCENE_H
