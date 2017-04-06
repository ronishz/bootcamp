/*
 * DisplayImage.cpp
 *
 *  Created on: 19-Jan-2017
 *  Author: Shubham Sureka
 */

#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<iostream>
#include<math.h>
#define pi (22.0/7.0)
using namespace std;
using namespace cv;
class filters{
	Mat image, newImage;
public:
	filters(int argc, char** argv);
	void contrastStretching();
	void displayImage();
	int computeOutput(int x, int r1, int s1, int r2, int s2);
	void blur();
	int computeBlur(int img,int x, int y, int c);
	void sharpen();
	int computeSharpen(int img,int x,int y,int c);
	void brightness();
	void rotation(int angle);
	void histogram();
	void probabilityMassFunction();
	void meanStandardDeviation();
};

filters :: filters(int argc, char** argv){
	image = imread(argv[1], 1);
	newImage = image.clone();

	if(argc != 2 || !image.data){
			printf("No image data \n");
			exit(0);
		}
}

void filters:: contrastStretching(){
	int r1,s1,r2,s2;
	cout<<"Enter r1: "; cin>>r1;
	cout<<"Enter s1: "; cin>>s1;
	cout<<"Enter r2: "; cin>>r2;
	cout<<"Enter s2: "; cin>>s2;

	for(int y=0; y<image.rows; y++){
			for(int x=0; x<image.cols; x++){
				for(int c=0; c<=2; c++){
					int output = computeOutput(image.at<Vec3b>(y,x)[c],r1,s1,r2,s2);
					newImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(output);
				}
			}
		}
	displayImage();
}

int filters :: computeOutput(int x, int r1, int s1, int r2, int s2)
{
    float result;
    if(x >= 0 && x <= r1){
        result = s1/r1 * x;
    }else if(r1 < x && x <= r2){
        result = ((s2 - s1)/(r2 - r1)) * (x - r1) + s1;
    }else if(r2 < x && x <= 255){
        result = ((255 - s2)/(255 - r2)) * (x - r2) + s2;
    }
    return (int)result;
}

void filters:: blur(){
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
			for(int c=0; c<3; c++){
				int output = computeBlur((int)image.at<Vec3b>(x,y)[c],x,y,c);
				newImage.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(output);
			}
		}
	}
	displayImage();
}

int filters:: computeBlur(int img, int x, int y,int c){
	int sum=0;
	int avg;
	for(int i=x; i<(x+3); i++){
		for(int j=y; j<(y+3); j++){
			sum+=image.at<Vec3b>(i,j)[c];
		}
	}
	avg=sum/9;
	return avg;
}

void filters:: sharpen(){
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
			for(int c=0; c<3; c++){
				int output = computeSharpen((int)image.at<Vec3b>(x,y)[c],x,y,c);
				newImage.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(output);
			}
		}
	}
	displayImage();
}

int filters:: computeSharpen(int img, int x, int y,int c){
	int sum=0;
	for(int i=x; i<(x+3); i++){
		for(int j=y; j<(y+3); j++){
			if(i==(x+1) && j==(y+1)){
				sum+=(9*newImage.at<Vec3b>(i,j)[c]);
			}
			else{
				sum+=(-1*newImage.at<Vec3b>(i,j)[c]);
			}
		}
	}
	return sum;
}

void filters:: brightness(){
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
			for(int c=0; c<3; c++){
				int output = (int)image.at<Vec3b>(x,y)[c]+50;
				newImage.at<Vec3b>(x,y)[c] = saturate_cast<uchar>(output);
			}
		}
	}
	displayImage();
}

void filters:: rotation(int angle){
	float newAngle=angle*(pi/180);int x0=image.rows/2, y0=image.cols/2;
	Mat newImage(image.rows, image.cols, CV_8UC3, Scalar(255, 255, 255));
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
				int x2 = cos(newAngle) * (x-x0) - sin(newAngle) * (y-y0) + x0;
				int y2 = sin(newAngle) * (x-x0) + cos(newAngle) * (y-y0) + y0;
				if(x2<image.rows && y2<image.cols && x2>0 && y2>0)
					newImage.at<Vec3b>(x2,y2) = image.at<Vec3b>(x,y);
		}
	}
	namedWindow("Original Image", 0);
	imshow("Original Image", image);

	namedWindow("New Image", 0);
	imshow("New Image", newImage);
	waitKey(10000);
}

void filters:: displayImage(){
	namedWindow("Original Image", 0);
	imshow("Original Image", image);

	namedWindow("New Image", 0);
	imshow("New Image", newImage);
	waitKey(10000);
}

