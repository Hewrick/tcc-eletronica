#include <WiFi.h>
#include <esp_camera.h>
#include <ESPAsyncWebServer.h>
 
// Camera configuration
camera_config_t config = {
    .pin_pwdn = 32,
    .pin_reset = -1,
    .pin_xclk = 0,
    .pin_SCCB_SDA = 26,
    .pin_SCCB_SCL = 27,
    .pin_d0 = 35,
    .pin_d1 = 34,
    .pin_d2 = 39,
    .pin_d3 = 36,
    .pin_d4 = 21,
    .pin_d5 = 19,
    .pin_d6 = 18,
    .pin_d7 = 5,
    .pin_vsync = 25,
    .pin_href = 23,
    .pin_pclk = 22,
    .xclk_freq_hz = 20000000,
    .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_SVGA,
    .jpeg_quality = 12,
    .fb_count = 2
};
 
// Credenciais da rede Wi-Fi
const char* ssid = "Pedro Ribeiro"; // Nome da rede Wi-Fi
const char* password = "1234567-8"; // Senha do Wi-Fi
 
AsyncWebServer server(80); // Create an instance of the server
 
void startCameraServer();
 
void setup() {
    Serial.begin(115200);
   
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
 
    // Initialize camera
    if (esp_camera_init(&config) != ESP_OK) {
        Serial.println("Camera initialization failed");
        return;
    }
 
    // Start camera server
    startCameraServer();
    Serial.println("Camera server started");
}
 
void startCameraServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });
 
    server.on("/capture", HTTP_GET, [](AsyncWebServerRequest *request){
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Camera capture failed");
            request->send(500);
            return;
        }
        request->send(200, "image/jpeg", fb->buf, fb->len);
        esp_camera_fb_return(fb);
    });
 
    server.begin();
}
 
// HTML for the view page
const char* index_html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ESP32-CAM</title>
</head>
<body>
<h1>ESP32-CAM</h1>
<img src="/capture" />
<button onclick="window.location.reload();">Refresh</button>
</body>
</html>
)rawliteral";
 
void loop() {
    // O servidor lida com requisições em segundo plano
}
