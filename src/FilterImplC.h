#pragma once

int filterSobelHoriz3x3_C(const unsigned char* pSrc, int srcStep, char* pDst, int dstStep, int width, int height);

int filterSobelVert3x3_C(const unsigned char* pSrc, int srcStep, char* pDst, int dstStep, int width, int height);

int filterSobel3x3_C(const unsigned char* pSrc, int srcStep, char* pDst, int dstStep, int width, int height);

int filterGauss3x3_C(const unsigned char* pSrc, int srcStep, char* pDst, int dstStep, int width, int height);

void kernelSobelHoriz3x3(const unsigned char* pSrc, int srcStep, char* pDst);

void kernelSobelVert3x3(const unsigned char* pSrc, int srcStep, char* pDst);

void kernelSobelHorizVert3x3(const unsigned char* pSrc, int srcStep, char* pDst);

void kernelGauss3x3(const unsigned char* pSrc, int srcStep, unsigned char* pDst);

template <int KernelSize, int DstIncrement, typename KernelFunction, typename DstType>
int filterUsingKernel(const unsigned char* pSrcOrig, int srcStep, DstType* pDstOrig, int dstStep, int width, int height, KernelFunction function)
{
  if(srcStep <= 0 || srcStep < width || dstStep <= 0 || dstStep <= width || width <= 0 || height <= 0)
  {
    return 1;
  }

  static const int border = KernelSize / 2;
  for(int y = border; y < height - border; ++y)
  {
    const unsigned char* pSrc = pSrcOrig + y * srcStep + border;
    DstType* pDst = pDstOrig + y * dstStep + border;
    const unsigned char* const pSrcEnd = pSrc + width - 2 * border;
    while(pSrc != pSrcEnd)
    {
      function(pSrc, srcStep, pDst);

      ++pSrc;
      pDst += DstIncrement;
    }
  }

  return 0;
}