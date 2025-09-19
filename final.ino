#include <driver/i2s.h>

#define I2S_WS      11
#define I2S_SD      10
#define I2S_SCK     12

#define SAMPLE_RATE 16000
#define I2S_PORT    I2S_NUM_0

void setupI2SMic() {
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  setupI2SMic();
  Serial.println("INMP441 ready. Reading audio...");
}

void loop() {
  const int bufferLen = 1024;
  int32_t buffer[bufferLen];
  size_t bytesRead;

  i2s_read(I2S_PORT, &buffer, sizeof(buffer), &bytesRead, portMAX_DELAY);
  int samplesRead = bytesRead / sizeof(int32_t);

  // Print a few shifted samples
  for (int i = 0; i < samplesRead; i += 100) {
    int32_t sample = buffer[i] >> 8;  // shift to convert from 32-bit to 24-bit signed
    Serial.printf("Sample %d: %d\n", i, sample);
  }

  delay(200);
}
