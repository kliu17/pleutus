#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unordered_map>

#include "ouch_message.h"
#include "buffer.h"

using namespace std;
const int BUFF_SIZE = 1024;

static char recv_buffer[BUFF_SIZE];

/*
 * count result for each stream:
 */
struct cnt_r{
    int stream_id;
    unsigned int num_accepted;
    unsigned int num_system_events;
    unsigned int num_replaced;
    unsigned int num_canceled;
    int executed[2];
    bool is_complete_package;
};

struct buffer *buffer_new(unsigned long capacity) {
        struct buffer *buf;
        buf = (struct buffer *)malloc(sizeof *buf + capacity);
        if (!buf)
                return NULL;
        buf->data       = (char *) buf + sizeof(*buf);
        buf->capacity   = capacity;
        buf->start      = 0;
        buf->end        = 0;
        return buf;
}

void buffer_delete(struct buffer *buf) {
        free(buf);
}

ssize_t buffer_nread(struct buffer *buf, int fd, size_t size) {
        size_t count;
        ssize_t len;
        void *end;
        end     = buffer_end(buf);
        count   = buffer_remaining(buf);
        if (count > size)
                count = size;
        len = read(fd, end, count);
        if (len < 0)
                return len;
        buf->end += len;
        return len;
}

static unsigned long ouch_out_message_size(uint8_t type) {
        switch (type) { 
        case OUCH_MSG_SYSTEM_EVENT:
                return sizeof (struct ouch_msg_system_event);
        case OUCH_MSG_ACCEPTED:
                return sizeof (struct ouch_msg_accepted);
        case OUCH_MSG_REPLACED:
                return sizeof (struct ouch_msg_replaced);
        case OUCH_MSG_CANCELED:
                return sizeof (struct ouch_msg_canceled);
        case OUCH_MSG_EXECUTED:
                return sizeof (struct ouch_msg_executed);
        default:
                break;
        };
        return 0;
}

/**
int ouch_in_message_decode(struct buffer *buf, struct ouch_message *msg) {
        void *start;
        size_t size;
        uint8_t type;
        start = buffer_start(buf);        type = buffer_get_8(buf);
        size = ouch_in_message_size(type);
        if (!size)
                return -1;
        memcpy(msg, start, size);
        buffer_advance(buf, size);
        return 0;
}       
**/

int ouch_out_message_decode(struct buffer *buf, struct ouch_message *msg) {
        void *start;
        size_t size;
        uint8_t type;
        start = buffer_start(buf);
        type = buffer_get_8(buf);
        size = ouch_out_message_size(type);
        if (!size)
                return -1;
        memcpy(msg, start, size);
        buffer_advance(buf, size);
        return 0;
}       

unordered_map<int,cnt_r> update_cnt(unordered_map<int,cnt_r> m, int id, char type, bool cp) {
    if (m.find(id) == m.end()) {
        // no stream id present, so create a new one
        cnt_r p;
        p.stream_id = id;
        p.num_accepted = 0;
        p.num_system_events = 0;
        p.num_replaced = 0;
        p.num_canceled = 0;
        p.executed[0] = 0;
        p.executed[1] = 0;
        p.is_complete_package = true;
        m.insert({id, {p}});
    }
    m[id].is_complete_package = cp;
    if (!cp) {
        m[id].is_complete_package = true;
        return m;
    }
    switch (type) {
        case OUCH_MSG_SYSTEM_EVENT:
                m[id].num_system_events++;
        case OUCH_MSG_ACCEPTED:
                m[id].num_accepted++;
        case OUCH_MSG_REPLACED:
                m[id].num_replaced++;
        case OUCH_MSG_CANCELED:
                m[id].num_canceled++;
        default:
                break;
    }
    return m;
}

unordered_map<uint16_t,cnt_r> update_cnt_executed(unordered_map<uint16_t,cnt_r> m, uint16_t id, uint32_t shares, bool cp) {
    if (m.find(id) == m.end()) {
        // no stream id present, so create a new one
        cnt_r p;
        p.stream_id = id;
        p.num_accepted = 0;
        p.num_system_events = 0;
        p.num_replaced = 0;
        p.num_canceled = 0;
        p.executed[0] = 0;
        p.executed[1] = 0;
        p.is_complete_package = true;
        m.insert({id, {p}});
    }
    m[id].is_complete_package = cp;
    if (!cp) {
        m[id].is_complete_package = true;
        return m;
    }
    m[id].executed[0]++;
    m[id].executed[1] += shares;
    return m;
}

