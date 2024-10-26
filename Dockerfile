# Utilise une image de base avec un compilateur C++
FROM gcc:latest

# Créer un répertoire de travail dans le conteneur
WORKDIR /app

# Copier tous les fichiers source dans le conteneur
COPY src/ src/

# Créer le dossier de rendu et de la bibliothèque statique
RUN mkdir -p /app/render src/raymath/lib

# Étape 1 : Compiler tous les fichiers source de raymath en fichiers objets en une seule commande
RUN for file in ./src/raymath/*.cpp; do g++ -c "$file" -o "src/raymath/lib/$(basename "$file" .cpp).o"; done

# Étape 2 : Créer la bibliothèque statique libraymath.a à partir des fichiers objets
RUN ar rcs ./src/raymath/lib/libraymath.a ./src/raymath/lib/*.o

# Étape 2 : Compiler le projet principal en incluant la bibliothèque statique
RUN g++ -o main ./src/*.cpp -I ./src/raymath/include/ -L ./src/raymath/lib -l raymath

# Définir la commande par défaut pour lancer le programme
CMD ["./main"]