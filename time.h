#ifndef TIME_H
#define TIME_H

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    int  get_ticks();
private:
    int start_tick_;
    int paused_tick_;

    bool is_paused_;
    bool is_started_;

};


#endif // TIME_H
