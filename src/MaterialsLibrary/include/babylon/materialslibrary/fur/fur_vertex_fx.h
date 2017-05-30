﻿#ifndef BABYLON_MATERIALS_LIBRARY_FUR_FUR_VERTEX_FX_H
#define BABYLON_MATERIALS_LIBRARY_FUR_FUR_VERTEX_FX_H

namespace BABYLON {

extern const char* furVertexShader;

const char* furVertexShader
  = "#ifdef GL_ES\n"
    "precision highp float;\n"
    "#endif\n"
    "\n"
    "// Attributes\n"
    "attribute vec3 position;\n"
    "attribute vec3 normal;\n"
    "\n"
    "#ifdef UV1\n"
    "attribute vec2 uv;\n"
    "#endif\n"
    "#ifdef UV2\n"
    "attribute vec2 uv2;\n"
    "#endif\n"
    "#ifdef VERTEXCOLOR\n"
    "attribute vec4 color;\n"
    "#endif\n"
    "\n"
    "#include<bonesDeclaration>\n"
    "\n"
    "// Uniforms\n"
    "uniform float furLength;\n"
    "uniform float furAngle;\n"
    "#ifdef HIGHLEVEL\n"
    "uniform float furOffset;\n"
    "uniform vec3 furGravity;\n"
    "uniform float furTime;\n"
    "uniform float furSpacing;\n"
    "uniform float furDensity;\n"
    "#endif\n"
    "#ifdef HEIGHTMAP\n"
    "uniform sampler2D heightTexture;\n"
    "#endif\n"
    "\n"
    "#ifdef HIGHLEVEL\n"
    "varying vec2 vFurUV;\n"
    "#endif\n"
    "\n"
    "#include<instancesDeclaration>\n"
    "\n"
    "uniform mat4 view;\n"
    "uniform mat4 viewProjection;\n"
    "\n"
    "#ifdef DIFFUSE\n"
    "varying vec2 vDiffuseUV;\n"
    "uniform mat4 diffuseMatrix;\n"
    "uniform vec2 vDiffuseInfos;\n"
    "#endif\n"
    "\n"
    "#ifdef POINTSIZE\n"
    "uniform float pointSize;\n"
    "#endif\n"
    "\n"
    "// Output\n"
    "varying vec3 vPositionW;\n"
    "#ifdef NORMAL\n"
    "varying vec3 vNormalW;\n"
    "#endif\n"
    "varying float vfur_length;\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "varying vec4 vColor;\n"
    "#endif\n"
    "\n"
    "#include<clipPlaneVertexDeclaration>\n"
    "#include<fogVertexDeclaration>\n"
    "#include<shadowsVertexDeclaration>[0..maxSimultaneousLights]\n"
    "\n"
    "float Rand(vec3 rv) {\n"
    "  float x = dot(rv, vec3(12.9898,78.233, 24.65487));\n"
    "  return fract(sin(x) * 43758.5453);\n"
    "}\n"
    "\n"
    "void main(void) {\n"
    "\n"
    "  #include<instancesVertex>\n"
    "  #include<bonesVertex>\n"
    "\n"
    "//FUR\n"
    "float r = Rand(position);\n"
    "#ifdef HEIGHTMAP\n"
    "  #if __VERSION__ > 100\n"
    "  vfur_length = furLength * texture(heightTexture, uv).x;\n"
    "  #else\n"
    "  vfur_length = furLength * texture2D(heightTexture, uv).r;\n"
    "  #endif\n"
    "#else  \n"
    "  vfur_length = (furLength * r);\n"
    "#endif\n"
    "  vec3 tangent1 = vec3(normal.y, -normal.x, 0);\n"
    "  vec3 tangent2 = vec3(-normal.z, 0, normal.x);\n"
    "  r = Rand(tangent1 * r);\n"
    "  float J = (2.0 + 4.0 * r);\n"
    "  r = Rand(tangent2*r);\n"
    "  float K = (2.0 + 2.0 * r);\n"
    "  tangent1 = tangent1*J + tangent2 * K;\n"
    "  tangent1 = normalize(tangent1);\n"
    "  \n"
    "  vec3 newPosition = position + normal * vfur_length*cos(furAngle) + tangent1 * vfur_length * sin(furAngle);\n"
    "  \n"
    "  #ifdef HIGHLEVEL\n"
    "  // Compute fur data passed to the pixel shader\n"
    "  vec3 forceDirection = vec3(0.0, 0.0, 0.0);\n"
    "  forceDirection.x = sin(furTime + position.x * 0.05) * 0.2;\n"
    "  forceDirection.y = cos(furTime * 0.7 + position.y * 0.04) * 0.2;\n"
    "  forceDirection.z = sin(furTime * 0.7 + position.z * 0.04) * 0.2;\n"
    "  \n"
    "  vec3 displacement = vec3(0.0, 0.0, 0.0);\n"
    "  displacement = furGravity + forceDirection;\n"
    "  \n"
    "  float displacementFactor = pow(furOffset, 3.0);\n"
    "  \n"
    "  vec3 aNormal = normal;\n"
    "  aNormal.xyz += displacement * displacementFactor;\n"
    "  \n"
    "  newPosition = vec3(newPosition.x, newPosition.y, newPosition.z) + (normalize(aNormal) * furOffset * furSpacing);\n"
    "  #endif\n"
    "  \n"
    "  #ifdef NORMAL\n"
    "  #ifdef HIGHLEVEL\n"
    "  vNormalW = normalize(vec3(finalWorld * vec4(normal, 0.0)) * aNormal);\n"
    "  #else\n"
    "  vNormalW = normalize(vec3(finalWorld * vec4(normal, 0.0)));\n"
    "  #endif\n"
    "  #endif\n"
    "  \n"
    "//END FUR\n"
    "  gl_Position = viewProjection * finalWorld * vec4(newPosition, 1.0);\n"
    "\n"
    "  vec4 worldPos = finalWorld * vec4(newPosition, 1.0);\n"
    "  vPositionW = vec3(worldPos);\n"
    "\n"
    "  // Texture coordinates\n"
    "#ifndef UV1\n"
    "  vec2 uv = vec2(0., 0.);\n"
    "#endif\n"
    "#ifndef UV2\n"
    "  vec2 uv2 = vec2(0., 0.);\n"
    "#endif\n"
    "\n"
    "#ifdef DIFFUSE\n"
    "  if (vDiffuseInfos.x == 0.)\n"
    "  {\n"
    "  vDiffuseUV = vec2(diffuseMatrix * vec4(uv, 1.0, 0.0));\n"
    "  }\n"
    "  else\n"
    "  {\n"
    "  vDiffuseUV = vec2(diffuseMatrix * vec4(uv2, 1.0, 0.0));\n"
    "  }\n"
    "  \n"
    "  #ifdef HIGHLEVEL\n"
    "  vFurUV = vDiffuseUV * furDensity;\n"
    "  #endif\n"
    "#else\n"
    "  #ifdef HIGHLEVEL\n"
    "  vFurUV = uv * furDensity;\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "  // Clip plane\n"
    "  #include<clipPlaneVertex>\n"
    "\n"
    "  // Fog\n"
    "  #include<fogVertex>\n"
    "\n"
    "  // Shadows\n"
    "  #include<shadowsVertex>[0..maxSimultaneousLights]\n"
    "\n"
    "  // Vertex color\n"
    "#ifdef VERTEXCOLOR\n"
    "  vColor = color;\n"
    "#endif\n"
    "\n"
    "  // Point size\n"
    "#ifdef POINTSIZE\n"
    "  gl_PointSize = pointSize;\n"
    "#endif\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_LIBRARY_FUR_FUR_VERTEX_FX_H
