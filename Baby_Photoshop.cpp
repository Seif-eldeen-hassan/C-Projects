// Purpose: This a Program of 15 different Filters  
// Author1: Seif Eldeen Hassan      ID:20230182       Email: seifeldeen568@gmail.com        section 19,20   Black & white , Flip , Crop Images , Resizing Images , Skew  
// Author2: Hesham Mohamed          ID:20230458       Email: hishmkotp358@gmail.com         section 19,20   Invert images , Rotate , blur , frame , purple
// Author3: Hussien Hassan Hussien  ID:20230124       Email: hussien.hassan6644@gmail.com   section 19,20   Brightness , Merge , Gray Filter , Edge detecion , infrared 
// Version: 2.0
// Date: 4/13/2024

#include <iostream>
#include <cstring>
#include "Image_Class.h"
#include <fstream>
#include <iomanip> 
using namespace std;

//////////  assign image  ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void assign(Image& image, const Image& other_image) {
    // Deallocate memory if already allocated
    if (image.imageData != nullptr) {
        free(image.imageData);
    }

    image.width = other_image.width;
    image.height = other_image.height;
    image.channels = other_image.channels;

    // Allocate memory for imageData
    image.imageData = (unsigned char*)malloc(image.width * image.height * image.channels);

    // Copy data from other_image to image
    memcpy(image.imageData, other_image.imageData, image.width * image.height * image.channels);
}

//////////  Isfile_exist  ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

bool isfile_exist(string image_name){
    ifstream image;
    image.open(image_name);
    if (!image){
        return false;
    }
    else{
        return true;
    }
}

//////////  Check_Valid_image  ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

bool Check_valid_image(string image_name){
 if (image_name.size() < 5){
    return false;
 }
 string extension = image_name.substr(image_name.size() - 4);
 if (extension != ".png"  && extension != ".jpg" && extension != ".bmp" && extension != ".tga"){
     return false;
  }
  else{
    return true;
  }
}

//////////  Get_1_images ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

string Get_1_image(){
    string image_name;
    cout << "Pls Enter image name and specify extension {.jpg, .bmp, .png, .tga}  ex: 'Image.jpg' \n";
    cin >> image_name;
    cin.ignore();
    while(!Check_valid_image(image_name)){
      cout << "\033[1;31mInvalid Extension,\033[0m Please Enter valid image name   ex: 'Image.jpg'\n";
      cin >> image_name;
      cin.ignore();
    }
    while(!isfile_exist(image_name)){
      cout << "\033[1;31mError,\033[0m Image doesnt Exist\n";
      cout << "Pls Enter image name and specify extension {.jpg, .bmp, .png, .tga}  ex: 'Image.jpg'\n";
      cin >> image_name;
      cin.ignore();
    }
    return image_name;
}



//////////  Save_Image ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void Save_Image(Image& image)
{
    string image_name;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga:  'Image.jpg' \n";
    cin >> image_name;
    cin.ignore();
    while(!Check_valid_image(image_name)){
      cout << "\033[1;31mInvalid Extension,\033[0m Please Enter valid image name   ex: 'Image.jpg'\n";
      cin >> image_name;
      cin.ignore();
    }
    image.saveImage(image_name);
    cout << image_name << " Saved Successfully ! \n";
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////  Black & white filter ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void Black_white(string& first_image , Image& image )
{  
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;

            for (int k = 0; k < image.channels; k++) {
                avg += image(i,j,k);
            }
            avg /= 3;      // Convert photo to Grayscale

            if(avg > 127.5) {           // Is the pixel is closer to white or closer to black ??
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, 255);
                }
            }else {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, 0);
                }
            }
        }
    }
     first_image += "--> Black/White ";
}

//////// Crop Images ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void Crop_Images(int x,int y, int w, int h , string& first_image , Image& image){       // Program 8 Crop images
    Image new_image(w,h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h ; j++) {
            for (int k = 0; k < 3 ; k++) {
                new_image(i,j,k) = image(x+i,y+j,k);
            }
        }
    }
    assign(image , new_image);
    first_image +=" --> Croped ";
}

///////////////  Flip  ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 /////////////////

void Flipped_Horizontally(string& first_image , Image& image){
    Image image2(image.width , image.height); 
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3 ; k++) {

                image2(i,j,k) = image(image.width-i - 1,j,k);

            }
        }
    }

    assign(image , image2);
    first_image += "--> Flip H ";

}

