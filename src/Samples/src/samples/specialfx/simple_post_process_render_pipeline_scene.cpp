#include <babylon/samples/specialfx/simple_post_process_render_pipeline_scene.h>

#include <babylon/cameras/free_camera.h>
#include <babylon/engine/scene.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/mesh/mesh.h>
#include <babylon/postprocess/black_and_white_post_process.h>
#include <babylon/postprocess/blur_post_process.h>
#include <babylon/postprocess/renderpipeline/post_process_render_effect.h>
#include <babylon/postprocess/renderpipeline/post_process_render_pipeline.h>
#include <babylon/postprocess/renderpipeline/post_process_render_pipeline_manager.h>

namespace BABYLON {
namespace Samples {

SimplePostProcessRenderPipelineScene::SimplePostProcessRenderPipelineScene(
  ICanvas* iCanvas)
    : IRenderableScene(iCanvas)
    , _blackAndWhite{nullptr}
    , _horizontalBlur{nullptr}
{
}

SimplePostProcessRenderPipelineScene::~SimplePostProcessRenderPipelineScene()
{
}

const char* SimplePostProcessRenderPipelineScene::getName()
{
  return "Simple Post Process Render Pipeline Scene";
}

void SimplePostProcessRenderPipelineScene::initializeScene(ICanvas* canvas,
                                                           Scene* scene)
{
  // Create a basic scene
  auto camera = FreeCamera::New("camera1", Vector3(0.f, 5.f, -10.f), scene);
  camera->setTarget(Vector3::Zero());
  camera->attachControl(canvas, true);
  auto light       = HemisphericLight::New("light1", Vector3(0, 1, 0), scene);
  light->intensity = 0.7f;
  auto sphere      = Mesh::CreateSphere("sphere1", 16, 2, scene);
  sphere->position().y = 1.f;
  auto ground          = Mesh::CreateGround("ground1", 6, 6, 2, scene);

  // Get the engine reference
  auto engine = scene->getEngine();

  // Create a standard pipeline
  auto standardPipeline
    = PostProcessRenderPipeline::New(engine, "standardPipeline");

  // Create post processes
  _blackAndWhite
    = BlackAndWhitePostProcess::New("bw", 1.f, nullptr, 0, engine, false);
  _horizontalBlur = BlurPostProcess::New("hb", Vector2(1.f, 0.f), 20.f, 1.f,
                                         nullptr, std::nullopt, engine, false);

  // Create effect with multiple post processes and add to pipeline
  auto blackAndWhiteThenBlur = PostProcessRenderEffect::New(
    engine, "blackAndWhiteThenBlur", [this]() -> std::vector<PostProcessPtr> {
      return {_blackAndWhite, _horizontalBlur};
    });
  standardPipeline->addEffect(blackAndWhiteThenBlur);

  // Add pipeline to the scene's manager and attach to the camera
  scene->postProcessRenderPipelineManager()->addPipeline(standardPipeline);
  scene->postProcessRenderPipelineManager()->attachCamerasToRenderPipeline(
    "standardPipeline", camera);
}

} // end of namespace Samples
} // end of namespace BABYLON
