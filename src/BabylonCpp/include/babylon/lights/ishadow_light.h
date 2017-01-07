#ifndef BABYLON_ISHADOW_LIGHT_H
#define BABYLON_ISHADOW_LIGHT_H

#include <babylon/babylon_global.h>
#include <babylon/math/vector3.h>

namespace BABYLON {

class BABYLON_SHARED_EXPORT IShadowLight {

public:
  IShadowLight();
  virtual ~IShadowLight();
  virtual bool computeTransformedPosition() = 0;
  virtual Scene* getScene()                 = 0;
  virtual void
  setShadowProjectionMatrix(Matrix& matrix, const Matrix& viewMatrix,
                            const std::vector<AbstractMesh*>& renderList)
    = 0;
  virtual bool supportsVSM() const         = 0;
  virtual bool needRefreshPerFrame() const = 0;
  virtual bool needCube() const            = 0;
  virtual Vector3 getShadowDirection(unsigned int faceIndex = 0) = 0;

public:
  std::string id;
  Vector3 position;
  Vector3 direction;
  Vector3 transformedPosition;
  std::string name;
  std::shared_ptr<ShadowGenerator> _shadowGenerator;

}; // end of class IShadowLight

} // end of namespace BABYLON

#endif // end of BABYLON_ISHADOW_LIGHT_H