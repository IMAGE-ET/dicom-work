#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "ptt-session.pb.h"
int main() {
    bool status;
    uint8_t buffer[128];

    PTTSession ptt_session;
    strncpy(ptt_session.ipaddr, "localhost", sizeof(ptt_session.ipaddr));
    ptt_session.port = 1234;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    status = pb_encode(&stream, PTTSession_fields, &ptt_session);
    printf("Encode result %d, bytes written %ld\n", status, stream.bytes_written);

    PTTSession session;
    pb_istream_t istream = pb_istream_from_buffer(buffer, stream.bytes_written);
    status = pb_decode(&istream, PTTSession_fields, &session);
    printf("Decode result %d, {%s, %d}\n", status, session.ipaddr, session.port);
    return 0;
}
