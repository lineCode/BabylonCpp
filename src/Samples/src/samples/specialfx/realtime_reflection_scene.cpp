#include <babylon/samples/specialfx/realtime_reflection_scene.h>

#include <babylon/cameras/arc_rotate_camera.h>
#include <babylon/engine/scene.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/fresnel_parameters.h>
#include <babylon/materials/standard_material.h>
#include <babylon/materials/textures/mirror_texture.h>
#include <babylon/materials/textures/render_target_texture.h>
#include <babylon/mesh/mesh.h>
#include <babylon/probes/reflection_probe.h>

namespace BABYLON {
namespace Samples {

RealtimeReflectionScene::RealtimeReflectionScene(ICanvas* iCanvas)
    : IRenderableScene(iCanvas)
    , _yellowSphere{nullptr}
    , _greenSphere{nullptr}
    , _blueSphere{nullptr}
{
}

RealtimeReflectionScene::~RealtimeReflectionScene()
{
}

const char* RealtimeReflectionScene::getName()
{
  return "Realtime Reflection Scene";
}

void RealtimeReflectionScene::initializeScene(ICanvas* canvas, Scene* scene)
{
  auto camera
    = ArcRotateCamera::New("camera1", 0.f, 0.f, 10.f, Vector3::Zero(), scene);

  camera->setPosition(Vector3(0.f, 5.f, -10.f));
  camera->attachControl(canvas, true);

  camera->upperBetaLimit   = Math::PI_2;
  camera->lowerRadiusLimit = 4.f;

  auto light = HemisphericLight::New("light1", Vector3(0.f, 1.f, 0.f), scene);
  light->intensity = 0.7f;

  auto knot = Mesh::CreateTorusKnot("knot", 1, 0.4f, 128, 64, 2, 3, scene);

  _yellowSphere = Mesh::CreateSphere("yellowSphere", 16, 1.5, scene);
  _yellowSphere->setPivotMatrix(Matrix::Translation(3.f, 0.f, 0.f), false);

  _blueSphere = Mesh::CreateSphere("blueSphere", 16, 1.5, scene);
  _blueSphere->setPivotMatrix(Matrix::Translation(-1.f, 3.f, 0.f), false);

  _greenSphere = Mesh::CreateSphere("greenSphere", 16, 1.5, scene);
  _greenSphere->setPivotMatrix(Matrix::Translation(0.f, 0.f, 3.f), false);

  const auto generateSatelliteMaterial =
    [&scene](const MeshPtr& root, const Color3& color,
             const std::vector<MeshPtr>& others) {
      auto material = StandardMaterial::New("satelliteMat" + root->name, scene);
      material->diffuseColor = color;

      auto probe
        = ReflectionProbe::New("satelliteProbe" + root->name, 512, scene);
      for (const auto& other : others) {
        probe->renderList().emplace_back(other.get());
      }

      material->reflectionTexture                   = probe->cubeTexture();
      material->reflectionFresnelParameters()->bias = 0.02f;

      root->material = material;
      probe->attachToMesh(root.get());
    };

  // Mirror
  auto mirror                    = Mesh::CreateBox("Mirror", 1.0, scene);
  mirror->scaling                = Vector3(100.f, 0.01f, 100.f);
  auto mirrorMaterial            = StandardMaterial::New("mirror", scene);
  auto diffuseTexture            = Texture::New("textures/amiga.jpg", scene);
  diffuseTexture->uScale         = 10.f;
  diffuseTexture->vScale         = 10.f;
  mirrorMaterial->diffuseTexture = diffuseTexture;
  auto reflectionTexture = MirrorTexture::New("mirror", 1024.f, scene, true);
  reflectionTexture->mirrorPlane = Plane(0.f, -1.f, 0.f, -2.f);
  reflectionTexture->renderList
    = {_greenSphere.get(), _yellowSphere.get(), _blueSphere.get(), knot.get()};
  reflectionTexture->level          = 0.5f;
  mirrorMaterial->reflectionTexture = reflectionTexture;
  mirror->position                  = Vector3(0.f, -2.f, 0.f);
  mirror->material                  = mirrorMaterial;

  // Main material
  auto mainMaterial = StandardMaterial::New("main", scene);
  knot->material    = mainMaterial;

  auto probe = ReflectionProbe::New("main", 512, scene);
  probe->renderList().emplace_back(_yellowSphere.get());
  probe->renderList().emplace_back(_greenSphere.get());
  probe->renderList().emplace_back(_blueSphere.get());
  probe->renderList().emplace_back(mirror.get());
  mainMaterial->diffuseColor                        = Color3(1.f, 0.5f, 0.5f);
  mainMaterial->reflectionTexture                   = probe->cubeTexture();
  mainMaterial->reflectionFresnelParameters()->bias = 0.02f;

  // Satellite
  generateSatelliteMaterial(_yellowSphere, Color3::Yellow(),
                            {_greenSphere, _blueSphere, knot, mirror});
  generateSatelliteMaterial(_greenSphere, Color3::Green(),
                            {_yellowSphere, _blueSphere, knot, mirror});
  generateSatelliteMaterial(_blueSphere, Color3::Blue(),
                            {_greenSphere, _yellowSphere, knot, mirror});

  // Fog
  scene->fogMode = Scene::FOGMODE_LINEAR;
  scene->fogColor
    = Color3(scene->clearColor.r, scene->clearColor.g, scene->clearColor.b);
  scene->fogStart = 20.f;
  scene->fogEnd   = 50.f;

  // Animations
  scene->registerBeforeRender([this](Scene*, EventState&) {
    _yellowSphere->rotation().y += 0.01f;
    _greenSphere->rotation().y += 0.01f;
    _blueSphere->rotation().y += 0.01f;
  });
}

} // end of namespace Samples
} // end of namespace BABYLON
