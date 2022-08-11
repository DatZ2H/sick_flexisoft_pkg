#include "sick_flexisoft_pkg/flexisoft_library.h"

clientSock::clientSock(string host, unsigned int port)
{
    int t = 0;
    HOST_IP = host;
    PORT_IP = port;
    connect();
}

void *task1(void *arg)
{
    clientSock *client = (clientSock *)arg;
    client->tcp_auto_read(1);
}

clientSock::clientSock(string host, unsigned int port, bool automsg)
{
    int t = 0;
    HOST_IP = host;
    PORT_IP = port;
    connect();
    //  tcp_auto_read(1);
}

clientSock::clientSock()
{
    connected = false;
}

clientSock::clientSock(int sock)
{
    sockfd = sock;
    connected = true;
}

clientSock::~clientSock()
{
    // disconnect();
}

int clientSock::connect()
{
    cout << "connecting!!" << endl;
    clientSock::host = HOST_IP;
    clientSock::port = PORT_IP;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    server = gethostbyname(host.data());
    bcopy((char *)server->h_addr, (char *)&servaddr.sin_addr.s_addr, server->h_length);
    servaddr.sin_port = htons(port);

    if (connected)
        disconnect();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // struct timeval tv;
    // tv.tv_sec = 10;//5 Secs Timeout
    // tv.tv_usec = 0;//Not init'ing this can cause strange errors
    // setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(struct timeval));
    // setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

    enable_keepalive(sockfd);

    for (size_t i = 0; i < 10; i++)
    { // try to connect 10 times
        if (::connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
            cout << "Error on connecting: " << errno << "  " << strerror(errno) << endl;
        else
        {
            connected = true;
            cout << "connected!!!" << endl;
            return 0;
        }
    }

    connected = false;
    return 1;
}

bool clientSock::hasError()
{
    if (sockfd == -1)
        return true;

    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);

    if (retval != 0 || error != 0)
        return true;
    else
        return false;
}

int clientSock::enable_keepalive(int sock)
{
    int yes = 1;

    if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) == -1)
        return -1;

    int idle = 1;

    if (setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) == -1)
        return -1;

    int interval = 1;

    if (setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) == -1)
        return -1;

    int maxpkt = 10;

    if (setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) == -1)
        return -1;

    return 0;
}

int clientSock::disconnect()
{
    if (!connected)
        return -1;

    close(sockfd);
    connected = false;

    return 0;
}

int clientSock::write(string mesg)
{

    if (!connected)
        return 1;

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);

    // cout << "w: " << mesg << endl;

    int sentBytes = 0;

    for (size_t i = 0; i < mesg.length(); i += sentBytes)
    {
        cout << "PRINT" << endl;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        int rv = select(sockfd + 1, NULL, &writefds, NULL, &tv);

        if (rv == -1)
        {
            cout << errno << "  " << strerror(errno) << endl;
            cout << "ERROR-1" << endl;
        }
        else if (rv == 0)
            sentBytes = 0;
        else if (rv > 0 && FD_ISSET(sockfd, &writefds))
        {
            sentBytes = ::write(sockfd, mesg.substr(i, mesg.length() - i).c_str(), mesg.length() - i);

            if (sentBytes == -1)
            {
                cout << "Error sending IDs: " << errno << "  " << strerror(errno) << endl;
                return 1;
                cout << "STOP" << endl;
            }
        }
    }
    cout << "STOP-START" << endl;
    return 0;
}

