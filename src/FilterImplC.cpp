#include "FilterImplC.h"

void kernelSobelHoriz3x3(const unsigned char* pSrc, int srcStep, char* pDst)
{
  int sobelHoriz =  1 * pSrc[-srcStep - 1] +  2 * pSrc[-srcStep + 0] +  1 * pSrc[-srcStep + 1] + 
                    0 * pSrc[-1] +            0 * pSrc[0] +             0 * pSrc[1] + 
                    -1 * pSrc[srcStep - 1] +  -2 * pSrc[srcStep + 0] +  -1 * pSrc[srcStep + 1];

  sobelHoriz = (sobelHoriz + 4) / 8;
  *pDst = (char)sobelHoriz;
}

void kernelSobelVert3x3(const unsigned char* pSrc, int srcStep, char* pDst)
{
  int sobelVert =  -1 * pSrc[-srcStep - 1] +  0 * pSrc[-srcStep + 0] +  1 * pSrc[-srcStep + 1] + 
                    -2 * pSrc[-1] +            0 * pSrc[0] +             2 * pSrc[1] + 
                    -1 * pSrc[srcStep - 1] +   0 * pSrc[srcStep + 0] +  -1 * pSrc[srcStep + 1];

  sobelVert = (sobelVert + 4) / 8;
  *pDst = (char)sobelVert;
}

void kernelSobelHorizVert3x3(const unsigned char* pSrc, int srcStep, char* pDst)
{
  int sobelHoriz =  1 * pSrc[-srcStep - 1] +  2 * pSrc[-srcStep + 0] +  1 * pSrc[-srcStep + 1] + 
                    0 * pSrc[-1] +            0 * pSrc[0] +             0 * pSrc[1] + 
                    -1 * pSrc[srcStep - 1] +  -2 * pSrc[srcStep + 0] +  -1 * pSrc[srcStep + 1];
  sobelHoriz = (sobelHoriz + 4) / 8;

  int sobelVert =  -1 * pSrc[-srcStep - 1] +  0 * pSrc[-srcStep + 0] +  1 * pSrc[-srcStep + 1] + 
                    -2 * pSrc[-1] +            0 * pSrc[0] +             2 * pSrc[1] + 
                    -1 * pSrc[srcStep - 1] +   0 * pSrc[srcStep + 0] +  -1 * pSrc[srcStep + 1];
  sobelVert = (sobelVert + 4) / 8;

  pDst[0] = (char)sobelHoriz;
  pDst[1] = (char)sobelVert;
}

void kernelGauss3x3(const unsigned char* pSrc, int srcStep, unsigned char* pDst)
{
  int gauss = 1 * pSrc[-srcStep - 1] +  2 * pSrc[-srcStep + 0] +  1 * pSrc[-srcStep + 1] + 
              2 * pSrc[-1] +            4 * pSrc[0] +             2 * pSrc[1] + 
              1 * pSrc[srcStep - 1] +   2 * pSrc[srcStep + 0] +   1 * pSrc[srcStep + 1];

  gauss = (gauss + 8) / 16;
  *pDst = (unsigned char)gauss;
}

int filterSobelHoriz3x3_C(const unsigned char* pSrcOrig, int srcStep, char* pDstOrig, int dstStep, int width, int height)
{
  return filterUsingKernel<3, 1>(pSrcOrig, srcStep, pDstOrig, dstStep, width, height, kernelSobelHoriz3x3);
}

int filterSobelVert3x3_C(const unsigned char* pSrcOrig, int srcStep, char* pDstOrig, int dstStep, int width, int height)
{
  return filterUsingKernel<3, 1>(pSrcOrig, srcStep, pDstOrig, dstStep, width, height, kernelSobelVert3x3);
}

int filterSobel3x3_C(const unsigned char* pSrcOrig, int srcStep, char* pDstOrig, int dstStep, int width, int height)
{
  return filterUsingKernel<3, 1>(pSrcOrig, srcStep, pDstOrig, dstStep, width, height, kernelSobelHorizVert3x3);
}

int filterGauss3x3_C(const unsigned char* pSrcOrig, int srcStep, unsigned char* pDstOrig, int dstStep, int width, int height)
{
  return filterUsingKernel<3, 1>(pSrcOrig, srcStep, pDstOrig, dstStep, width, height, kernelGauss3x3);
}

