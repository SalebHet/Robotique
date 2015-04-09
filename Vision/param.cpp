#include <opencv2/opencv.hpp>
#include <fstream>

#include "param.h"

param::param()
{

  init();
}
param::param(std::string s)
{
  if(!load(s))
 init();

}
param::~param()
{
  std::ofstream is("save");
  for(int i=0;i<taille;i++)
    is<<tab[i]<<std::endl;
}
void param::init()
{
  
  cv::createTrackbar("rGreen","win2",&tab[rgreen],500);
  cv::createTrackbar("rRed","win2",&tab[rred],2000);
  cv::createTrackbar("ry","win2",&tab[ry],500);
  cv::createTrackbar("rx","win2",&tab[rx],500);
  cv::createTrackbar("erode","win2",&tab[erode],20);
  cv::createTrackbar("dilate","win2",&tab[dilate],100);
}
void param::initVar()
{
  tab=new int[taille];
  tab[rgreen]=120;
  tab[rred]=300;
  tab[ry]=5;
  tab[rx]=120;
  tab[dilate]=5;
  tab[erode]=5;

}
float param::getValeur(nom n)
{
  if(n<erode)
    return ((float)tab[n])/100.f;
  else
    return tab[n];
}

void param::setValeur(nom n,int val)
{
  if(n<erode)
    tab[n]=val*10;
  else
    tab[n]=val;
}

bool param::load(std::string s)
{
  tab=new int[taille];
  std::ifstream is(s.c_str());
  if(!is)
    return false;
  for(int i=0;i<taille;i++)
    is>>tab[i];
  
}