bool clientSock::read_bit(uint8_t data_set, int address_word, int address_bit)
{

    bool result;
    switch (data_set)
    {
    case DATA_SET_01:
    {
        return (bool)((intput_data_set_01[address_word] >> address_bit) & 0b1);
    }
    break;
    case DATA_SET_02:
    {
        return (bool)((intput_data_set_02[address_word] >> address_bit) & 0b1);
    }
    break;
    case DATA_SET_03:
    {
        return (bool)((intput_data_set_03[address_word] >> address_bit) & 0b1);
    }
    break;
    case DATA_SET_04:
    {
        return (bool)((intput_data_set_03[address_word] >> address_bit) & 0b1);
    }
    break;
    }
}
uint8_t clientSock::read_half_byte(uint8_t data_set, int address_word, int address_bit)
{

    switch (data_set)
    {
    case DATA_SET_01:
    {
        return (uint8_t)((intput_data_set_01[address_word] >> address_bit) & 0b1111);
    }
    break;
    case DATA_SET_02:
    {
        return (uint8_t)((intput_data_set_02[address_word] >> address_bit) & 0b1111);
    }
    break;
    case DATA_SET_03:
    {
        return (uint8_t)((intput_data_set_03[address_word] >> address_bit) & 0b1111);
    }
    break;
    case DATA_SET_04:
    {
        return (uint8_t)((intput_data_set_03[address_word] >> address_bit) & 0b1111);
    }
    break;
    }
}
uint8_t clientSock::read_byte(uint8_t data_set, int address_word, int address_bit)
{

    switch (data_set)
    {
    case DATA_SET_01:
    {
        return (uint8_t)((intput_data_set_01[address_word] >> address_bit) & 0xFF);
    }
    break;
    case DATA_SET_02:
    {
        return (uint8_t)((intput_data_set_02[address_word] >> address_bit) & 0xFF);
    }
    break;
    case DATA_SET_03:
    {
        return (uint8_t)((intput_data_set_03[address_word] >> address_bit) & 0xFF);
    }
    break;
    case DATA_SET_04:
    {
        return (uint8_t)((intput_data_set_03[address_word] >> address_bit) & 0xFF);
    }
    break;
    }
}
uint16_t clientSock::read_word(uint8_t data_set, int address_word)
{
    switch (data_set)
    {
    case DATA_SET_01:
    {
        return intput_data_set_01[address_word];
    }
    break;
    case DATA_SET_02:
    {
        return intput_data_set_02[address_word];
    }
    break;
    case DATA_SET_03:
    {
        return intput_data_set_03[address_word];
    }
    break;
    case DATA_SET_04:
    {
        return intput_data_set_04[address_word];
    }
    break;
    }
}
int clientSock::write_bit(uint8_t data_set, int address_word, int address_bit, const bool value)
{

    switch (data_set)
    {
    case DATA_SET_01:
    {

        output_data_set_01[address_word] = ((output_data_set_01[address_word] & (uint16_t)(~(1 << address_bit)) | (((int)value) << address_bit)));
        return true;
    }
    break;
    case DATA_SET_02:
    {
        output_data_set_02[address_word] = ((output_data_set_02[address_word] & (uint16_t)(~(1 << address_bit)) | (((int)value) << address_bit)));

        return true;
    }
    break;
    case DATA_SET_03:
    {
        output_data_set_03[address_word] = ((output_data_set_03[address_word] & (uint16_t)(~(1 << address_bit)) | (((int)value) << address_bit)));
        return true;
    }
    break;
    case DATA_SET_04:
    {
        output_data_set_04[address_word] = ((output_data_set_04[address_word] & (uint16_t)(~(1 << address_bit)) | (((int)value) << address_bit)));
        return true;
    }
    break;

    case DATA_SET_05:
    {
        output_data_set_05[address_word] = ((output_data_set_05[address_word] & (uint16_t)(~(1 << address_bit)) | (((int)value) << address_bit)));
        return true;
    }
    break;
    }
}
int clientSock::write_half_byte(uint8_t data_set, int address_word, int address_bit, const uint8_t value)
{
    switch (data_set)
    {
    case DATA_SET_01:
    {

        output_data_set_01[address_word] = ((output_data_set_01[address_word] & (uint16_t)(~(0b1111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    case DATA_SET_02:
    {
        output_data_set_02[address_word] = ((output_data_set_02[address_word] & (uint16_t)(~(0b1111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    case DATA_SET_03:
    {
        output_data_set_03[address_word] = ((output_data_set_03[address_word] & (uint16_t)(~(0b1111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    case DATA_SET_04:
    {
        output_data_set_04[address_word] = ((output_data_set_04[address_word] & (uint16_t)(~(0b1111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;

    case DATA_SET_05:
    {
        output_data_set_05[address_word] = ((output_data_set_05[address_word] & (uint16_t)(~(0b1111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    }
}
int clientSock::write_byte(uint8_t data_set, int address_word, int address_bit, const uint8_t value)
{
    switch (data_set)
    {
    case DATA_SET_01:
    {

        output_data_set_01[address_word] = ((output_data_set_01[address_word] & (uint16_t)(~(0b11111111 << address_bit)) | (value << address_bit)));

        return true;
    }
    break;
    case DATA_SET_02:
    {
        output_data_set_02[address_word] = ((output_data_set_02[address_word] & (uint16_t)(~(0b11111111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    case DATA_SET_03:
    {
        output_data_set_03[address_word] = ((output_data_set_03[address_word] & (uint16_t)(~(0b11111111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    case DATA_SET_04:
    {
        output_data_set_04[address_word] = ((output_data_set_04[address_word] & (uint16_t)(~(0b11111111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;

    case DATA_SET_05:
    {
        output_data_set_05[address_word] = ((output_data_set_05[address_word] & (uint16_t)(~(0b11111111 << address_bit)) | (value << address_bit)));
        return true;
    }
    break;
    }
}
int clientSock::write_word(uint8_t data_set, int address_word, int address_bit, const uint16_t value)
{
    switch (data_set)
    {
    case DATA_SET_01:
    {

        output_data_set_01[address_word] = value;
        return true;
    }
    break;
    case DATA_SET_02:
    {
        output_data_set_02[address_word] = value;
        return true;
    }
    break;
    case DATA_SET_03:
    {
        output_data_set_03[address_word] = value;
        return true;
    }
    break;
    case DATA_SET_04:
    {
        output_data_set_04[address_word] = value;
        return true;
    }
    break;

    case DATA_SET_05:
    {
        output_data_set_05[address_word] = value;
        return true;
    }
    break;
    }
}
void clientSock::build_request(uint16_t *to_send, int func, bool data_set_01, bool data_set_02, bool data_set_03, bool data_set_04, bool data_set_05)
{
    if (func == FUNCTION_READ_INPUT)
    {
        to_send[0] = CMD_MODE_POLL_REQUEST;
        if (data_set_01 == true)
        {
            to_send[1] = PARA_READ_INPUT_DATA_SET_01;
        }
        else
        {
            to_send[1] = 0x0000;
        }
        if (data_set_02 == true)
        {
            to_send[2] = PARA_READ_INPUT_DATA_SET_02;
        }
        else
        {
            to_send[2] = 0x0000;
        }
        if (data_set_03 == true)
        {
            to_send[3] = PARA_READ_INPUT_DATA_SET_03;
        }
        else
        {
            to_send[3] = 0x0000;
        }
        if (data_set_04 == true)
        {
            to_send[4] = PARA_READ_INPUT_DATA_SET_04;
        }
        else
        {
            to_send[4] = 0x0000;
        }
    }
    else if (func == FUNCTION_WRITE_OUTPUT)
    {
        to_send[0] = CMD_MODE_READ_WRITE_SET;
        if (data_set_01 == true)
        {
            to_send[1] = PARA_WRITE_OUTPUT_DATA_SET_01;
            for (int i = 0; i < PARA_WRITE_OUTUT_LENGTH_SET_01 / 2; i++)
            {
                to_send[i + PARA_WRITE_OUTUT_LENGTH / 2] = flip_word(output_data_set_01[i]);
                /* code */
            }
        }
        else
        {
            to_send[1] = 0x0000;
        }
        if (data_set_02 == true)
        {
            to_send[2] = PARA_WRITE_OUTPUT_DATA_SET_02;
            for (int i = 0; i < PARA_WRITE_OUTUT_LENGTH_SET_02 / 2; i++)
            {
                to_send[i + PARA_WRITE_OUTUT_LENGTH / 2] = flip_word(output_data_set_02[i]);
                /* code */
            }
        }
        else
        {
            to_send[2] = 0x0000;
        }
        if (data_set_03 == true)
        {
            to_send[3] = PARA_WRITE_OUTPUT_DATA_SET_03;
            for (int i = 0; i < PARA_WRITE_OUTUT_LENGTH_SET_03 / 2; i++)
            {
                to_send[i + PARA_WRITE_OUTUT_LENGTH / 2] = flip_word(output_data_set_03[i]);
                /* code */
            }
        }
        else
        {
            to_send[3] = 0x0000;
        }
        if (data_set_04 == true)
        {
            to_send[4] = PARA_WRITE_OUTPUT_DATA_SET_04;
            for (int i = 0; i < PARA_WRITE_OUTUT_LENGTH_SET_04 / 2; i++)
            {
                to_send[i + PARA_WRITE_OUTUT_LENGTH / 2] = flip_word(output_data_set_04[i]);
                /* code */
            }
        }
        else
        {
            to_send[4] = 0x0000;
        }
        if (data_set_05 == true)
        {
            to_send[5] = PARA_WRITE_OUTPUT_DATA_SET_05;
            for (int i = 0; i < PARA_WRITE_OUTUT_LENGTH_SET_05 / 2; i++)
            {
                to_send[i + PARA_WRITE_OUTUT_LENGTH / 2] = flip_word(output_data_set_05[i]);
                /* code */
            }
        }
        else
        {
            to_send[5] = 0x0000;
        }
    }
    else if (func == FUNCTION_CONFIGURE)
    {
        to_send[0] = CMD_MODE_AUTO_REQUEST;
    }
    else if (func == FUNCTION_READ_AUTO)
    {
        to_send[0] = CMD_MODE_AUTO_REQUEST;
        if (data_set_01 == true)
        {
            to_send[1] = PARA_CONFIGURE_INPUT_DATA_SET_01;
        }
        else
        {
            to_send[1] = 0x0000;
        }
        if (data_set_02 == true)
        {
            to_send[2] = PARA_CONFIGURE_INPUT_DATA_SET_02;
        }
        else
        {
            to_send[2] = 0x0000;
        }
        if (data_set_03 == true)
        {
            to_send[3] = PARA_CONFIGURE_INPUT_DATA_SET_03;
        }
        else
        {
            to_send[3] = 0x0000;
        }
        if (data_set_04 == true)
        {
            to_send[4] = PARA_CONFIGURE_INPUT_DATA_SET_04;
        }
        else
        {
            to_send[4] = 0x0000;
        }
    }
    else
    {
        cout << "error";
    }
}
int clientSock::tcp_read(uint8_t data_set)
{
    request_read(data_set);
    int MAX_LENGTH;
    if (data_set == DATA_SET_01)
    {
        MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_01 / 2 + PARA_READ_INPUT_LENGTH / 2;
    }
    else if (data_set == DATA_SET_02)
    {
        MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_02 / 2 + PARA_READ_INPUT_LENGTH / 2;
    }
    else if (data_set == DATA_SET_03)
    {
        MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_03 / 2 + PARA_READ_INPUT_LENGTH / 2;
    }
    else if (data_set == DATA_SET_04)
    {
        MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_04 / 2 + PARA_READ_INPUT_LENGTH / 2;
    }

    uint16_t to_rec[MAX_LENGTH];
    ssize_t k = tcp_receive(to_rec, MAX_LENGTH);
    if (k = -1)
    {
    }
    if (to_rec[0] == CMD_MODE_POLL_RESONSE)
    {
        switch (data_set)
        {
        case DATA_SET_01:

            if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_01)
            {

                for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_01 / 2; i++)
                {
                    intput_data_set_01[i] = flip_word(to_rec[i + 5]);

                    /* code */
                }
            }

            break;
        case DATA_SET_02:
            if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_02)
            {
                for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_02 / 2; i++)
                {
                    intput_data_set_02[i] = flip_word(to_rec[i + 5]);
                    /* code */
                }
            }
            break;
        case DATA_SET_03:
            if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_03)
            {
                for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_03 / 2; i++)
                {
                    intput_data_set_03[i] = flip_word(to_rec[i + 5]);
                    /* code */
                }
            }
            break;
        case DATA_SET_04:
            if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_04)
            {
                for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_04 / 2; i++)
                {
                    intput_data_set_04[i] = flip_word(to_rec[i + 5]);
                    /* code */
                }
            }
            break;
        }
    }
}
int clientSock::tcp_auto_read(uint8_t data_set)
{
    // request_read(data_set);
    while (true)
    {
        int MAX_LENGTH;
        if (data_set == DATA_SET_01)
        {
            MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_01 / 2 + PARA_READ_INPUT_LENGTH / 2;
        }
        else if (data_set == DATA_SET_02)
        {
            MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_02 / 2 + PARA_READ_INPUT_LENGTH / 2;
        }
        else if (data_set == DATA_SET_03)
        {
            MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_03 / 2 + PARA_READ_INPUT_LENGTH / 2;
        }
        else if (data_set == DATA_SET_04)
        {
            MAX_LENGTH = PARA_READ_INPUT_LENGTH_SET_04 / 2 + PARA_READ_INPUT_LENGTH / 2;
        }

        uint16_t to_rec[MAX_LENGTH];
        ssize_t k = tcp_receive(to_rec, MAX_LENGTH);
        if (k = -1)
        {
        }
        if (to_rec[0] == CMD_MODE_AUTO_RESONSE)
        {
            switch (data_set)
            {
            case DATA_SET_01:

                if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_01)
                {

                    for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_01 / 2; i++)
                    {
                        intput_data_set_01[i] = flip_word(to_rec[i + 5]);

                        /* code */
                    }
                }

                break;
            case DATA_SET_02:
                if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_02)
                {
                    for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_02 / 2; i++)
                    {
                        intput_data_set_02[i] = flip_word(to_rec[i + 5]);
                        /* code */
                    }
                }
                break;
            case DATA_SET_03:
                if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_03)
                {
                    for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_03 / 2; i++)
                    {
                        intput_data_set_03[i] = flip_word(to_rec[i + 5]);
                        /* code */
                    }
                }
                break;
            case DATA_SET_04:
                if ((int)to_rec[1] == PARA_READ_INPUT_LENGTH_SET_04)
                {
                    for (size_t i = 0; i < (int)PARA_READ_INPUT_LENGTH_SET_04 / 2; i++)
                    {
                        intput_data_set_04[i] = flip_word(to_rec[i + 5]);
                        /* code */
                    }
                }
                break;
            }
        }
    }
}
int clientSock::tcp_write(uint8_t data_set)
{
    request_write(data_set);

    uint16_t to_rec[2];
    ssize_t k = tcp_receive(to_rec, 2);
    if (k = -1)
    {
        return 0;
    }
    if (to_rec[0] == CMD_MODE_POLL_RESONSE)
    {
        if (to_rec[1] == 0x0000)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    return 0;
}

void clientSock::print_data(uint16_t buffer[], int lengh)
{
    for (int i = 0; i < lengh; i++)
    {
        cout << "PRINT DATA [" << std::dec << i << "]= " << buffer[i] << " hex => " << hex << (uint16_t)buffer[i] << " endl " << endl;
        /* code */
    }
}

uint16_t *clientSock::get_data(uint8_t data_set)
{
    switch (data_set)
    {
    case DATA_SET_01:
        return intput_data_set_01;
        break;
    case DATA_SET_02:
        return intput_data_set_02;
        break;
    case DATA_SET_03:
        return intput_data_set_03;
        break;
    case DATA_SET_04:
        return intput_data_set_04;
        break;
    }
}

uint16_t clientSock::flip_word(uint16_t data_word)
{
    uint8_t new_high_byte = (data_word & (0XFF00)) >> 8;
    uint8_t new_low_byte = data_word & (0x00FF);
    return ((new_low_byte << 8) | new_high_byte & 0x00FF);
}

bool clientSock::request_read(uint8_t data_set)
{
    bool Data_Set_01 = false;
    bool Data_Set_02 = false;
    bool Data_Set_03 = false;
    bool Data_Set_04 = false;

    if (data_set == DATA_SET_01)
    {
        Data_Set_01 = true;
    }
    else if (data_set == DATA_SET_02)
    {
        Data_Set_02 = true;
    }
    else if (data_set == DATA_SET_03)
    {
        Data_Set_03 = true;
    }
    else if (data_set == DATA_SET_04)
    {
        Data_Set_04 = true;
    }

    if (connected)
    {
        uint16_t to_send[PARA_READ_INPUT_LENGTH / 2];
        build_request(to_send, FUNCTION_READ_INPUT, Data_Set_01, Data_Set_02, Data_Set_03, Data_Set_04, false);
        return tcp_send(to_send, PARA_READ_INPUT_LENGTH);
    }
    else
    {
        set_bad_con();
        return BAD_CON;
    }
}
bool clientSock::request_read_all()
{
    request_read(DATA_SET_01);
    request_read(DATA_SET_02);
    request_read(DATA_SET_03);
    request_read(DATA_SET_04);
    return 0;
}
bool clientSock::request_write(uint8_t data_set)
{
    bool Data_Set_01 = false;
    bool Data_Set_02 = false;
    bool Data_Set_03 = false;
    bool Data_Set_04 = false;
    bool Data_Set_05 = false;

    switch (data_set)
    {
    case DATA_SET_01:
    {
        Data_Set_01 = true;
    }
    break;
    case DATA_SET_02:
    {
        Data_Set_02 = true;
    }
    break;
    case DATA_SET_03:
    {
        Data_Set_03 = true;
    }
    break;
    case DATA_SET_04:
    {
        Data_Set_04 = true;
    }
    break;
    case DATA_SET_05:
    {
        Data_Set_05 = true;
    }
    break;

    default:
        break;
    }

    if (connected)
    {
        uint16_t to_send[PARA_WRITE_OUTUT_LENGTH_SET_01 / 2 + PARA_WRITE_OUTUT_LENGTH / 2];
        build_request(to_send, FUNCTION_WRITE_OUTPUT, Data_Set_01, Data_Set_02, Data_Set_03, Data_Set_04, Data_Set_05);
        return tcp_send(to_send, PARA_WRITE_OUTUT_LENGTH_SET_01 + PARA_WRITE_OUTUT_LENGTH);
    }
    else
    {
        set_bad_con();
        return BAD_CON;
    }
}
bool clientSock::request_write_all()
{
    request_write(DATA_SET_01);
    request_write(DATA_SET_02);
    request_write(DATA_SET_03);
    request_write(DATA_SET_04);
    request_write(DATA_SET_05);
}

int clientSock::tcp_read_all()
{
    tcp_read(DATA_SET_01);
    tcp_read(DATA_SET_02);
    tcp_read(DATA_SET_03);
    tcp_read(DATA_SET_04);
    return 0;
}
int clientSock::tcp_write_all()
{
    tcp_write(DATA_SET_01);
    tcp_write(DATA_SET_02);
    tcp_write(DATA_SET_03);
    tcp_write(DATA_SET_04);
    tcp_write(DATA_SET_05);
}
int clientSock::flex_write_bit(uint8_t data_set, int address_word, int address_bit, const bool value)
{
    write_bit(data_set, address_word, address_bit, value);
    tcp_write(data_set);
}
bool clientSock::flex_read_bit(uint8_t data_set, int address_word, int address_bit)
{
    tcp_read(data_set);
    return read_bit(data_set, address_word, address_bit);
}
size_t clientSock::tcp_send(uint16_t *to_send, int length)
{
    if (connected)
    {

        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);

        int sentBytes = 0;

        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        int rv = select(sockfd + 1, NULL, &writefds, NULL, &tv);

        if (rv == -1)
        {

            cout << errno << "  " << strerror(errno) << endl;
            set_bad_con();
        }
        else if (rv == 0)
        {

            set_bad_con();
            sentBytes = 0;
        }
        else if (rv > 0 && FD_ISSET(sockfd, &writefds))
        {
            uint16_t new_to_send[length];
            for (size_t i = 0; i < length; i++)
            {
                new_to_send[i] = flip_word(to_send[i]);
                /* code */
            }

            sentBytes = ::write(sockfd, (uint16_t *)new_to_send, length);

            if (sentBytes == -1)
            {
                cout << "Error sending IDs: " << errno << "  " << strerror(errno) << endl;
                set_bad_con();
                return 1;
            }
        }

        return 0;
    }
    else
    {
        connected = false;
        return 1;
    }
}
size_t clientSock::tcp_receive(uint16_t *buffer, int length)
{
    uint16_t buffer_array[buffSize];
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    uint16_t resp = 0;
    unsigned int n = 0;

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);

    if (rv <= -1)
    {
        cout << ("socket error accured") << endl;

        set_bad_con();
        return -1;
    }
    else if (rv == 0)
    {
        cout << ("socket timeout occured") << endl;

        set_bad_con();
        return -1;
    }
    else if (rv > 0 && FD_ISSET(sockfd, &readfds))
    {

        int tn = ::recv(sockfd, buffer_array, buffSize, 0); // avoid signcompare warning

        if (tn > 0)
        {

            for (int i = 0; i < length; i++)
            {
                buffer[i] = flip_word(buffer_array[i]);
            }
            return tn;
        }
        else if (tn == -1)
        {
            cout << ("socket timeout occured") << endl;
            set_bad_con();
            return -1;
        }
    }
    else
    {
        cout << "ERROR: rv: " << rv << endl;
        set_bad_con();
        return -1;
    }
}
void clientSock::set_bad_con()
{
    ROS_ERROR("DISCONNECT FLEXISOFT");
    connected = false;
}
void clientSock::set_bad_input()
{
}
