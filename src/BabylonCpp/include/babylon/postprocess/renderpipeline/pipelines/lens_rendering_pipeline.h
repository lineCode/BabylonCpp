#ifndef BABYLON_POSTPROCESS_RENDER_PIPELINE_PIPELINES_LENS_RENDERING_PIPLINE_H
#define BABYLON_POSTPROCESS_RENDER_PIPELINE_PIPELINES_LENS_RENDERING_PIPLINE_H

#include <babylon/babylon_api.h>
#include <babylon/interfaces/idisposable.h>
#include <babylon/postprocess/renderpipeline/post_process_render_pipeline.h>

namespace BABYLON {

class LensRenderingPipeline;
class PostProcess;
class Scene;
class RenderTargetTexture;
class Texture;
using LensRenderingPipelinePtr = std::shared_ptr<LensRenderingPipeline>;
using PostProcessPtr           = std::shared_ptr<PostProcess>;
using TexturePtr               = std::shared_ptr<Texture>;
using RenderTargetTexturePtr   = std::shared_ptr<RenderTargetTexture>;

struct LensRenderingPipelineParameters {
  TexturePtr grain_texture   = nullptr;
  float edge_blur            = 0;
  float grain_amount         = 0;
  float chromatic_aberration = 0;
  float distortion           = 0;
  float dof_gain             = -1;
  float dof_threshold        = 1;
  float dof_focus_distance   = -1;
  float dof_aperture         = 1;
  float dof_darken           = 0;
  bool dof_pentagon          = true;
  bool blur_noise            = true;
}; // end of struct LensRenderingPipelineParameters

/**
 * @brief BABYLON.JS Chromatic Aberration GLSL Shader.
 * Author: Olivier Guyot
 * Separates very slightly R, G and B colors on the edges of the screen
 * Inspired by Francois Tarlier & Martins Upitis
 *
 * Lens effects can be of the following:
 * - chromatic aberration (slight shift of RGB colors)
 * - blur on the edge of the lens
 * - lens distortion
 * - depth-of-field blur & highlights enhancing
 * - depth-of-field 'bokeh' effect (shapes appearing in blurred areas)
 * - grain effect (noise or custom texture)
 *
 * Two additional texture samplers are needed:
 * - depth map (for depth-of-field)
 * - grain texture
 */
class BABYLON_SHARED_EXPORT LensRenderingPipeline
    : public PostProcessRenderPipeline {

public:
  /**
   * The chromatic aberration PostProcess id in the pipeline
   */
  static constexpr const char* LensChromaticAberrationEffect
    = "LensChromaticAberrationEffect";
  /**
   * The highlights enhancing PostProcess id in the pipeline
   */
  static constexpr const char* HighlightsEnhancingEffect
    = "HighlightsEnhancingEffect";
  /**
   * The depth-of-field PostProcess id in the pipeline
   */
  static constexpr const char* LensDepthOfFieldEffect
    = "LensDepthOfFieldEffect";

public:
  template <typename... Ts>
  static LensRenderingPipelinePtr New(Ts&&... args)
  {
    auto renderingPipeline = std::shared_ptr<LensRenderingPipeline>(
      new LensRenderingPipeline(std::forward<Ts>(args)...));
    renderingPipeline->addToScene(renderingPipeline);

    return renderingPipeline;
  }
  virtual ~LensRenderingPipeline() override;

  void addToScene(const LensRenderingPipelinePtr& lensRenderingPipeline);

  // public methods (self explanatory)

  /**
   * @brief Sets the amount of blur at the edges.
   * @param amount blur amount
   */
  void setEdgeBlur(float amount);

  /**
   * @brief Sets edge blur to 0.
   */
  void disableEdgeBlur();

  /**
   * @brief Sets the amout of grain.
   * @param amount Amount of grain
   */
  void setGrainAmount(float amount);

  /**
   * @brief Set grain amount to 0.
   */
  void disableGrain();

  /**
   * @brief Sets the chromatic aberration amount.
   * @param amount amount of chromatic aberration
   */
  void setChromaticAberration(float amount);

  /**
   * @brief Sets chromatic aberration amount to 0.
   */
  void disableChromaticAberration();

  /**
   * @brief Sets the EdgeDistortion amount.
   * @param amount amount of EdgeDistortion
   */
  void setEdgeDistortion(float amount);

  /**
   * @brief Sets edge distortion to 0.
   */
  void disableEdgeDistortion();

  /**
   * @brief Sets the FocusDistance amount.
   * @param amount amount of FocusDistance
   */
  void setFocusDistance(float amount);

  /**
   * @brief Disables depth of field.
   */
  void disableDepthOfField();

  /**
   * @brief Sets the Aperture amount.
   * @param amount amount of Aperture
   */
  void setAperture(float amount);

  /**
   * @brief Sets the DarkenOutOfFocus amount.
   * @param amount amount of DarkenOutOfFocus
   */
  void setDarkenOutOfFocus(float amount);

  /**
   * @brief Creates a pentagon bokeh effect.
   */
  void enablePentagonBokeh();

  /**
   * @brief Disables the pentagon bokeh effect.
   */
  void disablePentagonBokeh();

  /**
   * @brief Enables noise blur.
   */
  void enableNoiseBlur();

  /**
   * @brief Disables noise blur.
   */
  void disableNoiseBlur();

  /**
   * @brief Sets the HighlightsGain amount.
   * @param amount amount of HighlightsGain
   */
  void setHighlightsGain(float amount);

  /**
   * @brief Sets the HighlightsThreshold amount.
   * @param amount amount of HighlightsThreshold
   */
  void setHighlightsThreshold(float amount);

  /**
   * @brief Disables highlights.
   */
  void disableHighlights();

  /**
   * @brief Removes the internal pipeline assets and detaches the pipeline from
   * the scene cameras.
   * @param disableDepthRender If the scens depth rendering should be disabled
   * (default: false)
   */
  void dispose(bool disableDepthRender         = false,
               bool disposeMaterialAndTextures = false) override;

protected:
  /**
   * @brief Constructor
   *
   * Effect parameters are as follow:
   * {
   *      chromatic_aberration: number;       // from 0 to x (1 for realism)
   *      edge_blur: number;                  // from 0 to x (1 for realism)
   *      distortion: number;                 // from 0 to x (1 for realism)
   *      grain_float amount ;                // from 0 to 1
   *      grain_texture: BABYLON.Texture;     // texture to use for grain
   *                                          // effect; if unset, use random
   *                                          // B&W noise
   *      dof_focus_distance: number;         // depth-of-field: focus distance;
   *                                          // unset to disable (disabled by
   *                                          // default)
   *      dof_aperture: number;               // depth-of-field: focus blur bias
   *                                          // (default: 1)
   *      dof_darken: number;                 // depth-of-field: darken that
   *                                          // which is out of focus (from 0
   *                                          // to 1, disabled by default)
   *      dof_pentagon: boolean;              // depth-of-field: makes a
   *                                          // pentagon-like "bokeh" effect
   *      dof_gain: number;                   // depth-of-field: highlights
   *                                          // gain; unset to disable
   *                                          // (disabled by default)
   *      dof_threshold: number;              // depth-of-field: highlights
   *                                          // threshold (default: 1)
   *      blur_noise: boolean;                // add a little bit of noise to
   *                                          // the blur (default: true)
   * }
   * Note: if an effect parameter is unset, effect is disabled
   *
   * @param name The rendering pipeline name
   * @param parameters - An object containing all parameters (see above)
   * @param scene The scene linked to this pipeline
   * @param ratio The size of the postprocesses (0.5 means that your postprocess
   * will have a width = canvas.width 0.5 and a height = canvas.height 0.5)
   * @param cameras The array of cameras that the rendering pipeline will be
   * attached to
   */
  LensRenderingPipeline(const std::string& name,
                        const LensRenderingPipelineParameters& parameters,
                        Scene* scene, float ratio = 1.f,
                        const std::vector<CameraPtr>& cameras = {});

private:
  /**
   * colors shifting and distortion
   */
  void _createChromaticAberrationPostProcess(float ratio);
  /**
   * highlights enhancing
   */
  void _createHighlightsPostProcess(float ratio);
  /**
   * colors shifting and distortion
   */
  void _createDepthOfFieldPostProcess(float ratio);
  /**
   * creates a black and white random noise texture, 512x512
   */
  void _createGrainTexture();

private:
  Scene* _scene;
  RenderTargetTexturePtr _depthTexture;
  TexturePtr _grainTexture;
  std::vector<CameraPtr> _cameraList;

  PostProcessPtr _chromaticAberrationPostProcess;
  PostProcessPtr _highlightsPostProcess;
  PostProcessPtr _depthOfFieldPostProcess;

  float _edgeBlur;
  float _grainAmount;
  float _chromaticAberration;
  float _distortion;
  float _highlightsGain;
  float _highlightsThreshold;
  float _dofDistance;
  float _dofAperture;
  float _dofDarken;
  bool _dofPentagon;
  bool _blurNoise;

}; // end of class LensRenderingPipeline

} // end of namespace BABYLON

#endif // end of
       // BABYLON_POSTPROCESS_RENDER_PIPELINE_PIPELINES_LENS_RENDERING_PIPLINE_H