void Flipped_Vertical(string& first_image , Image& image){  
    Image image2(image.width , image.height);       
    for (int i = 0; i < image.width ; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3 ; k++) {

                image2(i,j,k) = image(i , image.height-j - 1 ,k);

            }
        }
    }
    assign(image , image2);
    first_image += "--> Flip V ";
}

////////// Resizing Images ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void Resizing_Images(double new_width , double new_height , string& first_image , Image& image){      // program 11 Resizing Images
    Image new_image(new_width,new_height);
    double amount_width = image.width / new_width;
    double amount_height = image.height / new_height;

    for (int i = 0; i < new_width; i++){
        for (int j = 0; j < new_height ; j++){
            int org_width = i * amount_width;
            int org_height = j * amount_height;

            for (int k = 0; k < 3; k++){
                new_image(i,j,k) = image(org_width,org_height,k);
            }
        }
    }
    assign(image , new_image );
    first_image += "--> Resize ";
}

////////// Skew Images ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void skew(string& first_image , Image& image){
    double width , height , new_width;
    string Degree;
    bool Valid ;
    do {
        Valid = true;
        Degree ="";
        cout << "Please Enter  Degree of skewing between [0° : 90°[\n";
        getline(cin , Degree);
        
        for (char c : Degree){
            if (!isdigit(c)){
                Valid = false;
                cout <<"\033[1;31mError, \033[0m";
                break;
            }
        }
        if (Valid){
          if ((stod(Degree) < 0 || stod(Degree) >= 90)){
            Valid = false;
            cout <<"\033[1;31mError, \033[0m";
          }
        }
        
    }
    while (Valid == false);


    if (stod(Degree) == 0 ){
        first_image += "--> Skew by 0°" ;
    }

    else{
        width = image.width;
        height = image.height;
        new_width = width + (height * tan(stod(Degree)*3.14159/180));
        Image skewed_image(new_width , height);

        for (int w = 0; w < skewed_image.width ; w++) {
            for (int h = 0; h < skewed_image.height; h++) {
            skewed_image(w , h , 0) = 255;
            skewed_image(w , h , 1) = 255;
            skewed_image(w, h , 2) = 255;
            }
        }
        
        for (int w = 0; w < image.width ; w++) {
            for (int h = 0; h < image.height; h++) {
            int new_w = w + ((height - h) * tan(stod(Degree) * 3.14159 / 180));
            skewed_image(new_w , h , 0) = image(w , h , 0);
            skewed_image(new_w , h , 1) = image(w , h , 1);
            skewed_image(new_w , h , 2) = image(w , h , 2);
            }
        }
        assign(image , skewed_image);
        first_image += "--> Skew by " + Degree + "°";
    }
}


////////// Brightness ///////////////////// Hussien Hassan Hussien //////////////////////// ID 20230124 //////////////

void Brightness(string& first_image , Image& image ) 
{
    double dob_Brightness;
    string Brightness;

    cout << "1) Lighten Image\n";
    cout << "2) Darken Image\n";
    string choice = "";

    while (true) {
        getline(cin, choice);

        if (choice != "1" && choice != "2") {
            cout << "Please enter a valid choice (1 or 2): ";
            continue;
        }

        cout << "Please choose the percentage (1 to 100) %: ";

        while (true) {
            getline(cin, Brightness);
            bool isValid = true;

            for (char c : Brightness) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) {
                cout << "Invalid input, Please enter a valid integer between 1 and 100: ";
                continue;
            }

            dob_Brightness = stod(Brightness);

            if (dob_Brightness > 100 || dob_Brightness < 0) {
                cout << "Invalid input, Please enter a percentage between 1 and 100: ";
            }
            else {
                break;
            }
        } // Inner while loop

        break; // Exit the outer loop after valid input
    } // Outer while loop

    if (choice == "1") {
        dob_Brightness = 1 + (dob_Brightness / 100);
    }
    else if (choice == "2") {
        dob_Brightness = 1 - (dob_Brightness / 100);
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int avg = 0, new_rgb = 0;
                avg = image(i, j, k);
                new_rgb = avg * dob_Brightness;
                if (new_rgb > 255) {
                    new_rgb = 255;
                }
                else if (new_rgb < 0) {
                    new_rgb = 0;
                }
                image(i, j, k) = new_rgb;
            }
        }
    }
    first_image += "--> Brightness ";
}

