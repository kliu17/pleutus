#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include "ouch_message.h"
#include "buffer.h"

using namespace std;
const int BUFF_SIZE = 1024;

static char recv_buffer[BUFF_SIZE];

/*
 * count result for each stream:
 */
struct count_res{
    int stream_id = -1;
    unsigned int num_accepted;
    unsigned int num_system_events;
    unsigned int num_replaced;
    unsigned int num_canceled;
    int executed[2];
    bool is_complete_package = true;
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

void printResult(vector<count_res> vect) {
    count_res totals;
    totals.num_accepted = 0;
    totals.num_system_events = 0;
    totals.num_replaced = 0;
    totals.num_canceled = 0;
    totals.executed[0] = 0;
    totals.executed[1] = 0;

    if(vect.empty())
        cout << "\nNo values exist in the count result table.";
    else
        for (int count = 0; count < vect.size(); count++) {
            cout << "\nStream " << vect[count].stream_id << " messages" << "\n";
            cout << "Accepted: " << vect[count].num_accepted << " messages" << "\n";
            cout << "System Event: " << vect[count].num_system_events << " messages" << "\n";
            cout << "Replaced: " << vect[count].num_replaced << " messages" << "\n";
            cout << "Canceled: " << vect[count].num_canceled << " messages" << "\n";
            cout << "Executed: " << vect[count].executed[0] << " messages: " << vect[count].executed[1] << "executed shares" << "\n";
            totals.num_accepted += vect[count].num_accepted;
            totals.num_system_events += vect[count].num_system_events;
            totals.num_replaced += vect[count].num_replaced;
            totals.num_canceled += vect[count].num_canceled;
            totals.executed[0] += vect[count].executed[0];
            totals.executed[1] += vect[count].executed[1];
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
    vector <count_res> res;

/*
    count_res p;
    p.stream_id = 4;
    p.num_accepted = 1;
    p.num_system_events = 0;
    p.num_replaced = 0;
    p.num_canceled = 0;
    p.executed[0] = 0;
    p.executed[1] = 0;
    p.is_complete_package = false;

    res.push_back(p);
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
