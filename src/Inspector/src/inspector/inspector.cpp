#include <babylon/inspector/inspector.h>

#include <iomanip>
#include <sstream>

// GLFW
#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

// ImGui
#include <imgui.h>

// ImGui GL2
#include <babylon/imgui/imgui_impl_glfw_gl2.h>

// ImGUI bindings and utils
#include <babylon/imgui/icons_font_awesome_5.h>
#include <babylon/imgui/imgui_utils.h>

// BabylonCpp
#include <babylon/core/string.h>

// Inspector
#include <babylon/inspector/actions/action_store.h>
#include <babylon/inspector/components/actiontabs/action_tabs_component.h>
#include <babylon/inspector/components/sceneexplorer/scene_explorer_component.h>

namespace BABYLON {

static ImFont* _fontRegular = nullptr;
static ImFont* _fontSolid   = nullptr;

Inspector::Inspector(GLFWwindow* glfwWindow, Scene* scene)
    : _glfwWindow{glfwWindow}
    , _scene{scene}
    , _actionStore{std::make_unique<ActionStore>()}
    , _showInspectorWindow{true}
    , _sceneExplorerHost{nullptr}
    , _actionTabsHost{nullptr}
{
}

Inspector::~Inspector()
{
}

Scene* Inspector::scene() const
{
  return _scene;
}

void Inspector::setScene(Scene* scene)
{
  _scene = scene;

  // Create Scene explorer
  ISceneExplorerComponentProps sceneExplorerComponentProps;
  sceneExplorerComponentProps.scene = scene;
  _sceneExplorerHost
    = std::make_unique<SceneExplorerComponent>(sceneExplorerComponentProps);

  // Create action tabs
  IActionTabsComponentProps actionTabsComponentProps;
  actionTabsComponentProps.scene = scene;
  _actionTabsHost
    = std::make_unique<ActionTabsComponent>(actionTabsComponentProps);
}

void Inspector::intialize()
{
  // Setup ImGui binding
  ImGui::CreateContext();
  ImGui_ImplGlfwGL2_Init(_glfwWindow, true);
  // Loads fonts
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  static ImWchar ranges[] = {0xf000, 0xf82f, 0};
  ImFontConfig config;
  config.MergeMode = true;
  auto fontRegularPath
    = String::concat("../assets/fonts/", FONT_ICON_FILE_NAME_FAR);
  _fontRegular = io.Fonts->AddFontFromFileTTF(fontRegularPath.c_str(), 12.0f,
                                              &config, ranges);
  auto fontSolidPath
    = String::concat("../assets/fonts/", FONT_ICON_FILE_NAME_FAS);
  _fontSolid = io.Fonts->AddFontFromFileTTF(fontSolidPath.c_str(), 12.0f,
                                            &config, ranges);
  // Setup style
  ImGui::StyleColorsDark();
  // Actions
  _addActions();
}

void Inspector::render()
{
  // New ImGUI frame
  ImGui_ImplGlfwGL2_NewFrame();
  // Push Font
  _pushFonts();
  // Render main menu bar
  if (ImGui::BeginMainMenuBar()) {
    _fileMenu();
    {
      static std::ostringstream oss;
      oss.str("");
      oss << std::fixed << std::setprecision(1);
      oss << "FPS: " << ImGui::GetIO().Framerate << std::ends;
      oss << std::resetiosflags(std::ios_base::fixed
                                | std::ios_base::floatfield);
      const char* stats = oss.str().data();
      auto statsSize    = ImGui::CalcTextSize(stats);
      ImGui::SameLine(ImGui::GetContentRegionMax().x - statsSize.x);
      ImGui::Text("%s", stats);
    }
    _menuHeight = static_cast<int>(ImGui::GetWindowSize().y);
    ImGui::EndMainMenuBar();
  }
  // Render dock widgets
  _renderInspector();
  // Pop font
  _popFonts();
  // Rendering
  ImGui::Render();
  ImGui_ImplGlfwGL2_RenderDrawData(ImGui::GetDrawData());
}

void Inspector::dispose()
{
  // Shutdown ImGui
  ImGui_ImplGlfwGL2_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(_glfwWindow);
}

void Inspector::_fileMenu()
{
  if (!ImGui::BeginMenu("File")) {
    return;
  }
  _doMenuItem(*_actionStore->getAction("exit"), true);
  ImGui::EndMenu();
}

void Inspector::_addActions()
{
  _actionStore->addAction("exit", ICON_FA_POWER_OFF, "Exit", "Alt+F4", []() {});
}

void Inspector::_doMenuItem(InspectorAction& a, bool enabled)
{
  if (ImGui::MenuItem(a.iconWithLabel.c_str(), a.shortcut, a.isSelected(),
                      enabled)) {
    a.invoke();
  }
}

void Inspector::_pushFonts()
{
  ImGui::PushFont(_fontRegular);
  ImGui::PushFont(_fontSolid);
}

void Inspector::_popFonts()
{
  ImGui::PopFont();
  ImGui::PopFont();
}

void Inspector::_renderInspector()
{
  if (ImGui::GetIO().DisplaySize.y <= 0) {
    return;
  }

  // Setup window size
  auto pos  = ImVec2(0, _menuHeight);
  auto size = ImGui::GetIO().DisplaySize;
  size.y -= pos.y;

  ImGui::SetNextWindowPos(pos, ImGuiSetCond_Always);
  ImGui::SetNextWindowSize(size, ImGuiSetCond_Always);
  if (ImGui::Begin("INSPECTOR", &_showInspectorWindow,
                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
                     | ImGuiWindowFlags_NoScrollbar
                     | ImGuiWindowFlags_NoScrollWithMouse
                     | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
    auto width      = ImGui::GetContentRegionMax().x - 4.f;
    static auto sz1 = ImGui::GetContentRegionMax().y / 2.f;
    auto sz2        = ImGui::GetContentRegionMax().y - sz1 - 8.f;
    ImGui::Splitter(false, 1.f, &sz1, &sz2, 4, 4, width);
    // Render the scene explorer
    if (ImGui::BeginChild("SceneExplorer", ImVec2(width, sz1), true)) {
      if (_sceneExplorerHost) {
        _sceneExplorerHost->render();
      }
    }
    ImGui::EndChild();
    // Render the action tabs
    if (ImGui::BeginChild("ActionTabs", ImVec2(width, sz2), true)) {
      if (_actionTabsHost) {
        _actionTabsHost->render();
      }
    }
    ImGui::EndChild();
  }
  ImGui::End();
}

} // end of namespace BABYLON