////////// Gray Filter ///////////////////// Hussien Hassan Hussien //////////////////////// ID 20230124 //////////////

void Gray_Filter(string& first_image , Image& image)
{
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int Average = 0; // Initialize average value
            for (int k = 0; k < 3; ++k) {
                Average += image(i, j, k); // Accumulate pixel values
            }
            Average /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = Average;
            image(i, j, 1) = Average;
            image(i, j, 2) = Average;
        }
    }
     first_image += "--> Grey ";
}

////////// Edge Detection Filter ///////////////////// Hussien Hassan Hussien //////////////////////// ID 20230124 //////////////
void Edge_Detector(string& first_image , Image& image){
    Image Edge_image(image.width ,image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int Average = 0;
            for (int k = 0; k < 3; ++k) {
                Average += image(i, j, k); 
            }
            Average /= 3;

            // Set all channels to the average value
            image(i, j, 0) = Average;
            image(i, j, 1) = Average;
            image(i, j, 2) = Average;
        }
    }

    int Kernel_X[3][3] = {{-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1}};
  
    int Kernel_Y[3][3] = {{-1, -2, -1},
                          { 0,  0,  0},
                          { 1,  2,  1}};
    

    for (int w = 1; w < image.width - 1; w++) {
        for (int h = 1; h < image.height - 1; h++) {
            int Gradient_x_axis = 0 , Gradient_y_axis = 0; 
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    Gradient_x_axis += image(w + i, h + j, 0) * Kernel_X[i+1][j+1];
                    Gradient_y_axis += image(w + i, h + j, 0) * Kernel_Y[i+1][j+1];
                }
            }

            int Gradient_Magnitude = sqrt((Gradient_x_axis * Gradient_x_axis) + (Gradient_y_axis * Gradient_y_axis));

            if (Gradient_Magnitude > 111){
                Edge_image(w , h , 0) = 0;
                Edge_image(w , h , 1) = 0;
                Edge_image(w , h , 2) = 0;
            }
            else{
                Edge_image(w , h , 0) = 255;
                Edge_image(w , h , 1) = 255;
                Edge_image(w , h , 2) = 255;
            }

       
        }
    }



 assign(image , Edge_image);
 first_image += "--> Edge ";
}

////////// Merge Images ///////////////////// Hussien Hassan Hussien //////////////////////// ID 20230124 //////////////

void Merge_images(Image& image1 , Image& image2) 
{
    int Merged_Width = min(image1.width , image2.width);
    int Merged_Height = min(image1.height , image2.height);
    Image mergedImage(Merged_Width , Merged_Height);
    // Merge the two images
    for (int i = 0; i < mergedImage.width; ++i) {
        for (int j = 0; j < mergedImage.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int Intenisty = (image1(i, j, k) + image2(i, j, k)) / 2;
                mergedImage(i, j, k) = Intenisty;
            }
        }
    }

    assign(image1 , mergedImage);
}

////////// Infrared Images ///////////////////// Hussien Hassan Hussien //////////////////////// ID 20230124 //////////////

void Infrared(string& first_image , Image& image){
    for (int i = 0; i < image.width; i++){
        for (int j = 0; j < image.height; j++){
            for (int k = 0; k < 3; k++){
                k == 0 ? image.setPixel(i,j,k, 255) : image.setPixel(i,j,k, 255-image(i,j,k));
            }
        }
    }
    first_image += " --> Infrared ";
}



////////// Invert images ///////////////////// Hesham Mohamed //////////////////////// ID 20230458 //////////////

void Invert_images(string& first_image , Image& image) {

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
             image(i, j, k) = 255 - image(i, j, k);
            }
        }
    } 
    first_image += "--> Invert ";
}

////////// Rotate images ///////////////////// Hesham Mohamed //////////////////////// ID 20230458 //////////////

void Rotate_90(string& first_image , Image& image){
   Image Rotate(image.height, image.width);
   for (int i = 0; i < image.width; ++i) {
      for (int j = 0; j < image.height; ++j) {
        Rotate(image.height - j - 1, i, 0) = image(i, j, 0);
        Rotate(image.height - j - 1, i, 1) = image(i, j, 1);
        Rotate(image.height - j - 1, i, 2) = image(i, j, 2);
      }
    }
   assign(image , Rotate);
   first_image += "--> Rotate 90 ";
}
   

