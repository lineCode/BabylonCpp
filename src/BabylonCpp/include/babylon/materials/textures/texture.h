#ifndef BABYLON_MATERIALS_TEXTURES_TEXTURE_H
#define BABYLON_MATERIALS_TEXTURES_TEXTURE_H

#include <variant>

#include <babylon/babylon_api.h>
#include <babylon/engine/engine_constants.h>
#include <babylon/materials/textures/base_texture.h>
#include <babylon/materials/textures/texture_constants.h>
#include <babylon/math/matrix.h>
#include <babylon/tools/observable.h>

namespace BABYLON {

class Texture;
using TexturePtr = std::shared_ptr<Texture>;

/**
 * @brief This represents a texture in babylon. It can be easily loaded from a
 * network, base64 or html input.
 * @see http://doc.babylonjs.com/babylon101/materials#texture
 */
class BABYLON_SHARED_EXPORT Texture : public BaseTexture {

  friend Scene;

public:
  /**
   * Gets or sets a boolean which defines if the texture url must be build from
   * the serialized URL instead of just using the name and loading them side by
   * side with the scene file
   */
  static bool UseSerializedUrlIfAny;

public:
  template <typename... Ts>
  static TexturePtr New(Ts&&... args)
  {
    auto texture
      = std::shared_ptr<Texture>(new Texture(std::forward<Ts>(args)...));
    texture->addToScene(texture);

    return texture;
  }
  virtual ~Texture() override;

  virtual Type type() const override;

  /**
   * @brief Update the url (and optional buffer) of this texture if url was null
   * during construction.
   * @param url the url of the texture
   * @param buffer the buffer of the texture (defaults to null)
   */
  void updateURL(
    const std::string& iUrl,
    const std::optional<std::variant<std::string, ArrayBuffer, Image>>& buffer
    = std::nullopt);

  /**
   * @brief Finish the loading sequence of a texture flagged as delayed load.
   * @hidden
   */
  void delayLoad() override;

  /**
   * @brief Update the sampling mode of the texture.
   * Default is Trilinear mode.
   *
   * | Value | Type               | Description |
   * | ----- | ------------------ | ----------- |
   * | 1     | NEAREST_SAMPLINGMODE or NEAREST_NEAREST_MIPLINEAR  | Nearest is:
   * mag = nearest, min = nearest, mip = linear |
   * | 2     | BILINEAR_SAMPLINGMODE or LINEAR_LINEAR_MIPNEAREST | Bilinear is:
   * mag = linear, min = linear, mip = nearest |
   * | 3     | TRILINEAR_SAMPLINGMODE or
   * LINEAR_LINEAR_MIPLINEAR | Trilinear is: mag = linear, min = linear, mip =
   * linear |
   * | 4     | NEAREST_NEAREST_MIPNEAREST |             |
   * | 5     | NEAREST_LINEAR_MIPNEAREST |             |
   * | 6     | NEAREST_LINEAR_MIPLINEAR |             |
   * | 7     | NEAREST_LINEAR |             |
   * | 8     | NEAREST_NEAREST |             |
   * | 9     | LINEAR_NEAREST_MIPNEAREST |             |
   * | 10    | LINEAR_NEAREST_MIPLINEAR |             |
   * | 11    | LINEAR_LINEAR |             |
   * | 12    | LINEAR_NEAREST |             |
   *
   *    > _mag_: magnification filter (close to the viewer)
   *    > _min_: minification filter (far from the viewer)
   *    > _mip_: filter used between mip map levels
   *@param samplingMode Define the new sampling mode of the texture
   */
  void updateSamplingMode(unsigned int samplingMode);

  /**
   * @brief Get the current texture matrix which includes the requested
   * offsetting, tiling and rotation components.
   * @returns the transform matrix of the texture.
   */
  Matrix* getTextureMatrix() override;

  /**
   * @brief Get the current matrix used to apply reflection. This is useful to
   * rotate an environment texture for instance.
   * @returns The reflection texture transform
   */
  Matrix* getReflectionTextureMatrix() override;

  /**
   * @brief Clones the texture.
   * @returns the cloned texture
   */
  TexturePtr clone() const;

  /**
   * @brief Serialize the texture to a JSON representation we can easily use in
   * the resepective Parse function.
   * @returns The JSON representation of the texture
   */
  json serialize() const;

  /**
   * @brief Get the current class name of the texture usefull for serialization
   * or dynamic coding.
   * @returns "Texture"
   */
  const char* getClassName() const;

