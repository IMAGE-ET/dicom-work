#ifndef __MARSHAL_H__
#define __MARSHAL_H__

#define MARSHAL(TYPE, VAR, BUFFER, BUFLEN, OUTSTREAM) \
do { \
    OUTSTREAM = pb_ostream_from_buffer(BUFFER, BUFLEN); \
    bool status = pb_encode(&OUTSTREAM, TYPE##_fields, &VAR);\
    CHECK_FALSE(__FILE__, status);\
} while(0)

#define UNMARSHAL(TYPE, VAR, BUFFER, BUFLEN, INSTREAM) \
do { \
    INSTREAM = pb_istream_from_buffer(BUFFER, BUFLEN); \
    bool status = pb_decode(&INSTREAM, TYPE##_fields, &VAR);\
    CHECK_FALSE(__FILE__, status);\
} while(0)
#endif
