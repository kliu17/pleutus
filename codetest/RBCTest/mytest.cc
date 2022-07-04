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

int ouch_out_message_decode(struct buffer *buf, char *msg, char& mtype,  uint32_t package_size, uint16_t msg_size) {
        void *start;
        size_t size;
        uint8_t type;
        start = buffer_start(buf);
        //	type = buffer_get_8(buf);
	char msg_type=buf->data[(buf->start)+1];
	
	cout<<"inside decode type="<<msg_type<<endl;
	mtype = msg_type;	
	if(package_size >= msg_size + 2){
            size = ouch_out_message_size(msg_type);
            if (!size)
                return -1;
            memcpy(msg, start, size);
            buffer_advance(buf, size);
	} else {
            memcpy(msg, start, package_size-2);
            buffer_advance(buf, package_size-2);
	}

        return 0;
}     

int package_header_decode(struct buffer *buf,char *msg) {
        void *start;
        size_t size;
        start = buffer_start(buf);
        size = sizeof(struct package_header);
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
    if (!cp && !m[id].is_complete_package) {
        m[id].is_complete_package = true;
        return m;
    }
    m[id].is_complete_package = cp;
    switch (type) {
        case OUCH_MSG_SYSTEM_EVENT:
                m[id].num_system_events++;
                break;
        case OUCH_MSG_ACCEPTED:
                m[id].num_accepted++;
                break;
        case OUCH_MSG_REPLACED:
                m[id].num_replaced++;
                break;
        case OUCH_MSG_CANCELED:
                m[id].num_canceled++;
                break;
        default:
                break;
    }
    return m;
}

unordered_map<int,cnt_r> update_cnt_executed(unordered_map<int,cnt_r> m, int id, int shares, bool cp) {
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
    if (!cp && !m[id].is_complete_package) {
        m[id].is_complete_package = true;
        return m;
    }
    m[id].is_complete_package = cp;
    m[id].executed[0]++;
    m[id].executed[1] += shares;
    return m;
}

void print_result(unordered_map<int,cnt_r> m) {
    cnt_r totals;
    totals.num_accepted = 0;
    totals.num_system_events = 0;
    totals.num_replaced = 0;
    totals.num_canceled = 0;
    totals.executed[0] = 0;
    totals.executed[1] = 0;

    if (m.size()<=0)
        cout << "\nNo values exist in the count result table.";

    cout << "++++" <<endl;
    for (auto it=m.begin(); it!=m.end(); it++) {
        cout << "\nStream " << it->first << "\n";
        cout << "Accepted: " << it->second.num_accepted << " messages" << "\n";
        cout << "System Event: " << it->second.num_system_events << " messages" << "\n";
        cout << "Replaced: " << it->second.num_replaced << " messages" << "\n";
        cout << "Canceled: " << it->second.num_canceled << " messages" << "\n";
        cout << "Executed: " << it->second.executed[0] << " messages: " << it->second.executed[1] << " executed shares" << "\n";
        cout << "NoInComplete: " << it->second.is_complete_package << "\n";
        totals.num_accepted += it->second.num_accepted;
        totals.num_system_events += it->second.num_system_events;
        totals.num_replaced += it->second.num_replaced;
        totals.num_canceled += it->second.num_canceled;
        totals.executed[0] += it->second.executed[0];
        totals.executed[1] += it->second.executed[1];
    }

    cout << "++++" <<endl;
    cout << endl;
    cout << "\nTotals: " << "\n";
    cout << "Accepted: " << totals.num_accepted << " messages" << "\n"; 
    cout << "System Event: " << totals.num_system_events << " messages" << "\n";
    cout << "Replaced: " << totals.num_replaced << " messages" << "\n";
    cout << "Canceled: " << totals.num_canceled << " messages" << "\n";
    cout << "Executed: " << totals.executed[0] << " messages: " << totals.executed[1] << " executed shares" << "\n";
}

int main() {
    unordered_map<int,cnt_r> res;

    fstream fd;
    fd.open("OUCHLMM2.incoming.packets", ios::in | ios::binary);

    fd.seekg (0, ios::end);
    unsigned long bufferlength = fd.tellg();
    fd.seekg (0, ios::beg);

    cout << bufferlength << endl;
    //struct buffer* buff =  buffer_new(BUFF_SIZE);
    bufferlength = 8800;
    struct buffer* buff =  buffer_new(bufferlength);

    buffer_read(buff, fd);
    cout << buff->capacity << endl;
    while (buff->start < bufferlength){
        //buffer to hold header
        char header[sizeof (struct package_header)];

        //buffer to hold message
        char message[100];

        //read header
        package_header_decode(buff,header);
        struct package_header* h = (struct package_header*)header;
	uint32_t package_size = ntohl(h->PackageSize);
	uint16_t stream_id = ntohs(h->StreamId);
		
	uint16_t msg_len;	
		
	char msg_type;

	if(res.find(stream_id) != res.end()){ // stream not first time appear
	    if(!res[stream_id].is_complete_package ){ //second half - no message length field
	        cout<<"inside pkg size"<<package_size;
		buffer_advance(buff, package_size);
		cout<<"seconf half of incomplete message"<<endl;
            } else { //not second half, read messae length
		//read message length
                msg_len = ntohs(buffer_get_le16(buff));

                //read message
               	ouch_out_message_decode(buff, message,msg_type, package_size, msg_len);
            } 						

	} else { //the stream is first time- need to read message length field 
            //read message length
            msg_len = ntohs(buffer_get_le16(buff));

            //read message
            ouch_out_message_decode(buff, message,msg_type,  package_size, msg_len);
			
	}
		
	//true is complete package, update result
        bool flag = true;
        if(package_size != msg_len + 2){
            flag = false;	
            cout<<"incomplete message"<<endl;
	}

	if(msg_type == OUCH_MSG_EXECUTED){
            res = update_cnt_executed(res, (int)stream_id, 10, flag);
	} else {
	    res = update_cnt(res, (int)stream_id ,  msg_type, flag);
	}

        cout <<"stream id:"<< stream_id<<endl;
        cout <<"package size: " << package_size<<endl;
        cout <<"message len"<<msg_len<<endl;
	cout <<"out msg type:" << msg_type<<endl;
        cout <<"buffer position: " << buff->start << endl;
	cout <<"*********"<<endl;
    }
    buffer_delete(buff);

    print_result(res);
}
