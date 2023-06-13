#ifndef KAOHE_PLAYINGCHESS_H
#define KAOHE_PLAYINGCHESS_H

#include "ievent.h"
#include "chess.pb.h"
#include "session.h"
#include "ievent.h"
#include <map>
#include <vector>


using namespace chess_protocal;


//下棋的状态代码
enum CHESS_CODE
{
    WAITING  = 0,   //游戏等待玩家代码
    BEGGING  = 1,   //游戏准备代码
    PLAYING  = 2,   //正在进行代码
    NOSEAT   = 3,   //不能进入这场游戏
    ENTER    = 4    //等待进入游戏 
};


//下棋的事件
class chess_playing_request : public IEvent
{
public:
    chess_playing_request(i32 hall_no, i32 table_no, i32  game_stat = 4, i32 x = -1, i32 y = -1) : IEvent(EVENT_ID::PLAYING_CHESS_REQUEST)
    {
        chess_request_.set_hall_number(hall_no);
        chess_request_.set_table_number(table_no);
        chess_request_.set_game_stat(game_stat);
        chess_request_.set_x_pos(x);
        chess_request_.set_y_pos(y);
    }

    //获取消息的属性
    i32 getHallnumber() const
    {
        return chess_request_.hall_number();
    }

    i32 getTablenumber() const
    {
        return chess_request_.table_number();
    }

    i32 getGameStat() const
    {
        return chess_request_.game_stat();
    }

    i32 getXpos() const
    {
        return chess_request_.x_pos();
    }

    i32 getYpos() const
    {
        return chess_request_.y_pos();
    }

    //获取消息的大小
    virtual i32 getMessageSize() {return chess_request_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return chess_request_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os)
    {
        IEvent::dump(os);
        os << "大厅编号：" << chess_request_.hall_number() << " "
           << "桌子编号：" << chess_request_.table_number();
        os << std::endl;
        return os;
    }

private:
    playing_chess_request chess_request_;
};



typedef std::vector<session*> players_;
class chess_playing_response : public IEvent
{
public:
    chess_playing_response(RESPONSE_ID repid, i32  game_stat, i32 x_pos = -1, i32 y_pos = -1) : IEvent(EVENT_ID::PLAYING_CHESS_RESPONSE)
    {
        chess_response_.set_response_code((i32)repid);
        chess_response_.set_data(get_response_describe(repid));
        chess_response_.set_game_stat(game_stat);
        chess_response_.set_x_pos(x_pos);
        chess_response_.set_y_pos(y_pos);
    }

    //获取消息的属性
    i32 getXPos() const {return chess_response_.x_pos();}
    i32 getYpos() const {return chess_response_.y_pos();}
    RESPONSE_ID getResponseID() const {return (RESPONSE_ID)chess_response_.response_code();}
    std::string getData() const {return chess_response_.data();}
    i32 getGamestat() const {return chess_response_.game_stat();}

    //获取消息的大小
    virtual i32 getMessageSize() {return chess_response_.ByteSize();}

    //设置对手会话
    players_ getRival() {return rivals_;}
    void setRival(players_ rivals) {rivals_ = rivals;}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return chess_response_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os)
    {
        IEvent::dump(os);
        os << "响应编号：" << chess_response_.response_code() << " "
           << "响应状态：" << chess_response_.data() << " "
           << "游戏状态：" << chess_response_.game_stat() << " "
           << "坐标："    << "[" << chess_response_.x_pos() << ", " << chess_response_.y_pos() << "]";
        os << std::endl;
        return os;
    }

private:
    playing_chess_response chess_response_;
    //对战的玩家会话
    players_ rivals_;
};






#endif