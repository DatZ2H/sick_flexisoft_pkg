#ifndef FLEXISOFT_LIBRARY_H
#define FLEXISOFT_LIBRARY_H
#include <iostream>
#include <future>
#include <functional>

#include <errno.h>
#include <string.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/signal.h>

#include <ros/ros.h>
#include <boost/thread.hpp>
#include <sstream>
#include "std_msgs/Bool.h"


using namespace std;
	uint16_t test_array[25]={0x0000 , 0x0000 , 0x0000 , 0x0000 , 0x033F , 0x0000 , 0x0000 , 0x1191 , 0x0001 , 0x0000 , 0x0000 , 0x0100 , 0x310F , 0x310F , 0x0000 , 0x0000 , 0xF151 , 0x1F01 , 0x0000 , 0x0000 , 0x0F30 , 0x0F30 , 0xFFFF , 0xFFFF , 0x0000};

///Function Code
#define     READ_COILS        0x01
#define     READ_INPUT_BITS   0x02
#define     READ_REGS         0x03
#define     READ_INPUT_REGS   0x04
#define     WRITE_COIL        0x05
#define     WRITE_REG         0x06
#define     WRITE_COILS       0x0F
#define     WRITE_REGS        0x10

///Exception Codes

#define    EX_ILLEGAL_FUNCTION  0x01 // Function Code not Supported
#define    EX_ILLEGAL_ADDRESS   0x02 // Output Address not exists
#define    EX_ILLEGAL_VALUE     0x03 // Output Value not in Range
#define    EX_SERVER_FAILURE    0x04 // Slave Deive Fails to process request
#define    EX_ACKNOWLEDGE       0x05 // Service Need Long Time to Execute
#define    EX_SERVER_BUSY       0x06 // Server Was Unable to Accept MB Request PDU
#define    EX_NEGATIVE_ACK      0x07
#define    EX_MEM_PARITY_PROB   0x08
#define    EX_GATEWAY_PROBLEMP  0x0A // Gateway Path not Available
#define    EX_GATEWYA_PROBLEMF  0x0B // Target Device Failed to Response
#define    EX_BAD_DATA          0XFF // Bad Data lenght or Address

#define    BAD_CON              -1


#define    PARA_READ_INPUT_DATA_SET_01 0x0001
#define    PARA_READ_INPUT_DATA_SET_02 0x0001
#define    PARA_READ_INPUT_DATA_SET_03 0x0001
#define    PARA_READ_INPUT_DATA_SET_04 0x0001

#define    PARA_WRITE_OUTPUT_DATA_SET_01 0x000A
#define    PARA_WRITE_OUTPUT_DATA_SET_02 0x000A
#define    PARA_WRITE_OUTPUT_DATA_SET_03 0x000A
#define    PARA_WRITE_OUTPUT_DATA_SET_04 0x000A
#define    PARA_WRITE_OUTPUT_DATA_SET_05 0x000A

#define    PARA_CONFIGURE_INPUT_DATA_SET_01 0x0001
#define    PARA_CONFIGURE_INPUT_DATA_SET_02 0x0001
#define    PARA_CONFIGURE_INPUT_DATA_SET_03 0x0001
#define    PARA_CONFIGURE_INPUT_DATA_SET_04 0x0001

#define    PARA_CONFIGURE_INPUT_ENABLE_COS 0x0000

#define     CMD_MODE_POLL_REQUEST 0x00F1
#define     CMD_MODE_POLL_RESONSE 0x001F

#define     CMD_MODE_AUTO_REQUEST 0x00E1
#define     CMD_MODE_AUTO_RESONSE 0x001E
#define     CMD_MODE_AUTO_MSG_REQUEST 0x002E

#define     CMD_MODE_READ_WRITE_SET 0x00F2
#define     CMD_MODE_READ_WRITE_RESONSE 0x002F

#define    PARA_READ_INPUT_LENGTH_SET_01 50       //byte
#define    PARA_READ_INPUT_LENGTH_SET_02 32       //byte
#define    PARA_READ_INPUT_LENGTH_SET_03 60
#define    PARA_READ_INPUT_LENGTH_SET_04 60

#define    PARA_WRITE_OUTUT_LENGTH_SET_01 10
#define    PARA_WRITE_OUTUT_LENGTH_SET_02 10
#define    PARA_WRITE_OUTUT_LENGTH_SET_03 10
#define    PARA_WRITE_OUTUT_LENGTH_SET_04 10
#define    PARA_WRITE_OUTUT_LENGTH_SET_05 10

#define    PARA_READ_INPUT_LENGTH 10
#define    PARA_WRITE_OUTUT_LENGTH 12
#define    PARA_CONFIGURE_INPUT_LENGTH 12







