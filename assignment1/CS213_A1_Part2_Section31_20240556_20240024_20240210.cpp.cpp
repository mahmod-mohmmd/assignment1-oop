

/*
======================================

Image Processing Application

CS213 - Assignment 1 - part 2

File : CS213_A1_Part2_Section31_20240556_20240024_20240210.cpp

Description : This program implements an image processing filters application 

======================================

Team Members:

1. Mahmoud Mohamed - ID : 20240556 (5 Filters: Invert , Rotate , Adding a Frame , Blur Images ,sunlight(bonus) , Menu )

2. Ahmed Hassan    - ID : 20240024 (4 Filters: Grayscale , Merge , Darken and Lighten Image , Detect Image Edges)

3. Zyad Osama      - ID : 20240210 (4 Filters: Black and White , Flip , Crop Images , Resizing Images)

Section : S31

======================================
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

//Menu functions

string currentImage = "";

bool isValidExtension(string filename){
    string ext = filename.substr(filename.find_last_of(".") + 1);
    return ext == "bmp" || ext == "png" || ext == "jpg" || ext == "jpeg";
}


void Menu() {
    cout << "Welcome to the Image Processing Application!" << endl;
    cout << "1. Load Image" << endl;
    cout << "2. Process Image" << endl;
    cout << "3. Save Image" << endl;
    cout << "4. Exit" << endl;
    cout << "Please select an option: ";
}

void FiltersMenu() {
    cout << "Available Filters:" << endl;
    cout << "1.  Grayscale Conversion" << endl;
    cout << "2.  Black and White" << endl;
    cout << "3.  Invert Image" << endl;
    cout << "4.  Merge Images" << endl;
    cout << "5.  Flip Image" << endl;
    cout << "6.  Rotate Image" << endl;
    cout << "7.  Darken and Lighten Image" << endl;
    cout << "8.  Crop Image" << endl;
    cout << "9.  Add Frame to Image" << endl;
    cout << "10. Detect Image Edges" << endl;
    cout << "11. Resizing Images" << endl;
    cout << "12. Blur Image" << endl;
    cout << "13. sun effect(Bonus)" << endl;
    cout << "0.  Back to Main Menu" << endl;
    cout << "Please select a filter: ";
}

bool LoadImage(Image& image) {
    string filename ;
    cout << "Enter the filename to load: ";
    cin >> filename ;

    if (!isValidExtension(filename)) {
        cout << "Invalid file extension. Please use bmp, png, jpg, or jpeg." << endl;
        return false;
    }

    try {
        image = Image(filename);
        currentImage = filename;
        cout << "Image loaded successfully!" << image.width << "x" << image.height << endl;
        return true;
    }
    catch(const exception& e) {
        cout << "Failed to load image. Please check the filename and try again." << endl;
        return false;
    }
}
void SaveImage(Image& image){
    string filename ;
    if(!currentImage.empty()){
        char choice;
        cout << "Do you want to save the image with the same name (" << currentImage << ")? (y/n): ";
        cin >> choice;
        if(choice == 'y' || choice == 'Y'){
            filename = currentImage;
        }
        else{
            cout << "Enter the new filename : ";
            cin >> filename ;

            if (!isValidExtension(filename)) {
                cout << "Invalid file extension. Please use bmp, png, jpg, or jpeg." << endl;
                return;
            }
        }
    }
    else {
        cout << "No image loaded. Please enter a filename to save the image: ";
        cin >> filename ;

        if (!isValidExtension(filename)) {
            cout << "Invalid file extension. Please use bmp, png, jpg, or jpeg." << endl;
            return;
        }
    }

    try {
        image.saveImage(filename);
        currentImage = filename;
        cout << "Image saved successfully!" << endl;
    }
    catch(const exception& e) {
        cout << "Failed to save image. Please check the filename and try again." << endl;
    }
}
// FILTERS :

// filter 1 : grayscale

void GrayscaleImage(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg=0;
            for (int k = 0; k < 3; k++) {

                avg+=image(i,j,k);
            }
            avg=avg/3;
            for(int k=0;k<3;k++) {
                image(i,j,k)= avg;
            }
        }

    }
    cout << "Image converted to grayscale successfully!" << endl;
}

//Filter 2: Black and White

void BlackAndWhiteImage(Image& image) {
    int x = 128;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            unsigned int bw;
            if (avg > x) {
                bw = 255;
            } else {
                bw = 0;
            }
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = bw;
            }
        }
    }
    cout << "Image converted to black and white successfully!" << endl;
}

//Filter 3: Invert Image

void InvertImage(Image& image) {
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            for(int k = 0 ; k < image.channels ; k++){
                image(i, j, k) = 255 - image(i, j, k);}
        }
    }
    cout << "Image inverted successfully!" << endl;
}

//Filter 4: Merge Images

void MergeImages(Image& image) {
    string filename;
    cout << "Enter the filename of the second image: ";
    cin >> filename;

    Image secondImage(filename);

    int minWidth = min(image.width, secondImage.width);
    int minHeight = min(image.height, secondImage.height);

    for(int i = 0; i < minWidth; i++) {
        for(int j = 0; j < minHeight; j++) {
            for(int k = 0; k < image.channels; k++) {
                image(i, j, k) = (image(i, j, k) + secondImage(i, j, k)) / 2;
            }
        }
    }
    cout << "Images merged successfully!" << endl;
}

//Filter 5: Flip Image

void FlipImage(Image& image) {
     int x;
    cout << "choose 1.Flip horizontal\n2.flip vertical\n?";
    cin >> x;
    if (x == 1) {
        for (int i = 0; i < image.height; i++)
            for (int j = 0; j < image.width / 2; j++)
                for (int k = 0; k < image.channels; k++)
                    swap(image(j, i, k), image(image.width - 1 - j, i, k));
        image.saveImage("flipped_horizontal.png");
    }
    else if (x == 2) {
        for (int i = 0; i < image.height / 2; i++)
            for (int j = 0; j < image.width; j++)
                for (int k = 0; k < image.channels; k++)
                    swap(image(j, i, k), image(j, image.height - 1 - i, k));
        image.saveImage("flipped_vertical.png");
    }
    else {
        cout << "invalid choice";
    }
    cout << "Image flipped successfully!" << endl;
}

//Filter 6: Rotate Image

void RotateImage(Image& image){
    cout << "choose the angle of rotation (90, 180, 270): ";
    int angle;
    cin >> angle;
    switch (angle)
    {

    case 90:
        {
            Image rotatedImage(image.height, image.width);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < image.channels; k++) {
                        rotatedImage(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            image = rotatedImage;
            cout << "Image rotated by 90 degrees successfully!" << endl;
        }
        break;
    case 180:
        {
            Image rotatedImage(image.width, image.height);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < image.channels; k++) {
                        rotatedImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                    }
                }
            }
            image = rotatedImage;
            cout << "Image rotated by 180 degrees successfully!" << endl;
        }
        break;
    case 270:
        {
            Image rotatedImage(image.height, image.width);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < image.channels; k++) {
                        rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            image = rotatedImage;
            cout << "Image rotated by 270 degrees successfully!" << endl;
        }
        break;
    default:
        cout << "Invalid angle. Please choose 90, 180, or 270." << endl;
        break;
    }
}

// Filter 7 :  Darken and Lighten Image 
void DarkenLightenImage(Image& image){
    int choice;
    cout << "Choose an option:\n1. Darken Image\n2. Lighten Image\n?";
    cin >> choice;

    if(choice == 1){
        for(int i = 0 ; i < image.width ; i++){
            for(int j = 0 ; j < image.height ; j++){
                for(int k = 0 ; k < image.channels ; k++){
                    image(i, j, k) = max(0, image(i, j, k) - 100);
                }
            }
        }
        cout << "Image darkened successfully!" << endl;
    }
    else if(choice == 2){
        for(int i = 0 ; i < image.width ; i++){
            for(int j = 0 ; j < image.height ; j++){
                for(int k = 0 ; k < image.channels ; k++){
                    image(i, j, k) = min(255, image(i, j, k) + 100);
                }
            }
        }
        cout << "Image lightened successfully!" << endl;
    }
    else{
        cout << "Invalid choice." << endl;
    }
}
// Filter 8 : Crop Images
void CropImage(Image& image){
    int x, y, w, h;
    cout << "Enter the top-left corner (x y) and dimensions (width height) of the crop rectangle: ";
    cin >> x >> y >> w >> h;

    if(x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > image.width || y + h > image.height) {
        cout << "Invalid crop dimensions." << endl;
        return;
    }

    Image croppedImage(w, h);
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            for(int k = 0; k < image.channels; k++) {
                croppedImage(i, j, k) = image(x + i, y + j, k);
            }
        }
    }

    image = croppedImage;
    cout << "Image cropped successfully!" << endl;
}
// Filter 9 : Add Frame to Image
void AddFrameToImage(Image& image){
    cout << "choose the frame type : " << endl;
    cout << "1. simple frame" << endl;
    cout << "2. Fancy frame" << endl;
    cout << "enter your choice (1-2) ";
    int frameType;
    cin >> frameType;

    int frameThickness;
    if(frameType==1){
        frameThickness = 10 ;
        cout << "simple frame selected with thickness of 20 pixels" << endl;
    
    }
    else{
        frameThickness = 25 ;
        cout << "Fancy frame selected with thickness of 40 pixels" << endl;
    }
    int r , g ,b ;
    cout << "Enter the RGB values for the frame color (0-255 each): ";
    cin >> r >> g >> b ;
    r= max(0, min(255, r));
    g= max(0, min(255, g)); 
    b= max(0, min(255, b));

    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            if(i < frameThickness || i >= image.width - frameThickness ||
               j < frameThickness || j >= image.height - frameThickness){
                image(i, j, 0) = r ;
                image(i, j, 1) = g ;
                image(i, j, 2) = b ;
            }
        }
    }
    if(frameType == 2 ){
        int innerThickness =frameThickness/3;
        int outerthickness = frameThickness/3 ;
        for(int i = innerThickness ; i < image.width - innerThickness ; i++){
            for(int j = innerThickness ; j < image.height - innerThickness ; j++){
                if(j < innerThickness + 3 || j >= image.height - innerThickness - 3){
                    if(i >= innerThickness && i < image.width - innerThickness ){
                        image(i, j, 0) = 255 - r ;
                        image(i, j, 1) = 255 - g ;
                        image(i, j, 2) = 255 - b ;
                    }

                }
                if(i < innerThickness + 3 || i >= image.width - innerThickness - 3){
                    if(j >= innerThickness && j < image.height - innerThickness ){
                        image(i, j, 0) = 255 - r ;
                        image(i, j, 1) = 255 - g ;
                        image(i, j, 2) = 255 - b ;
                    }
                }
            }
        }

        for(int i = 0; i < image.width ; i++){
            for(int j = 0 ; j < image.height ; j++){
                if((i < outerthickness || i >= image.width - outerthickness || j < outerthickness || j >= image.height - outerthickness)
                &&(i<frameThickness && i>= outerthickness) ||
                (i>= image.width - frameThickness && i< image.width - outerthickness) ||
                (j<frameThickness && j>= outerthickness) ||
                (j>= image.height - frameThickness && j< image.height - outerthickness)){
                    image(i,j,0)=min(255, r + 50) ;
                    image(i,j,1)=min(255, g + 50) ; 
                    image(i,j,2)=min(255, b + 50) ;
                }
            }
        }
    }
    cout << "Frame added successfully!" << endl;
}

// Filter 10 : Detect Image Edges

void DetectImageEdges(Image& image){
    Image copy = image;
    cout << "choose the edge type : " << endl;
    cout << "1. white edges" << endl;
    cout << "2. black edges" << endl;
    cout << "enter your choice (1-2) ";
    int edgeType;
    cin >> edgeType;

    for(int i =0 ;i <image.width-1 ; i++){
        for(int j =0 ; j < image.height -1 ; j++){
            for(int k =0 ; k < image.channels ; k++){
                int gx = (copy(i+1,j,k) - copy(i,j,k));
                int gy = (copy(i,j+1,k) - copy(i,j,k));
                int g = sqrt(gx * gx + gy * gy);
                if(g > 255) g = 255;
                if(g < 0) g = 0;

                if(edgeType == 1){
                    image(i,j,k) = g ;
                }
                else{
                    image(i,j,k) =255- g ;
                }

            }
        }
    }
    cout << "Edge detection applied successfully!" << endl;
}
// Filter 11: Resizing Images 

void ResizeImage(Image& image){
    int newWidth, newHeight;
    cout << "Enter the new width and height: ";
    cin >> newWidth >> newHeight;

    if(newWidth <= 0 || newHeight <= 0) {
        cout << "Invalid dimensions." << endl;
        return;
    }

    Image resizedImage(newWidth, newHeight);
    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newHeight; j++) {
            int srcX = i * image.width / newWidth;
            int srcY = j * image.height / newHeight;
            for(int k = 0; k < image.channels; k++) {
                resizedImage(i, j, k) = image(srcX, srcY, k);
            }
        }
    }

    image = resizedImage;
    cout << "Image resized successfully!" << endl;
}

// Filrer 12 : Blur Image

void BlurImage(Image& image){

    int blurRadius = 20 ;

    Image copy(image.width, image.height);
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            for(int k = 0 ; k < image.channels ; k++){
                long sum =0 ;
                int pixels =0 ;
                for(int m = -blurRadius ; m <= blurRadius ; m++){
                        int x = i + m ;

                    if(x >=0 && x < image.width ){
                        sum += image(x, j, k);
                        pixels++;
                    }
                }
                if(pixels>0)
                    copy(i, j, k) = static_cast<unsigned char>(sum / pixels);
                else
                    copy(i, j, k) = 0 ;
            }
        }
    }

    for(int i =0 ; i < image.width ; i++){
        for(int j =0 ; j < image.height ; j++){
            for(int k =0 ; k < image.channels ; k++){
                long sum =0 ;
                int pixels =0 ;

                for(int n = -blurRadius ; n <= blurRadius ; n++){
                    int y = j + n ;
                    if( y >=0 && y < image.height){
                        sum += copy(i, y, k);
                        pixels++;
                    }
                }
                if(pixels>0)
                    image(i, j, k) =static_cast<unsigned char>(sum / pixels);
                else
                    image(i, j, k) = 0 ;
            }
        }
    }
    cout << "Image blurred successfully!" << endl;
}


//filter 13 : (bonus) sun effect
void sun(Image& image){
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            image(i,j,0)=min(255,image(i,j,0)+30);
            image(i,j,1)=min(255,image(i,j,1)+30);
            image(i,j,2)=max(0,image(i,j,2)-30);

        }
    }
    cout << "Sun effect applied successfully!" << endl;
}

int main () {
    Image image;
    bool imageLoaded = false;
    int choice;
    cout << "Welcome to the Image Processing Application!" << endl;
    cout << "Please load an image to start..." << endl;

    while (!imageLoaded) {
        imageLoaded = LoadImage(image);
    }

    while(true) {
        Menu ();
        cin >> choice ;

        if (choice ==1) {
            if(imageLoaded){
                char save ;
                cout << "Do you want to save the current image before loading a new one? (y/n): ";
                cin >> save ;
                if (save == 'y' || save == 'Y') {
                    SaveImage(image);
                }
                imageLoaded = LoadImage(image);
            }
        }
        else if (choice == 2 ){
            if(imageLoaded){
                int filterChoice;
                bool backToMainMenu = false;
                do{
                    FiltersMenu();
                    cin >> filterChoice;
                    if(filterChoice == 1){
                        GrayscaleImage(image);
                    }
                    else if(filterChoice == 2){
                        BlackAndWhiteImage(image);
                    }
                    else if(filterChoice == 3){
                        InvertImage(image);
                    }
                    else if(filterChoice == 4){
                        MergeImages(image);
                    }
                    else if(filterChoice == 5){
                        FlipImage(image);
                    }
                    else if(filterChoice == 6){
                        RotateImage(image);
                    }
                    else if(filterChoice == 7){
                        DarkenLightenImage(image);
                    }
                    else if(filterChoice == 8){
                        CropImage(image);
                    }
                    else if(filterChoice == 9){
                        AddFrameToImage(image);
                    }
                    else if(filterChoice == 10){
                        DetectImageEdges(image);
                    }
                    else if(filterChoice == 11){
                        ResizeImage(image);
                    }
                    else if(filterChoice == 12){
                        BlurImage(image);
                    }
                    else if(filterChoice == 13){
                        sun(image);
                    }

                    else if(filterChoice == 0){
                        cout << "Returning to Main Menu..." << endl;
                        backToMainMenu = true;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                    }

                    if(filterChoice >=1 && filterChoice <=14){
                        char applyAnother;
                        cout << "Do you want to apply another filter? (y/n): ";
                        cin >> applyAnother;
                        if(applyAnother == 'n' || applyAnother == 'N'){
                            backToMainMenu = true;
                        }
                    }

                } while(!backToMainMenu);
            }
            else{
                cout << "No image loaded. Please load an image " << endl;
            }
        }
        else if (choice == 3 ){
            if(imageLoaded){
                SaveImage(image);
            }
            else{
                cout << "No image loaded. Please load an image " << endl;
            }
        }
        else if (choice == 4 ){
            if(imageLoaded){
                char save ;
                cout << "Do you want to save the current image before exiting? (y/n): ";
                cin >> save ;
                if (save == 'y' || save == 'Y') {
                    SaveImage(image);
                }
            }
            cout << "Exiting the application. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}