  /**
   * @brief Dispose the texture and release its associated resources.
   */
  void dispose() override;

  /**
   * @brief Parse the JSON representation of a texture in order to recreate the
   * texture in the given scene.
   * @param parsedTexture Define the JSON representation of the texture
   * @param scene Define the scene the parsed texture should be instantiated in
   * @param rootUrl Define the root url of the parsing sequence in the case of
   * relative dependencies
   * @returns The parsed texture if successful
   */
  static BaseTexturePtr Parse(const json& parsedTexture, Scene* scene,
                              const std::string& rootUrl);

  /**
   * @brief Creates a texture from its base 64 representation.
   * @param data Define the base64 payload without the data: prefix
   * @param name Define the name of the texture in the scene useful fo caching
   * purpose for instance
   * @param scene Define the scene the texture should belong to
   * @param noMipmap Forces the texture to not create mip map information if
   * true
   * @param invertY define if the texture needs to be inverted on the y axis
   * during loading
   * @param samplingMode define the sampling mode we want for the texture while
   * fectching from it (Texture.NEAREST_SAMPLINGMODE...)
   * @param onLoad define a callback triggered when the texture has been loaded
   * @param onError define a callback triggered when an error occurred during
   * the loading session
   * @param format define the format of the texture we are trying to load
   * (Engine.TEXTUREFORMAT_RGBA...)
   * @returns the created texture
   */
  static TexturePtr CreateFromBase64String(
    const std::string& data, const std::string& name, Scene* scene,
    bool noMipmap = false, bool invertY = false,
    unsigned int samplingMode = TextureConstants::TRILINEAR_SAMPLINGMODE,
    const std::function<void()>& onLoad = nullptr,
    const std::function<void(const std::string& message,
                             const std::string& exception)>& onError
    = nullptr,
    unsigned int format = EngineConstants::TEXTUREFORMAT_RGBA);

  /**
   * @brief Creates a texture from its data: representation. (data: will be
   * added in case only the payload has been passed in).
   * @param data Define the base64 payload without the data: prefix
   * @param name Define the name of the texture in the scene useful fo caching
   * purpose for instance
   * @param buffer define the buffer to load the texture from in case the
   * texture is loaded from a buffer representation
   * @param scene Define the scene the texture should belong to
   * @param deleteBuffer define if the buffer we are loading the texture from
   * should be deleted after load
   * @param noMipmap Forces the texture to not create mip map information if
   * true
   * @param invertY define if the texture needs to be inverted on the y axis
   * during loading
   * @param samplingMode define the sampling mode we want for the texture while
   * fectching from it (Texture.NEAREST_SAMPLINGMODE...)
   * @param onLoad define a callback triggered when the texture has been loaded
   * @param onError define a callback triggered when an error occurred during
   * the loading session
   * @param format define the format of the texture we are trying to load
   * (Engine.TEXTUREFORMAT_RGBA...)
   * @returns the created texture
   */
  static TexturePtr LoadFromDataString(
    const std::string& name,
    const std::optional<std::variant<std::string, ArrayBuffer, Image>>& buffer,
    Scene* scene, bool deleteBuffer = false, bool noMipmap = false,
    bool invertY              = true,
    unsigned int samplingMode = TextureConstants::TRILINEAR_SAMPLINGMODE,
    const std::function<void()>& onLoad = nullptr,
    const std::function<void(const std::string& message,
                             const std::string& exception)>& onError
    = nullptr,
    unsigned int format = EngineConstants::TEXTUREFORMAT_RGBA);

protected:
  /**
   * @brief Instantiates a new texture.
   * This represents a texture in babylon. It can be easily loaded from a
   * network, base64 or html input.
   * @see http://doc.babylonjs.com/babylon101/materials#texture
   * @param url define the url of the picture to load as a texture
   * @param scene define the scene the texture will belong to
   * @param noMipmap define if the texture will require mip maps or not
   * @param invertY define if the texture needs to be inverted on the y axis
   * during loading
   * @param samplingMode define the sampling mode we want for the texture while
   * fectching from it (Texture.NEAREST_SAMPLINGMODE...)
   * @param onLoad define a callback triggered when the texture has been loaded
   * @param onError define a callback triggered when an error occurred during
   * the loading session
   * @param buffer define the buffer to load the texture from in case the
   * texture is loaded from a buffer representation
   * @param deleteBuffer define if the buffer we are loading the texture from
   * should be deleted after load
   * @param format define the format of the texture we are trying to load
   * (Engine.TEXTUREFORMAT_RGBA...)
   */
  Texture(
    const std::string& url, Scene* scene, bool noMipmap = false,
    bool invertY              = true,
    unsigned int samplingMode = TextureConstants::TRILINEAR_SAMPLINGMODE,
    const std::function<void()>& onLoad = nullptr,
    const std::function<void(const std::string& message,
                             const std::string& exception)>& onError
    = nullptr,
    const std::optional<std::variant<std::string, ArrayBuffer, Image>>& buffer
    = std::nullopt,
    bool deleteBuffer                         = false,
    const std::optional<unsigned int>& format = std::nullopt);