void filters:: histogram(){
	int red[image.rows*image.cols],green[image.rows*image.cols],blue[image.rows*image.cols];
	int redf[256],greenf[256],bluef[256];
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
				red[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[0];
				green[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[1];
				blue[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[2];
		}
	}
	for(int i=1; i<255; i++){
		redf[i]=0;
		greenf[i]=0;
		bluef[i]=0;
	}
	for(int i=0; i<(image.rows*image.cols); i++){
		for(int j=1; j<255; j++){
			if(red[i]==j)
				redf[j]+=1;
			if(green[i]==j)
				greenf[j]+=1;
			if(blue[i]==j)
				bluef[j]+=1;
		}
	}
	//draw histogram
	int hWidth = 256; int hHeight = 400;
	int binWidth = hWidth/256;
	Mat histImageR(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	Mat histImageG(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	Mat histImageB(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	// find the maximum intensity element from histogram
	int maxR = redf[1], maxG = greenf[1], maxB = bluef[1];
	for(int i =1; i < 255; i++){
		if(maxR < redf[i])
			maxR = redf[i];
		if(maxG < greenf[i])
			maxG = greenf[i];
		if(maxB < bluef[i])
			maxB = bluef[i];
	}
	// normalize the histogram between 0 and histImage.rows
	for(int i=1; i<255; i++){
		redf[i] = ((double)redf[i]/maxR)*histImageR.rows;
		greenf[i] = ((double)greenf[i]/maxG)*histImageG.rows;
		bluef[i] = ((double)bluef[i]/maxB)*histImageB.rows;
	}
	// draw the intensity line for histogram
	for(int i = 1; i < 255; i++)
	{
		line(histImageR, Point(binWidth*i, hHeight), Point(binWidth*i, hHeight-redf[i]),Scalar(0,0,0), 1, 8, 0);
		line(histImageG, Point(binWidth*i, hHeight), Point(binWidth*i, hHeight-greenf[i]),Scalar(0,0,0), 1, 8, 0);
		line(histImageB, Point(binWidth*i, hHeight), Point(binWidth*i, hHeight-bluef[i]),Scalar(0,0,0), 1, 8, 0);
	}
	imshow("histImageR", histImageR);
	imshow("histImageG", histImageG);
	imshow("histImageB", histImageB);
	waitKey(10000);
}

void filters:: probabilityMassFunction(){
	int red[image.rows*image.cols],green[image.rows*image.cols],blue[image.rows*image.cols];
	int redf[256],greenf[256],bluef[256];
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
				red[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[0];
				green[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[1];
				blue[x*image.cols+y] = (int)image.at<Vec3b>(x,y)[2];
		}
	}
	for(int i=1; i<255; i++){
		redf[i]=0;
		greenf[i]=0;
		bluef[i]=0;
	}
	for(int i=0; i<(image.rows*image.cols); i++){
		for(int j=1; j<255; j++){
			if(red[i]==j)
				redf[j]+=1;
			if(green[i]==j)
				greenf[j]+=1;
			if(blue[i]==j)
				bluef[j]+=1;
		}
	}
	for(int i=1; i<255; i++){
		redf[i]=((double)redf[i]/(image.rows*image.cols))*10000;
		greenf[i]=((double)greenf[i]/(image.rows*image.cols))*10000;
		bluef[i]=((double)bluef[i]/(image.rows*image.cols))*10000;
	}
	//draw histogram
	int hWidth = 512; int hHeight = 256;
	int binWidth = cvRound((double) hWidth/256);
	Mat pmfImageR(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	Mat pmfImageG(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	Mat pmfImageB(hHeight, hWidth, CV_8UC1, Scalar(255, 255, 255));
	// find the maximum intensity element from histogram
	int maxR = redf[1], maxG = greenf[1], maxB = bluef[1];
	for(int i =1; i < 255; i++){
		if(maxR < redf[i])
			maxR = redf[i];
		if(maxG < greenf[i])
			maxG = greenf[i];
		if(maxB < bluef[i])
			maxB = bluef[i];
	}
	// normalize the histogram between 0 and histImage.rows
	for(int i=1; i<255; i++){
		redf[i] = ((double)redf[i]/maxR)*pmfImageR.rows;
		greenf[i] = ((double)greenf[i]/maxG)*pmfImageG.rows;
		bluef[i] = ((double)bluef[i]/maxB)*pmfImageB.rows;
	}
	// draw the intensity line for histogram
	for(int i = 1; i < 255; i++)
	{
		line(pmfImageR, Point(binWidth*i, hHeight-redf[i]), Point(binWidth*i, hHeight-redf[i]),Scalar(0,0,0), 1, 8, 0);
		line(pmfImageG, Point(binWidth*i, hHeight-greenf[i]), Point(binWidth*i, hHeight-greenf[i]),Scalar(0,0,0), 1, 8, 0);
		line(pmfImageB, Point(binWidth*i, hHeight-bluef[i]), Point(binWidth*i, hHeight-bluef[i]),Scalar(0,0,0), 1, 8, 0);
	}
	imshow("pmfImageR", pmfImageR);
	imshow("pmfImageG", pmfImageG);
	imshow("pmfImageB", pmfImageB);
	waitKey(10000);
}

void filters:: meanStandardDeviation(){
	float meanR, meanG, meanB;
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
			meanR+=(int)image.at<Vec3b>(x,y)[0];
			meanG+=(int)image.at<Vec3b>(x,y)[1];
			meanB+=(int)image.at<Vec3b>(x,y)[2];
		}
	}
	meanR/=(image.rows*image.cols);
	meanG/=(image.rows*image.cols);
	meanB/=(image.rows*image.cols);
	cout<<"\nRed Mean:"<<meanR;
	cout<<"\nGreen Mean:"<<meanG;
	cout<<"\nBlue Mean:"<<meanB<<endl;
	long summationR=0, summationG=0, summationB=0;
	for(int x=0; x<image.rows; x++){
		for(int y=0; y<image.cols; y++){
			summationR += ((int)image.at<Vec3b>(x,y)[0]-meanR) * ((int)image.at<Vec3b>(x,y)[0]-meanR);
			summationG += ((int)image.at<Vec3b>(x,y)[1]-meanG) * ((int)image.at<Vec3b>(x,y)[1]-meanG);
			summationB += ((int)image.at<Vec3b>(x,y)[2]-meanB) * ((int)image.at<Vec3b>(x,y)[2]-meanB);
		}
	}
	double stdDevR, stdDevG, stdDevB;
	stdDevR = sqrt(summationR/((image.rows * image.cols)-1));
	stdDevG = sqrt(summationG/((image.rows * image.cols)-1));
	stdDevB = sqrt(summationB/((image.rows * image.cols)-1));

	cout<<"\nRed Standard Deviation:"<<stdDevR;
	cout<<"\nGreen Standard Deviation:"<<stdDevG;
	cout<<"\nBlue Standard Deviation:"<<stdDevB<<endl;
}

int main(int argc, char** argv){

	int choice;
	filters obj(argc,argv);

	while(true){
		cout<<"\n1. Contrast Stretching\n2. Blur\n3. Sharpen\n"
				"4. Brightness and Contrast\n5. Rotate by angle\n"
				"6. Histogram\n7.PMF\n8. Mean and Standard Deviation\n9. Exit\n Enter Choice:";
		cin>>choice;
		switch(choice){
		case 1:
			obj.contrastStretching();
			break;
		case 2:
			obj.blur();
			break;
		case 3:
			obj.sharpen();
			break;
		case 4:
			obj.brightness();
			break;
		case 5:
			cout<<"Enter angle of rotation:";
			int angle;
			cin>>angle;
			obj.rotation(angle);
			break;
		case 6:
			obj.histogram();
			break;
		case 7:
			obj.probabilityMassFunction();
			break;
		case 8:
			obj.meanStandardDeviation();
			break;
		case 9:
			cout<<"**************Terminated**************";
			exit(0);
		default:
			cout<<"Select proper choice!!\n";
			break;
		}
	}
	return 0;
}



//Go to Project>Properties>C/C++ BUild>Settings>GCC Compiler>includes>include (I):/usr/local/include/opencv
//include path /usr/local/lib in libraries(-L)
//libraries(-l): opencv_core  opencv_imgproc  opencv_highgui

/*OUTPUT
1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:1
Enter r1: 100
Enter s1: 200
Enter r2: 300
Enter s2: 400
init done
opengl support available

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:2

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:3

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:4

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:5
Enter angle of rotation:180
init done
opengl support available

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:6


1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:7
init done
opengl support available

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:8

Red Mean:115.893
Green Mean:109.79
Blue Mean:126.013

Red Standard Deviation:96.6747
Green Standard Deviation:71.8818
Blue Standard Deviation:87.1149

1. Contrast Stretching
2. Blur
3. Sharpen
4. Brightness and Contrast
5. Rotate by angle
6. Histogram
7.PMF
8. Mean and Standard Deviation
9. Exit
 Enter Choice:9
**************Terminated**************

 */

