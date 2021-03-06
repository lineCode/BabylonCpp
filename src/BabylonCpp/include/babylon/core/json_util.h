#ifndef BABYLON_CORE_JSON_UTIL_H
#define BABYLON_CORE_JSON_UTIL_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace BABYLON {
namespace json_util {

inline bool is_null(const json& j)
{
  return j.is_null();
}

inline bool has_key(const json& o, const std::string& key)
{
  return (o.find(key) != o.end());
}

inline bool has_valid_key_value(const json& o, const std::string& key)
{
  return has_key(o, key) && !is_null(o[key]);
}

template <typename T = bool>
inline T get_bool(const json& j, const std::string& key, T defaultValue = T())
{
  if (!j.is_null() && has_key(j, key) && j[key].is_boolean()) {
    return j[key].get<T>();
  }
  else {
    return defaultValue;
  }
}

template <typename T>
inline T get_number(const json& j, const std::string& key, T defaultValue = T())
{
  if (!j.is_null() && has_key(j, key) && j[key].is_number()) {
    return j[key].get<T>();
  }
  else {
    return defaultValue;
  }
}

template <typename T = std::string>
inline T get_string(const json& j, const std::string& key,
                    const std::string& defaultValue = "")
{
  if (!j.is_null() && has_key(j, key) && j[key].is_string()) {
    return j[key].get<T>();
  }
  else {
    return defaultValue;
  }
}

template <typename T>
inline std::vector<T> get_array(const json& j, const std::string& key)
{
  std::vector<T> v;
  if (!j.is_null() && has_key(j, key) && j[key].is_array() && !j[key].empty()) {
    v = j[key].get<std::vector<T>>();
  }

  return v;
}

} // end of namespace json_util
} // end of namespace BABYLON

#endif // end of BABYLON_CORE_JSON_UTIL_H
