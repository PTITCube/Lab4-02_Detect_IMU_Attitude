/**
 * VÍ DỤ 4-2: ĐỌC DỮ LIỆU CẢM BIẾN QUÁN TÍNH 9 TRỤC (IMU 9-DOF)
 * 
 * Mô tả:
 * Ví dụ này minh họa cách thu thập toàn bộ dữ liệu 9 trục từ cảm biến:
 * - 3 trục Gia tốc (Accelerometer - MPU6050/MPU6500)
 * - 3 trục Con quay hồi chuyển (Gyroscope - MPU6050/MPU6500)
 * - 3 trục La bàn từ trường (Magnetometer - QMC5883L)
 */

#include <Arduino.h>
#include <PTITCube.h>

PTIT_Sensor mySensor;

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    Serial.println("\n[EXAMPLE] Bắt đầu bài test Cảm biến Quán tính 9 trục (IMU)...");
    mySensor.init(false, true, true);
}

void loop() {
    // Phải gọi update() liên tục để lấy giá trị mới nhất
    mySensor.update();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 1000) {
        lastPrint = millis();
        
        float ax = mySensor.getAccX();
        float ay = mySensor.getAccY();
        float az = mySensor.getAccZ();
        float gx = mySensor.getGyroX();
        float gy = mySensor.getGyroY();
        float gz = mySensor.getGyroZ();
        float mx = mySensor.getMagX();
        float my = mySensor.getMagY();
        float mz = mySensor.getMagZ();

        // Tính Góc nghiêng (Roll & Pitch)
        float roll = atan2(ay, az) * 180.0 / PI;
        float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

        // Tính góc hướng La bàn
        float heading = atan2(my, mx) * 180.0 / PI;
        if (heading < 0) heading += 360.0;

        Serial.println("==================================================");
        
        // 1. Dữ liệu Gia tốc (m/s^2)
        Serial.println(">>> GIA TỐC (ACCELEROMETER) <<<");
        Serial.printf("  X: %6.2f m/s^2 | Y: %6.2f m/s^2 | Z: %6.2f m/s^2\n", 
                      ax, ay, az);

        // 2. Dữ liệu Vận tốc góc (rad/s)
        Serial.println(">>> CON QUAY HỒI CHUYỂN (GYROSCOPE) <<<");
        Serial.printf("  X: %6.2f rad/s | Y: %6.2f rad/s | Z: %6.2f rad/s\n", 
                      gx, gy, gz);

        // 3. Góc nghiêng (Tilt Angle)
        Serial.println(">>> GÓC NGHIÊNG (TILT ANGLE) <<<");
        Serial.printf("  Roll (Lắc ngang)  : %6.2f° | Pitch (Chúc/Ngóc) : %6.2f°\n", 
                      roll, pitch);

        // 4. Dữ liệu Từ trường (uT) & La bàn (Heading)
        Serial.println(">>> LA BÀN TỪ TRƯỜNG (MAGNETOMETER) <<<");
        Serial.printf("  X: %6.2f uT    | Y: %6.2f uT    | Z: %6.2f uT    | Heading: %6.2f°\n", 
                      mx, my, mz, heading);
        
        Serial.println("==================================================\n");
    }
}
