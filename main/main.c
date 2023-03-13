#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/uart.h>
#include <string.h>

#define GPS_UART_NUM UART_NUM_2
#define GPS_UART_TX_PIN 12
#define GPS_UART_RX_PIN 34
#define GPS_UART_BAUDRATE 9600
#define GPS_UART_BUF_SIZE 1024

//This is a function definition for parsing the GGA sentence, which takes in the GGA sentence string,
//and pointers to store the latitude, longitude, and altitude.
void parse_gga_sentence(char *gga_sentence, float *latitude, float *longitude, float *altitude) {
    char *token;
    int token_count = 0;
    token = strtok(gga_sentence, ",");
    while (token != NULL) {
        if (token_count == 2) { // Latitude
            float lat_degrees = atof(token);
            token = strtok(NULL, ",");
            float lat_minutes = atof(token);
            *latitude = lat_degrees + lat_minutes / 60;
        } else if (token_count == 3) { // Latitude direction (N/S)
            if (strcmp(token, "S") == 0) {
                *latitude *= -1;
            }
        } else if (token_count == 4) { // Longitude
            float lon_degrees = atof(token);
            token = strtok(NULL, ",");
            float lon_minutes = atof(token);
            *longitude = lon_degrees + lon_minutes / 60;
        } else if (token_count == 5) { // Longitude direction (E/W)
            if (strcmp(token, "W") == 0) {
                *longitude *= -1;
            }
        } else if (token_count == 9) { // Altitude
            *altitude = atof(token);
        }
        token = strtok(NULL, ",");
        token_count++;
    }
}


void gps_task(void *pvParameters) {
    uart_config_t uart_config = {
        .baud_rate = GPS_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(GPS_UART_NUM, &uart_config);
    uart_set_pin(GPS_UART_NUM, GPS_UART_TX_PIN, GPS_UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(GPS_UART_NUM, GPS_UART_BUF_SIZE, 0, 0, NULL, 0);

    uint8_t gps_data[256];
    int len = 0;
    while(1) {
        len = uart_read_bytes(GPS_UART_NUM, gps_data, sizeof(gps_data), 100 / portTICK_RATE_MS);
        if(len > 0) {
//            printf("GPS data received: %.*s\n", len, gps_data);
            // Parse GPS data here
            // Parse GPS data here
            char *gga_sentence = strstr((char *)gps_data, "$GPGGA");
            if (gga_sentence != NULL) {
            	float latitude, longitude, altitude;
                parse_gga_sentence(gga_sentence, &latitude, &longitude, &altitude);
                printf("Latitude: %f, Longitude: %f, Altitude: %f\n", latitude, longitude, altitude);
            }
        }
    }
}

void app_main() {
    xTaskCreate(gps_task, "gps_task", 4096, NULL, 5, NULL);
}
