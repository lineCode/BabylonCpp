#ifndef BABYLON_LOADING_GLTF_2_0_GLTF_LOADER_EXTENSION_H
#define BABYLON_LOADING_GLTF_2_0_GLTF_LOADER_EXTENSION_H

#include <babylon/babylon_global.h>

namespace BABYLON {
namespace GLTF2 {

class BABYLON_SHARED_EXPORT GLTFLoaderExtension {

public:
  bool enabled() const;
  const char* name() const;

  //
  // Utilities
  //
  static bool TraverseNode(
    GLTFLoader& loader, const string_t& context, IGLTFNode* node,
    const ::std::function<bool(IGLTFNode* node, IGLTFNode* parentNode)>& action,
    IGLTFNode* parentNode);
  static bool LoadNode(GLTFLoader& loader, const string_t& context,
                       IGLTFNode* node);
  static bool LoadMaterial(
    GLTFLoader& loader, const string_t& context, IGLTFMaterial& material,
    const ::std::function<void(Material* babylonMaterial, bool isNew)>& assign);

protected:
  virtual bool _traverseNode(
    GLTFLoader& loader, const string_t& context, IGLTFNode* node,
    const ::std::function<bool(IGLTFNode* node, IGLTFNode* parentNode)>& action,
    IGLTFNode* parentNode);
  virtual bool _loadNode(GLTFLoader& loader, const string_t& context,
                         IGLTFNode* node);
  virtual bool _loadMaterial(
    GLTFLoader& loader, const string_t& context, IGLTFMaterial& material,
    const ::std::function<void(Material* babylonMaterial, bool isNew)>& assign);
  template <typename T>
  bool _loadExtension(
    const string_t& context, IGLTFProperty& property,
    const ::std::function<void(const string_t& context, const T& extension,
                               const ::std::function<void()>& onComplete)>&
      action);

private:
  //
  // Utilities
  //
  static _ApplyExtensions(
    const ::std::function<bool(const GLTFLoaderExtension& extension)>& action);

public:
  vector_t<GLTFLoaderExtension> _Extensions;

private:
  bool _enabled;

}; // end of class GLTFLoaderExtension

} // end of namespace GLTF2
} // end of namespace BABYLON

#endif // end of BABYLON_LOADING_GLTF_2_0_GLTF_LOADER_EXTENSION_H
