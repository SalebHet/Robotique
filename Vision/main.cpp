#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>

#include "param.h"

#define AFFICHER_COULEUR false
cv::Mat frame;
enum color{green,red,yellow};
void onMouse(int event, int x, int y, int, void*)
{
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Vec3b& pixel = frame.at<cv::Vec3b>(y,x);
        std::cout << "Pixel at [" << x << "," << y << "] = ";
        std::cout << (int)pixel[2] << ",";
        std::cout << (int)pixel[1] << ",";
        std::cout << (int)pixel[0] << std::endl;
    }
}

void init()
{
#ifdef AFFICHER
  cv::namedWindow("win1");
  cv::namedWindow("win2");
  cv::namedWindow("win3");

  cv::setMouseCallback("win3", onMouse, NULL);
  
#endif
}
#if 0
void encadrement(cv::Vec3b& pixel,param& p)
{
  if (
      pixel[2] >= p.getValeur(rinf) && pixel[2] <= p.getValeur(rsup) && //R
      pixel[0] >= p.getValeur(binf) && pixel[0] <= p.getValeur(bsup) && //B
      pixel[1] >= p.getValeur(ginf) && pixel[1] <= p.getValeur(gsup)    //G
      )
    {
      pixel[0] = 255;
      pixel[1] = 255;
      pixel[2] = 255;
    } 
  else 
    {
      pixel[0] = 0;
      pixel[1] = 0;
      pixel[2] = 0;
    }

}
#endif
void rapport(cv::Vec3b& pixel,cv::Vec3b& pixel2,color c,param& p)
{
  switch(c)
  {
  case green:
    if(pixel[2]*p.getValeur(rgreen)<pixel[1] && pixel[0]*p.getValeur(rgreen)<pixel[1])
    {
      pixel2[0]=0;
      pixel2[1]=255;
      pixel2[2]=0;
    }
    else
    {
      pixel2[0]=0;
      pixel2[1]=0;
      pixel2[2]=0;
    }
    break;
  case red:
    if(pixel[1]*p.getValeur(rred)<pixel[2] && pixel[0]*p.getValeur(rred)<pixel[2] &&
       (p.getValeur(ry)+pixel[0])*p.getValeur(rx)>pixel[1] && (p.getValeur(ry)+pixel[1])*p.getValeur(rx)>pixel[0])
    {    
      pixel2[0]=0;
      pixel2[1]=0;
      pixel2[2]=255;
    }
    break;
  case yellow:
    if(pixel[2]>pixel[0]*1.5 && pixel[1]>pixel[0]*1.5 && 
       (20+pixel[2])*1.5>pixel[1] && pixel[2]<(20+pixel[1])*1.5)
    {    
      pixel2[0]=0;
      pixel2[1]=255;
      pixel2[2]=255;
    }
    break;
  }
}
void test(cv::Mat & f)
{
  for(int i=0;i<f.rows;i++)
  {
    int a=0;
    int b=f.cols-1;
    while(f.at<cv::Vec3b>(i,a)[1]==0 and a<f.cols)
      a++;
    while(f.at<cv::Vec3b>(i,b)[1]==0 and b>a)
      b--;
    if(a>=b)
      continue;
    a=(a>25)?a-25:0;
    b=(b+25>=frame.cols)?frame.cols-1:b+25;
    for(;a<b;a++)
    {
      f.at<cv::Vec3b>(i,a)[0]=0;
      f.at<cv::Vec3b>(i,a)[1]=255;
      f.at<cv::Vec3b>(i,a)[2]=0;
    }
  }
#if 1
  for(int i=0;i<f.cols;i++)
  {
    int a=0;
    int b=f.rows-1;
    while(f.at<cv::Vec3b>(a,i)[1]==0 and a<f.rows)
      a++;
    while(f.at<cv::Vec3b>(b,i)[1]==0 and b>a)
      b--;
    if(a>=b)
      continue;
    a=(a>25)?a-25:0;
    b=(b+25>=frame.rows)?frame.rows-1:b+25;
    for(;a<b;a++)
    {
      f.at<cv::Vec3b>(a,i)[0]=0;
      f.at<cv::Vec3b>(a,i)[1]=255;
      f.at<cv::Vec3b>(a,i)[2]=0;
    }
  }
#endif
}
int main()
{
  int t=std::clock();
  init();
  param p("save");
  //void(*traitement)(cv::Vec3b&,param&)=rapport;
  
  cv::Mat f2,f3;

  cv::VideoCapture camera(1);
  camera.set(CV_CAP_PROP_FRAME_WIDTH,1);
  camera.set(CV_CAP_PROP_FRAME_HEIGHT,1);
std::cout<<"test"<<std::endl;    
    if (!camera.isOpened()) {
        std::cerr << "Unable to open camera" << std::endl;
        return 1;
    }
    
    camera >> frame;
    f2=f3=frame;
    int x=0;
    int y=0;
    
    while (cv::waitKey(10)!=1048603) {
      //std::cout<<1/((std::clock()-t)/(float)CLOCKS_PER_SEC)<<std::endl;
      //t=std::clock();
        camera >> frame;
	f3=frame.clone();
#ifdef AFFICHER
	cv::imshow("win3",f2);
#endif

	
        long sumX = 0;
        long sumY = 0;
        long count = 0;
        for (int i=0;i<frame.rows;i++) {
            for (int j=0;j<frame.cols;j++) {
                cv::Vec3b& pixel = frame.at<cv::Vec3b>(i,j);
                rapport(pixel,pixel,green,p);
            }
        }
	cv::erode(frame,f2,getStructuringElement(cv::MORPH_RECT,cv::Size(2,2)),cv::Point(-1,-1),p.getValeur(erode));
	//cv::dilate(f2,frame,getStructuringElement(cv::MORPH_RECT,cv::Size(2,2)),cv::Point(-1,-1),p.getValeur(dilate));
	test(f2);
	#if 1
	for(int i=0;i<f2.rows;i++)
	  for(int j=0;j<f2.cols;j++)
	  {
	    cv::Vec3b& pixel=frame.at<cv::Vec3b>(i,j);
	    if(pixel[1]==255)
	    {
              cv::Vec3b& pixel2=f3.at<cv::Vec3b>(i,j);
	      rapport(pixel2,pixel,red,p);
	      //rapport(pixel2,pixel,yellow,p);
	    }
	  }
	#endif
	if (count > 0) {
	  x = sumX/count;
	  y = sumY/count;
	  //cv::circle(frame, cv::Point(x, y), 10, cv::Scalar(0, 0, 255), -1);
        }
	
#ifdef AFFICHER
        cv::imshow("win1", frame);
#endif
    }
    
    return 0;
}