void Rotate_180(string& first_image , Image& image){
    int width = image.width;
    int height = image.height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            for (int k = 0; k < 3; k++) {
                int fliped = image(j, i, k);
                image(j, i, k) = image(width - 1 - j,i,k);
                image(width - 1 - j, i,k) = fliped;
            }
        }
    }
    for (int i = 0; i < height /2 ; i++) {
        for (int j = 0; j < width ; j++) {
            for (int k = 0; k < 3; k++) {
                int fliped = image(j, i, k);
                image(j, i, k) = image(j,height-1-i,k);
                image(j,height-1-i,k) = fliped;
            }
        }
    }
    first_image += "--> Rotate 180 ";
}

void Rotate_270(string& first_image , Image& image){
    Image Rotate(image.height, image.width);
     for (int i = 0; i < image.width; ++i) {
      for (int j = 0; j < image.height; ++j) {
        Rotate(j, image.width - i - 1, 0) = image(i, j, 0);
        Rotate(j, image.width - i - 1, 1) = image(i, j, 1);
        Rotate(j, image.width - i - 1, 2) = image(i, j, 2);
      }
    }
    first_image += "--> Rotate 270 ";
}

////////// Purple Filter ///////////////////// Hesham Mohamed //////////////////////// ID 20230458 //////////////

void Purple(string& first_image , Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 1) *= 0.68; 
             if (image(i,j,1)<0)
                image(i,j,1) = 0;
        }
    }
    first_image += " --> Purple";
}

////////// Image Blur Filter ///////////////////// Hesham Mohamed //////////////////////// ID 20230458 //////////////

void imageBlur(string& first_image , Image &image, int newblurDegree) {
    int check1[8] = {-1, 0, 1, -1, -1, 1, 0, 1};
    int check2[8] = {-1, -1, -1, 0, 1, 0, 1, 1};
     float blurRadius = (newblurDegree * 5) / 100;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int sum = 0;
                int elements = 0;
                for (int f = 0; f < 8; ++f) {
                    int x = i + blurRadius * check1[f];
                    int y = j + blurRadius * check2[f];
                    if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                        sum += image(x, y, k);
                        elements++;
                    }
                }
                if (elements > 0) {
                    sum /= elements;
                    image(i, j, k) = sum;
                }
            } 
        }
    }
    first_image += " --> Blured ";
}

////////// Frame Filter ///////////////////// Hesham Mohamed //////////////////////// ID 20230458 //////////////

void isValidColor(string& color, int& R, int& G, int& B) {
    cout << "Color list is:  1) red    3) white   5) green      \n";
    cout << "                2) blue   4) violet  6) yellow     \n";
    getline(cin, color);

    if (color == "6") {
        R = 255, G = 253, B = 85;
    } else if (color == "1") {
        R = 255, G = 0, B = 0;
    } else if (color == "5") {
        R = 0, G = 255, B = 0;
    } else if (color == "2") {
        R = 0, G = 0, B = 255;
    } else if (color == "4") {
        R = 100, G = 23, B = 107;
    } else if (color == "3") {
        R = 255, G = 255, B = 255;
    } else {
        cout << "Invalid input or the color does not exist.\n";
        isValidColor(color, R, G, B);
    }
}


