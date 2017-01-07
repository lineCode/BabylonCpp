#ifndef BABYLON_MATH_VIEWPORT_H
#define BABYLON_MATH_VIEWPORT_H

#include <babylon/babylon_global.h>

namespace BABYLON {

/**
 * @brief Represents a Viewport.
 */
class BABYLON_SHARED_EXPORT Viewport {

public:
  Viewport();
  Viewport(int x, int y, int width, int height);
  Viewport(const Viewport& otherViewport);
  Viewport(Viewport&& otherViewport);
  Viewport& operator=(const Viewport& otherViewport);
  Viewport& operator=(Viewport&& otherViewport);
  ~Viewport();
  Viewport copy() const;
  std::unique_ptr<Viewport> clone() const;
  friend std::ostream& operator<<(std::ostream& os, const Viewport& viewport);

  /** Methods **/
  Viewport toGlobal(int renderWidth, int renderHeight);

public:
  int x, y;
  int width, height;

}; // end of class Viewport

std::ostream& operator<<(std::ostream& os, const Viewport& viewport);

} // end of namespace BABYLON

#endif // end of BABYLON_MATH_VIEWPORT_H