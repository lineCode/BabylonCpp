#ifndef BABYLON_MATERIALS_TEXTURES_RENDER_TARGET_TEXTURE_H
#define BABYLON_MATERIALS_TEXTURES_RENDER_TARGET_TEXTURE_H

#include <babylon/babylon_api.h>
#include <babylon/engine/engine_constants.h>
#include <babylon/materials/textures/irender_target_options.h>
#include <babylon/materials/textures/texture.h>
#include <babylon/tools/observable.h>
#include <babylon/tools/observer.h>

namespace BABYLON {

class AbstractMesh;
class Camera;
class Engine;
class PostProcess;
class PostProcessManager;
class RenderingManager;
class RenderTargetTexture;
class SubMesh;
using AbstractMeshPtr             = std::shared_ptr<AbstractMesh>;
using CameraPtr                   = std::shared_ptr<Camera>;
using PostProcessPtr              = std::shared_ptr<PostProcess>;
using RenderTargetCreationOptions = IRenderTargetOptions;
using RenderTargetTexturePtr      = std::shared_ptr<RenderTargetTexture>;
using SubMeshPtr                  = std::shared_ptr<SubMesh>;

class BABYLON_SHARED_EXPORT RenderTargetTexture : public Texture {

private:
  static constexpr unsigned int _REFRESHRATE_RENDER_ONCE             = 0;
  static constexpr unsigned int _REFRESHRATE_RENDER_ONEVERYFRAME     = 1;
  static constexpr unsigned int _REFRESHRATE_RENDER_ONEVERYTWOFRAMES = 2;

public:
  static constexpr unsigned int REFRESHRATE_RENDER_ONCE()
  {
    return RenderTargetTexture::_REFRESHRATE_RENDER_ONCE;
  }

  static constexpr unsigned int REFRESHRATE_RENDER_ONEVERYFRAME()
  {
    return RenderTargetTexture::_REFRESHRATE_RENDER_ONEVERYFRAME;
  }

  static constexpr unsigned int REFRESHRATE_RENDER_ONEVERYTWOFRAMES()
  {
    return RenderTargetTexture::_REFRESHRATE_RENDER_ONEVERYTWOFRAMES;
  }

public:
  template <typename... Ts>
  static RenderTargetTexturePtr New(Ts&&... args)
  {
    auto texture = std::shared_ptr<RenderTargetTexture>(
      new RenderTargetTexture(std::forward<Ts>(args)...));
    texture->addToScene(texture);

    return texture;
  }
  ~RenderTargetTexture() override;

  /**
   * @brief Creates a depth stencil texture.
   * This is only available in WebGL 2 or with the depth texture extension
   * available.
   * @param comparisonFunction Specifies the comparison function to set on the
   * texture. If 0 or undefined, the texture is not in comparison mode
   * @param bilinearFiltering Specifies whether or not bilinear filtering is
   * enable on the texture
   * @param generateStencil Specifies whether or not a stencil should be
   * allocated in the texture
   */
  void createDepthStencilTexture(int comparisonFunction = 0,
                                 bool bilinearFiltering = true,
                                 bool generateStencil   = false);

  void _onRatioRescale();

  RenderTargetCreationOptions& renderTargetOptions();
  const RenderTargetCreationOptions& renderTargetOptions() const;
  void resetRefreshCounter();
  void addPostProcess(const PostProcessPtr& postProcess);
  void clearPostProcesses(bool dispose = false);
  void removePostProcess(const PostProcessPtr& postProcess);
  /** Hidden */
  bool _shouldRender();
  bool isReady() override;
  ISize& getRenderSize();
  int getRenderWidth() const;
  int getRenderHeight() const;
  bool canRescale() const;
  void scale(float ratio) override;
  Matrix* getReflectionTextureMatrix() override;
  void resize(const ISize& size);
  void render(bool useCameraPostProcess = false, bool dumpForDebug = false);

