# Utilise une image de base avec un compilateur C++
FROM gcc:latest

# Créer un répertoire de travail dans le conteneur
WORKDIR /app

# Copier tous les fichiers source dans le conteneur
COPY src/ src/

# Créer le dossier de rendu
RUN mkdir -p /app/render

# Compiler tous les fichiers .cpp de src/ et générer un exécutable nommé 'main'
RUN g++ -o main src/*.cpp

# Définir la commande par défaut pour lancer le programme
CMD ["./main"]