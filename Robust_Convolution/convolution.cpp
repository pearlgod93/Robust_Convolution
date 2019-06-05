#include "convolution.hpp"
void conv(double * pSrcA, uint32_t srcALen, double * pSrcB, uint32_t srcBLen,double * pDst)
{
    double *pIn1; //Input A Pointer
    double *pIn2; //Input B Pointer
    double *pOut = pDst; //Output Pointer
    double *px;     //Intermediate A Pointer
    double *py;     //Intermediate B pointer

    double *pSrc1 ,*pSrc2;
    double sum, acc0,acc1,acc2,acc3;

    double x0,x1,x2,x3,c0;
    uint32_t j,k,countr, blkCnt,blkSize1, blkSize2,blkSize3; //Loop counters

    if(srcALen >= srcBLen)
    {
        pIn1 = pSrcA;
        pIn2 = pSrcB;
    }
    else
    {
        pIn1 = pSrcB;
        pIn2 = pSrcA;
        j = srcBLen;
        srcBLen = srcALen;
        srcALen = j;
    //}
    blkSize1 = srcBLen - 1;
    blkSize2 = srcALen-(srcBLen-1);
    blkSize3 = blkSize1;

    countr = 1;
    px = pIn1;
    py = pIn2;

    while(blkSize1 > 0){
        sum = 0.0;
        k = countr >>2; //Rightshifted by 2 - divided by 4

        while(k>0){
            sum+= *px++ * *py--; //x[0]
            sum+= *px++ * *py--; //x[1]
            sum+= *px++ * *py--; //x[2]
            sum+= *px++ * *py--; //x[3]

            k--;
        }
        k = countr %0x4;

        while(k>0){
            sum+= *px++ * *py--;
            k--;
    }
    *pOut ++ = sum;
    py = pIn2 + countr;
    px = pIn1;

    countr++;
    blkSize1--;
}
px = pIn1;
pSrcB = pIn2+(srcBLen-1);
py = pSrc2;

countr = 0;

if(srcBLen>=4)
{

blkCnt = blkSize2 >>2;
while(blkCnt >0)
{
    acc0 =0.0;
    acc1 = 0.0;
    acc2 = 0.0;
    acc3 = 0.0;

    x0 =*(px++);
    x1 =*(px++);
    x2 =*(px++);

    k = srcBLen >>2;
    do{
        c0 = *(py--);
        acc0 += x0*c0;
        acc1 += x1*c0;
        acc2 += x2*c0;
        acc3 += x3*c0;

        c0 = *(py--);
        x0 = (*px+1);

        acc0 += x1*c0;
        acc1 += x2*c0;
        acc2 += x3*c0;
        acc3 += x0*c0;

        c0 = *(py--);
        x1 = (*px+2);

        acc0 += x2*c0;
        acc1 += x3*c0;
        acc2 += x0*c0;
        acc3 += x1*c0;

        c0 = *(py--);
        x2 = (*px+3);
        px += 4;
        acc0 += x3*c0;
        acc1 += x0*c0;
        acc2 += x1*c0;
        acc3 += x2*c0;
    }while(--k);
    k = srcBLen %0x4;
    while(k>0)
    {
        c0 = *(py--);
        //Read x[7] sample
        x3 = *(px++);

        acc0 += x0 * c0;
        acc1 += x1 * c0;
        acc2 += x2 * c0;
        acc3 += x3 * c0;

        x0 = x1;
        x1 = x2;
        x2 = x3;

        k--;
    }

    *pOut++ = acc0;
    *pOut++ = acc1;
    *pOut++ = acc2;
    *pOut++ = acc3;

    countr +=4;
    px = pIn1 + countr;
    py = pSrc2;

    blkCnt--;
}
blkCnt = blkSize2%0x4;
while(blkCnt>0)
{
    sum = 0.0;
    k = srcBLen >> 2;
    while(k>0){
        sum += *px++ * *py--;
        sum += *px++ * *py--;
        sum += *px++ * *py--;
        sum += *px++ * *py--;

        k--;
    }
    k = srcBLen %0x4;
    while(k>0)
    {
        sum+= *px++ * *py--;
        k--;
    }
    *pOut = sum;
    countr++;

    px = pIn1 +countr;
    py = pSrc2;
    blkCnt--;
}
}
else{
    //IF the srcBLEN is not a multiple of 4 blocksize loop cannot be unrolled by 4
    blkCnt = blkSize2;
    while(blkCnt >0)
    {
        sum = 0.0;
        k = srcBLen;
        while(k>0){
            sum += *px++ * *py--;
            k--;
        }
        *pOut = sum;
        countr++;

        px = pIn1 + countr;
        py = pSrc2;

        pSrc1 = (pIn1 + srcALen) - (srcBLen -1);
        px = pSrc1;

        pSrc2 = pIn2 + (srcBLen-1);
        py = pSrc2;

        while(k>0){
            sum += *px++ * *py--;
            sum += *px++ * *py--;
            sum += *px++ * *py--;
            sum += *px++ * *py--;

            k--;
        }

        k = blkSize3%0x4;
        while(k>0){
            sum += *px++ * *py--;

            k--;
        }
        *pOut++ = sum;

        px = ++pSrc1;
        py = pSrc2;

        blkSize3--;
    }
}
}
}
