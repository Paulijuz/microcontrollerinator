#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

if [[ "${1-}" =~ ^-*h(elp)?$ ]]; then
    echo 'Usage: ./installer.sh /path/to/toolchain/install/dir 

Add argument for custom install directory for Arm GNU Toolchain. 
Default install location is /opt.

'
    exit
fi

ARM_INSTALL_DIR="/opt"

if [ $# -eq 0 ]
  then
    echo "Arm GNU Toolchain defaulting to installdir /opt"

else
    ARM_INSTALL_DIR="$(dirname "$0")"
fi


main() {
    echo "--- Downloading Arm GNU Toolchain ---"
    wget https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz
    echo "--- Unpacking Arm GNU Toolchain ---"
    tar xvf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz
    sudo mv arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi arm-none-eabi-13.2
    sudo mv arm-none-eabi-13.2 $ARM_INSTALL_DIR
    echo "--- Installing requirements ---"
    sudo add-apt-repository -y ppa:deadsnakes/ppa
    sudo apt-get update
    sudo apt install -y libncursesw5
    sudo apt install -y python3.8
    echo "--- Cleaning up ---"
    sudo rm arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz     
    #echo "--- Cloning Handout Code ---"
    #git clone https://github.com/ITK-TTK4235/nrf52dk_devenvironment.git
    echo "--- Installation Complete ---"
}

main "$@"
