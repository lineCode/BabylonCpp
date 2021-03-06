#ifndef BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_FOG_PROPERTY_GRID_COMPONENT_H
#define BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_FOG_PROPERTY_GRID_COMPONENT_H

#include <babylon/babylon_api.h>
#include <babylon/engine/scene.h>
#include <babylon/inspector/components/actiontabs/lines/color3_line_component.h>
#include <babylon/inspector/components/actiontabs/lines/float_line_component.h>
#include <babylon/inspector/components/actiontabs/lines/options_line_component.h>

namespace BABYLON {

struct BABYLON_SHARED_EXPORT FogPropertyGridComponent {

  static void render(Scene* scene)
  {
    static std::vector<std::pair<const char*, unsigned int>> fogModeOptions{
      {"None", Scene::FOGMODE_NONE},
      {"Linear", Scene::FOGMODE_LINEAR},
      {"Exp", Scene::FOGMODE_EXP},
      {"Exp2", Scene::FOGMODE_EXP2},
    };

    const auto& stateMode = scene->fogMode();

    OptionsLineComponent::render(
      "Fog mode", scene->fogMode(), fogModeOptions,
      [&](unsigned int value) { scene->fogMode = value; });
    if (stateMode != Scene::FOGMODE_NONE) {
      Color3LineComponent::render("Fog color", scene->fogColor);
    }
    if (stateMode == Scene::FOGMODE_EXP || stateMode == Scene::FOGMODE_EXP2) {
      FloatLineComponent::render("Fog density", scene->fogDensity);
    }
    if (stateMode == Scene::FOGMODE_LINEAR) {
      FloatLineComponent::render("Fog start", scene->fogStart);
    }
    if (stateMode == Scene::FOGMODE_LINEAR) {
      FloatLineComponent::render("Fog end", scene->fogEnd);
    }
  }

}; // end of struct FogPropertyGridComponent

} // end of namespace BABYLON

#endif // end of
       // BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_FOG_PROPERTY_GRID_COMPONENT_H