typedef enum FUNCTION
{
    FUNCTION_READ_INPUT = 0,
    FUNCTION_WRITE_OUTPUT = 1,
    FUNCTION_CONFIGURE = 2,
    FUNCTION_READ_AUTO = 3,

}FC;
typedef enum DATA_SET 
{
  DATA_SET_01 = 1,
  DATA_SET_02 = 2,
  DATA_SET_03 = 3,
  DATA_SET_04 = 4,
  DATA_SET_05 = 5,

}DS;

typedef enum ERROR_CONNECT
{
  ERROR_CONNECT_DISCONNECT = 1,
  ERROR_CONNECT_SEND_DATA = 2,
  ERROR_CONNECT_RECV_DATA = 3,
  ERROR_CONNECT_TIME_OUT_SEND = 4,
  ERROR_CONNECT_TIME_OUT_RECV = 5,
  ERROR_CONNECT_FUNC_ERROR = 5,
  ERROR_CONNECT_DATA_ERROR = 2,

}EC;





class clientSock {
  public:
    clientSock(string host, unsigned int port);
    clientSock(string host, unsigned int port,bool automsg);
    clientSock();
    clientSock(int sock);
    ~clientSock();

    bool hasError();
    int connect();
    int disconnect();

    int write(string mesg);
  
    

    bool read_bit(uint8_t data_set,int address_word, int address_bit);
    uint8_t read_half_byte(uint8_t data_set,int address_word, int address_bit);
    uint8_t read_byte(uint8_t data_set,int address_word, int address_bit);
    uint16_t read_word(uint8_t data_set, int address_word);

    int write_bit (uint8_t data_set, int address_word, int address_bit, const bool value );
    int write_half_byte (uint8_t data_set, int address_word, int address_bit, const uint8_t value);
    int write_byte (uint8_t data_set, int address_word, int address_bit, const uint8_t value);
    int write_word ( uint8_t data_set, int address_word, int address_bit, const uint16_t value);

    bool* dec_to_bin_16(uint16_t dec);
    uint16_t array_bit_to_dec_16 (bool arraybit[16]);
    uint16_t* array_bit_16_to_array_hex (bool array[][16]);
    int array_hex_to_array_bit_16(uint16_t array_hex[25], bool (&array_bit)[25][16]);

    int tcp_read_all();
    int tcp_write_all();



    int tcp_read(uint8_t data_set);
    int tcp_write( uint8_t data_set);
  int tcp_auto_read( uint8_t data_set);
    int flex_write_bit(uint8_t data_set, int address_word, int address_bit, const bool value);
    bool flex_read_bit(uint8_t data_set,int address_word, int address_bit);
    //void print_data(int func, uint8_t data_set);
    void print_data(uint16_t buffer[],int lengh);

    
    uint16_t* get_data(uint8_t data_set);

    uint16_t flip_word(uint16_t data_word);
    
    string host;
    unsigned int port;
    bool connected;


  protected:

  private:
  
    string HOST_IP;
    unsigned int PORT_IP;

    int enable_keepalive(int sock);


  

    void build_request(uint16_t *to_send, int func,bool data_set_01,bool data_set_02,bool data_set_03,bool data_set_04,bool data_set_05);

    
    bool request_read(uint8_t data_set);
    bool request_read_all();

    bool request_write(uint8_t data_set);
    bool request_write_all();


    size_t tcp_send(uint16_t *to_send,int length);
    size_t tcp_receive(uint16_t *buffer,int length);


    void set_bad_con();
    void set_bad_input();

   // void print_data(uint16_t buffer[],int lengh);

    static const unsigned int buffSize = 1024;
    int sockfd;//establish connection to ID distribution server

    struct sockaddr_in servaddr;
    uint16_t recv[buffSize];
    uint16_t output_data_set_01[PARA_WRITE_OUTUT_LENGTH_SET_01/2]={0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
    uint16_t output_data_set_02[PARA_WRITE_OUTUT_LENGTH_SET_02/2]={0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
    uint16_t output_data_set_03[PARA_WRITE_OUTUT_LENGTH_SET_03/2]={0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
    uint16_t output_data_set_04[PARA_WRITE_OUTUT_LENGTH_SET_04/2]={0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
    uint16_t output_data_set_05[PARA_WRITE_OUTUT_LENGTH_SET_05/2]={0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
    struct hostent* server;

    uint16_t intput_data_set_01[PARA_READ_INPUT_LENGTH_SET_01/2];
    uint16_t intput_data_set_02[PARA_READ_INPUT_LENGTH_SET_02/2];
    uint16_t intput_data_set_03[PARA_READ_INPUT_LENGTH_SET_03/2];
    uint16_t intput_data_set_04[PARA_READ_INPUT_LENGTH_SET_04/2];


    


};

#endif // CLIENTSOCK_H