#ifndef http_req_h
#define http_req_h

#include <WiFiClientSecure.h>
#include <WiFiClient.h>

#include "util.h"
extern WiFiClientSecure client; // global WiFiClient Secure object
extern WiFiClient client2;      // global WiFiClient Secure object
/*https communication requires certificates to be known ahead of time so each entity will trust one another.
   This is a cert for google's generic servers below, allowing us to connect over https with their resources
*/
extern char *CA_CERT;

extern const uint16_t RESPONSE_TIMEOUT;
extern const uint16_t IN_BUFFER_SIZE;  // size of buffer to hold HTTP request
extern const uint16_t OUT_BUFFER_SIZE; // size of buffer to hold HTTP response
extern const uint16_t JSON_BODY_SIZE;
// #define RESPONSE_TIMEOUT 6000
// #define IN_BUFFER_SIZE 5000  // size of buffer to hold HTTP request
// #define OUT_BUFFER_SIZE 1000 // size of buffer to hold HTTP response
// #define JSON_BODY_SIZE 3000
extern char request[];
extern char response[]; // char array buffer to hold HTTP request
extern char json_body[];
extern char request_body[];
/*----------------------------------
   char_append Function:
   Arguments:
      char* buff: pointer to character array which we will append a
      char c:
      uint16_t buff_size: size of buffer buff

   Return value:
      boolean: True if character appended, False if not appended (indicating buffer full)
*/
uint8_t char_append(char *buff, char c, uint16_t buff_size);

/*----------------------------------
 * do_http_request Function:
 * Arguments:
 *    char* host: null-terminated char-array containing host to connect to
 *    char* request: null-terminated char-arry containing properly formatted HTTP request
 *    char* response: char-array used as output for function to contain response
 *    uint16_t response_size: size of response buffer (in bytes)
 *    uint16_t response_timeout: duration we'll wait (in ms) for a response from server
 *    uint8_t serial: used for printing debug information to terminal (true prints, false doesn't)
 * Return value:
 *    void (none)
 */
void do_http_request(char *host, char *request, char *response, uint16_t response_size, uint16_t response_timeout, uint8_t serial);

/*----------------------------------
   do_https_request Function. Similar to do_http_request, but supports https requests
   Arguments:
      char* host: null-terminated char-array containing host to connect to
      char* request: null-terminated char-arry containing properly formatted HTTP request
      char* response: char-array used as output for function to contain response
      uint16_t response_size: size of response buffer (in bytes)
      uint16_t response_timeout: duration we'll wait (in ms) for a response from server
      uint8_t serial: used for printing debug information to terminal (true prints, false doesn't)
   Return value:
      void (none)
*/
void do_https_request(char *host, char *request, char *response, uint16_t response_size, uint16_t response_timeout, uint8_t serial);
#endif