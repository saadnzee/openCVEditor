#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace cv;
class ImageProcessor {
private:
 Mat workingImage;
 string imagePath;
 string savePath;
public:
 // Constructor (intializing!)
 ImageProcessor() {
 workingImage = Mat();
 imagePath = string();
 savePath = string();
 namedWindow("Image Editor", WINDOW_NORMAL);
 }
 // Copy Constructor
 ImageProcessor(const ImageProcessor& other) {
 workingImage = other.workingImage.clone();
 imagePath = other.imagePath;
 savePath = other.savePath;
 }
 // reading the image and checking for possible events
 void loadAndProcessImage() {
 cout << "Enter the path of the image to load: " << endl;
 cin >> imagePath;
 workingImage = imread(imagePath, IMREAD_COLOR);
 if (workingImage.empty()) {
 cerr << "Error!! Could not open or load the image." << endl;
 return;
 }
 imshow("Image Editor", workingImage);
 handleEvents();
 }
 // possible functionalities
 void processImage(int processingChoice) {
 if (processingChoice == 1) {
 cvtColor(workingImage, workingImage, COLOR_BGR2GRAY); 
 }
 else if (processingChoice == 2) {
 GaussianBlur(workingImage, workingImage, Size(0, 0), 5); 
 }
 else if (processingChoice == 3) {
 Mat sharpeningKernel = (Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
 filter2D(workingImage, workingImage, workingImage.depth(), sharpeningKernel); 
 }
 else if (processingChoice == 4) {
 rotateImage();
 }
 else if (processingChoice == 5) {
 adjustBrightnessContrast();
 }
 else if (processingChoice == 6) {
 cropImage();
 }
 else if (processingChoice == 7) {
 resizeImage();
 }
 else if (processingChoice == 8) {
 bitwise_not(workingImage, workingImage);
 }
 
 if (processingChoice != 7) {
 imshow("Image Editor", workingImage);
 }
 }
 // handling possible events!
 void handleEvents() {
 while (true) {
 cout << "What do you want to do with the image? \n(1: Convert to Grayscale, 2: Blur, 3: 
Sharpen, 4: Rotate, 5: Adjust Brightness/Contrast, 6: Crop, 7: Resize, 8: Inversion, 9: Load Another 
Image, s: Save, q: Quit): " << endl;
 int choice = waitKey(0);
 if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || 
choice == '7' || choice == '8') {
 processImage(choice - '0');
 }
 else if (choice == '9') {
 loadAndProcessImage();
 }
 else if (choice == 's') {
 saveImage();
 }
 else if (choice == 'q') {
 break;
 }
 }
 }
 void rotateImage() {
 double angle;
 cout << "Enter the rotation angle (in degrees): ";
 cin >> angle;
 Point2f center(workingImage.cols / 2.0, workingImage.rows / 2.0);
 Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
 warpAffine(workingImage, workingImage, rotationMatrix, workingImage.size());
 }
 void adjustBrightnessContrast() {
 double alpha, beta;
 cout << "Enter the alpha value (contrast, 1.0 means no change): ";
 cin >> alpha;
 cout << "Enter the beta value (brightness, 0 means no change): ";
 cin >> beta;
 workingImage.convertTo(workingImage, -1, alpha, beta);
 }
 void cropImage() {
 int width, height;
 cout << "Enter the width and height of the crop region: ";
 cin >> width >> height;
 int x = (workingImage.cols - width) / 2;
 int y = (workingImage.rows - height) / 2;
 x = max(0, x);
 y = max(0, y);
 width = min(width, workingImage.cols - x);
 height = min(height, workingImage.rows - y);
 Rect cropRegion(x, y, width, height);
 workingImage = workingImage(cropRegion).clone();
 }
 void resizeImage() {
 double ratio;
 cout << "Enter the resize ratio: ";
 cin >> ratio;
 int width = workingImage.cols;
 int height = workingImage.rows;
 int newWidth = static_cast<int>(width * ratio);
 int newHeight = static_cast<int>(height * ratio);
 resize(workingImage, workingImage, Size(newWidth, newHeight));
 resizeWindow("Image Editor", newWidth, newHeight);
 imshow("Image Editor", workingImage);
 }
 void saveImage() {
 cout << "Enter the path to save the image: ";
 cin >> savePath;
 imwrite(savePath, workingImage);
 cout << "Image saved successfully." << endl;
 }
 // Destructor
 ~ImageProcessor() {
 destroyAllWindows();
 }
};
int main() {
 ImageProcessor obj;
 obj.loadAndProcessImage();
 return 0;
}
