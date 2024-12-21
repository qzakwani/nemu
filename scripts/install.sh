#!/bin/sh

# General Variables
APP_NAME="nemu"
ICON="nemu.png"
VERSION="v1.0.0"
GITHUB_REPO="https://github.com/qzakwani/$APP_NAME/releases/download/$VERSION"

# Directories
BIN_DIR="/usr/local/bin"
ICON_DIR="/usr/local/share/icons"
DESKTOP_FILE_DIR="/usr/local/share/applications"
TEMP_DIR="$HOME/tmp/nemu"
IS_DESKTOP=true

echo "Checking environment..."


# Check if the system is x86_64 Linux
ARCH=$(uname -m)
OS=$(uname -s)

if [ "$ARCH" != "x86_64" ] || [ "$OS" != "Linux" ]; then
    echo "This app supports only x86_64 Linux systems."
    exit 1
fi

# Check init system
INIT_SYSTEM=$(ps -p 1 -o comm=)
if [ "$INIT_SYSTEM" != "systemd" ]; then
    echo "Nemu requires a systemd-based system to run NOW! Soon, Nemu will be customizable and work with more systems. Please keep an eye on this repo."
    exit 1
fi

# Check if the environment supports .desktop files
if [ -n "$XDG_CURRENT_DESKTOP" ]; then
    IS_DESKTOP=true
    sudo mkdir -p "$DESKTOP_FILE_DIR" "$ICON_DIR"
else
    IS_DESKTOP=false
fi

# Create necessary directories
sudo mkdir -p "$BIN_DIR" "$TEMP_DIR"

# Download the app binary from GitHub releases
echo "Downloading the latest release..."
if ! sudo curl -L --progress-bar "$GITHUB_REPO/$APP_NAME" -o "$TEMP_DIR/$APP_NAME"; then
    echo -e "\033[1;31m❌ Failed to download nemu. Please check your internet connection and try again.\033[0m"
    exit 1
fi

if [ "$IS_DESKTOP" = true ]; then
if ! sudo curl -L --progress-bar "$GITHUB_REPO/$ICON" -o "$TEMP_DIR/$ICON"; then
    echo -e "\033[1;31m❌ Failed to download nemu. Please check your internet connection and try again.\033[0m"
    exit 1
fi
fi

if [ "$IS_DESKTOP" = true ]; then
sudo touch "$TEMP_DIR/$APP_NAME.desktop"
cat << EOF | sudo tee "$TEMP_DIR/$APP_NAME.desktop" > /dev/null
[Desktop Entry]
Name=Nemu
Version=1.0.0
Exec=$BIN_DIR/$APP_NAME
Icon=$ICON_DIR/$ICON
Terminal=false
Type=Application
StartupNotify=true
StartupWMClass=nemu
Categories=Utility;
EOF
fi

echo "Installing nemu..."
sudo mv "$TEMP_DIR/$APP_NAME" "$BIN_DIR"
sudo mv "$TEMP_DIR/$ICON" "$ICON_DIR"
if [ "$IS_DESKTOP" = true ]; then
sudo mv "$TEMP_DIR/$APP_NAME.desktop" "$DESKTOP_FILE_DIR"
fi

# Make the binary executable
sudo chmod +x "$BIN_DIR/$APP_NAME"


echo "Cleaning up..."
sudo rm -rf "$TEMP_DIR"

# Check if the bin directory is in PATH
if ! echo "$PATH" | grep -q "$BIN_DIR"; then
    echo ""
    echo -e "\033[1;33m⚠️  WARNING:\033[0m The directory \033[1;34m$BIN_DIR\033[0m is not in your PATH."
    echo -e "To temporarily add it to your PATH for the current session, run:"
    echo -e "\033[1;32mexport PATH=\$PATH:$BIN_DIR\033[0m"
    echo -e "To make this change permanent, add the following line to your shell configuration file (e.g., \033[1;36m~/.bashrc\033[0m or \033[1;36m~/.zshrc\033[0m):"
    echo -e "\033[1;32mexport PATH=\$PATH:$BIN_DIR\033[0m"
    echo ""
fi

# Success message
echo ""
echo -e "\033[1;32m🎉 Congratulations!\033[0m The app has been installed successfully!"
echo ""
echo -e "You can now use \033[1;34m$APP_NAME\033[0m in the following ways:"
echo -e "1. Run the app from the CLI using: \033[1;32m'$APP_NAME' or '$APP_NAME -'\033[0m (for second theme)"
if [ "$IS_DESKTOP" = true ]; then
echo -e "2. Use the desktop application. Visit https://github.com/qzakwani/revmo  for a cool application launcher."
fi
echo ""