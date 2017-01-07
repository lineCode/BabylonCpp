#include <babylon/math/angle.h>

#include <babylon/math/vector2.h>

namespace BABYLON {

Angle::Angle()
{
}

Angle::Angle(float iradians) : _radians{iradians}
{
  if (_radians < 0.f) {
    _radians += (2 * Math::PI);
  }
}

Angle::Angle(const Angle& otherAngle) : _radians{otherAngle._radians}
{
}

Angle::Angle(Angle&& otherAngle) : _radians{std::move(otherAngle._radians)}
{
}

Angle& Angle::operator=(const Angle& otherAngle)
{
  if (&otherAngle != this) {
    _radians = otherAngle._radians;
  }

  return *this;
}

Angle& Angle::operator=(Angle&& otherAngle)
{
  if (&otherAngle != this) {
    std::swap(_radians, otherAngle._radians);
  }

  return *this;
}

Angle::~Angle()
{
}

Angle Angle::copy() const
{
  return Angle(*this);
}

std::unique_ptr<Angle> Angle::clone() const
{
  return std_util::make_unique<Angle>(*this);
}

std::ostream& operator<<(std::ostream& os, const Angle& angle)
{
  os << "{\"Degrees\":" << angle.degrees() << "}";
  return os;
}

float Angle::degrees() const
{
  return _radians * 180.f / Math::PI;
}

float Angle::radians() const
{
  return _radians;
}

Angle Angle::BetweenTwoPoints(const Vector2& a, const Vector2& b)
{
  auto delta = b.subtract(a);
  auto theta = std::atan2(delta.y, delta.x);
  return Angle(theta);
}

Angle Angle::FromRadians(float radians)
{
  return Angle(radians);
}

Angle Angle::FromDegrees(float degrees)
{
  return Angle(degrees * Math::PI / 180.f);
}

} // end of namespace BABYLON