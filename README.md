# Intersection Cortical Model Luminosity Time Matrix (ICM-LTM)

This code provides a C++ implementation for modifying the luminosity of an input image using the Intersection Cortical Model. The process enhances the local brightness in the image. Here's a description of the code:

## Dependencies
- OpenCV: This code relies on OpenCV for image loading, manipulation, and saving.

Make sure you have OpenCV installed on your system. You can typically install it using a package manager or build it from source. For example, on Linux, you can use:

```bash
sudo apt-get install libopencv-dev
```

## Function: `ICM-LTM`

```cpp
Mat ICM-LTM(const Mat& I)
```

This function performs the Local Thresholding Method for contrast enhancement. It takes an input image `I` and returns the modified image. The key parameters and steps within this function include:

- `Ep`: The number of iterations for contrast enhancement.
- `W[3][3]`: A 3x3 matrix used as a filter for convolution.
- `f`, `g`, and `h`: Parameters used in the contrast enhancement process.

The function applies a series of operations on the input image to enhance its contrast locally. It employs a combination of filtering, thresholding, and iteration.

## Usage in `main`

1. The `main` function loads an input image using OpenCV's `imread` function.

2. If the image fails to load, it prints an error message and exits.

3. The `ICM-LTM` function is called with the loaded image, and the resulting image is stored in the `lsImage` variable.

4. The modified image is saved using `imwrite`, and the output is typically named "output_image.jpg."

## How to Use

1. Ensure you have OpenCV installed on your system.

2. Place the code in a C++ source file.

3. Update the image path in the `main` function by modifying the following line:

   ```cpp
   Mat I = imread("cameraman.jpg", IMREAD_GRAYSCALE); // Load your input image here
   ```

   Replace `"cameraman.jpg"` with the path to the image you want to process.

4. Compile the code with a C++ compiler (e.g., g++):

   ```bash
   g++ -o contrast_enhancement contrast_enhancement.cpp `pkg-config opencv --cflags --libs`
   ```

5. Run the compiled binary:

   ```bash
   ./contrast_enhancement
   ```

6. The modified image will be saved in the same directory as "output_image.jpg."

This code can be useful for enhancing the local contrast of images, which can improve the visual quality and details in certain scenarios.
