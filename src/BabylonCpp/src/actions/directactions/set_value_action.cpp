#include <babylon/actions/directactions/set_value_action.h>

#include <nlohmann/json.hpp>

#include <babylon/animations/ianimatable.h>

namespace BABYLON {

SetValueAction::SetValueAction(unsigned int triggerOptions,
                               const IAnimatablePtr& target,
                               const std::string& iPropertyPath,
                               AnimationValue* iValue, Condition* condition)
    : Action(triggerOptions, condition)
    , propertyPath{iPropertyPath}
    , value{iValue}
    , _target{target}
    , _effectiveTarget{target}
{
}

SetValueAction::~SetValueAction()
{
}

void SetValueAction::_prepare()
{
  _effectiveTarget = _getEffectiveTarget(_effectiveTarget, propertyPath);
  _property        = _getProperty(propertyPath);
}

void SetValueAction::execute(const ActionEvent& /*evt*/)
{
  // _effectiveTarget[_property] = value;

  // if (_target->markAsDirty()) {
  //  _target->markAsDirty(_property);
  //}
}

json SetValueAction::serialize(json& /*parent*/) const
{
  return nullptr;
}

} // end of namespace BABYLON
