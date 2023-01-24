#include "Eyer2DCrop.hpp"

namespace Eyer
{
    Eyer2DCrop::Eyer2DCrop(float _canvasWidth, float _canvasHeight)
    {
        canvasWidth = _canvasWidth;
        canvasHeight = _canvasHeight;
    }

    Eyer2DCrop::~Eyer2DCrop()
    {

    }

    Eatrix4x4<float> & Eyer2DCrop::Crop2(float viewWidth, float viewHeight, EyerCropType cropType)
    {
        if(cropType == EyerCropType::FIT_XY){
            Eatrix4x4<float> ortho;
            ortho.SetOrtho(0.0, canvasWidth, 0.0, canvasHeight, 0.0, -1.0);

            Eatrix4x4<float> view;
            view.LookAt(0.0, 0.0, 1.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

            Eatrix4x4<float> modelScale;
            modelScale.SetScale(canvasWidth * 0.5, canvasHeight * 0.5, 1.0);

            Eatrix4x4<float> modelTrans;
            modelTrans.SetTrans(canvasWidth * 0.5, canvasHeight * 0.5, 1.0);

            res = ortho * modelTrans * modelScale;
        }
        if(cropType == EyerCropType::CENTER_CROP){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            Eatrix4x4<float> modelMoveTrans;
            if (viewAspect < canvasAspect) {
                targetH = 1.0 / viewAspect * canvasWidth;
                targetW = canvasWidth;

                modelMoveTrans.SetTrans(0.0, - (targetH - canvasHeight) / 2, 0.0);
            }
            else {
                targetW = viewAspect * canvasHeight;
                targetH = canvasHeight;

                // TODO No Test
                modelMoveTrans.SetTrans(- (targetW - canvasWidth) / 2, 0.0, 0.0);
            }

            Eatrix4x4<float> ortho;
            ortho.SetOrtho(0.0, canvasWidth, 0.0, canvasHeight, 0.0, -1.0);

            Eatrix4x4<float> view;
            view.LookAt(0.0, 0.0, 1.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

            Eatrix4x4<float> modelScale;
            modelScale.SetScale(targetW * 0.5, targetH * 0.5, 1.0);

            Eatrix4x4<float> modelTrans;
            modelTrans.SetTrans(targetW * 0.5, targetH * 0.5, 1.0);

            res = ortho * modelMoveTrans * modelTrans * modelScale;
        }

        if(cropType == EyerCropType::FIT_CENTER){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            Eatrix4x4<float> modelMoveTrans;
            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
                x = (canvasWidth - targetW) / 2;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
                y = (canvasHeight - targetH) / 2;
            }

            modelMoveTrans.SetTrans(x, y, 0.0);

            Eatrix4x4<float> ortho;
            ortho.SetOrtho(0.0, canvasWidth, 0.0, canvasHeight, 0.0, -1.0);

            Eatrix4x4<float> view;
            view.LookAt(0.0, 0.0, 1.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

            Eatrix4x4<float> modelScale;
            modelScale.SetScale(targetW * 0.5, targetH * 0.5, 1.0);

            Eatrix4x4<float> modelTrans;
            modelTrans.SetTrans(targetW * 0.5, targetH * 0.5, 1.0);

            res = ortho * modelMoveTrans * modelTrans * modelScale;
        }

        return res;
    }


    Eatrix4x4<float> & Eyer2DCrop::Crop(float viewWidth, float viewHeight, EyerCropType cropType)
    {
        // 缩放坐标系
        ortho.SetOrtho(0.0, canvasWidth, 0.0, canvasHeight, 0.0, 100);

        // 缩放小图
        s.SetScale(0.5, -0.5, 1.0);
        t.SetTrans(1.0, -1.0, 0.0);

        // 进行 Crop
        if(cropType == EyerCropType::FIT_XY){
            scale.SetScale(canvasWidth,  canvasHeight, 1.0);
            trans.SetTrans(0.0, 0.0, 0.0);
        }
        else if(cropType == EyerCropType::FIT_CENTER){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
                x = (canvasWidth - targetW) / 2;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
                y = (canvasHeight - targetH) / 2;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        else if(cropType == EyerCropType::FIT_START){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        else if(cropType == EyerCropType::FIT_END){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
                x = canvasWidth - targetW;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
                y = canvasHeight - targetH;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        else if(cropType == EyerCropType::CENTER_CROP){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = 1.0 / viewAspect * canvasWidth;
                targetW = canvasWidth;
            }
            else {
                targetW = viewAspect * canvasHeight;
                targetH = canvasHeight;
            }
            scale.SetScale(targetW,  targetH, 1.0);
        }

        res = res.Eye() * ortho * trans * scale * s * t;

        return res;
    }
}