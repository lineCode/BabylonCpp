#ifndef BABYLON_SAMPLES_ANIMATIONS_ANIMATIONS_SCENE_H
#define BABYLON_SAMPLES_ANIMATIONS_ANIMATIONS_SCENE_H

#include <babylon/interfaces/irenderable_scene.h>

namespace BABYLON {
namespace Samples {

/**
 * @brief Animations scene. Example demonstrating how to add animations.
 * @see https://doc.babylonjs.com/babylon101/animations
 */
struct AnimationsScene : public IRenderableScene {

  AnimationsScene(ICanvas* iCanvas);
  ~AnimationsScene() override;

  const char* getName() override;
  void initializeScene(ICanvas* canvas, Scene* scene) override;

}; // end of struct AnimationsScene

} // end of namespace Samples
} // end of namespace BABYLON

#endif // end of BABYLON_SAMPLES_ANIMATIONS_ANIMATIONS_SCENE_H
