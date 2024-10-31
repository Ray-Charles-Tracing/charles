#include "../../include/rayimage/Config.hpp"

const std::unordered_map<std::string, ShaderType> Config::shaderTypeMap = {
    {"phong", ShaderType::PHONG},
    {"flat", ShaderType::FLAT},
    {"diffus", ShaderType::DIFFUS},
    {"pecular", ShaderType::PECULAR}};

const std::unordered_map<std::string, MaterialType> Config::materialTypeMap = {
    {"wood", MaterialType::WOOD},
    {"metal", MaterialType::METAL},
    {"plastic", MaterialType::PLASTIC},
    {"glass", MaterialType::GLASS},
    {"ceramic", MaterialType::CERAMIC}};

const std::unordered_map<std::string, ShapeType> Config::shapeTypeMap = {
    {"sphere", ShapeType::SPHERE},
    {"plan", ShapeType::PLAN},
    {"triangle", ShapeType::TRIANGLE},
    {"cube", ShapeType::CUBE}};

Config::Config(const std::string& configFilePath)
    : configFilePath(configFilePath) {}

bool Config::loadConfig() {
  std::ifstream config_file(configFilePath);
  if (!config_file.is_open()) {
    std::cerr << "Failed to open " << configFilePath << std::endl;
    return false;
  }
  config_file >> config;
  return true;
}

std::string Config::getOutputDirectory() const {
  return config["output_directory"].get<std::string>();
}

int Config::getImageWidth() const { return config["image"]["width"]; }

int Config::getImageHeight() const { return config["image"]["height"]; }

int Config::getMaxReflections() const { return config["max_reflections"]; }

Color Config::getBackgroundColor() const {
  return jsonToColor(config["background"]["color"]);
}

std::vector<Light> Config::getLights() const {
  std::vector<Light> lights;
  for (const auto& light : config["lights"]) {
    lights.emplace_back(jsonToColor(light["color"]),
                        jsonToVector(light["position"]));
  }
  return lights;
}

std::vector<std::unique_ptr<Shape>> Config::getShapes() const {
  std::vector<std::unique_ptr<Shape>> shapes;
  for (const auto& shape : config["shapes"]) {
    MaterialType materialType = MaterialType::METAL;  // Default material
    auto it = materialTypeMap.find(shape["material_type"]);
    if (it != materialTypeMap.end()) {
      materialType = it->second;
    }

    ShapeType shapeType = ShapeType::UNKNOWN;
    auto shapeIt = shapeTypeMap.find(shape["type"]);
    if (shapeIt != shapeTypeMap.end()) {
      shapeType = shapeIt->second;
    }

    ReflectionType reflectionType = shape["reflection_type"] == "reflective"
                                        ? ReflectionType::REFLECTIVE
                                        : ReflectionType::MAT;

    switch (shapeType) {
      case ShapeType::SPHERE:
        shapes.push_back(std::make_unique<Sphere>(
            jsonToVector(shape["position"]), shape["radius"], reflectionType,
            jsonToColor(shape["color"]), materialType));
        break;
      case ShapeType::PLAN:
        shapes.push_back(std::make_unique<Plan>(
            jsonToVector(shape["position"]), jsonToVector(shape["normal"]),
            reflectionType, jsonToColor(shape["color"]), materialType));
        break;
      case ShapeType::TRIANGLE:
        shapes.push_back(std::make_unique<Triangle>(
            jsonToVector(shape["v1"]), jsonToVector(shape["v2"]),
            jsonToVector(shape["v3"]), reflectionType,
            jsonToColor(shape["color"]), materialType));
        break;
      case ShapeType::CUBE:
        shapes.push_back(std::make_unique<Cube>(
            jsonToVector(shape["position"]), shape["size"],
            jsonToColor(shape["color"]), reflectionType, materialType));
        break;
      default:
        std::cerr << "Unknown shape type: " << shape["type"] << std::endl;
        break;
    }
  }
  return shapes;
}

std::shared_ptr<Shader> Config::getShader() const {
  std::string shaderTypeStr = config["shader"].get<std::string>();
  ShaderType shaderType = ShaderType::UNKNOWN;

  auto it = shaderTypeMap.find(shaderTypeStr);
  if (it != shaderTypeMap.end()) {
    shaderType = it->second;
  }

  switch (shaderType) {
    case ShaderType::PHONG:
      return std::make_shared<ShaderPhong>();
    case ShaderType::FLAT:
      return std::make_shared<ShaderFlat>();
    case ShaderType::DIFFUS:
      return std::make_shared<ShaderDiffus>();
    case ShaderType::PECULAR:
      return std::make_shared<ShaderPecular>();
    default:
      std::cerr << "Unknown shader type: " << shaderTypeStr << std::endl;
      return nullptr;
  }
}

Vector Config::jsonToVector(const json& j) const {
  return Vector(j[0], j[1], j[2]);
}

Color Config::jsonToColor(const json& j) const {
  return Color(j[0], j[1], j[2]);
}