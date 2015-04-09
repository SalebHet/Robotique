#ifndef PARAM
#define PARAM
#include <string>
enum nom{rgreen,rred,ry,rx,dilate,erode,taille};
#define AFFICHER
class param
{
 public:
  param();
  param(std::string);
  ~param();
  float getValeur(nom);
  void setValeur(nom,int);

 private:
  bool load(std::string);
  void init();
  void initVar();
  void save(std::string);
  int* tab;
};

#endif
