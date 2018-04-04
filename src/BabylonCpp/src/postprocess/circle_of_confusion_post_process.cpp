#include <babylon/postprocess/circle_of_confusion_post_process.h>

#include <babylon/cameras/camera.h>
#include <babylon/core/logging.h>
#include <babylon/engine/scene.h>
#include <babylon/materials/effect.h>
#include <babylon/materials/textures/render_target_texture.h>

namespace BABYLON {

CircleOfConfusionPostProcess::CircleOfConfusionPostProcess(
  const string_t& name, RenderTargetTexture* depthTexture,
  const Variant<float, PostProcessOptions>& options, Camera* camera,
  unsigned int samplingMode, Engine* engine, bool reusable,
  unsigned int textureType, bool blockCompilation)
    : PostProcess{name,
                  "circleOfConfusion",
                  {"cameraMinMaxZ", "focusDistance", "cocPrecalculation"},
                  {"depthSampler"},
                  options,
                  camera,
                  samplingMode,
                  engine,
                  reusable,
                  nullptr,
                  textureType,
                  "",
                  {},
                  blockCompilation}
    , lensSize{50.f}
    , fStop{1.4f}
    , focusDistance{2000.f}
    , focalLength{50.f}
    , _depthTexture{depthTexture}
{
  onApplyObservable.add([&](Effect* effect, EventState& /*es*/) {
    if (!_depthTexture) {
      BABYLON_LOG_WARN("CircleOfConfusionPostProcess",
                       "No depth texture set on CircleOfConfusionPostProcess")
      return;
    }
    effect->setTexture("depthSampler", _depthTexture);

    // Circle of confusion calculation, See
    // https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch23.html
    float aperture = lensSize / fStop;
    float cocPrecalculation
      = ((aperture * focalLength)
         / ((focusDistance - focalLength))); // * ((focusDistance -
                                             // pixelDistance)/pixelDistance)
                                             // [This part is done in shader]

    effect->setFloat("focusDistance", focusDistance);
    effect->setFloat("cocPrecalculation", cocPrecalculation);

    if (_depthTexture->activeCamera) {
      effect->setFloat2("cameraMinMaxZ", _depthTexture->activeCamera->minZ,
                        _depthTexture->activeCamera->maxZ);
    }
  });
}

CircleOfConfusionPostProcess::~CircleOfConfusionPostProcess()
{
}

void CircleOfConfusionPostProcess::setDepthTexture(RenderTargetTexture* value)
{
  _depthTexture = value;
}

} // end of namespace BABYLON
