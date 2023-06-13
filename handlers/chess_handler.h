#ifndef KAOHE_CHESS_HANDLER_H
#define KAOHE_CHESS_HANDLER_H


#include "events.h"
#include "playingchess.h"
#include "handlers.h"
#include "ihandlers.h"
#include "ievent.h"


using namespace chess_protocal;


typedef std::vector<session*> players_;
typedef std::map<i32, players_> chess_battles_;


//处理下棋事件的处理函数
class Chess_battle_handler : public IHandler
{
public:
    Chess_battle_handler();
    virtual ~Chess_battle_handler();

    //具体的处理函数
    virtual IEvent* handler(IEvent* event);    

private:
    //请求大厅事件的处理函数
    chess_playing_response* handler_chess_event(chess_playing_request* ev);

    //对战的描述
    pthread_mutex_t locker_chess_battles;
    chess_battles_ chess_battles;
};





#endif