#include "image.h"

image::image(cv::Mat m)
{
  imageRaw=m.clone();
  imageProcessed=cv::Mat(m.size(),m.type());
  
}
