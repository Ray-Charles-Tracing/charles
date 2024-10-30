# Projet C++ avec Docker et Docker Compose

Ce projet est une application C++ qui génère des images PNG et les enregistre dans un dossier partagé entre le conteneur Docker et votre machine. L'application utilise plusieurs classes et est organisée dans un dossier `src` pour une meilleure gestion du code.

## Structure du projet

project/
├── Dockerfile
├── docker-compose.yml
├── README.md
├── src/
│ └── main.cpp
└── render/

- **Dockerfile** : Contient les instructions pour construire l'image Docker de l'application.
- **docker-compose.yml** : Automatiser la création du conteneur, le montage du volume pour les images PNG, et le lancement du programme.
- **src/** : Dossier contenant tous les fichiers source de l’application.
- **render/** : Dossier de sortie pour les images PNG générées, partagé entre la machine hôte et le conteneur.

## Prérequis

- [Docker](https://www.docker.com/get-started)
- [Docker Compose](https://docs.docker.com/compose/install/)

## Instructions d'installation

1. Clonez ce dépôt dans un répertoire local :

```bash
  git clone https://github.com/votre-utilisateur/votre-repo.git
  cd votre-repo
```

2. Créez le dossier render pour stocker les images PNG générées :

```bash
  mkdir render
```

## Utilisation

1. Construisez et lancez l'application avec Docker Compose :

```bash
docker-compose up --build
```

- L’option `--build` force la reconstruction de l'image Docker pour prendre en compte les changements éventuels dans le code.
- Docker Compose va compiler les fichiers sources du dossier `src/`, créer un exécutable, et exécuter le programme dans un conteneur.

2. Les images PNG générées par le programme seront accessibles dans le dossier `render` de votre machine.

## Arrêt de l'application

Pour arrêter et nettoyer les conteneurs créés par Docker Compose, utilisez :

```bash
docker-compose down
```
