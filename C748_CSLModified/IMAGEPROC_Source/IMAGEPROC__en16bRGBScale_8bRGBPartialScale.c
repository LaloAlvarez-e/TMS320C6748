/*
 * IMAGEPROC__en16bRGBScale_8bRGBPartialScale.c
 *
 *  Created on: 28/08/2019
 *      Author: Lalo
 */




#include <ImageProcessing.h>

#define OPT (20)
IMAGPROC_nStatus IMAGEPROC__en16bRGBScale_8bRGBPartialScale(LCDC_TFT_TypeDef *psLayerSource, LCDC_TFT_TypeDef*psLayerDestRed, LCDC_TFT_TypeDef * psLayerDestGreen,LCDC_TFT_TypeDef *psLayerDestBlue,LCDC_DIMENSIONS_TypeDef sDim)
{

    LCDC_TFT_TypeDef sLayer;
    LCDC_DIMENSIONS_TypeDef sDimLayer;
    int32_t s32Index=0;

    uint16_t u16DimX0=sDim.X[0];
    uint16_t u16DimX1=sDim.X[1];
    uint16_t u16DimX2=sDim.X[2];
    uint16_t u16DimX3=sDim.X[3];
    uint16_t u16DimY0=sDim.Y[0];
    uint16_t u16DimY1=sDim.Y[1];
    uint16_t u16DimY2=sDim.Y[2];
    uint16_t u16DimY3=sDim.Y[3];

    uint32_t u32LayerDestRedWidthTotal=psLayerDestRed->layerWidthTotal;
    uint32_t u32LayerDestGreenWidthTotal=psLayerDestGreen->layerWidthTotal;
    uint32_t u32LayerDestBlueWidthTotal=psLayerDestBlue->layerWidthTotal;
    uint32_t u32LayerDestRedHeightTotal=psLayerDestRed->layerHeightTotal;
    uint32_t u32LayerDestGreenHeightTotal=psLayerDestGreen->layerHeightTotal;
    uint32_t u32LayerDestBlueHeightTotal=psLayerDestBlue->layerHeightTotal;

    uint32_t u32LayerSourceWidthTotal=psLayerSource->layerWidthTotal;
    uint32_t u32LayerSourceHeightTotal=psLayerSource->layerHeightTotal;

    uint16_t u16DimWidth=sDim.width;
    uint16_t u16DimHeight=sDim.height;

    uint16_t u16Aux=0;

    uint8_t u8Mod=0;

    if((psLayerSource->variableType != VARIABLETYPE_enUSHORT) || (psLayerDestRed->variableType != VARIABLETYPE_enUCHAR)
            || (psLayerDestGreen->variableType != VARIABLETYPE_enUCHAR)
            || (psLayerDestBlue->variableType != VARIABLETYPE_enUCHAR))
            return IMAGPROC_enERROR;

    if(u16DimX0>u32LayerSourceWidthTotal)
        return IMAGPROC_enERROR;
    if(u16DimX1>u32LayerDestRedWidthTotal)
        return IMAGPROC_enERROR;
    if(u16DimX2>u32LayerDestBlueWidthTotal)
        return IMAGPROC_enERROR;
    if(u16DimX3>u32LayerDestGreenWidthTotal)
        return IMAGPROC_enERROR;

    if(u16DimY0>u32LayerSourceHeightTotal)
        return IMAGPROC_enERROR;
    if(u16DimY1>u32LayerDestRedHeightTotal)
        return IMAGPROC_enERROR;
    if(u16DimY2>u32LayerDestGreenHeightTotal)
        return IMAGPROC_enERROR;
    if(u16DimY3>u32LayerDestBlueHeightTotal)
        return IMAGPROC_enERROR;

    if((u16DimWidth+ u16DimX0)>u32LayerSourceWidthTotal)
        u16DimWidth= u32LayerSourceWidthTotal- u16DimX0;
    if((u16DimHeight+ u16DimY0)>u32LayerSourceHeightTotal)
        u16DimHeight= u32LayerSourceHeightTotal- u16DimY0;

    if((u16DimWidth+ u16DimX1)>u32LayerDestRedWidthTotal)
        u16DimWidth= u32LayerDestRedWidthTotal- u16DimX1;
    if((u16DimHeight+ u16DimY1)>u32LayerDestRedHeightTotal)
        u16DimHeight= u32LayerDestRedHeightTotal- u16DimY1;


    if((u16DimWidth+ u16DimX2)>u32LayerDestGreenWidthTotal)
        u16DimWidth= u32LayerDestGreenWidthTotal- u16DimX2;
    if((u16DimHeight+ u16DimY2)>u32LayerDestGreenHeightTotal)
        u16DimHeight= u32LayerDestGreenHeightTotal- u16DimY2;


    if((u16DimWidth+ u16DimX3)>u32LayerDestBlueWidthTotal)
        u16DimWidth= u32LayerDestBlueWidthTotal- u16DimX3;
    if((u16DimHeight+ u16DimY3)>u32LayerDestBlueHeightTotal)
        u16DimHeight= u32LayerDestBlueHeightTotal- u16DimY3;

    Cache__vWbInvL2 ((uint32_t)psLayerSource->layerDataAddress,psLayerSource->layerWidthTotal*psLayerSource->layerHeightTotal*2);
    u8Mod=(u16DimWidth*u16DimHeight)%OPT;
    if(u8Mod)
        u8Mod=OPT-u8Mod;
    uint16_t* restrict pu16LayerSource =(uint16_t *) memalign(1024*1024,sizeof(uint16_t)*u16DimWidth*u16DimHeight+u8Mod);
    uint8_t* restrict pu8LayerDestRed =(uint8_t *) memalign(1024*1024,sizeof(uint8_t)*u16DimWidth*u16DimHeight+u8Mod);
    uint8_t* restrict pu8LayerDestGreen =(uint8_t *) memalign(1024*1024,sizeof(uint8_t)*u16DimWidth*u16DimHeight+u8Mod);
    uint8_t* restrict pu8LayerDestBlue =(uint8_t *) memalign(1024*1024,sizeof(uint8_t)*u16DimWidth*u16DimHeight+u8Mod);

    uint16_t* pu16LayerSourceInitial=pu16LayerSource;
    uint8_t* pu8LayerDestRedInitial=pu8LayerDestRed;
    uint8_t* pu8LayerDestGreenInitial=pu8LayerDestGreen;
    uint8_t* pu8LayerDestBlueInitial=pu8LayerDestBlue;

    if((pu16LayerSourceInitial == 0) || (pu8LayerDestRedInitial==0) || (pu8LayerDestGreenInitial==0) || (pu8LayerDestBlueInitial==0))
    {
        free(pu8LayerDestBlueInitial);
        free(pu8LayerDestGreenInitial);
        free(pu8LayerDestRedInitial);
        free(pu16LayerSourceInitial);
        return IMAGPROC_enALLOCERROR;
    }

    Cache__vWbInvL2 ((uint32_t)pu16LayerSource,u16DimWidth*u16DimHeight*2);
    sLayer.layerWidthTotal=u16DimWidth;
    sLayer.layerHeightTotal=u16DimHeight;
    sDimLayer.width=u16DimWidth;
    sDimLayer.height=u16DimHeight;

    sDimLayer.X[1]=0;
    sDimLayer.Y[1]=0;
    sDimLayer.X[0]=u16DimX0;
    sDimLayer.Y[0]=u16DimY0;
    sLayer.variableType=VARIABLETYPE_enUSHORT;
    sLayer.layerDataAddress=(uint32_t)pu16LayerSource;
    LCDC__enLayer_Copy(psLayerSource,&sLayer,sDimLayer);

    _nassert ((int)(pu16LayerSource) % 8 == 0);
    _nassert ((int)(pu8LayerDestRed) % 8 == 0);
    _nassert ((int)(pu8LayerDestGreen) % 8 == 0);
    _nassert ((int)(pu8LayerDestBlue) % 8 == 0);


    #pragma UNROLL(OPT)
    #pragma MUST_ITERATE (OPT,,OPT)
    for(s32Index=0;s32Index<(u16DimHeight*u16DimWidth)+u8Mod;s32Index++)
    {
        u16Aux=*((uint16_t*)pu16LayerSource);
        *((uint8_t*)pu8LayerDestRed)= (u16Aux>>11)&0x1F;
        *((uint8_t*)pu8LayerDestGreen)= (u16Aux>>5)&0x3F;
        *((uint8_t*)pu8LayerDestBlue)= (u16Aux&0x001F);
        pu16LayerSource++;
        pu8LayerDestRed++;
        pu8LayerDestGreen++;
        pu8LayerDestBlue++;
    }
    Cache__vWbL2 ((uint32_t)pu8LayerDestRedInitial, u16DimHeight*u16DimWidth);
    Cache__vWbL2 ((uint32_t)pu8LayerDestGreenInitial, u16DimHeight*u16DimWidth);
    Cache__vWbL2 ((uint32_t)pu8LayerDestBlueInitial, u16DimHeight*u16DimWidth);

    sLayer.variableType=VARIABLETYPE_enUCHAR;
    sDimLayer.X[1]=u16DimX1;
    sDimLayer.Y[1]=u16DimY1;
    sDimLayer.X[0]=0;
    sDimLayer.Y[0]=0;
    sLayer.layerDataAddress=(uint32_t)pu8LayerDestRedInitial;
    LCDC__enLayer_Copy(&sLayer,psLayerDestRed,sDimLayer);

    sDimLayer.X[1]=u16DimX2;
    sDimLayer.Y[1]=u16DimY2;
    sLayer.layerDataAddress=(uint32_t)pu8LayerDestGreenInitial;
    LCDC__enLayer_Copy(&sLayer,psLayerDestGreen,sDimLayer);

    sDimLayer.X[1]=u16DimX3;
    sDimLayer.Y[1]=u16DimY3;
    sLayer.layerDataAddress=(uint32_t)pu8LayerDestBlueInitial;
    LCDC__enLayer_Copy(&sLayer,psLayerDestBlue,sDimLayer);

    free(pu8LayerDestBlueInitial);
    free(pu8LayerDestGreenInitial);
    free(pu8LayerDestRedInitial);
    free(pu16LayerSourceInitial);
    return IMAGPROC_enOK;
}





