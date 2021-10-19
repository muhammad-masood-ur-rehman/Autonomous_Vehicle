#include <Arduino.h>

#include "esp_camera.h"
#include "fd_forward.h"

#include <Servo.h>

#define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22



int FACE_DETECT_TIME  = 500;      // Duration of face detect signal, after no face detection
static bool FaceDetected = false;
static unsigned int detections = 0;
static const int servoPin = 4;
static unsigned long FaceDetectMillis = millis();
Servo servo;
 
mtmn_config_t mtmn_config = {0};

bool initCamera() {
 
  camera_config_t config;
 
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;
 
  esp_err_t result = esp_camera_init(&config);
 
  return (result == ESP_OK);
}

 
void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
  Serial.printf("Initializing...\n");

  if (!initCamera()) {
 
    Serial.printf("Failed to initialize camera...\n");
    return;
  }
 
  mtmn_config = mtmn_init_config();

  
  Serial.printf("Ready\n");
}

 
void loop() {
 
  
  camera_fb_t * frame;
  frame = esp_camera_fb_get();
 
  dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, frame->width, frame->height, 3);
  fmt2rgb888(frame->buf, frame->len, frame->format, image_matrix->item);
 
  esp_camera_fb_return(frame);
 
  box_array_t *boxes = face_detect(image_matrix, &mtmn_config);
 
  if (boxes != NULL) {
    detections = detections+1;
    Serial.printf("Faces detected %d times\n", detections);

    
    FaceDetectMillis = millis();
    FaceDetected = true;
 

    free(boxes->score);
    free(boxes->box);
    free(boxes->landmark);
    free(boxes);
  }
  else if (FaceDetected && (millis() - FaceDetectMillis >= FACE_DETECT_TIME))
  {
   
    FaceDetected = true;
  }

  if (boxes == NULL)
  {
    FACE_DETECT_TIME = FACE_DETECT_TIME-100;
  }

  if(FACE_DETECT_TIME < 500)
  {
    FaceDetected =true;
  }
 
  dl_matrix3du_free(image_matrix);

  if(FaceDetected == true)
  {
     for(int angle = 0; angle<=90; angle++)
     {
        servo.write(angle);
        delay(10);
     }
     for(int angle=90; angle>=0; angle--)
     {
        servo.write(angle);
        delay(10);
     }
  } 
}