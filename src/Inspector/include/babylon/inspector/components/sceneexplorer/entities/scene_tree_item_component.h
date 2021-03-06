#ifndef BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_ENTITIES_SCENE_TREE_ITEM_COMPONENT_H
#define BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_ENTITIES_SCENE_TREE_ITEM_COMPONENT_H

#include <functional>
#include <memory>

#include <babylon/babylon_api.h>
#include <babylon/imgui/icons_font_awesome_5.h>

namespace BABYLON {

class Camera;
class Scene;
using CameraPtr = std::shared_ptr<Camera>;

struct ISceneTreeItemComponentProps {
  CameraPtr camera                = nullptr;
  std::function<void()> onRefresh = nullptr;
}; // end of struct ISceneTreeItemComponentProps

struct SceneTreeItemComponentState {
  bool isSelected      = false;
  bool isInPickingMode = false;
  unsigned int gizmoMode;
}; // end of struct SceneTreeItemComponentState

class BABYLON_SHARED_EXPORT SceneTreeItemComponent {

public:
  /** Font Awesome Icon Unicodes **/
  static constexpr const char* faSyncAlt    = ICON_FA_SYNC_ALT;
  static constexpr const char* faImage      = ICON_FA_IMAGE;
  static constexpr const char* faCrosshairs = ICON_FA_CROSSHAIRS;
  static constexpr const char* faArrowsAlt  = ICON_FA_ARROWS_ALT;
  static constexpr const char* faCompress   = ICON_FA_COMPRESS;
  static constexpr const char* faRedoAlt    = ICON_FA_REDO_ALT;

public:
  SceneTreeItemComponent(const ISceneTreeItemComponentProps& props);
  ~SceneTreeItemComponent();

  void componentWillMount();
  void componentWillUnmount();
  void onSelect();
  void onPickingMode();
  void setGizmoMode(unsigned int mode);
  void render();

public:
  ISceneTreeItemComponentProps props;
  SceneTreeItemComponentState state;

}; // end of class SceneTreeItemComponent

} // end of namespace BABYLON

#endif // end of
       // BABYLON_INSPECTOR_COMPONENTS_SCENE_EXPLORER_ENTITIES_SCENE_TREE_ITEM_COMPONENT_H
