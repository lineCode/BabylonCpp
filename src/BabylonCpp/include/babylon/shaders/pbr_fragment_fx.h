﻿#ifndef BABYLON_SHADERS_PBR_FRAGMENT_FX_H
#define BABYLON_SHADERS_PBR_FRAGMENT_FX_H

namespace BABYLON {

extern const char* pbrPixelShader;

const char* pbrPixelShader
  = "#ifdef BUMP\n"
    "#extension GL_OES_standard_derivatives : enable\n"
    "#endif\n"
    "\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "#extension GL_EXT_shader_texture_lod : enable\n"
    "#endif\n"
    "\n"
    "#ifdef LOGARITHMICDEPTH\n"
    "#extension GL_EXT_frag_depth : enable\n"
    "#endif\n"
    "\n"
    "#ifdef GL_ES\n"
    "precision highp float;\n"
    "#endif\n"
    "\n"
    "uniform vec3 vEyePosition;\n"
    "uniform vec3 vAmbientColor;\n"
    "uniform vec3 vReflectionColor;\n"
    "uniform vec4 vAlbedoColor;\n"
    "\n"
    "// CUSTOM CONTROLS\n"
    "uniform vec4 vLightingIntensity;\n"
    "uniform vec4 vCameraInfos;\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "uniform vec4 vOverloadedIntensity;\n"
    "uniform vec3 vOverloadedAmbient;\n"
    "uniform vec3 vOverloadedAlbedo;\n"
    "uniform vec3 vOverloadedReflectivity;\n"
    "uniform vec3 vOverloadedEmissive;\n"
    "uniform vec3 vOverloadedReflection;\n"
    "uniform vec3 vOverloadedMicroSurface;\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "uniform vec4 vOverloadedShadowIntensity;\n"
    "#endif\n"
    "\n"
    "#if defined(REFLECTION) || defined(REFRACTION)\n"
    "uniform vec2 vMicrosurfaceTextureLods;\n"
    "#endif\n"
    "\n"
    "uniform vec4 vReflectivityColor;\n"
    "uniform vec3 vEmissiveColor;\n"
    "\n"
    "// Input\n"
    "varying vec3 vPositionW;\n"
    "\n"
    "#ifdef NORMAL\n"
    "varying vec3 vNormalW;\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "varying vec4 vColor;\n"
    "#endif\n"
    "\n"
    "// Lights\n"
    "#include<lightFragmentDeclaration>[0..maxSimultaneousLights]\n"
    "\n"
    "// Samplers\n"
    "#ifdef ALBEDO\n"
    "varying vec2 vAlbedoUV;\n"
    "uniform sampler2D albedoSampler;\n"
    "uniform vec2 vAlbedoInfos;\n"
    "#endif\n"
    "\n"
    "#ifdef AMBIENT\n"
    "varying vec2 vAmbientUV;\n"
    "uniform sampler2D ambientSampler;\n"
    "uniform vec3 vAmbientInfos;\n"
    "#endif\n"
    "\n"
    "#ifdef OPACITY  \n"
    "varying vec2 vOpacityUV;\n"
    "uniform sampler2D opacitySampler;\n"
    "uniform vec2 vOpacityInfos;\n"
    "#endif\n"
    "\n"
    "#ifdef EMISSIVE\n"
    "varying vec2 vEmissiveUV;\n"
    "uniform vec2 vEmissiveInfos;\n"
    "uniform sampler2D emissiveSampler;\n"
    "#endif\n"
    "\n"
    "#ifdef LIGHTMAP\n"
    "varying vec2 vLightmapUV;\n"
    "uniform vec2 vLightmapInfos;\n"
    "uniform sampler2D lightmapSampler;\n"
    "#endif\n"
    "\n"
    "#if defined(REFLECTIVITY) || defined(METALLICWORKFLOW) \n"
    "varying vec2 vReflectivityUV;\n"
    "uniform vec2 vReflectivityInfos;\n"
    "uniform sampler2D reflectivitySampler;\n"
    "#endif\n"
    "\n"
    "// Fresnel\n"
    "#include<fresnelFunction>\n"
    "\n"
    "#ifdef OPACITYFRESNEL\n"
    "uniform vec4 opacityParts;\n"
    "#endif\n"
    "\n"
    "#ifdef EMISSIVEFRESNEL\n"
    "uniform vec4 emissiveLeftColor;\n"
    "uniform vec4 emissiveRightColor;\n"
    "#endif\n"
    "\n"
    "// Refraction Reflection\n"
    "#if defined(REFLECTIONMAP_SPHERICAL) || defined(REFLECTIONMAP_PROJECTION) || defined(REFRACTION)\n"
    "uniform mat4 view;\n"
    "#endif\n"
    "\n"
    "// Refraction\n"
    "#ifdef REFRACTION\n"
    "uniform vec4 vRefractionInfos;\n"
    "\n"
    "#ifdef REFRACTIONMAP_3D\n"
    "uniform samplerCube refractionCubeSampler;\n"
    "#else\n"
    "uniform sampler2D refraction2DSampler;\n"
    "uniform mat4 refractionMatrix;\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "// Reflection\n"
    "#ifdef REFLECTION\n"
    "uniform vec2 vReflectionInfos;\n"
    "\n"
    "#ifdef REFLECTIONMAP_3D\n"
    "uniform samplerCube reflectionCubeSampler;\n"
    "#else\n"
    "uniform sampler2D reflection2DSampler;\n"
    "#endif\n"
    "\n"
    "#ifdef REFLECTIONMAP_SKYBOX\n"
    "varying vec3 vPositionUVW;\n"
    "#else\n"
    "#ifdef REFLECTIONMAP_EQUIRECTANGULAR_FIXED\n"
    "varying vec3 vDirectionW;\n"
    "#endif\n"
    "\n"
    "#if defined(REFLECTIONMAP_PLANAR) || defined(REFLECTIONMAP_CUBIC) || defined(REFLECTIONMAP_PROJECTION)\n"
    "uniform mat4 reflectionMatrix;\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "#include<reflectionFunction>\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef CAMERACOLORGRADING\n"
    "  #include<colorGradingDefinition>\n"
    "#endif\n"
    "\n"
    "#ifdef CAMERACOLORCURVES\n"
    "  #include<colorCurvesDefinition>\n"
    "#endif\n"
    "\n"
    "// PBR\n"
    "#include<pbrShadowFunctions>\n"
    "#include<pbrFunctions>\n"
    "\n"
    "#ifdef CAMERACOLORGRADING\n"
    "  #include<colorGrading>\n"
    "#endif\n"
    "\n"
    "#ifdef CAMERACOLORCURVES\n"
    "  #include<colorCurves>\n"
    "#endif\n"
    "\n"
    "#include<harmonicsFunctions>\n"
    "#include<pbrLightFunctions>\n"
    "\n"
    "#include<helperFunctions>\n"
    "#include<bumpFragmentFunctions>\n"
    "#include<clipPlaneFragmentDeclaration>\n"
    "#include<logDepthDeclaration>\n"
    "\n"
    "// Fog\n"
    "#include<fogFragmentDeclaration>\n"
    "\n"
    "void main(void) {\n"
    "#include<clipPlaneFragment>\n"
    "\n"
    "  vec3 viewDirectionW = normalize(vEyePosition - vPositionW);\n"
    "\n"
    "  // Bump\n"
    "  #ifdef NORMAL\n"
    "  vec3 normalW = normalize(vNormalW);\n"
    "  #else\n"
    "  vec3 normalW = vec3(1.0, 1.0, 1.0);\n"
    "  #endif\n"
    "\n"
    "  #include<bumpFragment>\n"
    "\n"
    "  // Albedo\n"
    "  vec4 surfaceAlbedo = vec4(1., 1., 1., 1.);\n"
    "  vec3 surfaceAlbedoContribution = vAlbedoColor.rgb;\n"
    "\n"
    "  // Alpha\n"
    "  float alpha = vAlbedoColor.a;\n"
    "\n"
    "#ifdef ALBEDO\n"
    "  surfaceAlbedo = texture2D(albedoSampler, vAlbedoUV + uvOffset);\n"
    "  surfaceAlbedo = vec4(toLinearSpace(surfaceAlbedo.rgb), surfaceAlbedo.a);\n"
    "\n"
    "#ifndef LINKREFRACTIONTOTRANSPARENCY\n"
    "#ifdef ALPHATEST\n"
    "  if (surfaceAlbedo.a < 0.4)\n"
    "  discard;\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "#ifdef ALPHAFROMALBEDO\n"
    "  alpha *= surfaceAlbedo.a;\n"
    "#endif\n"
    "\n"
    "  surfaceAlbedo.rgb *= vAlbedoInfos.y;\n"
    "#else\n"
    "  // No Albedo texture.\n"
    "  surfaceAlbedo.rgb = surfaceAlbedoContribution;\n"
    "  surfaceAlbedoContribution = vec3(1., 1., 1.);\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "  surfaceAlbedo.rgb *= vColor.rgb;\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  surfaceAlbedo.rgb = mix(surfaceAlbedo.rgb, vOverloadedAlbedo, vOverloadedIntensity.y);\n"
    "#endif\n"
    "\n"
    "  // Ambient color\n"
    "  vec3 ambientColor = vec3(1., 1., 1.);\n"
    "\n"
    "#ifdef AMBIENT\n"
    "  ambientColor = texture2D(ambientSampler, vAmbientUV + uvOffset).rgb * vAmbientInfos.y;\n"
    "  ambientColor = vec3(1., 1., 1.) - ((vec3(1., 1., 1.) - ambientColor) * vAmbientInfos.z);\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  ambientColor.rgb = mix(ambientColor.rgb, vOverloadedAmbient, vOverloadedIntensity.x);\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "  // Reflectivity map\n"
    "  float microSurface = vReflectivityColor.a;\n"
    "  vec3 surfaceReflectivityColor = vReflectivityColor.rgb;\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  surfaceReflectivityColor.rgb = mix(surfaceReflectivityColor.rgb, vOverloadedReflectivity, vOverloadedIntensity.z);\n"
    "#endif\n"
    "\n"
    "#ifdef REFLECTIVITY\n"
    "  vec4 surfaceReflectivityColorMap = texture2D(reflectivitySampler, vReflectivityUV + uvOffset);\n"
    "  surfaceReflectivityColor = surfaceReflectivityColorMap.rgb;\n"
    "  surfaceReflectivityColor = toLinearSpace(surfaceReflectivityColor);\n"
    "\n"
    "  #ifdef OVERLOADEDVALUES\n"
    "  surfaceReflectivityColor = mix(surfaceReflectivityColor, vOverloadedReflectivity, vOverloadedIntensity.z);\n"
    "  #endif\n"
    "\n"
    "  #ifdef MICROSURFACEFROMREFLECTIVITYMAP\n"
    "  microSurface = surfaceReflectivityColorMap.a;\n"
    "  #else\n"
    "  #ifdef MICROSURFACEAUTOMATIC\n"
    "  microSurface = computeDefaultMicroSurface(microSurface, surfaceReflectivityColor);\n"
    "  #endif\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "#ifdef METALLICWORKFLOW\n"
    "  vec4 surfaceMetallicColorMap = texture2D(reflectivitySampler, vReflectivityUV + uvOffset);\n"
    "\n"
    "  // No gamma space fro the metallic map in metallic workflow.\n"
    "  float metallic = surfaceMetallicColorMap.r; // Unity like base channel for metallness.\n"
    "\n"
    "  // Diffuse is used as the base of the reflectivity.\n"
    "  vec3 baseColor = surfaceAlbedo.rgb;\n"
    "\n"
    "  // Drop the surface diffuse by the 1.0 - metalness.\n"
    "  surfaceAlbedo.rgb *= (1.0 - metallic);\n"
    "  \n"
    "  // Default specular reflectance at normal incidence.\n"
    "  // 4% corresponds to index of refraction (IOR) of 1.50, approximately equal to glass.    \n"
    "  const vec3 DefaultSpecularReflectanceDielectric = vec3(0.04, 0.04, 0.04);\n"
    "\n"
    "  // Compute the converted reflectivity.\n"
    "  surfaceReflectivityColor = mix(DefaultSpecularReflectanceDielectric, baseColor, metallic);\n"
    "\n"
    "  #ifdef OVERLOADEDVALUES\n"
    "  surfaceReflectivityColor = mix(surfaceReflectivityColor, vOverloadedReflectivity, vOverloadedIntensity.z);\n"
    "  #endif\n"
    "\n"
    "  #ifdef METALLICROUGHNESSGSTOREINALPHA\n"
    "  microSurface = 1.0 - surfaceMetallicColorMap.a;\n"
    "  #else\n"
    "  #ifdef METALLICROUGHNESSGSTOREINGREEN\n"
    "  microSurface = 1.0 - surfaceMetallicColorMap.g;\n"
    "  #endif\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  microSurface = mix(microSurface, vOverloadedMicroSurface.x, vOverloadedMicroSurface.y);\n"
    "#endif\n"
    "\n"
    "  // Compute N dot V.\n"
    "  float NdotV = max(0.00000000001, dot(normalW, viewDirectionW));\n"
    "\n"
    "  // Adapt microSurface.\n"
    "  microSurface = clamp(microSurface, 0., 1.) * 0.98;\n"
    "\n"
    "  // Compute roughness.\n"
    "  float roughness = clamp(1. - microSurface, 0.000001, 1.0);\n"
    "\n"
    "  // Lighting\n"
    "  vec3 lightDiffuseContribution = vec3(0., 0., 0.);\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "  vec3 shadowedOnlyLightDiffuseContribution = vec3(1., 1., 1.);\n"
    "#endif\n"
    "\n"
    "#ifdef SPECULARTERM\n"
    "  vec3 lightSpecularContribution = vec3(0., 0., 0.);\n"
    "#endif\n"
    "  \n"
    "  float notShadowLevel = 1.; // 1 - shadowLevel\n"
    "\n"
    "  #ifdef LIGHTMAP\n"
    "  vec3 lightmapColor = texture2D(lightmapSampler, vLightmapUV + uvOffset).rgb * vLightmapInfos.y;\n"
    "  #endif\n"
    "\n"
    "  float NdotL = -1.;\n"
    "  lightingInfo info;\n"
    "\n"
    "  // Compute reflectance.\n"
    "  float reflectance = max(max(surfaceReflectivityColor.r, surfaceReflectivityColor.g), surfaceReflectivityColor.b);\n"
    "\n"
    "  // For typical incident reflectance range (between 4% to 100%) set the grazing reflectance to 100% for typical fresnel effect.\n"
    "  // For very low reflectance range on highly diffuse objects (below 4%), incrementally reduce grazing reflecance to 0%.\n"
    "  float reflectance90 = clamp(reflectance * 25.0, 0.0, 1.0);\n"
    "  vec3 specularEnvironmentR0 = surfaceReflectivityColor.rgb;\n"
    "  vec3 specularEnvironmentR90 = vec3(1.0, 1.0, 1.0) * reflectance90;\n"
    "\n"
    "#include<pbrLightFunctionsCall>[0..maxSimultaneousLights]\n"
    "\n"
    "#ifdef SPECULARTERM\n"
    "  lightSpecularContribution *= vLightingIntensity.w;\n"
    "#endif\n"
    "\n"
    "#ifdef OPACITY\n"
    "  vec4 opacityMap = texture2D(opacitySampler, vOpacityUV + uvOffset);\n"
    "\n"
    "#ifdef OPACITYRGB\n"
    "  opacityMap.rgb = opacityMap.rgb * vec3(0.3, 0.59, 0.11);\n"
    "  alpha *= (opacityMap.x + opacityMap.y + opacityMap.z)* vOpacityInfos.y;\n"
    "#else\n"
    "  alpha *= opacityMap.a * vOpacityInfos.y;\n"
    "#endif\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXALPHA\n"
    "  alpha *= vColor.a;\n"
    "#endif\n"
    "\n"
    "#ifdef OPACITYFRESNEL\n"
    "  float opacityFresnelTerm = computeFresnelTerm(viewDirectionW, normalW, opacityParts.z, opacityParts.w);\n"
    "\n"
    "  alpha += opacityParts.x * (1.0 - opacityFresnelTerm) + opacityFresnelTerm * opacityParts.y;\n"
    "#endif\n"
    "\n"
    "  // Refraction\n"
    "  vec3 surfaceRefractionColor = vec3(0., 0., 0.);\n"
    "\n"
    "  // Go mat -> blurry reflexion according to microSurface\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "  float alphaG = convertRoughnessToAverageSlope(roughness);\n"
    "#endif\n"
    "\n"
    "#ifdef REFRACTION\n"
    "  vec3 refractionVector = refract(-viewDirectionW, normalW, vRefractionInfos.y);\n"
    "\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "#ifdef USEPMREMREFRACTION\n"
    "  float lodRefraction = getMipMapIndexFromAverageSlopeWithPMREM(vMicrosurfaceTextureLods.y, alphaG);\n"
    "#else\n"
    "  float lodRefraction = getMipMapIndexFromAverageSlope(vMicrosurfaceTextureLods.y, alphaG);\n"
    "#endif\n"
    "#else\n"
    "  float biasRefraction = (vMicrosurfaceTextureLods.y + 2.) * (1.0 - microSurface);\n"
    "#endif\n"
    "\n"
    "#ifdef REFRACTIONMAP_3D\n"
    "  refractionVector.y = refractionVector.y * vRefractionInfos.w;\n"
    "\n"
    "  if (dot(refractionVector, viewDirectionW) < 1.0)\n"
    "  {\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "#ifdef USEPMREMREFRACTION\n"
    "  // Empiric Threshold\n"
    "  if ((vMicrosurfaceTextureLods.y - lodRefraction) > 4.0)\n"
    "  {\n"
    "  // Bend to not reach edges.\n"
    "  float scaleRefraction = 1. - exp2(lodRefraction) / exp2(vMicrosurfaceTextureLods.y); // CubemapSize is the size of the base mipmap\n"
    "  float maxRefraction = max(max(abs(refractionVector.x), abs(refractionVector.y)), abs(refractionVector.z));\n"
    "  if (abs(refractionVector.x) != maxRefraction) refractionVector.x *= scaleRefraction;\n"
    "  if (abs(refractionVector.y) != maxRefraction) refractionVector.y *= scaleRefraction;\n"
    "  if (abs(refractionVector.z) != maxRefraction) refractionVector.z *= scaleRefraction;\n"
    "  }\n"
    "#endif\n"
    "\n"
    "  surfaceRefractionColor = textureCubeLodEXT(refractionCubeSampler, refractionVector, lodRefraction).rgb * vRefractionInfos.x;\n"
    "#else\n"
    "  surfaceRefractionColor = textureCube(refractionCubeSampler, refractionVector, biasRefraction).rgb * vRefractionInfos.x;\n"
    "#endif\n"
    "  }\n"
    "\n"
    "#ifndef REFRACTIONMAPINLINEARSPACE\n"
    "  surfaceRefractionColor = toLinearSpace(surfaceRefractionColor.rgb);\n"
    "#endif\n"
    "#else\n"
    "  vec3 vRefractionUVW = vec3(refractionMatrix * (view * vec4(vPositionW + refractionVector * vRefractionInfos.z, 1.0)));\n"
    "\n"
    "  vec2 refractionCoords = vRefractionUVW.xy / vRefractionUVW.z;\n"
    "\n"
    "  refractionCoords.y = 1.0 - refractionCoords.y;\n"
    "\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "  surfaceRefractionColor = texture2DLodEXT(refraction2DSampler, refractionCoords, lodRefraction).rgb * vRefractionInfos.x;\n"
    "#else\n"
    "  surfaceRefractionColor = texture2D(refraction2DSampler, refractionCoords, biasRefraction).rgb * vRefractionInfos.x;\n"
    "#endif    \n"
    "\n"
    "  surfaceRefractionColor = toLinearSpace(surfaceRefractionColor.rgb);\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "  // Reflection\n"
    "  vec3 environmentRadiance = vReflectionColor.rgb;\n"
    "  vec3 environmentIrradiance = vReflectionColor.rgb;\n"
    "\n"
    "#ifdef REFLECTION\n"
    "  vec3 vReflectionUVW = computeReflectionCoords(vec4(vPositionW, 1.0), normalW);\n"
    "\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "#ifdef USEPMREMREFLECTION\n"
    "  float lodReflection = getMipMapIndexFromAverageSlopeWithPMREM(vMicrosurfaceTextureLods.x, alphaG);\n"
    "#else\n"
    "  float lodReflection = getMipMapIndexFromAverageSlope(vMicrosurfaceTextureLods.x, alphaG);\n"
    "#endif\n"
    "#else\n"
    "  float biasReflection = (vMicrosurfaceTextureLods.x + 2.) * (1.0 - microSurface);\n"
    "#endif\n"
    "\n"
    "#ifdef REFLECTIONMAP_3D\n"
    "\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "#ifdef USEPMREMREFLECTION\n"
    "  // Empiric Threshold\n"
    "  if ((vMicrosurfaceTextureLods.y - lodReflection) > 4.0)\n"
    "  {\n"
    "  // Bend to not reach edges.\n"
    "  float scaleReflection = 1. - exp2(lodReflection) / exp2(vMicrosurfaceTextureLods.x); // CubemapSize is the size of the base mipmap\n"
    "  float maxReflection = max(max(abs(vReflectionUVW.x), abs(vReflectionUVW.y)), abs(vReflectionUVW.z));\n"
    "  if (abs(vReflectionUVW.x) != maxReflection) vReflectionUVW.x *= scaleReflection;\n"
    "  if (abs(vReflectionUVW.y) != maxReflection) vReflectionUVW.y *= scaleReflection;\n"
    "  if (abs(vReflectionUVW.z) != maxReflection) vReflectionUVW.z *= scaleReflection;\n"
    "  }\n"
    "#endif\n"
    "\n"
    "  environmentRadiance = textureCubeLodEXT(reflectionCubeSampler, vReflectionUVW, lodReflection).rgb * vReflectionInfos.x;\n"
    "#else\n"
    "  environmentRadiance = textureCube(reflectionCubeSampler, vReflectionUVW, biasReflection).rgb * vReflectionInfos.x;\n"
    "#endif\n"
    "\n"
    "#ifdef USESPHERICALFROMREFLECTIONMAP\n"
    "#ifndef REFLECTIONMAP_SKYBOX\n"
    "  vec3 normalEnvironmentSpace = (reflectionMatrix * vec4(normalW, 1)).xyz;\n"
    "  environmentIrradiance = EnvironmentIrradiance(normalEnvironmentSpace);\n"
    "#endif\n"
    "#else\n"
    "  environmentRadiance = toLinearSpace(environmentRadiance.rgb);\n"
    "\n"
    "  environmentIrradiance = textureCube(reflectionCubeSampler, normalW, 20.).rgb * vReflectionInfos.x;\n"
    "  environmentIrradiance = toLinearSpace(environmentIrradiance.rgb);\n"
    "  environmentIrradiance *= 0.2; // Hack in case of no hdr cube map use for environment.\n"
    "#endif\n"
    "#else\n"
    "  vec2 coords = vReflectionUVW.xy;\n"
    "\n"
    "#ifdef REFLECTIONMAP_PROJECTION\n"
    "  coords /= vReflectionUVW.z;\n"
    "#endif\n"
    "\n"
    "  coords.y = 1.0 - coords.y;\n"
    "#ifdef LODBASEDMICROSFURACE\n"
    "  environmentRadiance = texture2DLodEXT(reflection2DSampler, coords, lodReflection).rgb * vReflectionInfos.x;\n"
    "#else\n"
    "  environmentRadiance = texture2D(reflection2DSampler, coords, biasReflection).rgb * vReflectionInfos.x;\n"
    "#endif\n"
    "\n"
    "  environmentRadiance = toLinearSpace(environmentRadiance.rgb);\n"
    "\n"
    "  environmentIrradiance = texture2D(reflection2DSampler, coords, 20.).rgb * vReflectionInfos.x;\n"
    "  environmentIrradiance = toLinearSpace(environmentIrradiance.rgb);\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  environmentIrradiance = mix(environmentIrradiance, vOverloadedReflection, vOverloadedMicroSurface.z);\n"
    "  environmentRadiance = mix(environmentRadiance, vOverloadedReflection, vOverloadedMicroSurface.z);\n"
    "#endif\n"
    "\n"
    "  environmentRadiance *= vLightingIntensity.z;\n"
    "  environmentIrradiance *= vLightingIntensity.z;\n"
    "\n"
    "  // Specular Environment Fresnel.\n"
    "  vec3 specularEnvironmentReflectance = FresnelSchlickEnvironmentGGX(clamp(NdotV, 0., 1.), specularEnvironmentR0, specularEnvironmentR90, sqrt(microSurface));\n"
    "\n"
    "  // Compute refractance\n"
    "  vec3 refractance = vec3(0.0, 0.0, 0.0);\n"
    "\n"
    "#ifdef REFRACTION\n"
    "  vec3 transmission = vec3(1.0, 1.0, 1.0);\n"
    "  #ifdef LINKREFRACTIONTOTRANSPARENCY\n"
    "  // Transmission based on alpha.\n"
    "  transmission *= (1.0 - alpha);\n"
    "\n"
    "  // Tint the material with albedo.\n"
    "  // TODO. PBR Tinting.\n"
    "  vec3 mixedAlbedo = surfaceAlbedoContribution.rgb * surfaceAlbedo.rgb;\n"
    "  float maxChannel = max(max(mixedAlbedo.r, mixedAlbedo.g), mixedAlbedo.b);\n"
    "  vec3 tint = clamp(maxChannel * mixedAlbedo, 0.0, 1.0);\n"
    "\n"
    "  // Decrease Albedo Contribution\n"
    "  surfaceAlbedoContribution *= alpha;\n"
    "\n"
    "  // Decrease irradiance Contribution\n"
    "  environmentIrradiance *= alpha;\n"
    "\n"
    "  // Tint reflectance\n"
    "  surfaceRefractionColor *= tint;\n"
    "\n"
    "  // Put alpha back to 1;\n"
    "  alpha = 1.0;\n"
    "  #endif\n"
    "\n"
    "  // Add Multiple internal bounces.\n"
    "  vec3 bounceSpecularEnvironmentReflectance = (2.0 * specularEnvironmentReflectance) / (1.0 + specularEnvironmentReflectance);\n"
    "  specularEnvironmentReflectance = mix(bounceSpecularEnvironmentReflectance, specularEnvironmentReflectance, alpha);\n"
    "\n"
    "  // In theory T = 1 - R.\n"
    "  transmission *= 1.0 - specularEnvironmentReflectance;\n"
    "\n"
    "  // Should baked in diffuse.\n"
    "  refractance = surfaceRefractionColor * transmission;\n"
    "#endif\n"
    "\n"
    "  // Apply Energy Conservation taking in account the environment level only if the environment is present.\n"
    "  surfaceAlbedo.rgb = (1. - reflectance) * surfaceAlbedo.rgb;\n"
    "\n"
    "  refractance *= vLightingIntensity.z;\n"
    "  environmentRadiance *= specularEnvironmentReflectance;\n"
    "\n"
    "  // Emissive\n"
    "  vec3 surfaceEmissiveColor = vEmissiveColor;\n"
    "#ifdef EMISSIVE\n"
    "  vec3 emissiveColorTex = texture2D(emissiveSampler, vEmissiveUV + uvOffset).rgb;\n"
    "  surfaceEmissiveColor = toLinearSpace(emissiveColorTex.rgb) * surfaceEmissiveColor * vEmissiveInfos.y;\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDVALUES\n"
    "  surfaceEmissiveColor = mix(surfaceEmissiveColor, vOverloadedEmissive, vOverloadedIntensity.w);\n"
    "#endif\n"
    "\n"
    "#ifdef EMISSIVEFRESNEL\n"
    "  float emissiveFresnelTerm = computeFresnelTerm(viewDirectionW, normalW, emissiveRightColor.a, emissiveLeftColor.a);\n"
    "\n"
    "  surfaceEmissiveColor *= emissiveLeftColor.rgb * (1.0 - emissiveFresnelTerm) + emissiveFresnelTerm * emissiveRightColor.rgb;\n"
    "#endif\n"
    "\n"
    "  // Composition\n"
    "#ifdef EMISSIVEASILLUMINATION\n"
    "  vec3 finalDiffuse = max(lightDiffuseContribution * surfaceAlbedoContribution + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "  shadowedOnlyLightDiffuseContribution = max(shadowedOnlyLightDiffuseContribution * surfaceAlbedoContribution + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "#endif\n"
    "#else\n"
    "#ifdef LINKEMISSIVEWITHALBEDO\n"
    "  vec3 finalDiffuse = max((lightDiffuseContribution + surfaceEmissiveColor) * surfaceAlbedoContribution + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "  shadowedOnlyLightDiffuseContribution = max((shadowedOnlyLightDiffuseContribution + surfaceEmissiveColor) * surfaceAlbedoContribution + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "#endif\n"
    "#else\n"
    "  vec3 finalDiffuse = max(lightDiffuseContribution * surfaceAlbedoContribution + surfaceEmissiveColor + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "  shadowedOnlyLightDiffuseContribution = max(shadowedOnlyLightDiffuseContribution * surfaceAlbedoContribution + surfaceEmissiveColor + vAmbientColor, 0.0) * surfaceAlbedo.rgb;\n"
    "#endif\n"
    "#endif\n"
    "#endif\n"
    "\n"
    "#ifdef OVERLOADEDSHADOWVALUES\n"
    "  finalDiffuse = mix(finalDiffuse, shadowedOnlyLightDiffuseContribution, (1.0 - vOverloadedShadowIntensity.y));\n"
    "#endif\n"
    "\n"
    "#ifdef SPECULARTERM\n"
    "  vec3 finalSpecular = lightSpecularContribution * surfaceReflectivityColor;\n"
    "#else\n"
    "  vec3 finalSpecular = vec3(0.0);\n"
    "#endif\n"
    "\n"
    "#ifdef SPECULAROVERALPHA\n"
    "  alpha = clamp(alpha + getLuminance(finalSpecular), 0., 1.);\n"
    "#endif\n"
    "\n"
    "#ifdef RADIANCEOVERALPHA\n"
    "  alpha = clamp(alpha + getLuminance(environmentRadiance), 0., 1.);\n"
    "#endif\n"
    "\n"
    "  // Composition\n"
    "  // Reflection already includes the environment intensity.\n"
    "#ifdef EMISSIVEASILLUMINATION\n"
    "  vec4 finalColor = vec4(finalDiffuse * ambientColor * vLightingIntensity.x + surfaceAlbedo.rgb * environmentIrradiance + finalSpecular * vLightingIntensity.x + environmentRadiance + surfaceEmissiveColor * vLightingIntensity.y + refractance, alpha);\n"
    "#else\n"
    "  vec4 finalColor = vec4(finalDiffuse * ambientColor * vLightingIntensity.x + surfaceAlbedo.rgb * environmentIrradiance + finalSpecular * vLightingIntensity.x + environmentRadiance + refractance, alpha);\n"
    "#endif\n"
    "\n"
    "#ifdef LIGHTMAP\n"
    "  #ifndef LIGHTMAPEXCLUDED\n"
    "  #ifdef USELIGHTMAPASSHADOWMAP\n"
    "  finalColor.rgb *= lightmapColor;\n"
    "  #else\n"
    "  finalColor.rgb += lightmapColor;\n"
    "  #endif\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "  finalColor = max(finalColor, 0.0);\n"
    "\n"
    "#ifdef CAMERATONEMAP\n"
    "  finalColor.rgb = toneMaps(finalColor.rgb);\n"
    "#endif\n"
    "\n"
    "  finalColor.rgb = toGammaSpace(finalColor.rgb);\n"
    "\n"
    "#include<logDepthFragment>\n"
    "#include<fogFragment>(color, finalColor)\n"
    "\n"
    "#ifdef CAMERACONTRAST\n"
    "  finalColor = contrasts(finalColor);\n"
    "#endif\n"
    "\n"
    "  finalColor.rgb = clamp(finalColor.rgb, 0., 1.);\n"
    "\n"
    "#ifdef CAMERACOLORGRADING\n"
    "  finalColor = colorGrades(finalColor);\n"
    "#endif\n"
    "\n"
    "#ifdef CAMERACOLORCURVES\n"
    "  finalColor.rgb = applyColorCurves(finalColor.rgb);\n"
    "#endif\n"
    "\n"
    "  // Normal Display.\n"
    "  // gl_FragColor = vec4(normalW * 0.5 + 0.5, 1.0);\n"
    "\n"
    "  // Ambient reflection color.\n"
    "  // gl_FragColor = vec4(ambientReflectionColor, 1.0);\n"
    "\n"
    "  // Reflection color.\n"
    "  // gl_FragColor = vec4(reflectionColor, 1.0);\n"
    "\n"
    "  // Base color.\n"
    "  // gl_FragColor = vec4(surfaceAlbedo.rgb, 1.0);\n"
    "\n"
    "  // Specular color.\n"
    "  // gl_FragColor = vec4(surfaceReflectivityColor.rgb, 1.0);\n"
    "\n"
    "  // MicroSurface color.\n"
    "  // gl_FragColor = vec4(microSurface, microSurface, microSurface, 1.0);\n"
    "\n"
    "  // Specular Map\n"
    "  // gl_FragColor = vec4(reflectivityMapColor.rgb, 1.0);\n"
    "\n"
    "  // Refractance\n"
    "  // gl_FragColor = vec4(refractance.rgb, 1.0);\n"
    "\n"
    "  //// Emissive Color\n"
    "  //vec2 test = vEmissiveUV * 0.5 + 0.5;\n"
    "  //gl_FragColor = vec4(test.x, test.y, 1.0, 1.0);\n"
    "\n"
    "  gl_FragColor = finalColor;\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_SHADERS_PBR_FRAGMENT_FX_H