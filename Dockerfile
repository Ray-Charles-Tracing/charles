# Utilise une image de base avec un compilateur C++
FROM gcc:latest

# Créer un répertoire de travail dans le conteneur
WORKDIR /app

# Copier tous les fichiers source dans le conteneur
COPY src/ src/

# Créer le dossier de rendu et de la bibliothèque statique
RUN mkdir -p /app/render

# Étape 1 : Compiler tous les fichiers source des différentes lib en fichiers objets
RUN for file in ./src/lib/lodepng/*.cpp; do g++ -c "$file" -o "./src/lib/lodepng/$(basename "$file" .cpp).o"; done
RUN for file in ./src/lib/raymath/*.cpp; do g++ -c "$file" -o "./src/lib/raymath/$(basename "$file" .cpp).o"; done
RUN for file in ./src/lib/rayimage/*.cpp; do g++ -c "$file" -o "./src/lib/rayimage/$(basename "$file" .cpp).o"; done

# Étape 2 : Créer les bibliothèques statique à partir des fichiers objets
RUN ar rcs ./src/lib/liblodepng.a ./src/lib/lodepng/*.o
RUN ar rcs ./src/lib/libraymath.a ./src/lib/raymath/*.o
RUN ar rcs ./src/lib/librayimage.a ./src/lib/rayimage/*.o

# Étape 2 : Compiler le projet principal en incluant la bibliothèque statique
RUN g++ -o main src/*.cpp -I src/include -L src/lib -lrayimage -lraymath -llodepng

# Définir la commande par défaut pour lancer le programme
CMD ["./main"]