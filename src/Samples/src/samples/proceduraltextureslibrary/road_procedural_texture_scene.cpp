#include <babylon/samples/proceduraltextureslibrary/road_procedural_texture_scene.h>

#include <babylon/cameras/arc_rotate_camera.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/standard_material.h>
#include <babylon/mesh/mesh.h>
#include <babylon/proceduraltextureslibrary/road/road_procedural_texture.h>

namespace BABYLON {
namespace Samples {

RoadProceduralTextureScene::RoadProceduralTextureScene(ICanvas* iCanvas)
    : IRenderableScene(iCanvas)
{
}

RoadProceduralTextureScene::~RoadProceduralTextureScene()
{
}

const char* RoadProceduralTextureScene::getName()
{
  return "Road Procedural Texture Scene";
}

void RoadProceduralTextureScene::initializeScene(ICanvas* canvas, Scene* scene)
{
  auto camera = ArcRotateCamera::New("Camera", 2.5f * Math::PI_2, Math::PI_2,
                                     25.f, Vector3::Zero(), scene);
  camera->attachControl(canvas, false);

  auto light0 = HemisphericLight::New("Light", Vector3(0.f, 10.f, 0.f), scene);

  auto roadMaterial = StandardMaterial::New("RoadMaterial", scene);
  auto roadTexture  = ProceduralTexturesLibrary::RoadProceduralTexture::New(
    "RoadMaterialtext", 512, scene);
  roadMaterial->diffuseTexture = roadTexture;

  auto plane      = Mesh::CreatePlane("RoadPlane", 20, scene);
  plane->material = roadMaterial;
  plane->rotate(Vector3(1.f, 1.f, 0.5f), Math::PI / 3.f, Space::LOCAL);
}

} // end of namespace Samples
} // end of namespace BABYLON