  /**
   * @brief Overrides the default sort function applied in the renderging group
   * to prepare the meshes.
   * This allowed control for front to back rendering or reversly depending of
   * the special needs.   *
   * @param renderingGroupId The rendering group id corresponding to its index
   * @param opaqueSortCompareFn The opaque queue comparison function use to
   * sort.
   * @param alphaTestSortCompareFn The alpha test queue comparison function use
   * to sort.
   * @param transparentSortCompareFn The transparent queue comparison function
   * use to sort.
   */
  void setRenderingOrder(
    unsigned int renderingGroupId,
    const std::function<int(const SubMeshPtr& a, const SubMeshPtr& b)>&
      opaqueSortCompareFn
    = nullptr,
    const std::function<int(const SubMeshPtr& a, const SubMeshPtr& b)>&
      alphaTestSortCompareFn
    = nullptr,
    const std::function<int(const SubMeshPtr& a, const SubMeshPtr& b)>&
      transparentSortCompareFn
    = nullptr);

  /**
   * @brief Specifies whether or not the stencil and depth buffer are cleared
   * between two rendering groups.
   * @param renderingGroupId The rendering group id corresponding to its index
   * @param autoClearDepthStencil Automatically clears depth and stencil between
   * groups if true.
   */
  void setRenderingAutoClearDepthStencil(unsigned int renderingGroupId,
                                         bool autoClearDepthStencil);
  RenderTargetTexturePtr clone();
  Json::object serialize() const;

  /**
   * @brief This will remove the attached framebuffer objects. The texture will
   * not be able to be used as render target anymore.
   */
  void disposeFramebufferObjects();

  void dispose() override;
  /** Hidden */
  void _rebuild() override;

  /**
   * @brief Clear the info related to rendering groups preventing retention
   * point in material dispose.
   */
  void freeRenderingGroups();

protected:
  /**
   * @brief Instantiate a render target texture. This is mainly to render of
   * screen the scene to for instance apply post processse or used a shadow,
   * depth texture...
   * @param name The friendly name of the texture
   * @param size The size of the RTT (number if square, or {with: number,
   * height:number} or {ratio:} to define a ratio from the main scene)
   * @param scene The scene the RTT belongs to. The latest created scene will be
   * used if not precised.
   * @param generateMipMaps True if mip maps need to be generated after render.
   * @param doNotChangeAspectRatio True to not change the aspect ratio of the
   * scene in the RTT
   * @param type The type of the buffer in the RTT (int, half float, float...)
   * @param isCube True if a cube texture needs to be created
   * @param samplingMode The sampling mode to be usedwith the render target
   * (Linear, Nearest...)
   * @param generateDepthBuffer True to generate a depth buffer
   * @param generateStencilBuffer True to generate a stencil buffer
   * @param isMulti True if multiple textures need to be created (Draw Buffers)
   * @param format The internal format of the buffer in the RTT (RED, RG, RGB,
   * RGBA, ALPHA...)
   */
  RenderTargetTexture(
    const std::string& name, const ISize& size, Scene* scene,
    bool generateMipMaps = false, bool doNotChangeAspectRatio = true,
    unsigned int type         = EngineConstants::TEXTURETYPE_UNSIGNED_INT,
    bool isCube               = false,
    unsigned int samplingMode = TextureConstants::TRILINEAR_SAMPLINGMODE,
    bool generateDepthBuffer = true, bool generateStencilBuffer = false,
    bool isMulti        = false,
    unsigned int format = EngineConstants::TEXTUREFORMAT_RGBA);

  /**
   * @brief Use this list to define the list of mesh you want to render.
   */
  std::vector<AbstractMeshPtr>& get_renderList();
  void set_renderList(const std::vector<AbstractMeshPtr>& value);

  /**
   * @brief Gets or sets the size of the bounding box associated with the
   * texture (when in cube mode) When defined, the cubemap will switch to local
   * mode
   * @see
   * https://community.arm.com/graphics/b/blog/posts/reflections-based-on-local-cubemaps-in-unity
   * Example: https://www.babylonjs-playground.com/#RNASML
   */
  virtual void
  set_boundingBoxSize(const std::optional<Vector3>& value) override;
  virtual std::optional<Vector3>& get_boundingBoxSize() override;

  /** Events **/
  void set_onAfterUnbind(
    const std::function<void(RenderTargetTexture*, EventState&)>& callback);
  void set_onBeforeRender(
    const std::function<void(int* faceIndex, EventState&)>& callback);
  void set_onAfterRender(
    const std::function<void(int* faceIndex, EventState&)>& callback);
  void
  set_onClear(const std::function<void(Engine* engine, EventState&)>& callback);

  virtual unsigned int get_samples() const;
  virtual void set_samples(unsigned int value);
  int get_refreshRate() const;
  void set_refreshRate(int value);

