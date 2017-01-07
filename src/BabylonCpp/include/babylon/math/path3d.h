#ifndef BABYLON_MATH_PATH3D_H
#define BABYLON_MATH_PATH3D_H

#include <babylon/babylon_global.h>

namespace BABYLON {

/**
 * @brief Represents an Path3D.
 */
class BABYLON_SHARED_EXPORT Path3D {

public:
  Path3D();
  /**
   * new Path3D(path, normal, raw)
   * Creates a Path3D. A Path3D is a logical math object, so not a mesh.
   * path : an array of Vector3, the curve axis of the Path3D
   * normal (optional) : Vector3, the first wanted normal to the curve. Ex (0,
   * 1, 0) for a vertical normal.
   * raw (optional, default false) : boolean, if true the returned Path3D isn't
   * normalized. Useful to depict path acceleration or speed.
   */
  Path3D(const std::vector<Vector3>& path);
  Path3D(const std::vector<Vector3>& path, const Vector3& firstNormal,
         bool raw = false);
  Path3D(const Path3D& otherPath);
  Path3D(Path3D&& otherPath);
  Path3D& operator=(const Path3D& otherPath);
  Path3D& operator=(Path3D&& otherPath);
  ~Path3D();
  Path3D copy() const;
  std::unique_ptr<Path3D> clone() const;
  friend std::ostream& operator<<(std::ostream& os, const Path3D& path);

  /**
   * Returns the Path3D array of successive Vector3 designing its curve.
   */
  std::vector<Vector3>& getCurve();

  /**
   * Returns an array populated with tangent vectors on each Path3D curve point.
   */
  std::vector<Vector3>& getTangents();

  /**
   * Returns an array populated with normal vectors on each Path3D curve point.
   */
  std::vector<Vector3>& getNormals();

  /**
   * Returns an array populated with binormal vectors on each Path3D curve
   * point.
   */
  std::vector<Vector3>& getBinormals();

  /**
   * Returns an array populated with distances (float) of the i-th point from
   * the first curve point.
   */
  std::vector<float>& getDistances();

  /**
   * Forces the Path3D tangent, normal, binormal and distance recomputation.
   * Returns the same object updated.
   */
  Path3D& update(const std::vector<Vector3>& path);
  Path3D& update(const std::vector<Vector3>& path, const Vector3& firstNormal);

private:
  // Computes tangents, normals and binormals.
  void _compute(const Vector3* firstNormal);
  Vector3 _getFirstNonNullVector(unsigned int index);
  Vector3 _getLastNonNullVector(unsigned int index);
  Vector3 _normalVector(const Vector3& v0, const Vector3& vt,
                        const Vector3* va);

private:
  std::vector<Vector3> _curve;
  std::vector<float> _distances;
  std::vector<Vector3> _tangents;
  std::vector<Vector3> _normals;
  std::vector<Vector3> _binormals;
  bool _raw;

}; // end of class Path3D

std::ostream& operator<<(std::ostream& os, const Path3D& path);

} // end of namespace BABYLON

#endif // end of BABYLON_MATH_PATH3D_H