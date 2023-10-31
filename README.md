# ICM-LTM Image Enhancement

## Introduction

This code is an implementation of the Intersection Cortical Model Luminosity Time Matrix (ICM-LTM) for enhancing the local brightness of images. The ICM-LTM is a method developed by Kevin Salvador Aguilar Domínguez, and it can be useful for improving the visual quality and details in images.

The primary purpose of this code is to enhance the brightness of an input image while preserving the local details. It uses a combination of convolution, thresholding, and time matrices to achieve this enhancement.

## Dependencies

- OpenCV (Open Source Computer Vision Library)
- C++ Standard Library

## Usage

1. Make sure you have OpenCV installed and properly configured.
2. Replace the `"cm.jpg"` string in the `imread` function with the path to the input image you want to enhance.
3. Adjust the parameters such as `f`, `g`, `h`, and `y` to fine-tune the enhancement process if needed.
4. Run the code, and it will process the input image and save the enhanced image as `"output.jpg"`.

## Methodology

The code follows these main steps:

1. Load the input image and normalize it.
2. Initialize various matrices to store intermediate results.
3. Apply convolution with a predefined kernel.
4. Calculate and update the output based on thresholding and time matrices.
5. Normalize the time matrix (MT).
6. Perform image output adjustment to enhance local brightness.
7. Save the enhanced image.

## Citations

If you use this methodology or code in your work, please cite the following papers where it was proposed:

1. K. S. A. Domínguez, M. M. Lavalle, A. M. Salazar and G. R. Salgado, "Pulsed Neural Net plus Time Matrix for Bright Images Enhancement," 2019 International Conference on Mechatronics, Electronics and Automotive Engineering (ICMEAE), Cuernavaca, Mexico, 2019, pp. 79-83, doi: 10.1109/ICMEAE.2019.00022.

If you use this method for medical image enhancement, please also cite:

2. Aguilar Domínguez, Kevin S., Mejía Lavalle, Manuel, & Sossa, Humberto. "Mejora eficiente de la luminosidad en imágenes del cerebro humano utilizando redes neuronales pulso-acopladas," Computación y Sistemas, 24(1), 105-120. Epub 27 de septiembre de 2021. [https://doi.org/10.13053/cys-24-1-3187](https://doi.org/10.13053/cys-24-1-3187).
