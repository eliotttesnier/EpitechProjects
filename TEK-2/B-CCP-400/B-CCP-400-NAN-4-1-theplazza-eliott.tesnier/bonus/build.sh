#!/bin/bash

# Script de compilation pour Plazza
# Usage: ./compile.sh [clean|debug|release|help]

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PROJECT_DIR="$(pwd)"
BUILD_DIR="build"
CMAKE_BUILD_TYPE="Release"
VERBOSE=false

# Fonction d'aide
show_help() {
    echo -e "${BLUE}Script de compilation Plazza${NC}"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  clean      Nettoie le répertoire de build"
    echo "  debug      Compile en mode debug"
    echo "  release    Compile en mode release (défaut)"
    echo "  verbose    Affiche les détails de compilation"
    echo "  help       Affiche cette aide"
    echo ""
    echo "Exemples:"
    echo "  $0                 # Compilation release normale"
    echo "  $0 debug           # Compilation en mode debug"
    echo "  $0 clean debug     # Nettoie puis compile en debug"
    echo "  $0 verbose         # Compilation avec détails"
}

# Fonction de nettoyage
clean_build() {
    echo -e "${YELLOW}🧹 Nettoyage du répertoire de build...${NC}"
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        echo -e "${GREEN}✓ Répertoire de build nettoyé${NC}"
    else
        echo -e "${BLUE}ℹ Aucun répertoire de build à nettoyer${NC}"
    fi
}

# Fonction de vérification des dépendances
check_dependencies() {
    echo -e "${BLUE}🔍 Vérification des dépendances...${NC}"

    # Vérifier CMake
    if ! command -v cmake &> /dev/null; then
        echo -e "${RED}❌ CMake non trouvé. Veuillez l'installer.${NC}"
        exit 1
    fi

    # Vérifier le compilateur C++
    if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
        echo -e "${RED}❌ Aucun compilateur C++ trouvé (g++ ou clang++).${NC}"
        exit 1
    fi

    # Vérifier Qt6 (optionnel)
    if command -v qmake6 &> /dev/null || command -v qmake &> /dev/null; then
        echo -e "${GREEN}✓ Qt6 détecté - Support GUI activé${NC}"
    else
        echo -e "${YELLOW}⚠ Qt6 non détecté - Compilation sans GUI${NC}"
    fi

    echo -e "${GREEN}✓ Dépendances vérifiées${NC}"
}

# Fonction de configuration CMake
configure_cmake() {
    echo -e "${BLUE}⚙️ Configuration CMake...${NC}"

    # Créer le répertoire de build
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    # Commande CMake de base
    CMAKE_CMD="cmake -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE .."

    # Exécuter la configuration
    if $VERBOSE; then
        echo -e "${YELLOW}Commande: $CMAKE_CMD${NC}"
    fi

    if $CMAKE_CMD; then
        echo -e "${GREEN}✓ Configuration CMake réussie${NC}"
    else
        echo -e "${RED}❌ Échec de la configuration CMake${NC}"
        exit 1
    fi

    cd "$PROJECT_DIR"
}

# Fonction de compilation
build_project() {
    echo -e "${BLUE}🔨 Compilation du projet...${NC}"

    cd "$BUILD_DIR"

    # Déterminer le nombre de threads
    NPROC=$(nproc 2>/dev/null || echo 4)

    # Commande de build
    if $VERBOSE; then
        BUILD_CMD="cmake --build . --parallel $NPROC -- VERBOSE=1"
    else
        BUILD_CMD="cmake --build . --parallel $NPROC"
    fi

    echo -e "${YELLOW}Compilation avec $NPROC threads...${NC}"

    if $VERBOSE; then
        echo -e "${YELLOW}Commande: $BUILD_CMD${NC}"
    fi

    if $BUILD_CMD; then
        echo -e "${GREEN}✓ Compilation réussie${NC}"

        # Vérifier l'exécutable
        if [ -f "plazza" ]; then
            echo -e "${GREEN}✓ Exécutable 'plazza' créé${NC}"

            # Copier l'exécutable dans le répertoire principal
            cp plazza "$PROJECT_DIR/"
            echo -e "${GREEN}✓ Exécutable copié dans le répertoire principal${NC}"
        else
            echo -e "${YELLOW}⚠ Exécutable non trouvé dans le répertoire de build${NC}"
        fi
    else
        echo -e "${RED}❌ Échec de la compilation${NC}"
        exit 1
    fi

    cd "$PROJECT_DIR"
}

# Fonction d'affichage des informations finales
show_completion_info() {
    echo ""
    echo -e "${GREEN}🎉 Compilation terminée avec succès !${NC}"
    echo ""
    echo -e "${BLUE}Pour exécuter le programme :${NC}"
    echo -e "  ${YELLOW}./plazza <multiplier> <cooks_per_kitchen> <regeneration_time_ms>${NC}"
    echo -e "  ${YELLOW}./plazza <multiplier> <cooks_per_kitchen> <regeneration_time_ms>${NC} -d"
    echo ""
    echo -e "${BLUE}Exemples :${NC}"
    echo -e "  ${YELLOW}./plazza 2 5 1000${NC}                    # Mode CLI"
    echo -e "  ${YELLOW}./plazza 2 5 1000${NC} -d                 # Mode GUI"
    echo ""

    # Afficher la taille de l'exécutable
    if [ -f "plazza" ]; then
        SIZE=$(du -h plazza | cut -f1)
        echo -e "${BLUE}Taille de l'exécutable : ${YELLOW}$SIZE${NC}"
    fi
}

# Analyse des arguments
CLEAN=false
for arg in "$@"; do
    case $arg in
        clean)
            CLEAN=true
            ;;
        debug)
            CMAKE_BUILD_TYPE="Debug"
            ;;
        release)
            CMAKE_BUILD_TYPE="Release"
            ;;
        verbose)
            VERBOSE=true
            ;;
        help)
            show_help
            exit 0
            ;;
        *)
            echo -e "${RED}❌ Argument inconnu: $arg${NC}"
            echo "Utilisez '$0 help' pour voir l'aide."
            exit 1
            ;;
    esac
done

# Exécution principale
echo -e "${BLUE}🍕 Compilation de Plazza - Mode $CMAKE_BUILD_TYPE${NC}"
echo ""

# Nettoyer si demandé
if $CLEAN; then
    clean_build
    echo ""
fi

# Vérifier les dépendances
check_dependencies
echo ""

# Configurer CMake
configure_cmake
echo ""

# Compiler le projet
build_project

# Afficher les informations finales
show_completion_info