void Frame(string& first_image , Image &image){
    string color;
    int R = 0, G = 0, B = 0;
    cout << "1- one_color filter design: \n";
    cout << "2- two_color filter design V1: \n";
    cout << "3- two_color filter design V2: \n";
    cout << "4- two_color filter design V3: \n";
    string choose ;
    cin >> choose;
    cin.ignore();
    if (choose == "2") {            
        cout << "Enter the first frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 10 || i >= image.width - 10 || j < 10 || j >= image.height - 10)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }   
        }
    
        cout << "Enter the second frame color \n";
        isValidColor(color, R, G, B); 
        for (int i = 20; i < image.width - 35; ++i) {
            for (int j = 20; j < image.height - 35; ++j) {
                if ((i < 20 || i >= image.width - 20 || j < 20 || j >= image.height - 20)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
        }
        first_image += " --> Frame_V1 ";
    }
    else if(choose=="1") {
        cout << "enter the first frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 15 || i >= image.width - 15 || j < 15 || j >= image.height - 15)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
        }
        first_image += " --> 1_color_frame ";    
    }

    else if(choose=="3") {
        cout << "Enter the first frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 10 || i >= image.width - 10 || j < 10 || j >= image.height - 10)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                } 
                else if ((i < 20 || i >= image.width - 20 || j < 20 || j >= image.height - 20)) {
                }
                else if ((i < 35 || i >= image.width - 35 || j < 35 || j >= image.height - 35)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
        }
        cout << "Enter the second frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 30 && j < 30) || (i >= image.width - 30 && j < 30) || (i < 30 && j >= image.height - 30) || (i >= image.width - 30 && j >= image.height - 30)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }else if ((i < 20 && j < 20) || (i >= image.width - 20 && j < 20) || (i < 20 && j >= image.height - 20) || (i >= image.width - 20 && j >= image.height - 20)) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 0;
                }
            }
        }
        first_image += " --> Frame_V2 ";
        
    }
    
    else if(choose=="4") {
        cout << "Enter the first frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 10 || i >= image.width - 10 || j < 10 || j >= image.height - 10)) {
                } else if ((i < 20 || i >= image.width - 20 || j < 20 || j >= image.height - 20)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                } else if ((i < 30 || i >= image.width - 30 || j < 30 || j >= image.height - 30)) {
                }
            }
        }
        cout << "Enter the second frame color \n";
        isValidColor(color, R, G, B);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if ((i < 5 || i >= image.width - 5 || j < 5 || j >= image.height - 5)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                    }else if ((i < 10 && j < 10) || (i >= image.width - 10 && j < 10) || (i < 10 && j >= image.height - 10) || (i >= image.width - 10 && j >= image.height - 10)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }else  if ((i < 20 && j < 20) || (i >= image.width - 20 && j < 20) || (i < 20 && j >= image.height - 20) || (i >= image.width - 20 && j >= image.height - 20)) {
                }else if ((i < 30 && j < 30) || (i >= image.width - 30 && j < 30) || (i < 30 && j >= image.height - 30) || (i >= image.width - 30 && j >= image.height - 30)) {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
        }
        first_image += " --> Frame_V3 ";
    }
    
}

//////////  MainMenu   ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

void printMenu(string first_image , string second_image) {
    cout << "\033[0m";
    cout << "\033[1;36m"
         << " ┌────────────────────────────┐┌────────────────────────────┐\n"
         << " │       Baby Photoshop       ││       Image Editing        │\n"
         << " └────────────────────────────┘└────────────────────────────┘\n"
         << "\033[0m";

    cout << "\033[1;33m";
    cout << "A) Load Image 📂                    B) Save Image 💾 \033[0m             ┌────────────────────────────┐\n";               
    cout << "1) Darken/Lighten Image             2) Merge Images               │ Loaded images:             │\n";
    cout << "3) Grayscale Conversion             4) Black & White Effect       │ 1) " << first_image << "      \n";                      
    cout << "5) Flip Image                       6) Resizing Images            │ 2) " << second_image << "     \n";                     
    cout << "7) Crop Images                      8) Invert Colors              │                            │\n";
    cout << "9) Rotate Image                     10) Skew Image                │                            │\n";
    cout << "11) Edge Detection                  12) Purple Filter             └────────────────────────────┘\n";
    cout << "13) Bluring Filter                  14) Frame                                                   \n";
    cout << "15) Infrared                        16) Exit                                                    \n";
}



//////////  Main Program ///////////////////// Seif eldeen hassan //////////////////////// ID 20230182 //////////////

