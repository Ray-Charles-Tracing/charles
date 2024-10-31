#!/bin/bash

# Étape 1 : Compiler tous les fichiers source des différentes lib en fichiers objets
for file in ./src/lib/lodepng/*.cpp; do
  g++ -std=c++17 -c "$file" -o "./src/lib/lodepng/$(basename "$file" .cpp).o"
done

for file in ./src/lib/raymath/*.cpp; do
  g++ -std=c++17 -c "$file" -o "./src/lib/raymath/$(basename "$file" .cpp).o"
done

for file in ./src/lib/rayimage/*.cpp; do
  g++ -std=c++17 -c "$file" -o "./src/lib/rayimage/$(basename "$file" .cpp).o"
done

# Étape 2 : Créer les bibliothèques statiques à partir des fichiers objets
ar rcs ./src/lib/liblodepng.a ./src/lib/lodepng/*.o
ar rcs ./src/lib/libraymath.a ./src/lib/raymath/*.o
ar rcs ./src/lib/librayimage.a ./src/lib/rayimage/*.o

# Étape 3 : Compiler le projet principal en incluant la bibliothèque statique
g++ -std=c++17 -o main src/*.cpp -I src/include -L src/lib -lrayimage -lraymath -llodepng

# Définir la commande par défaut pour lancer le programme et mesurer le temps d'exécution
/usr/bin/time -f 'Elapsed time: %E' ./main