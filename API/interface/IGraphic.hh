#ifndef IGRAPHIC_HH_
#define IGRAPHIC_HH_

class IGraphic
{
public:
  virtual ~IGraphic () {};

  virtual bool handleEvent() = 0;
  virtual void printWindow() = 0;
};

#endif