void print_result(unordered_map<uint16_t,cnt_r> m) {
    cnt_r totals;
    totals.num_accepted = 0;
    totals.num_system_events = 0;
    totals.num_replaced = 0;
    totals.num_canceled = 0;
    totals.executed[0] = 0;
    totals.executed[1] = 0;

    if (m.size()<=0)
        cout << "\nNo values exist in the count result table.";

    for (auto it=m.begin(); it!=m.end(); it++) {
        cout << "\nStream " << it->first << "\n";
        cout << "Accepted: " << it->second.num_accepted << " messages" << "\n";
        cout << "System Event: " << it->second.num_system_events << " messages" << "\n";
        cout << "Replaced: " << it->second.num_replaced << " messages" << "\n";
        cout << "Canceled: " << it->second.num_canceled << " messages" << "\n";
        cout << "Executed: " << it->second.executed[0] << " messages: " << it->second.executed[1] << "executed shares" << "\n";
        totals.num_accepted += it->second.num_accepted;
        totals.num_system_events += it->second.num_system_events;
        totals.num_replaced += it->second.num_replaced;
        totals.num_canceled += it->second.num_canceled;
        totals.executed[0] += it->second.executed[0];
        totals.executed[1] += it->second.executed[1];
    }

    cout << endl;
    cout << "\nTotals: " << "\n";
    cout << "Accepted: " << totals.num_accepted << " messages" << "\n"; 
    cout << "System Event: " << totals.num_system_events << " messages" << "\n";
    cout << "Replaced: " << totals.num_replaced << " messages" << "\n";
    cout << "Canceled: " << totals.num_canceled << " messages" << "\n";
    cout << "Executed: " << totals.executed[0] << " messages: " << totals.executed[1] << "executed shares" << "\n";
}

int main() {
    unordered_map<int,cnt_r> res;

/*

    sid=4;
    cnt_r p;
    p.stream_id = 4;
    p.num_accepted = 1;
    p.num_system_events = 0;
    p.num_replaced = 0;
    p.num_canceled = 0;
    p.executed[0] = 0;
    p.executed[1] = 0;
    p.is_complete_package = false;

    res.insert({sid, {p}});
*/

   // char buff[BUFF_SIZE];
    fstream fd;
    fd.open("OUCHLMM2.incoming.packets", ios::in | ios::binary);

    //myFile.read (buff,  BUFF_SIZE);
  struct buffer* buff =  buffer_new(BUFF_SIZE); 
  buffer_read(buff, fd);
  
    /* char hbuff[6];
    memcpy(hbuff, buff,6);	 	
    
     package_header* temp = (struct package_header*)hbuff;
    uint16_t  sid = ntohs(temp->StreamId);
    uint32_t  psize = ntohl((temp->PackageSize));
    
     char mlen[2];
    memcpy(mlen, buff+99, 2);
    uint16_t* tmp =(uint16_t*)mlen;
    uint16_t message_len = ntohs(*tmp);
    


   cout << "stream #: " <<  sid << endl;
   cout << "package size #: " <<  psize << endl;
   cout << "message size #: " <<  message_len << endl; */
   return 0;    


}
/*        struct ouch_message *msg = (void *) recv_buffer;
        struct buffer *buf;
        buf = buffer_new(1024);
        int fd;
        fd = open("./" "OUCHLMM2.incoming.packets", O_RDONLY);

        unordered_map<string, int> countResults[256];

    //ifstream file ("OUCHLMM2.incoming.packets", ios::in|ios::binary);

        fail_if(fd < 0);

        fail_if(buffer_xread(buf, fd) < 0);

        fail_if(ouch_in_message_decode(buf, msg) < 0);
*/
/*
        assert_int_equals(BOE_MAGIC, msg->header.StartOfMessage);
        assert_int_equals(8, msg->header.MessageLength);
        assert_int_equals(LogoutRequest, msg->header.MessageType);
        assert_int_equals(0, msg->header.MatchingUnit);
        assert_int_equals(0, msg->header.SequenceNumber);

        countResults[sid]["Accepted"] ++;
        countResults[sid]["Event"] ++;
        countResults[sid]["Replaced"] ++;
        countResults[sid]["Cancelled"] ++;
        countResults[sid]["Executed"] ++;
        countResults[sid]["ExecutedShares"] = countResults[sid]["ExecutedShares"] + msg->ExecutedShares;

*/
        
//        buffer_delete(buf);
//        fail_if(close(fd) < 0);

/*
    unsigned short streamid;
    int packlen;
    char buff[128];
    char ch[2];
    char level[4];
    char thetime[4];

    if (file.is_open()) {
       while (!file.eof()) {
          file.read(buff, 2);
          streamid=(unsigned short)buff;
          file.read(buff, 4);
          packlen=atoi(buff);

          cout << streamid << endl;
          cout << packlen << endl;
          break;
       }
       file.close();
    }
    printf("hello, world\n");
*/
//    return 0;
//}
