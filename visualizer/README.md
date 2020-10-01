# Visualizer
## Overview:
  TODO: Add build status here 
## Setup:
**1.** Download [Virtual Box.](https://www.virtualbox.org/wiki/Downloads)

   - Virtual Box is a hypervisor (a piece of software) that runs on top of your operating system and allows you to create a virtual machine (VM) .

**2.** Download the virtual hard drive [soar_vm.qcow2](https://mega.nz/file/MP4inJRI#SsqFDn-Ordc9cEUt1QtwAAlqP3Tg8FSQSDG1eoB7kpQ)

   - The virtual hard drive will contain the telemetry-subsystem software to run on your VM. Note you will need the [7zip software](https://www.7-zip.org/download.html) to extract the contents of the zip file.
    
**3.**  On Virtual Box, create a new VM with the virtual hard drive file mentioned above. 

   - The machine version of the VM should be Windows 7 or above. For memory size, make sure the VM has at least 4000 MB (4 GB) of RAM and 2 CPUs. 

**4.** Power on your virtual machine.

**5.** Run and build the current visualizer code. May need to use 'git pull'.  

   - Go to the left hand panel and click for "Terminal".
    
   - Execute the following shell commands:
    
      Change directory to correct place.
      ```console
      cd Desktop/repos/Telemetry-Subsystem/visualizer/build
      ```
      Generate a makefile/update assets folder.
      ```console
      cmake ..
      ```
      Run makefile and compile telemetry-subsystem code.
      ```console
      make 
      ```
      Run rotating cube example.
      ```console
      ./visualizer 
      ```
