#ifndef _phi_PadCoordinatesConversion_h_
#define _phi_PadCoordinatesConversion_h_


#include <TPad.h>

namespace phi {

  inline
  double
  GetGPadWidth()
  {
    return gPad->GetAbsWNDC() * gPad->GetWw();
  }

  inline
  double
  GetGPadHeight()
  {
    return gPad->GetAbsHNDC() * gPad->GetWh();
  }



  // Before actual conversions - font related functions which relate to pad
  // sizes
  inline
  bool
  IsPixelFont(const int font)
  {
    return font % 10 == 3;
  }

  inline
  double
  GetGPadSizeForFonts()
  {
    return std::min(GetGPadWidth(), GetGPadHeight());
  }

  inline
  double
  GetFontSizePixels(const double ndc)
  {
    return ndc * GetGPadSizeForFonts();
  }

  inline
  double
  GetFontSizeNDC(const double p)
  {
    return p / GetGPadSizeForFonts();
  }

  inline
  double
  GetFontSizePixels(const int font, const double size)
  {
    return IsPixelFont(font) ? size : GetFontSizePixels(size);
  }

  inline
  double
  GetFontSizeNDC(const int font, const double size)
  {
    return IsPixelFont(font) ? GetFontSizeNDC(size) : size;
  }




  // in case of log axes, e.g. gPad->GetUxmax() does not return the value of
  // TAxis::GetXmax(), but rather log10(TAxis::GetXmax())
  inline
  double
  AxisToUser(const double x, const bool logx)
  {
    return logx ? std::pow(10.0, x) : x;
  }

  inline
  double
  AxisToX(const double ax)
  {
    return AxisToUser(ax, gPad->GetLogx());
  }

  inline
  double
  AxisToY(const double ay)
  {
    return AxisToUser(ay, gPad->GetLogy());
  }

  inline
  double
  UserToAxis(const double x, const bool logx)
  {
    return logx ? std::log10(x) : x;
  }

  inline
  double
  XtoAxis(const double x)
  {
    return UserToAxis(x, gPad->GetLogx());
  }

  inline
  double
  YtoAxis(const double y)
  {
    return UserToAxis(y, gPad->GetLogy());
  }



  inline
  double
  GetUxmin()
  {
    gPad->Update();
    return gPad->GetUxmin();
  }

  inline
  double
  GetUxmax()
  {
    gPad->Update();
    return gPad->GetUxmax();
  }

  inline
  double
  GetUymin()
  {
    gPad->Update();
    return gPad->GetUymin();
  }

  inline
  double
  GetUymax()
  {
    gPad->Update();
    return gPad->GetUymax();
  }



  inline
  double
  GetFrameWidthNDC()
  {
    return 1.0 - gPad->GetLeftMargin() - gPad->GetRightMargin();
  }

  inline
  double
  GetFrameHeightNDC()
  {
    return 1.0 - gPad->GetTopMargin() - gPad->GetBottomMargin();
  }

  inline
  double
  GetFrameWidthAxis()
  {
    return GetUxmax() - GetUxmin();
  }

  inline
  double
  GetFrameHeightAxis()
  {
    return GetUymax() - GetUymin();
  }

  inline
  double
  GetRatioWidthNDCAxis()
  {
    return GetFrameWidthNDC() / GetFrameWidthAxis();
  }

  inline
  double
  GetRatioHeightNDCAxis()
  {
    return GetFrameHeightNDC() / GetFrameHeightAxis();
  }



  inline
  double
  NDCtoX(const double ndcx)
  {
    const double ax =
        (ndcx - gPad->GetLeftMargin()) / GetRatioWidthNDCAxis() + GetUxmin();
    return AxisToX(ax);
  }

  inline
  double
  NDCtoY(const double ndcy)
  {
    const double ay =
        (ndcy - gPad->GetBottomMargin()) / GetRatioHeightNDCAxis() + GetUymin();
    return AxisToY(ay);
  }

  inline
  double
  XtoNDC(const double x)
  {
    const double ax = XtoAxis(x);
    return GetRatioWidthNDCAxis() * (ax - GetUxmin()) + gPad->GetLeftMargin();
  }

  inline
  double
  YtoNDC(const double y)
  {
    const double ay = YtoAxis(y);
    return GetRatioHeightNDCAxis() * (ay - GetUymin()) +
        gPad->GetBottomMargin();
  }



  inline
  double
  NDCtoPixelX(const double ndcx)
  {
    return ndcx * GetGPadWidth();
  }

  inline
  double
  NDCtoPixelY(const double ndcy)
  {
    return (1.0 - ndcy) * GetGPadHeight();
  }

  inline
  double
  PixelXtoNDC(const double px)
  {
    return px / GetGPadWidth();
  }

  inline
  double
  PixelYtoNDC(const double py)
  {
    return 1.0 - py / GetGPadHeight();
  }



  inline
  double
  PixelToX(const double px)
  {
    return NDCtoX(PixelXtoNDC(px));
  }

  inline
  double
  PixelToY(const double py)
  {
    return NDCtoY(PixelYtoNDC(py));
  }

  inline
  double
  XtoPixel(const double x)
  {
    return NDCtoPixelX(XtoNDC(x));
  }

  inline
  double
  YtoPixel(const double y)
  {
    return NDCtoPixelY(YtoNDC(y));
  }


}

#endif
