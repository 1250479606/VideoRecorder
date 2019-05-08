
/**
 * Ҷ����
 * QQȺ121376426
 * http://blog.yundiantech.com/
 */

#ifndef SAVEVIDEOFILE_H
#define SAVEVIDEOFILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

extern"C"
{
#include "libavutil/mathematics.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"


#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_events.h"

}

struct BufferDataNode
{
    uint8_t * buffer;
    int bufferSize;
    long time;
    BufferDataNode * next;
};

/**
 * @brief The SaveVideoFileThread class
 * ����������Ƶ
 * ��Ҫ�ο��� ffmpeg��output_example.c
 * output_example.c�������аٶ����ص�
 */

class SaveVideoFileThread
{
public:
    explicit SaveVideoFileThread();
    ~SaveVideoFileThread();

    void setFileName(char *str);

    void setQuantity(int value);
    void setWidth(int width,int height);

    bool startWrite();
    bool stopWrite();

    void videoDataQuene_Input(uint8_t * buffer, int size, long time);
    BufferDataNode *videoDataQuene_get(double time);

    void audioDataQuene_Input(uint8_t * buffer,int size);
    BufferDataNode *audioDataQuene_get();

    int audio_input_frame_size;

    void setContainsVideo(bool);
    void setContainsAudio(bool);

    void setVideoFrameRate(int value);

    double getVideoPts();
    double getAudioPts();


//private:

    char filename[128];

    int m_videoFrameRate;

    uint8_t picture_buf[2000*2000*4]; //�����СֻҪ����һ֡h264���У�����ʵ���ϲ���Ҫ��ô��
    bool isStop;

    float t, tincr, tincr2;
    int16_t *samples;
    uint8_t *audio_outbuf;
    int audio_outbuf_size;

    AVFrame *picture, *tmp_picture;
    uint8_t *video_outbuf;
    int video_outbuf_size;

    double audio_pts, video_pts;

    int mBitRate; //video bitRate

    int WIDTH;
    int HEIGHT;

    bool m_containsVideo;
    bool m_containsAudio;

    SDL_mutex *videoMutex;
    BufferDataNode * videoDataQueneHead;
    BufferDataNode * videoDataQueneTail;

    SDL_mutex *audioMutex;
    BufferDataNode * AudioDataQueneHead;
    BufferDataNode * AudioDataQueneTail;

    BufferDataNode * lastVideoNode; //��һ�ε�֡��֡�����ʱ������һ�ε�֡����ȫ��
    int videoBufferCount;
    int audioBufferCount;

    void open_audio(AVFormatContext *oc, AVStream *st);
    void close_audio(AVFormatContext *oc, AVStream *st);

    void open_video(AVFormatContext *oc, AVStream *st);
    void close_video(AVFormatContext *oc, AVStream *st);

    AVStream *add_video_stream(AVFormatContext *oc, AVCodecID codec_id);
    AVStream *add_audio_stream(AVFormatContext *oc, AVCodecID codec_id);

    bool write_audio_frame(AVFormatContext *oc, AVStream *st);
    bool write_video_frame(AVFormatContext *oc, AVStream *st, double time);

};



#endif // SAVEVIDEOFILE_H
