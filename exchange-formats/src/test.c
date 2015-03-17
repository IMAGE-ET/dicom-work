#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "ptt-session.pb.h"
#include "marshal.h"
#include "my-pjlib-utils.h"

int main() {
    uint8_t buffer[128];

    PTTSession ptt_session;
    strncpy(ptt_session.ipaddr, "localhost", sizeof(ptt_session.ipaddr));
    ptt_session.port = 1234;

    pb_ostream_t stream;
    MARSHAL(PTTSession, ptt_session, buffer, sizeof(buffer), stream);

    printf("Encode result bytes written %ld\n", stream.bytes_written);

    PTTSession session;

    pb_istream_t istream;
    UNMARSHAL(PTTSession, session, buffer, stream.bytes_written, istream);

//    pb_istream_t istream = pb_istream_from_buffer(buffer, stream.bytes_written);
//    status = pb_decode(&istream, PTTSession_fields, &session);
    printf("Decode result {%s, %d}\n", session.ipaddr, session.port);
    return 0;
}
