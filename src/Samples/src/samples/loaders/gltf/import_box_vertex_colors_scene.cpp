#include <babylon/samples/loaders/gltf/import_box_vertex_colors_scene.h>

#include <babylon/cameras/arc_rotate_camera.h>
#include <babylon/engine/scene.h>
#include <babylon/helpers/environment_helper.h>
#include <babylon/loading/glTF/gltf_file_loader.h>
#include <babylon/loading/scene_loader.h>

namespace BABYLON {
namespace Samples {

ImportBoxVertexColorsScene::ImportBoxVertexColorsScene(ICanvas* iCanvas)
    : IRenderableScene(iCanvas)
{
  GLTF2::GLTFFileLoader::RegisterAsSceneLoaderPlugin();
}

ImportBoxVertexColorsScene::~ImportBoxVertexColorsScene()
{
}

const char* ImportBoxVertexColorsScene::getName()
{
  return "Import Box Vertex Colors Scene (glTF)";
}

void ImportBoxVertexColorsScene::initializeScene(ICanvas* /*canvas*/,
                                                 Scene* scene)
{
  SceneLoader::ImportMesh(
    {}, "glTF-Sample-Models/2.0/BoxVertexColors/glTF/", "BoxVertexColors.gltf",
    scene,
    [scene](const std::vector<AbstractMeshPtr>& /*meshes*/,
            const std::vector<IParticleSystemPtr>& /*particleSystems*/,
            const std::vector<SkeletonPtr>& /*skeletons*/,
            const std::vector<AnimationGroupPtr>& /*animationGroups*/) {
      scene->createDefaultCameraOrLight(true, true, true);
      // Set the camera position
      auto camera
        = std::static_pointer_cast<ArcRotateCamera>(scene->activeCamera);
      if (camera) {
        camera->setTarget(Vector3::Zero());
        camera->alpha  = 0.9f;
        camera->beta   = 1.f;
        camera->radius = 2.5f;
      }
    });
}

} // end of namespace Samples
} // end of namespace BABYLON
