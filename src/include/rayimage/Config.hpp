#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../nlohmann/json.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Light.hpp"
#include "../raymath/MaterialType.hpp"
#include "../raymath/Plan.hpp"
#include "../raymath/ReflectionType.hpp"
#include "../raymath/Shader.hpp"
#include "../raymath/ShaderDiffus.hpp"
#include "../raymath/ShaderFlat.hpp"
#include "../raymath/ShaderPecular.hpp"
#include "../raymath/ShaderPhong.hpp"
#include "../raymath/Shape.hpp"
#include "../raymath/Sphere.hpp"
#include "../raymath/Triangle.hpp"
#include "../raymath/Vector.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Scene.hpp"

using json = nlohmann::json;

enum class ShaderType { PHONG, FLAT, DIFFUS, PECULAR, UNKNOWN };
enum class ShapeType { SPHERE, PLAN, TRIANGLE, UNKNOWN };

class Config {
 public:
  Config(const std::string& configFilePath);
  bool loadConfig();
  std::string getOutputDirectory() const;
  int getImageWidth() const;
  int getImageHeight() const;
  int getMaxReflections() const;
  Color getBackgroundColor() const;
  std::vector<Light> getLights() const;
  std::vector<std::unique_ptr<Shape>> getShapes() const;
  std::shared_ptr<Shader> getShader() const;

 private:
  std::string configFilePath;
  json config;
  static const std::unordered_map<std::string, ShaderType> shaderTypeMap;
  static const std::unordered_map<std::string, MaterialType> materialTypeMap;
  static const std::unordered_map<std::string, ShapeType> shapeTypeMap;

  Vector jsonToVector(const json& j) const;
  Color jsonToColor(const json& j) const;
};