  void unbindFrameBuffer(Engine* engine, unsigned int faceIndex);

private:
  void _processSizeParameter(const ISize& size);
  int _bestReflectionRenderTargetDimension(int renderDimension,
                                           float scale) const;
  void renderToTarget(unsigned int faceIndex,
                      const std::vector<AbstractMeshPtr>& currentRenderList,
                      size_t currentRenderListLength, bool useCameraPostProcess,
                      bool dumpForDebug);

public:
  /**
   * Use this predicate to dynamically define the list of mesh you want to
   * render.
   * If set, the renderList property will be overwritten.
   */
  std::function<bool(AbstractMesh*)> renderListPredicate;

  /**
   * Use this list to define the list of mesh you want to render
   */
  Property<RenderTargetTexture, std::vector<AbstractMeshPtr>> renderList;

  bool renderParticles;
  bool renderSprites;
  CameraPtr activeCamera;
  std::function<void(const std::vector<SubMeshPtr>& opaqueSubMeshes,
                     const std::vector<SubMeshPtr>& alphaTestSubMeshes,
                     const std::vector<SubMeshPtr>& transparentSubMeshes,
                     const std::vector<SubMeshPtr>& depthOnlySubMeshes,
                     const std::function<void()>& beforeTransparents)>
    customRenderFunction;
  bool useCameraPostProcesses;
  bool ignoreCameraViewport;
  std::optional<Color4> clearColor;
  /** Hidden */
  bool _generateMipMaps;
  /** Hidden */
  std::vector<std::string> _waitingRenderList;
  // std::function<void()> onAfterRender;
  // std::function<void()> onBeforeRender;

  /**
   * Gets or sets the center of the bounding box associated with the texture
   * (when in cube mode) It must define where the camera used to render the
   * texture is set
   */
  Vector3 boundingBoxPosition;

  /**
   * In case the RTT has been created with a depth texture, get the associated
   * depth texture.
   * Otherwise, return null.
   */
  InternalTexturePtr depthStencilTexture;

  // Events

  /**
   * An event triggered when the texture is unbind.
   */
  Observable<RenderTargetTexture> onBeforeBindObservable;

  /**
   * An event triggered when the texture is unbind.
   */
  Observable<RenderTargetTexture> onAfterUnbindObservable;

  WriteOnlyProperty<RenderTargetTexture,
                    std::function<void(RenderTargetTexture*, EventState&)>>
    onAfterUnbind;

  /**
   * An event triggered before rendering the texture
   */
  Observable<int> onBeforeRenderObservable;

  WriteOnlyProperty<RenderTargetTexture,
                    std::function<void(int* faceIndex, EventState&)>>
    onBeforeRender;

  /**
   * An event triggered after rendering the texture
   */
  Observable<int> onAfterRenderObservable;

  WriteOnlyProperty<RenderTargetTexture,
                    std::function<void(int* faceIndex, EventState&)>>
    onAfterRender;

  /**
   * An event triggered after the texture clear
   */
  Observable<Engine> onClearObservable;

  WriteOnlyProperty<RenderTargetTexture,
                    std::function<void(Engine* engine, EventState&)>>
    onClear;

  Property<RenderTargetTexture, unsigned int> samples;

  Property<RenderTargetTexture, int> refreshRate;

protected:
  RenderTargetCreationOptions _renderTargetOptions;
  ISize _size;
  ISize _initialSizeParameter;
  float _sizeRatio;
  std::unique_ptr<RenderingManager> _renderingManager;
  bool _doNotChangeAspectRatio;
  int _currentRefreshId;
  int _refreshRate;
  std::unique_ptr<Matrix> _textureMatrix;
  unsigned int _samples;
  Engine* _engine;

private:
  std::vector<AbstractMeshPtr> _renderList;
  std::unique_ptr<PostProcessManager> _postProcessManager;
  std::vector<PostProcessPtr> _postProcesses;
  Observer<Engine>::Ptr _resizeObserver;
  // Events
  Observer<RenderTargetTexture>::Ptr _onAfterUnbindObserver;
  Observer<int>::Ptr _onBeforeRenderObserver;
  Observer<int>::Ptr _onAfterRenderObserver;
  Observer<Engine>::Ptr _onClearObserver;
  // Properties
  int _faceIndex;
  std::optional<Vector3> _boundingBoxSize;

}; // end of class RenderTargetTexture

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_TEXTURES_RENDER_TARGET_TEXTURE_H