  bool get_noMipmap() const;
  void set_isBlocking(bool value) override;
  bool get_isBlocking() const override;
  unsigned int get_samplingMode() const;
  Observable<Texture>& get_onLoadObservable();

private:
  void _prepareRowForTextureGeneration(float x, float y, float z, Vector3& t);

public:
  /**
   * Define the url of the texture.
   */
  std::string url;

  /**
   * Define an offset on the texture to offset the u coordinates of the UVs
   * @see http://doc.babylonjs.com/how_to/more_materials#offsetting
   */
  float uOffset;

  /**
   * Define an offset on the texture to offset the v coordinates of the UVs
   * @see http://doc.babylonjs.com/how_to/more_materials#offsetting
   */
  float vOffset;

  /**
   * Define an offset on the texture to scale the u coordinates of the UVs
   * @see http://doc.babylonjs.com/how_to/more_materials#tiling
   */
  float uScale;

  /**
   * Define an offset on the texture to scale the v coordinates of the UVs
   * @see http://doc.babylonjs.com/how_to/more_materials#tiling
   */
  float vScale;

  /**
   * Define an offset on the texture to rotate around the u coordinates of the
   * UVs
   * @see http://doc.babylonjs.com/how_to/more_materials
   */
  float uAng;

  /**
   * Define an offset on the texture to rotate around the v coordinates of the
   * UVs
   * @see http://doc.babylonjs.com/how_to/more_materials
   */
  float vAng;

  /**
   * Define an offset on the texture to rotate around the w coordinates of the
   * UVs (in case of 3d texture)
   * @see http://doc.babylonjs.com/how_to/more_materials
   */
  float wAng;

  /**
   * Defines the center of rotation (U)
   */
  float uRotationCenter;

  /**
   * Defines the center of rotation (V)
   */
  float vRotationCenter;

  /**
   * Defines the center of rotation (W)
   */
  float wRotationCenter;

  /**
   * Are mip maps generated for this texture or not.
   */
  ReadOnlyProperty<Texture, bool> noMipmap;

  /**
   * Hidden
   */
  bool _invertY;

  /**
   * Get the current sampling mode associated with the texture.
   */
  unsigned int _samplingMode;

  /**
   * Get the current sampling mode associated with the texture.
   */
  ReadOnlyProperty<Texture, unsigned int> samplingMode;

  /**
   * Observable triggered once the texture has been loaded.
   */
  ReadOnlyProperty<Texture, Observable<Texture>> onLoadObservable;

protected:
  const std::optional<unsigned int> _format;
  Observable<Texture> _onLoadObservable;
  bool _isBlocking;

private:
  bool _noMipmap;
  std::unique_ptr<Matrix> _rowGenerationMatrix;
  std::unique_ptr<Matrix> _cachedTextureMatrix;
  std::unique_ptr<Matrix> _projectionModeMatrix;
  Vector3 _t0;
  Vector3 _t1;
  Vector3 _t2;

  float _cachedUOffset;
  float _cachedVOffset;
  float _cachedUScale;
  float _cachedVScale;
  float _cachedUAng;
  float _cachedVAng;
  float _cachedWAng;
  int _cachedProjectionMatrixId;
  unsigned int _cachedCoordinatesMode;
  std::optional<std::variant<std::string, ArrayBuffer, Image>> _buffer;
  bool _deleteBuffer;
  std::function<void(InternalTexture*, EventState&)> _delayedOnLoad;
  std::function<void(const std::string& message, const std::string& exception)>
    _delayedOnError;

  std::function<void()> _onLoad;
  std::function<void(InternalTexture*, EventState&)> _load;

}; // end of class Texture

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_TEXTURES_TEXTURE_H
