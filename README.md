# AlexLens

AlexLens is an Image Classification and Transfer Learning program for heterogeneous platforms with the Neural-Net-Classification built from scratch. It was developed during a project at KIT.
The team consisted of Viet Pham, Dmitrii Seletkov, Aleksandr Eismont, Jakub Trzciński and Friedemann Claus.


The program is designed to run on a specific PC, which has Ubuntu 18.04 as the operating system, 8 GB of RAM, a Core-i5 4600 CPU and its onboard graphics as the GPU.
But with exception to the GPU classification of AlexNet it should work on most other hardware (not software) as well - unsupportedly. It also takes advantage of up to four Intel Movidius Neural Compute Sticks (Gen 1 is officially supported, but Gen 2 also works according to our tests).


### Installation:

For it to run you need to follow three steps:

 1. Download "resources" [here](https://cloud.viet-pham.de/s/eKRM5JyxBpAAjEn?path=%2F)
 2. Unzip it and place it in the AlexLens folder
 3. Install the necessary libraries, if you don't have them running already:
 
 Optionally, we also provide a training dataset as an example [here](https://cloud.viet-pham.de/s/eKRM5JyxBpAAjEn?path=%2F).
 
 
 The necessary libraries are:
 
 | Library | Usecase | Download/ Tutorial | Comments |
 | --- | --- | --- | --- |
 | Qt5 | GUI | [Download Page](https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5)  | You can skip the registration. In the installer, select under "Qt 5.13.0": Desktop gcc 64-bit, Sources, Qt Charts, Qt Data Visualization, Qt Debug Information Files and under "Developer and Designer Tools": Qt 3D Studio 2.4.0 
 | Eigen | Matrices and vectors | `sudo apt-get install libeigen3-dev` | that's all
 | Torch | Transfer Learning and CPU-Classification of other Neural Networks than AlexNet | [Download](https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.2.0.zip) | Unzip and move libtorch folder to AlexLens/thirdparty |
 | OpenVINO | ASIC-Sticks and the included OpenCV | [Tutorial](https://docs.openvinotoolkit.org/latest/_docs_install_guides_installing_openvino_linux.html#Hello-World-Face-Detection-Tutorial) | Go through steps 1,2,3,5,7 and 9. After Step 9 you should have a folder named "inference_enginge_samples_build" in your /home/"username" directory |
 | OpenCL | Low-level access to the GPU | `sudo apt update` `sudo apt install ocl-icd-opencl-dev` `sudo apt-get install beignet` | Confirmed to work on Intel HD Graphics of 4th, 7th and 8th generation |
 | HDF5 | To read the weights file with a good performance | `sudo apt-get install libhdf5-dev` | that's all
 | Libusb | For dynamically detecting the amount of USB-devices used | `sudo apt-get install libusb-1.0-0-dev` | that's all