int main(){
    int count = 0;
    Image image ;
    Image first_im;
    Image second_im;
    string first_image , second_image ;
    while (true){
        printMenu(first_image , second_image);
        string choice;
        getline(cin, choice);

        if (count == 0 && (choice == "b" || choice == "B" || choice == "1"|| choice == "2" || choice == "3" || choice == "4" || choice == "5"|| choice == "6" ||
            choice == "7"|| choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14"|| choice == "15")){
            cout << "\033[1;31mError, Load at least 1 image\n\033[0m";
            continue;
        }

        if (choice == "A" || choice == "a"){
            cout << "\033[1;33mNote: Loading new image will delete the previous image \n\033[0m";
            first_image = Get_1_image();
            Image get_first_image(first_image);
            assign (first_im , get_first_image );
            count++;
        }

        else if (choice == "B" || choice == "b"){
            Save_Image(first_im);
        } 

        else if (choice == "1"){
            Brightness( first_image  , first_im);
        }

        else if (choice == "2"){
          cout << "Please Load the 2nd image\n";
          second_image = Get_1_image();
          Image get_sec_img (second_image);
          assign(second_im , get_sec_img );
          Merge_images(first_im , second_im);
          first_image += " ---> Merged( " + first_image + " + " + second_image + " ) ";
          second_image+= " --↗";
        }

        else if (choice == "3"){
            Gray_Filter( first_image  , first_im);
        }

        else if (choice == "4"){
            Black_white(first_image  , first_im);
        }

        else if (choice == "5"){
            while(true){
            cout << ">>>>>> A) Flip Horizontal \n";
            cout << ">>>>>> B) Flip Vertical   \n";
            string choose;
            getline(cin , choose);
            if (choose == "A" || choose == "a" ){
                Flipped_Horizontally(first_image  , first_im);
                break;
            }
            else if (choose == "B" || choose == "b"){
                Flipped_Vertical(first_image  , first_im);
                break;
            }
            else{
                cout << "Invalid, Please Enter valid choice\n";
                continue;
            }
            }
        }

        else if (choice == "6"){
            double new_width , new_height;
            cout << "Enter the new width: ";
            cin >> new_width;
            cin.ignore();
            cout << "Enter the new height: ";
            cin >> new_height;
            cin.ignore();
            Resizing_Images( new_width , new_height , first_image  , first_im);
        }

        else if (choice == "7"){
            int x,y,w,h;
            cout << "Enter the started point upper left corner (X,Y):\n";
            cout << "X: ";
            cin >> x;
            cin.ignore();
            cout << "Y: ";
            cin >> y;
            cin.ignore();
            cout << "Enter the new Width:";
            cin >> w;
            cin.ignore();
            cout << "Enter the new Height:";
            cin >> h;
            cin.ignore();
            Crop_Images(x , y , w , h , first_image , first_im);
        }

        else if (choice == "8"){
            Invert_images(first_image , first_im);
        }

        else if (choice == "9"){
            while(true){
            cout << ">>>>>> A) Rotate 90 \n";
            cout << ">>>>>> B) Rotate 180   \n";
            cout << ">>>>>> C) Rotate 270  \n";
            string choose;
            getline(cin , choose);
            if (choose == "A" || choose == "a" ){
                Rotate_90(first_image , first_im);
                break;
            }
            else if (choose == "B" || choose == "b"){
                Rotate_180(first_image , first_im);
                break;
            }
            else if (choose == "C" || choose == "c"){
                Rotate_270(first_image , first_im);
                break;
            }
            else{
                cout << "Invalid, Please Enter valid choice\n";
                continue;
            }
            }
        }

        else if (choice == "10"){
            skew(first_image , first_im);

        }

        else if (choice == "11"){
            Edge_Detector(first_image , first_im);
        }

        else if (choice == "12"){
            Purple(first_image , first_im);
        }

        else if (choice == "13"){
            string blurDegree;
            int newblurDegree;
            while (true) {
                cout << "Enter blur degree (0% to 100%):\n";
                cout << "NB:dont enter ( % ): ";
                cin >> blurDegree;
                cin.ignore();
                bool validInput = true;
                for (char i : blurDegree) {
                    if (!isdigit(i)) {
                        cout << "Enter a valid integer number." << endl;
                        validInput = false;
                        break;
                    }
                }
                if (validInput) {
                    newblurDegree = stoi(blurDegree);
                    if (newblurDegree > 100 || newblurDegree < 0) {
                        cout << "Please enter a number between 0 and 100." << endl;
                    } 
                    else{
                        break;
                    }
                }
            } 
            imageBlur(first_image ,first_im, newblurDegree);
        }

        else if (choice == "14"){
            Frame(first_image , first_im);
        }

        else if (choice == "15"){
            Infrared(first_image , first_im);
        }
        
        else if (choice == "16"){
            cout << "\033[3;31mExiting Program.....\033[0m" << endl;
            exit(0);
        }
        else{
            cout << "Invalid, Please Enter valid choice\n";
        }



    }
}

 
    
