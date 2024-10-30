#include "../../include/rayimage/Config.hpp"

const std::unordered_map<std::string, ShaderType> Config::shaderTypeMap = {
    {"phong", ShaderType::PHONG},
    {"flat", ShaderType::FLAT},
    {"diffus", ShaderType::DIFFUS},
    {"pecular", ShaderType::PECULAR}};

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
  return Color(config["background"]["color"][0],
               config["background"]["color"][1],
               config["background"]["color"][2]);
}

std::vector<Light> Config::getLights() const {
  std::vector<Light> lights;
  for (const auto& light : config["lights"]) {
    lights.emplace_back(
        Color(light["color"][0], light["color"][1], light["color"][2]),
        Vector(light["position"][0], light["position"][1],
               light["position"][2]));
  }
  return lights;
}

std::vector<std::unique_ptr<Shape>> Config::getShapes() const {
  std::vector<std::unique_ptr<Shape>> shapes;
  for (const auto& shape : config["shapes"]) {
    if (shape["type"] == "sphere") {
      shapes.push_back(std::make_unique<Sphere>(
          Vector(shape["position"][0], shape["position"][1],
                 shape["position"][2]),
          shape["radius"],
          shape["reflection_type"] == "reflective" ? ReflectionType::REFLECTIVE
                                                   : ReflectionType::MAT,
          Color(shape["color"][0], shape["color"][1], shape["color"][2])));
    }
    // TODO: Add other shapes later
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