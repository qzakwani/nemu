#!/bin/sh

# General Variables
APP_NAME="nemu"
ICON="nemu.png"
VERSION="v1.0.0"


# Colors
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' 

# Directories
BIN_DIR="/usr/local/bin"
ICON_DIR="/usr/local/share/icons"
DESKTOP_FILE_DIR="/usr/local/share/applications"


# Function to remove the binary
remove_binary() {
    if [ -f "$BIN_DIR/$APP_NAME" ]; then
        sudo rm "$BIN_DIR/$APP_NAME"
    else
        echo -e "${RED}Error: $BIN_DIR/$APP_NAME not found.${NC}"
        exit 1
    fi
}

# Function to remove the icon
remove_icon() {
    if [ -f "$ICON_DIR/$ICON" ]; then
        sudo rm "$ICON_DIR/$ICON"
    else
        echo -e "${YELLOW}Warning: $ICON_DIR/$ICON not found.${NC}"
    fi
}


remove_desktop_file() {
    if [ -f "$DESKTOP_FILE_DIR/$APP_NAME.desktop" ]; then
        sudo rm "$DESKTOP_FILE_DIR/$APP_NAME.desktop"
    else
        echo -e "${YELLOW}Warning: $DESKTOP_FILE_DIR/$APP_NAME.desktop not found.${NC}"
    fi
}

echo "Uninstalling nemu..."
remove_binary
if [ -n "$XDG_CURRENT_DESKTOP" ]; then
remove_icon
remove_desktop_file
fi


echo "Uninstallation complete."
echo ""
echo -e "${YELLOW}If you decide to reinstall, you can visit the GitHub page: https://github.com/qzakwani/nemu${NC}"
echo ""