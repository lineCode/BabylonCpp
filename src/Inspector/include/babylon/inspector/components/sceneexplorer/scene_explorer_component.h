#ifndef BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_SCENE_EXPLORER_COMPONENT_H
#define BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_SCENE_EXPLORER_COMPONENT_H

#include <memory>

#include <babylon/babylon_api.h>

namespace BABYLON {

class CameraTreeItemComponent;
class LightTreeItemComponent;
class MaterialTreeItemComponent;
class MeshTreeItemComponent;
class Scene;

struct ISceneExplorerComponentProps {
  Scene* scene;
}; // end of struct ISceneExplorerComponentProps

class BABYLON_SHARED_EXPORT SceneExplorerComponent {

public:
  SceneExplorerComponent(const ISceneExplorerComponentProps& props);
  ~SceneExplorerComponent();

  void render();

private:
  ISceneExplorerComponentProps props;
  // Testing
  std::unique_ptr<CameraTreeItemComponent> _cameraTreeItemComponent;
  std::unique_ptr<LightTreeItemComponent> _lightTreeItemComponent;
  std::unique_ptr<MeshTreeItemComponent> _meshTreeItemComponent;
  std::unique_ptr<MaterialTreeItemComponent> _materialTreeItemComponent;

}; // end of class SceneExplorerComponent

} // end of namespace BABYLON

#endif // end of
       // BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_SCENE_EXPLORER_COMPONENT_H
