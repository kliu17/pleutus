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
ssize_t buffer_read(struct buffer *buf, fstream& fd) {
        size_t count;
        ssize_t len;
        char *end;
        end     = buffer_end(buf);
        count   = buffer_remaining(buf);

        //len = read(fd, end, count);
        fd.read( end, count);

        buf->end += count;
        return count;
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
        cout<<"after read type start: "<<buf->start<<endl;
        cout<<"type=" <<type<<endl;
        size = ouch_out_message_size(type);
        cout<<"size="<<size<<endl;
        if (!size)
                return -1;
        memcpy(msg, start, size);
        cout<<"start="<<buf->start<<endl;
        buffer_advance(buf, size);
       cout<<"after start="<<buf->start<<endl;
        return 0;
}     
int package_header_decode(struct buffer *buf,char *msg) {
        void *start;
        size_t size;
        uint8_t type;
        start = buffer_start(buf);
        size = sizeof(struct package_header);
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

unordered_map<uint16_t,cnt_r> update_cnt_executed(unordered_map<uint16_t,cnt_r> m, int id, int shares, bool cp) {
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

        fstream fd;
        fd.open("OUCHLMM2.incoming.packets", ios::in | ios::binary);

        struct buffer* buff =  buffer_new(BUFF_SIZE);
        buffer_read(buff, fd);
//      while(buff->start <=(BUFF_SIZE -100)){
                //buffer to hold header
                char header[6];
                //buffer to hold message
                ouch_message message[100];

                //read header
                package_header_decode(buff,header);
                struct package_header* h = (struct package_header*)header;

                //read message length
                uint16_t msg_len = buffer_get_le16(buff);
                cout<<buff->start<<endl;

                //read message
                ouch_out_message_decode(buff, message);


                cout << ntohs(h->StreamId)<<endl;
                cout <<ntohl( h->PackageSize)<<endl;
                cout <<ntohs(msg_len)<<endl;
                cout<<message->MessageType<<endl;
                cout <<buff->start<<endl;
//      }


        /* char hbuff[6];
           memcpy(hbuff, buff,6);

           package_header* temp = (struct package_header*)hbuff;
           uint16_t  sid = ntohs(temp->StreamId);
           uint32_t  psize = ntohl((temp->PackageSize));

           char mlen[2];
           memcpy(mlen, buff+99, 2);
           uint16_t* tmp =(uint16_t*)mlen;
           uint16_t message_len = ntohs(*tmp);
         */
}
