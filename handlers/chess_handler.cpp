#include "chess_handler.h"
#include "dispatchmsgserver.h"
#include <algorithm>

Chess_battle_handler::Chess_battle_handler() : IHandler("下棋事件处理函数")
{
    DispatchMsgServer::getInstance()->subscribeHandlers(EVENT_ID::PLAYING_CHESS_REQUEST, this);
    pthread_mutex_init(&locker_chess_battles, nullptr);
}

Chess_battle_handler::~Chess_battle_handler()
{
    DispatchMsgServer::getInstance()->unsubscribeHandlers(EVENT_ID::PLAYING_CHESS_REQUEST, this);
    pthread_mutex_destroy(&locker_chess_battles);
}


IEvent* Chess_battle_handler::handler(IEvent* event)
{
    EVENT_ID eid = event->getEid();

    if(eid == EVENT_ID::PLAYING_CHESS_REQUEST)
    {
        return handler_chess_event((chess_playing_request*)event);
    }

    return nullptr;
}


//处理下棋事件
chess_playing_response* Chess_battle_handler::handler_chess_event(chess_playing_request* ev)
{
    //请求的对局桌子id
    i32 table_id = ev->getTablenumber();
    // ev->dump(cout);

    //返回的下棋响应
    chess_playing_response* chess_response = nullptr;

    //从对战表中找到对战信息
    thread_mutex_lock(&locker_chess_battles);
    auto iter = chess_battles.find(table_id);

    //桌子上面没有用户
    if(iter == chess_battles.end())                         
    {
        players_ players;
        players.push_back((session*)ev->getSession());
        chess_battles[table_id] = players;
        
        chess_response = new chess_playing_response(RESPONSE_ID::ERRC_SUCCESS, CHESS_CODE::WAITING);
        thread_mutex_unlock(&locker_chess_battles);

        chess_response->setRival(chess_battles[table_id]);
        return chess_response;
    }

    if((*iter).second.size() == 1)
    {
        (*iter).second.push_back((session*)ev->getSession());
        chess_response = new chess_playing_response(RESPONSE_ID::ERRC_SUCCESS, CHESS_CODE::BEGGING);
        thread_mutex_unlock(&locker_chess_battles);

        chess_response->setRival(chess_battles[table_id]);
        return chess_response;
    }

    if((*iter).second.size() == 2)
    {
        auto iter_cs = find((*iter).second.begin(), (*iter).second.end(), (session*)ev->getSession());
        if(iter_cs == (*iter).second.end())
        {
            thread_mutex_unlock(&locker_chess_battles);
            return new chess_playing_response(RESPONSE_ID::ERRC_SUCCESS, CHESS_CODE::NOSEAT);
        }
        else
        {
            chess_response = new chess_playing_response(RESPONSE_ID::ERRC_SUCCESS, CHESS_CODE::PLAYING, ev->getXpos(), ev->getYpos());
            chess_response->setRival(chess_battles[table_id]);
            thread_mutex_unlock(&locker_chess_battles);

            return chess_response;
        }
    }

    return chess_response;
}