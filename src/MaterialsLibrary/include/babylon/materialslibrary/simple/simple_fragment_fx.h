﻿#ifndef BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_FRAGMENT_FX_H
#define BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_FRAGMENT_FX_H

namespace BABYLON {

extern const char* simplePixelShader;

const char* simplePixelShader
  = "#ifdef GL_ES\n"
    "precision highp float;\n"
    "#endif\n"
    "\n"
    "// Constants\n"
    "uniform vec3 vEyePosition;\n"
    "uniform vec4 vDiffuseColor;\n"
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
    "#include<__decl__lightFragment>[0..maxSimultaneousLights]\n"
    "\n"
    "\n"
    "#include<lightsFragmentFunctions>\n"
    "#include<shadowsFragmentFunctions>\n"
    "\n"
    "// Samplers\n"
    "#ifdef DIFFUSE\n"
    "varying vec2 vDiffuseUV;\n"
    "uniform sampler2D diffuseSampler;\n"
    "uniform vec2 vDiffuseInfos;\n"
    "#endif\n"
    "\n"
    "#include<clipPlaneFragmentDeclaration>\n"
    "\n"
    "// Fog\n"
    "#include<fogFragmentDeclaration>\n"
    "\n"
    "void main(void) {\n"
    "#include<clipPlaneFragment>\n"
    "\n"
    "  vec3 viewDirectionW = normalize(vEyePosition - vPositionW);\n"
    "\n"
    "  // Base color\n"
    "  vec4 baseColor = vec4(1., 1., 1., 1.);\n"
    "  vec3 diffuseColor = vDiffuseColor.rgb;\n"
    "\n"
    "  // Alpha\n"
    "  float alpha = vDiffuseColor.a;\n"
    "\n"
    "#ifdef DIFFUSE\n"
    "  baseColor = texture2D(diffuseSampler, vDiffuseUV);\n"
    "\n"
    "#ifdef ALPHATEST\n"
    "  if (baseColor.a < 0.4)\n"
    "  discard;\n"
    "#endif\n"
    "\n"
    "  baseColor.rgb *= vDiffuseInfos.y;\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "  baseColor.rgb *= vColor.rgb;\n"
    "#endif\n"
    "\n"
    "  // Normal\n"
    "#ifdef NORMAL\n"
    "  vec3 normalW = normalize(vNormalW);\n"
    "#else\n"
    "  vec3 normalW = vec3(1.0, 1.0, 1.0);\n"
    "#endif\n"
    "\n"
    "  // Lighting\n"
    "  vec3 diffuseBase = vec3(0., 0., 0.);\n"
    "  lightingInfo info;\n"
    "  float shadow = 1.;\n"
    "  float glossiness = 0.;\n"
    "\n"
    "#ifdef SPECULARTERM\n"
    "  vec3 specularBase = vec3(0., 0., 0.);\n"
    "#endif    \n"
    "#include<lightFragment>[0..maxSimultaneousLights]\n"
    "\n"
    "\n"
    "#ifdef VERTEXALPHA\n"
    "  alpha *= vColor.a;\n"
    "#endif\n"
    "\n"
    "  vec3 finalDiffuse = clamp(diffuseBase * diffuseColor, 0.0, 1.0) * baseColor.rgb;\n"
    "\n"
    "  // Composition\n"
    "  vec4 color = vec4(finalDiffuse, alpha);\n"
    "\n"
    "#include<fogFragment>\n"
    "\n"
    "  gl_FragColor = color;\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_FRAGMENT_FX_H
