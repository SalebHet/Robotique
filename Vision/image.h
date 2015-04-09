#include <opencv2/opencv.hpp>

class image
{
 public:
  image(cv::Mat);
  void rapport(cv::Vec3b& pixel,cv::Vec3b& pixel2,color c,param& p);
  void rapport(cv::Vec3b& pixel,cv::Vec3b& pixel2,color c,color masque,param& p);
 private:
  cv::Mat imageRaw;
  cv::Mat imageProcessed;
};
