## debug configure for jlink
 {
    "name": "Test ACE OS",
    "cwd": "${workspaceFolder}",
    "executable": "${workspaceFolder}/ACE/Test_ace_os/_build/ace_os.out",
    "request": "launch",
    "type": "cortex-debug",
    "runToEntryPoint": "main",
    "servertype": "jlink",
    "serverpath": "C:/Program Files/SEGGER/JLink_V810c/JLinkGDBServerCL.exe",
    "serverArgs": [],
    "device": "NRF52840_XXAA",
    "interface": "jtag",
    "serialNumber": "", //If you have more than one J-Link probe, add the serial number here.
    "postLaunchCommands": ["monitor sleep 0", "monitor speed auto"],
    "svdFile": "${workspaceFolder}/svd/nrf52840.svd",
    "armToolchainPath": "C:/gcc-arm-none-eabi/bin"
}

## 
