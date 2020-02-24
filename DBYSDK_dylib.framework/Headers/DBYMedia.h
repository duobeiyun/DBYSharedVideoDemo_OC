//
//  DBYMedia.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/8/12.
//

#ifndef DBYMedia_h
#define DBYMedia_h

typedef struct {
    int width;  //width of video frame
    int height;  //height of video frame
    int yStride;  //stride of Y data buffer
    int uStride;  //stride of U data buffer
    int vStride;  //stride of V data buffer
    void *yBuffer;  //Y data buffer
    void *uBuffer;  //U data buffer
    void *vBuffer;  //V data buffer
}DBYVideoFrame;

typedef struct  {
    int size;
    int bytesPerSample;  //number of bytes per sample: 2 for PCM16
    int channels;  //number of channels (data are interleaved if stereo)
    int sampleRate;  //sampling rate
    void *buffer;  //data buffer
} DBYAudioFrame;

#endif /* DBYMedia_h */
