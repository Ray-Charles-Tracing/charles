#pragma once

#include <algorithm>  // For std::min and std::max
#include <iostream>

#include "Color.hpp"
#include "MaterialType.hpp"
#include "ReflectionType.hpp"

class Material {
 protected:
  ReflectionType reflectionType;
  Color color;
  MaterialType materialType;
  float diffuseReflexionCoef;
  float specularReflexionCoef;
  float roughness;  // Coefficient de rugosité

 public:
  Material(ReflectionType reflectionType, Color color,
           MaterialType materialType)
      : reflectionType(reflectionType),
        color(color),
        materialType(materialType) {
    setMaterialCoefficients(materialType);
    adjustCoefficientsForReflectionType();
  }

  virtual ~Material() = default;

  void setMaterialCoefficients(MaterialType materialType) {
    switch (materialType) {
      case MaterialType::WOOD:
        diffuseReflexionCoef = 0.7f;
        specularReflexionCoef = 0.3f;
        roughness = 0.5f;  // Exemple de rugosité pour le bois
        break;
      case MaterialType::METAL:
        diffuseReflexionCoef = 0.3f;
        specularReflexionCoef = 0.8f;
        roughness = 0.1f;  // Exemple de rugosité pour le métal
        break;
      case MaterialType::PLASTIC:
        diffuseReflexionCoef = 0.6f;
        specularReflexionCoef = 0.6f;
        roughness = 0.3f;  // Exemple de rugosité pour le plastique
        break;
      case MaterialType::GLASS:
        diffuseReflexionCoef = 0.1f;
        specularReflexionCoef = 1.0f;
        roughness = 0.0f;  // Exemple de rugosité pour le verre
        break;
      case MaterialType::CERAMIC:
        diffuseReflexionCoef = 0.5f;
        specularReflexionCoef = 0.4f;
        roughness = 0.4f;  // Exemple de rugosité pour la céramique
        break;
      default:
        diffuseReflexionCoef = 0.5f;   // Valeurs par défaut
        specularReflexionCoef = 0.5f;  // Valeurs par défaut
        roughness = 0.5f;              // Valeur par défaut
        break;
    }
  }

  void adjustCoefficientsForReflectionType() {
    switch (reflectionType) {
      case ReflectionType::MAT:
        diffuseReflexionCoef =
            std::min(diffuseReflexionCoef * 1.2f,
                     1.0f);  // Augmenter légèrement la réflexion diffuse
        specularReflexionCoef =
            std::max(specularReflexionCoef * 0.5f,
                     0.0f);  // Réduire la réflexion spéculaire
        break;

      case ReflectionType::REFLECTIVE:
        diffuseReflexionCoef = std::max(diffuseReflexionCoef * 0.5f,
                                        0.0f);  // Réduire la réflexion diffuse
        specularReflexionCoef =
            std::min(specularReflexionCoef * 1.5f,
                     1.0f);  // Augmenter la réflexion spéculaire
        break;

      default:
        break;  // Aucun ajustement par défaut
    }
  }

  ReflectionType getReflectionType() const { return reflectionType; }
  Color getColor() const { return color; }
  float getDiffuseReflexionCoef() const { return diffuseReflexionCoef; }
  float getSpecularReflexionCoef() const { return specularReflexionCoef; }
  float getRoughness() const { return roughness; }  // Getter pour la rugosité

  friend std::ostream& operator<<(std::ostream& _stream,
                                  Material const& material) {
    _stream << "(ReflectionType: " << static_cast<int>(material.reflectionType)
            << ", Color: " << material.color
            << ", K_D: " << material.diffuseReflexionCoef
            << ", K_S: " << material.specularReflexionCoef
            << ", Roughness: " << material.roughness
            << ")";  // Affichez la rugosité
    return _stream;
  }
};
