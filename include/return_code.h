/*
    CS349 Assignment3 - return_code.h
    Author:- Rohit Rangan
    Author:- Siddharth Ancha

    This file contains the FTP Server return codes.
*/

#ifndef LAB3_RETURN_CODE_H_
#define LAB3_RETURN_CODE_H_

#define OPENING_DATA    150
#define GENERIC_SUCCESS 200
#define SERVICE_READY   220
#define SERVICE_CLOSE   221
#define DATA_CONN_OPEN  225
#define DATA_CONN_CLOSE 226
#define FILE_FOUND      250
#define GENERIC_ERROR   500
#define FILE_NOT_FOUND  550

#endif  /* LAB3_RETURN_CODE_H_ */
